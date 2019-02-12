//
// Sample.cpp : Defines the entry point for the console application.
//
#include <windows.h>
#include "atc3dg.h"		// ATC3DG API
#include "sample.h"		// class declarations
#include <string.h>		// string handling

//using namespace std;

CSystem			ATC3DG;
CSensor			*pSensor=NULL;
CXmtr			*pXmtr=NULL;
int				errorCode;

int				sensorID;
short			id;
int				records = 100;	
char			output[256];
int				numberBytes;

int InitEMT()
{
	int i;

	errorCode = InitializeBIRDSystem();
	if(errorCode!=BIRD_ERROR_SUCCESS) return errorCode;


	// GET SYSTEM CONFIGURATION

	errorCode = GetBIRDSystemConfiguration(&ATC3DG.m_config);
	if(errorCode!=BIRD_ERROR_SUCCESS) return errorCode;;


	// GET SENSOR CONFIGURATION

	pSensor = new CSensor[ATC3DG.m_config.numberSensors];
	for(i=0;i<ATC3DG.m_config.numberSensors;i++)
	{
		errorCode = GetSensorConfiguration(i, &(pSensor+i)->m_config);
		if(errorCode!=BIRD_ERROR_SUCCESS) return errorCode;
	}


	//
	// GET TRANSMITTER CONFIGURATION
	//
	pXmtr = new CXmtr[ATC3DG.m_config.numberTransmitters];
	for(i=0;i<ATC3DG.m_config.numberTransmitters;i++)
	{
		errorCode = GetTransmitterConfiguration(i, &(pXmtr+i)->m_config);
		if(errorCode!=BIRD_ERROR_SUCCESS) return errorCode;
	}

	// Initialize the ATC3DG driver and DLL	
	//
	// Search for the first attached transmitter and turn it on
	//
	for(id=0;id<ATC3DG.m_config.numberTransmitters;id++)
	{
		if((pXmtr+id)->m_config.attached)
		{
			errorCode = SetSystemParameter(SELECT_TRANSMITTER, &id, sizeof(id));
			if(errorCode!=BIRD_ERROR_SUCCESS) return errorCode;
			break;
		}
	}

	return 0;
}

int SampleEMT(double *pdata)
{

	int				i;
	//


	//
	// Collect data from all birds
	// Loop through all sensors and get a data record if the sensor is attached.
	//
	DOUBLE_POSITION_ANGLES_RECORD record, *pRecord = &record;

	// collect as many records as specified in the command line
	//for(i=0;i<records;i++)

	// scan the sensors and request a record
	for(sensorID=0;sensorID<ATC3DG.m_config.numberSensors;sensorID++)
	{
		// sensor attached so get record
		errorCode = GetAsynchronousRecord(sensorID, pRecord, sizeof(record));
		if(errorCode!=BIRD_ERROR_SUCCESS) {return errorCode;}

		// get the status of the last data record
		// only report the data if everything is okay
		unsigned int status = GetSensorStatus( sensorID);

		if( status == VALID_STATUS)
		{
			// send output to console
			pdata[sensorID*6+0]=record.x;
			pdata[sensorID*6+1]=record.y;
			pdata[sensorID*6+2]=record.z;
			pdata[sensorID*6+3]=record.a;
			pdata[sensorID*6+4]=record.e;
			pdata[sensorID*6+5]=record.r;
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//
	//  Free memory allocations before exiting
	//
	return 0;
}


void CloseEMT()
{
	// Turn off the transmitter before exiting
	// We turn off the transmitter by "selecting" a transmitter with an id of "-1"
	//
	id = -1;
	errorCode = SetSystemParameter(SELECT_TRANSMITTER, &id, sizeof(id));
	
	if (pSensor)
		delete []pSensor;
	if(pXmtr)
		delete []pXmtr;
}