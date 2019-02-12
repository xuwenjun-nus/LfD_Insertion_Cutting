#ifndef storeThread_H
#define storeThread_H

#include<windows.h>  /// for HANDLE
#include <Qthread>
#include <QTimer>

class StoreThread: public QThread  
{  
	Q_OBJECT
private:
	HANDLE myhandle;
	QTimer *myDrawTimer;
public:  
	StoreThread() ;
	~StoreThread() ;
public slots:
	void draw();
};  

#endif 

