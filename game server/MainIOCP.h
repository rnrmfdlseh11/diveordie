#pragma once
#pragma once

#include "IOCP.h"
#include "DBConnector.h"


#define DB_ADDRESS      "localhost"
#define DB_PORT         3306
#define DB_ID           "root"
#define DB_PW           "qwer123$"
#define DB_SCHEMA       ""

enum EPacketType
{
    SIGNUP,
    LOGIN
};

class MainIOCP : public IOCP
{
public:
    MainIOCP();
    ~MainIOCP();

    virtual bool CreateWorkerThread();
    virtual void WorkerThread();

    virtual void ServerStart() override;

    static void Send(SOCKETINFO* pSocket);

private:
    static map<int, SOCKET> SessionSocket;
    static float            HitPoint;
    static DBConnector      Conn;

    FuncProcess             fnProcess[100];

    // ȸ������
    static void SignUp(stringstream& RecvStream, SOCKETINFO* pSocket);
    // DB�� �α���
    static void Login(stringstream& RecvStream, SOCKETINFO* pSocket);


};