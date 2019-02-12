#include "Test.h"
#include "HighResolutionTimer.h" 
#include<windows.h> 
#include <iostream> 
#include <fstream>

#include <string> 
#include <cstring>
#include <sstream>

#include <math.h> 


////////////////////////////////////// global variables area//////////////////////////////////////////////////
extern   double  smoothslavePositionX,  smoothslavePositionY, smoothslavePositionZ;
extern   double   previousSlavePositionX,  previousSlavePositionY, previousSlavePositionZ;
extern   double   difference[3];   
extern   double  OZrotate,			OYrotate;
extern   double  previousOZrotate,			previousOYrotate;
extern  int BUTTON0,BUTTON1,BUTTON2;
extern	 double  test1 ,	test2 ,	test3,		test4,test5,test6;
int N=21;
double dd=5.5, H0=0.8, r=25;
const double ScaleX=10; // linear map the master workspace to robot workspace
const double ScaleY=10;
const double ScaleZ=10;
const int off_A=1500; 
const int off_B=1500;
const int step_base=0;
const double pi=3.14159;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
Test::Test()
{
	//struct PortSettings myComSettingCom1 = {BAUD57600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
	//Com1 = new Win_QextSerialPort("com4",myComSettingCom1,QextSerialBase::EventDriven);
	//bool open=Com1 ->open(QIODevice::WriteOnly);
	struct PortSettings myComSettingCom1 = {BAUD57600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
	Com1 = new Win_QextSerialPort("com5",myComSettingCom1,QextSerialBase::EventDriven);
	Com1 ->open(QIODevice::WriteOnly);
	sendTimer=new QTimer();

	connect(sendTimer,SIGNAL(timeout()),this,SLOT(sendMyCom()));
 	sendTimer->start(20);
	sleep(10);
	//Com1->write("BP0200"); //reset
	//Com1->write("BP0100"); 

}

void Test::sendMyCom()// send command to the motor set
{
	
	angle = smoothslavePositionY/(N-1)/180*pi;
	zb=(smoothslavePositionX+100)*45;
	l1= (N-1)*(dd*sin(angle/2)-2*H0*sin(angle/4)*sin(angle/4));
	l2=-(N-1)*(dd*sin(angle/2)+2*H0*sin(angle/4)*sin(angle/4));
	double dalpha1=l1*180/(pi*r);
	double dalpha2=l2*180/(pi*r);
	double dalphax=(abs(dalpha1)+abs(dalpha2))/2*l1/(abs(l1)); // servo rotation angle 
	//double dalphay=(abs(dalpha2)+abs(dalpha2))/2*l1/(abs(l1)); // servo rotation angle 
	int OCR4A=off_A+dalpha1*1000/(100);
	//double OCR4B=off_B+dalphay*1000/(100);
	//sprintf(ComPos1, "1LA%d\n3LA%d\n2LA%d\n6LA%d\n5LA%d\nM\n",Position1,Position3,Position2,Position6,Position5);	
	sprintf(commandS, "RP%04d", OCR4A);

	sprintf(command1, "BP%04d", zb);
	if(BUTTON0==1){ //move back forward only if main button is pressed 
		Com1->write(command1);}

 if(BUTTON1==1){
	Com1->write(commandS);}
}