#include "HapticControl.h"  
#include "dhdc.h"
#include "HighResolutionTimer.h" 
#include <ShellAPI.h>
#include <iostream>  
#include <sstream>  
#include <fstream>  
#include <string> 
////////////////////////////////////// global variables area//////////////////////////////////////////////////
extern   double  smoothslavePositionX,	smoothslavePositionY,		smoothslavePositionZ;
double  OZrotate,	OYrotate;
int BUTTON0; int BUTTON1; int BUTTON2;
extern	 double  test1 ,			test2 ,				test3,		test4,test5,test6;
double	 positionEx=0,              positionEy=0,       positionEz=0;
double   previousSlavePositionX=0,  previousSlavePositionY=0, previousSlavePositionZ=0;
double  previousOZrotate,			previousOYrotate;
double difference[3];
extern   bool enableSig;
extern   Timer    *systemTime;
bool readReady=0;
int  currentPoint=0;
QByteArray dataBuffer;
double minTorque=100;
double maxTorque=0;
const double pi=3.14159;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

HapticControl::HapticControl() 
{ //bool ini=true;
	//dhdEnableExpertMode ();	
	/// initial hap tic device
//	MessageBox("hello");

	 dhdOpen ();
	/* if (dhdOpen () < 0) {
		 ini=!ini;
    //printf ("error: cannot open device (%s)\n", dhdErrorGetLastStr());
    dhdSleep (2.0);
  
  }*/
	/* if(dhdGetSystemType() == DHD_DEVICE_FALCON){
		 
		 dhdSleep (2.0);
	 }*/

	 //printf ("%s device detected\n\n", dhdGetSystemName());

		// required to change asynchronous operation mode
	//dhdEnableExpertMode ();
	dhdEmulateButton (DHD_ON);	// emulate button on supported devices
	dhdEnableForce (DHD_ON);	// enable force	
	dhdSetGravityCompensation(DHD_ON);
	//dhdSetForceAndGripperForce(0,0,0,0); 
	dhdConfigLinearVelocity (16,DHD_VELOCITY_WINDOWING);

	positionReadTimer=new QTimer();
	connect(positionReadTimer,SIGNAL(timeout()),this,SLOT(positionReadLoop()));
 	positionReadTimer->start(20); 

	//sendT2FalconTimer=new QTimer();
	//connect(sendT2FalconTimer,SIGNAL(timeout()),this,SLOT(sendT2FalconLoop()));
 	//sendT2FalconTimer->start(5); 

	//readFromFalconTimer=new QTimer();
	//connect(readFromFalconTimer,SIGNAL(timeout()),this,SLOT(readFromFalconLoop()));
 	//readFromFalconTimer->start(10); 

	//GripperCom = new CommUtils();
	//GripperCom->OpenCom(0);///but it is 5 here

	homePositionX=0;homePositionY=0;homePositionZ=0;
	 myfile.open ("falcon.txt");//open file


	/*struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
	myCom = new Win_QextSerialPort("com4",myComSetting,QextSerialBase::EventDriven);
	myCom ->open(QIODevice::ReadWrite);
	connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));*/
	beginTime=systemTime->getElapsedTimeInSec();
	BUTTON0=0;BUTTON1=0;BUTTON2=0;
	previousSlavePositionX=0;
	previousSlavePositionY=0;
	previousSlavePositionZ=0;
	difference[0]=0; difference[1]=0; difference[2]=0; 
	sleep(5);
}  

void HapticControl::positionReadLoop()
{
	currentTime=(systemTime->getElapsedTimeInSec()-beginTime);
	//this is to get the position from NovintFalcon
	double µ=0.4;
	
	//if (enableSig==1)
	//{
		/*if (dhdGetButtonMask()) 
		{BUTTON = 1;}
		else
		{BUTTON = 0;}*/
	// this is to get the buttoa=n status of the falcon: 0: main buttonh to contorl the  section;2: front button to control the base stepper; 1: left button to control the distal section
	if(dhdGetButton(0)) 
	{BUTTON0=1;}
	else
	{BUTTON0=0;}
	if(dhdGetButton(1)) 
	{BUTTON1=1;}
	else
	{{BUTTON1=0;}}
	if(dhdGetButton(2)) 
	{BUTTON2=1;}
	else
	{BUTTON2=0;}
		double temp1=0,temp2=0,temp3=0;
		dhdGetPosition(&temp1,&temp2,&temp3);
		if( abs(temp1)>0.035)
			temp1=0.035*temp1/abs(temp1);
				if( abs(temp2)>0.05)
					temp2=0.05*temp2/abs(temp2);
						if( abs(temp3)>0.05)
							temp3=0.05*temp3/abs(temp3);					
		double slavePositionX=100*temp1/0.035-homePositionX;
		double slavePositionY=100*temp2/0.05-homePositionY;
		double slavePositionZ=100*temp3/0.05-homePositionZ;
		
		if (abs(slavePositionX)>100 ) 
			{
				slavePositionX=100.0*slavePositionX/abs (slavePositionX);
			}
				if (abs(slavePositionY)>100 ) 
				{
					slavePositionY=100.0*slavePositionY/abs (slavePositionY);
				}
					if (abs(slavePositionZ)>100 ) 
					{
						slavePositionZ=100.0*slavePositionZ/abs (slavePositionZ);
					}
			
			//implement LPF
			smoothslavePositionX = µ * slavePositionX + (1-µ) * previousSlavePositionX; //controlling base motor
			 smoothslavePositionY = µ * slavePositionY + (1-µ) * previousSlavePositionY;
			 smoothslavePositionZ = µ * slavePositionZ + (1-µ) * previousSlavePositionZ;

			// alternatively, implement moving average filter

			OYrotate=atan2(smoothslavePositionZ,smoothslavePositionX); //controlling up down benidng
			OZrotate=atan2(smoothslavePositionY,smoothslavePositionX); // controlling left right bending 
			difference[0]=smoothslavePositionX-previousSlavePositionX;
			difference[1]=smoothslavePositionY-previousSlavePositionY;
			difference[2]=smoothslavePositionZ-previousSlavePositionZ;
			test1=smoothslavePositionY; //control angle
			test2=smoothslavePositionX;// control z
			test4=difference[0];
			test5=difference[1]; // difference of y position to control bending up/down 
			test6=difference[2];
			previousSlavePositionX=smoothslavePositionX;//updating position
			previousSlavePositionY=smoothslavePositionY;
			previousSlavePositionZ=smoothslavePositionZ;
				
	

	////////////////////////////////////////////////////
	// write to file
	//////////////////////////////////////////////////////
	
 if (myfile.is_open())
  {
    //myfile << "This is a line.\n";
	  if(BUTTON0==1){
		  myfile <<0<<" "<<test1<<" "<<test2<<" "<<currentTime<< "\n";} // read test2
	  if(BUTTON1==1){
		  myfile <<1<<" "<<test1<<" "<<test2<<" "<<currentTime<< "\n";} //read test1
    if(currentTime>100000)
	{myfile.close();}
  }
  else cout << "Unable to open file";
  //sleep (10);
}

