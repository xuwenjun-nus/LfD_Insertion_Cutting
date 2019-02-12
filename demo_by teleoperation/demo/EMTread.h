#ifndef EMTread_H
#define EMTread_H
#include<windows.h> 
#include <Qthread>
#include <fstream> 
#include "Sample.h"
#include "HighResolutionTimer.h"
#include <QTimer>

using namespace std;

class EMTread: public QThread  
{  
    Q_OBJECT  
private:
	QTimer *ReadTimer;
	//QTimer *sendT2FalconTimer;
	//QTimer *readFromFalconTimer;
	//CommUtils* GripperCom;
	double beginTime;
	double currentTime;
	ofstream myfile;

public:  
    EMTread();  
    //void run(); 
public slots:
	void ReadLoop();
	//void sendT2FalconLoop();
	//void readFromFalconLoop();
	//void readMyCom();
}; 
#endif 