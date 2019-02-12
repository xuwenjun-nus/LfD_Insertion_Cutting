#ifndef HapticControl_H
#define HapticControl_H
#include<windows.h> 
#include <Qthread>
#include <fstream> 
#include "HighResolutionTimer.h"
#include <QTimer>
#include <win_qextserialport.h>
using namespace std; 
class HapticControl: public QThread  
{  
    Q_OBJECT  
private:
	QTimer *positionReadTimer;
	//QTimer *sendT2FalconTimer;
	//QTimer *readFromFalconTimer;
	//CommUtils* GripperCom;
	double homePositionX,homePositionY,homePositionZ;
	double beginTime;
	double currentTime;
	ofstream myfile;

public:  
    HapticControl();  
    //void run(); 
public slots:
	void positionReadLoop();

}; 
#endif 