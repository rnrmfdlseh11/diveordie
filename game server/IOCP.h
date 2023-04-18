#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <map>
#include "Core.h"

#define MAX_BUFFER 4096
#define SERVER_PORT 25565
#define MAX_CLIENTS 100

struct SOCKETINFO
{
    WSAOVERLAPPED   overlapped;
    WSABUF          dataBuf;
    SOCKET          socket;
    char            messageBuffer[MAX_BUFFER];
    int             recvBytes;
    int             sendBytes;
};

struct FuncProcess
{
    void(*funcProcessPacket)(stringstream& RecvStream, SOCKETINFO* pSocket);
    FuncProcess()
    {
        funcProcessPacket = nullptr;
    }
};

class IOCP
{
public:
    IOCP();
    virtual ~IOCP();

    // ���� ��� �� ���� ����
    bool Initialize();

    // ���� ����
    virtual void ServerStart();
    
    virtual bool CreateWorkerThread();

    virtual void WorkerThread();


    // Ŭ���̾�Ʈ �۽�
    virtual void Send(SOCKETINFO* pSocket);

    // Ŭ���̾�Ʈ ���� ���
    virtual void Recv(SOCKETINFO* pSocket);

protected:
    SOCKETINFO* SocketInfo;
    SOCKET      ListenSocket;
    HANDLE      hIOCP;
    bool        bWorkerThread;
    bool        bWorkerThread = true;
    HANDLE* hWorkerHandle;
    int         iThreadCnt;
};

