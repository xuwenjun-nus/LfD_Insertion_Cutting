#include "demo.h"
#include <QtGui/QApplication>
#include "HapticControl.h"	
#include "StoreThread.h"
#include "HighResolutionTimer.h"
#include "MotorControl.h"
#include "EMTread.h"
#include <Qthread>
///////////////////////////////////////////////////

double   smoothslavePositionX=0.0,		smoothslavePositionY=0.0,		smoothslavePositionZ=0.0;
double   masterPositionX=0.0,		masterPositionY=0.0,	masterPositionZ=0.0,gripperPosition;

int      gripperTorque=0;
Timer    *systemTime;
double	 test1=0,					test2=0,				test3=0, test4=0,test5,test6;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	demo w;
	w.show();
	/// start system timer	
	
	systemTime=new Timer();
	systemTime->start();
	//initial hap tic device
	//HapticControl *mth= new HapticControl(); 
	//mth->start(QThread::NormalPriority);
	//MotorControl *mc=new MotorControl();
	//mc->start(QThread::NormalPriority);
	EMTread *me=new EMTread();
	me->start(QThread::NormalPriority);
	//initial communication
	//MasterSlaveComuniThread *myMasterSlaveComuniThread=new MasterSlaveComuniThread();
	//myMasterSlaveComuniThread->start(QThread::TimeCriticalPriority);
	//initial storing data thread
	StoreThread *mystoreThread= new StoreThread();
	mystoreThread->start(QThread::NormalPriority); 

	//delete mystoreThread;
	return a.exec();
}
