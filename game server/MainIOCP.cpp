#include "MainIOCP.h"
#include <sstream>
#include <algorithm>
#include <process.h>

map<int, SOCKET>    MainIOCP::SessionSocket;
DBConnector         MainIOCP::Conn;

unsigned int WINAPI CallWorkerThread(LPVOID p)
{
    MainIOCP* pOverlappedEvent = (MainIOCP*)p;
    pOverlappedEvent->WorkerThread();
    return 0;
}

MainIOCP::MainIOCP()
{
    if (Conn.Connect(DB_ADDRESS, DB_ID, DB_PW, DB_SCHEMA, DB_PORT))
    {
        cout << "[INFO] DB ���� ����" << endl;
    }
    else
    {
        cout << "[INFO] DB ���� ����" << endl;
    }

    fnProcess[EPacketType::SIGNUP].funcProcessPacket = SignUp;
    fnProcess[EPacketType::LOGIN].funcProcessPacket = Login;

}

MainIOCP::~MainIOCP()
{
    WSACleanup();

    if (SocketInfo)
    {
        delete[] SocketInfo;
        SocketInfo = NULL;
    }

    if (hWorkerHandle)
    {
        delete[] hWorkerHandle;
        hWorkerHandle = NULL;
    }

    Conn.Close();
}

void MainIOCP::ServerStart()
{
    IOCP::ServerStart();
}

void MainIOCP::Send(SOCKETINFO* pSocket)
{
    int iResult;
    DWORD sendBytes;
    DWORD dwFlags = 0;

    iResult = WSASend(
        pSocket->socket,
        &(pSocket->dataBuf),
        1,
        &sendBytes,
        dwFlags,
        NULL,
        NULL
    );

    if (iResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
    {
        cout << "[ERROR] WSASend ���� : " << WSAGetLastError() << endl;
    }
}

void MainIOCP::SignUp(stringstream& RecvStream, SOCKETINFO* pSocket)
{
    string Id;
    string Pw;

    RecvStream >> Id;
    RecvStream >> Pw;

    cout << "[INFO] ȸ������ �õ� {" << Id << "} {" << Pw << "}" << endl;

    stringstream SendStream;
    SendStream << EPacketType::SIGNUP << endl;
    SendStream << Conn.SignUpAccount(Id, Pw) << endl;

    CopyMemory(pSocket->messageBuffer, (CHAR*)SendStream.str().c_str(), SendStream.str().length());
    pSocket->dataBuf.buf = pSocket->messageBuffer;
    pSocket->dataBuf.len = SendStream.str().length();

    Send(pSocket);
}

void MainIOCP::Login(stringstream& RecvStream, SOCKETINFO* pSocket)
{
    string Id;
    string Pw;

    RecvStream >> Id;
    RecvStream >> Pw;

    cout << "[INFO] �α��� �õ� {" << Id << "} {" << Pw << "}" << endl;

    stringstream SendStream;
    SendStream << EPacketType::LOGIN << endl;
    SendStream << Conn.SearchAccount(Id, Pw) << endl;

    CopyMemory(pSocket->messageBuffer, (CHAR*)SendStream.str().c_str(), SendStream.str().length());
    pSocket->dataBuf.buf = pSocket->messageBuffer;
    pSocket->dataBuf.len = SendStream.str().length();

    Send(pSocket);
}

bool MainIOCP::CreateWorkerThread()
{
    unsigned int threadId;
    // �ý��� ���� ������
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    cout << "[INFO] CPU ���� : " << sysInfo.dwNumberOfProcessors << endl;
    // ������ �۾� �������� ������ (CPU * 2) + 1
    iThreadCnt = sysInfo.dwNumberOfProcessors * 2;

    // thread handler ����
    hWorkerHandle = new HANDLE[iThreadCnt];
    // thread ����
    for (int i = 0; i < iThreadCnt; i++)
    {
        hWorkerHandle[i] = (HANDLE*)_beginthreadex(
            NULL, 0, &CallWorkerThread, this, CREATE_SUSPENDED, &threadId
        );
        if (hWorkerHandle[i] == NULL)
        {
            cout << "[ERROR] Worker Thread ���� ����" << endl;
            return false;
        }
        ResumeThread(hWorkerHandle[i]);
    }
    cout << "[INFO] Worker Thread ����...." << endl;
    return true;
}

void MainIOCP::WorkerThread()
{
    // �Լ� ȣ�� ���� ����
    BOOL	bResult;
    int		nResult;
    // Overlapped I/O �۾����� ���۵� ������ ũ��
    DWORD	recvBytes;
    DWORD	sendBytes;
    // Completion Key�� ���� ������ ����
    SOCKETINFO* pCompletionKey;
    // I/O �۾��� ���� ��û�� Overlapped ����ü�� ���� ������	
    SOCKETINFO* pSocketInfo;
    DWORD	dwFlags = 0;


    while (bWorkerThread)
    {
        /**
         * �� �Լ��� ���� ��������� WaitingThread Queue �� �����·� ���� ��
         * �Ϸ�� Overlapped I/O �۾��� �߻��ϸ� IOCP Queue ���� �Ϸ�� �۾��� ������
         * ��ó���� ��
         */
        bResult = GetQueuedCompletionStatus(hIOCP,
            &recvBytes,				// ������ ���۵� ����Ʈ
            (PULONG_PTR)&pCompletionKey,	// completion key
            (LPOVERLAPPED*)&pSocketInfo,			// overlapped I/O ��ü
            INFINITE				// ����� �ð�
        );

        if (!bResult && recvBytes == 0)
        {
            cout << "[INFO] socket(" << pSocketInfo->socket << ") ���� ����" << endl;
            closesocket(pSocketInfo->socket);
            free(pSocketInfo);
            continue;
        }

        pSocketInfo->dataBuf.len = recvBytes;

        if (recvBytes == 0)
        {
            closesocket(pSocketInfo->socket);
            free(pSocketInfo);
            continue;
        }

        try
        {
            // ��Ŷ ����
            int PacketType;
            // Ŭ���̾�Ʈ ���� ������ȭ
            stringstream RecvStream;

            RecvStream << pSocketInfo->dataBuf.buf;
            RecvStream >> PacketType;

            // ��Ŷ ó��
            if (fnProcess[PacketType].funcProcessPacket != nullptr)
            {
                fnProcess[PacketType].funcProcessPacket(RecvStream, pSocketInfo);
            }
            else
            {
                cout << "[ERROR] ���� ���� ���� ��Ŷ : " << PacketType << endl;
            }
        }
        catch (const std::exception& e)
        {
            cout << "[ERROR] �� �� ���� ���� �߻� : " << e.what() << endl;
        }

        // Ŭ���̾�Ʈ ���
        Recv(pSocketInfo);
    }
}