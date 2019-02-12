#ifndef _CommUtils_H__
#define _CommUtils_H__
#include <Windows.h>
class CommUtils  
{
public:
    bool ReadCom(char * ReceiveData, DWORD& ReceiveLength);
    void CloseCom();
    bool WriteCom(char * sendchar,int sendsize);
    bool OpenCom(char *portname);
	int ReadData(char *buffer, unsigned int nbChar);

    CommUtils();
    virtual ~CommUtils();
    int m_Port;
    char szCurPath[256];

private:
    OVERLAPPED ReadovReady, WriteovReady;
    HANDLE hComm;
    bool bOpenCom;
	COMSTAT status;
        //Keep track of last error
    DWORD errors;

};

#endif
