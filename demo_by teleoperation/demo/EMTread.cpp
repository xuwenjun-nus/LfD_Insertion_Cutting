#include "EMTread.h"
#include "HighResolutionTimer.h" 
#include<windows.h> 
#include <iostream> 
#include <fstream>

#include <string> 
#include <cstring>
#include <sstream>

#include <math.h> 
#include <array>

////////////////////////////////////// global variables area//////////////////////////////////////////////////
extern double  test1 ,			test2 ,				test3,		test4,test5,test6;
extern   Timer    *systemTime;
double EMTP[24];
extern   bool enableSig;
extern  int BUTTON0;
extern int BUTTON1;
////////////////////////////////////////////////////////////////////////////////////////////////


 EMTread::EMTread() 
{
	 InitEMT();// initilization

	 myfile.open ("EMT.txt");
	ReadTimer=new QTimer();
	connect(ReadTimer,SIGNAL(timeout()),this,SLOT(ReadLoop()));

 	ReadTimer->start(20); 
	beginTime=systemTime->getElapsedTimeInSec();
}


 void EMTread:: ReadLoop()
 {
	currentTime=(systemTime->getElapsedTimeInSec()-beginTime);
	SampleEMT(EMTP);
	 
	 int i= sizeof(EMTP);
	 test4=EMTP[0];
	 test5=EMTP[1];
	 test6=EMTP[2];
	 
	 if (myfile.is_open())
  {
    //myfile << "This is a line.\n";
	myfile << "Sensor1\n";
	myfile <<EMTP[0]<<" "<<EMTP[1]<<" "<<EMTP[2]<<" "<<EMTP[3]<<" "<<EMTP[4]<<" "<<EMTP[5]<<" "<<currentTime<<"\n";
	myfile << "Sensor2\n";
	myfile <<EMTP[6]<<" "<<EMTP[7]<<" "<<EMTP[8]<<" "<<EMTP[9]<<" "<<EMTP[10]<<" "<<EMTP[11]<<" "<<currentTime<<"\n";
	//myfile << "Sensor3\n";
	//myfile <<EMTP[12]<<" "<<EMTP[13]<<" "<<EMTP[14]<<" "<<EMTP[15]<<" "<<EMTP[16]<<" "<<EMTP[17]<<"\n";
	//myfile << "Sensor4\n";
	//myfile <<EMTP[18]<<" "<<EMTP[19]<<" "<<EMTP[20]<<" "<<EMTP[21]<<" "<<EMTP[22]<<" "<<EMTP[23]<<"\n";
    if(currentTime>10000)
	{myfile.close();}
  }
  else cout << "Unable to open file";



 }