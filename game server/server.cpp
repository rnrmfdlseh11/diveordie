#pragma once

#include "MainIOCP.h"

int main()
{
    MainIOCP iocp_server;

    if (iocp_server.Initialize())
    {
        iocp_server.ServerStart();
    }
    return 0;
}
