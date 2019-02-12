#ifndef Test_H
#define Test_H
#include<windows.h>  /// for HANDLE
#include <Qthread>
#include <QTimer>
#include <fstream> 
#include "HighResolutionTimer.h"

#include <win_qextserialport.h>
#include <SerialPort.h>
#include <QTimer>

using namespace std;

class Test: public QThread  
{  
	Q_OBJECT
	
private:
	Win_QextSerialPort *Com1;//serialport for arduino send command
	
	double beginTime;
	double currentTime;
	//ofstream myfile;
	QTimer *sendTimer;
	double angle;
	double l1,l2;
	int zb;
	char commandS[10];
	char command1[6];
public:  
	Test();
	//void run();
	
public slots:
  void sendMyCom();
  //void lookUp(); // determine the control input according to the lookup table 

};  

#endif 

