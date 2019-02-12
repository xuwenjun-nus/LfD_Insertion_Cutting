//#include "stdafx.h"
#include "SerialPort.h"
#include "stdio.h"
const int READ_TIMEOUT = 500;

CommUtils::CommUtils()
{
    bOpenCom = false;
}

CommUtils::~CommUtils()
{
    this->CloseCom();
}

bool CommUtils::OpenCom(char* portname)
{
    if (bOpenCom)
    {
        this->CloseCom();
        bOpenCom = false;
    }
    //char szport[10];
	int nIndex = MultiByteToWideChar(CP_ACP, 0, portname , -1, NULL, 0); 
	TCHAR *portname1 = new TCHAR[nIndex + 1]; 
	MultiByteToWideChar(CP_ACP, 0, portname , -1, portname1, nIndex); 
    //sprintf(szport,"COM%d",Port);
    hComm = CreateFile( portname1,
                        GENERIC_READ|GENERIC_WRITE,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        FILE_FLAG_OVERLAPPED, //FILE_ATTRIBUTE_NORMAL|
                        NULL);
    
    
    if (hComm == INVALID_HANDLE_VALUE)        return false;
    if (!SetupComm(hComm, 1024, 512))        return false;
    
    COMMTIMEOUTS commtimeouts;
    commtimeouts.ReadIntervalTimeout = MAXDWORD;
    commtimeouts.ReadTotalTimeoutConstant =0;
    commtimeouts.ReadTotalTimeoutMultiplier =0;
    commtimeouts.WriteTotalTimeoutConstant =0;
    commtimeouts.WriteTotalTimeoutMultiplier=0;
    
    if (!SetCommTimeouts(hComm, &commtimeouts))        return false;

    memset(&ReadovReady,0,sizeof(OVERLAPPED));
    memset(&WriteovReady,0,sizeof(OVERLAPPED));
    ReadovReady.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
    WriteovReady.hEvent =CreateEvent(NULL,TRUE,FALSE,NULL);
    
    SECURITY_ATTRIBUTES sa;
    sa.nLength=sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor=NULL;
    sa.bInheritHandle=TRUE;
    
    DCB dcb;
    GetCommState(hComm, &dcb);
    dcb.fBinary = TRUE;
    dcb.fParity = TRUE;
    dcb.BaudRate = CBR_57600;        // 波特率 57600
    dcb.ByteSize = 8;                // 8 位数据位
    dcb.Parity = NOPARITY;            // 无奇偶校验
    dcb.StopBits = ONESTOPBIT;        // 1 个停止位
    
    if (!SetCommState(hComm, &dcb ))        return false;

    bOpenCom = true;
    return bOpenCom;
}

bool CommUtils::WriteCom(char *sendchar, int sendsize)
{
    if (!bOpenCom)    return false;
    
    DWORD    BytesSent;
    DWORD    resD;        
    
    PurgeComm(hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
    
    BytesSent=0;
    BOOL hr = WriteFile(hComm,                            // Handle to COMM Port
                        sendchar,                        // Pointer to message buffer in calling finction
                        sendsize,                        // Length of message to send
                        &BytesSent,                        // Where to store the number of bytes sent
                        &WriteovReady);                    // Overlapped structure
    if(!hr)
    {
        if(GetLastError() != ERROR_IO_PENDING)
        {
            return false;
        }
        else
        {
            resD=WaitForSingleObject(WriteovReady.hEvent,INFINITE);
        }
        switch(resD)
        {
            case WAIT_OBJECT_0:
            {
                if(!GetOverlappedResult(hComm,&WriteovReady,&BytesSent,false))
                    return false;
                else
                    return true;
                
            }
            default:
                return false;
                break;
        }
    }
    return true;
}

void CommUtils::CloseCom()
{
    if (!bOpenCom)    return;

    CloseHandle(hComm);
    hComm=NULL;
    
    CloseHandle(ReadovReady.hEvent);
    CloseHandle(WriteovReady.hEvent );
    ReadovReady.hEvent =NULL;
    WriteovReady.hEvent =NULL;
}

bool CommUtils::ReadCom(char * ReceiveData, DWORD& ReceiveLength)
{
    if (!bOpenCom)    return false;
    if (ReadovReady.hEvent == NULL)    return false;
    
    ReceiveLength = 0;
    if (ReadFile(hComm, ReceiveData, 1, &ReceiveLength, &ReadovReady) == FALSE) 
    {
        if (GetLastError() != ERROR_IO_PENDING)    return false;
    }

    if(ReceiveLength == 0)    return false;
    ReceiveData[ReceiveLength] = 0;

    DWORD dwRead;
    DWORD dwRes = WaitForSingleObject(ReadovReady.hEvent, READ_TIMEOUT);
    switch(dwRes)
    {
        case WAIT_OBJECT_0:
            if (!GetOverlappedResult(hComm, &ReadovReady, &dwRead, FALSE))    return false;
            break;

        case WAIT_TIMEOUT:
            break;                
            
        default:
            break;
    }
    return true;

}
int CommUtils::ReadData(char *buffer, unsigned int nbChar)
{
    //Number of bytes we'll have read
    DWORD bytesRead;
    //Number of bytes we'll really ask to read
    unsigned int toRead;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(this->hComm, &this->errors, &this->status);

    //Check if there is something to read
    if(this->status.cbInQue>0)
    {
        //If there is we check if there is enough data to read the required number
        //of characters, if not we'll read only the available characters to prevent
        //locking of the application.
        if(this->status.cbInQue>nbChar)
        {
            toRead = nbChar;
        }
        else
        {
            toRead = this->status.cbInQue;
        }

        //Try to read the require number of chars, and return the number of read bytes on success
        if(ReadFile(this->hComm, buffer, toRead, &bytesRead, NULL) && bytesRead != 0)
        {
            return bytesRead;
        }

    }
}