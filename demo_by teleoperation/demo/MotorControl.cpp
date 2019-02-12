#include "MotorControl.h"
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
extern   Timer    *systemTime;
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
/////////////////////////////////////////control ptotocol////////////////////////////////////////////////////
//1st sectioncase 'w':  {Serial.println("Up Stepper Forward!"); break;} -> cable1
//      case 's':  {Serial.println("Down Stepper Backward!"); break;}->cable2
//      case 'a':  {Serial.println("Left Stepper Forward!"); break;}->cable3
//      case 'd':  {Serial.println("Right Stepper Backward!"); break;}-> cable4
      
//2nd section   case 't':  {Serial.println("1st Section Up Stepper Forward!"); break;}-> cable5
//      case 'g':  {Serial.println("1st Section Down Stepper Backward!"); break;}->cable6
//      case 'f':  {Serial.println("1st Section Left Stepper Forward!"); break;}->cable7
//      case 'h':  {Serial.println("1st Section Right Stepper Backward!"); break;}->cable8
      
//      case 'i':  {Serial.println("Base Stepper Forward!"); break;}
//      case 'k':  {Serial.println("Base Stepper Backward!"); break;}     
//      case 'j':  {Serial.println("Constraint Stepper Forward!"); break;}
//      case 'l':  {Serial.println("Constraint Stepper Backward!"); break;}
      
/////////////////////////////////////////////////////////////////////////////////
MotorControl::MotorControl()
{
	//struct PortSettings myComSettingCom1 = {BAUD57600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
	//Com1 = new Win_QextSerialPort("com4",myComSettingCom1,QextSerialBase::EventDriven);
	//bool open=Com1 ->open(QIODevice::WriteOnly);
	struct PortSettings myComSettingCom1 = {BAUD57600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
	Com1 = new Win_QextSerialPort("com5",myComSettingCom1,QextSerialBase::EventDriven);
	Com1 ->open(QIODevice::WriteOnly);
	sendTimer=new QTimer();
	motorfile.open ("motor.txt");//open file
	connect(sendTimer,SIGNAL(timeout()),this,SLOT(sendMyCom()));
 	sendTimer->start(20);
	beginTime=systemTime->getElapsedTimeInSec();
	sleep(10);
	//Com1->write("BP0200"); //reset
	//Com1->write("BP0100"); 

}

void MotorControl::sendMyCom()// send command to the motor set
{
	currentTime=(systemTime->getElapsedTimeInSec()-beginTime);
	angle = smoothslavePositionY*1.2/(N-1)/180*pi;
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

  if (motorfile.is_open())
  {
    //myfile << "This is a line.\n";
	  if(BUTTON0==1){
		  motorfile <<0<<" "<<zb<<" "<<OCR4A<<" "<<currentTime<< "\n";} // read test2
	  if(BUTTON1==1){
		  motorfile <<1<<" "<<zb<<" "<<OCR4A<<" "<<currentTime<< "\n";} //read test1
    if(currentTime>100000)
	{motorfile.close();}
  }
  else cout << "Unable to open file";
// }//move left right only if 1 button is pressed
	//look up the position in the lookup table 
	/*double Px=slavePositionX*ScaleX;
	double Py=slavePositionY*ScaleY;
	double Pz=slavePositionZ*ScaleZ;*/

	//a test program
	/*Com1->write("w"); //1st section
	sleep(3000);
	Com1->write("s");
	sleep(3000);
	/*Com1->write("a");
	sleep(3000);
	Com1->write("d");
	sleep(3000);
	Com1->write("t");// 2nd section
	sleep(3000);
	Com1->write("g");
	sleep(3000);
	Com1->write("f");
	sleep(3000);
	Com1->write("h");
	sleep(3000);
	Com1->write("i");// forward backward
	sleep(3000);
	Com1->write("k");
	sleep(3000);*/


	// joint space mapping scheme 1
	//x: forward/backward; y: left/right; z: upward/down
	
}

/*void MotorControl::lookUp()
{
	//determine l1-l8 and z

}*/