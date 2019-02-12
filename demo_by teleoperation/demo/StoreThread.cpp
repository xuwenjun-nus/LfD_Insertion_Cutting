#include "StoreThread.h"
#include "dhdc.h"

////////////////////////////////////// global variables area//////////////////////////////////////////////////

extern double	test1 ,	test2 ,	test3,test4,test5,test6;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
StoreThread::StoreThread()  
{  
	myhandle=CreateFileMappingA(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,7*sizeof(double),"MyInfo");
	myDrawTimer=new QTimer();

	connect(myDrawTimer,SIGNAL(timeout()),this,SLOT(draw()));
 	myDrawTimer->start(20); 
} 	

void StoreThread::draw()
{
	double *p=NULL;
	p=(double *)MapViewOfFile(myhandle,FILE_MAP_WRITE,0,0,sizeof(int));
	p[0]=test1;
	p[1]=test2;
	p[2]=test3;
	p[3]=test4;
	p[4]=test5;
	p[5]=test6;
	
	//UnmapViewOfFile(p);
}
	
StoreThread::~StoreThread()
{
	double aa=1;
}