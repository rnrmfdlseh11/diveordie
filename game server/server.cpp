#include <iostream>
#include <WS2tcpip.h>
using namespace std;
#pragma comment (lib, "WS2_32.LIB")

const short SERVER_PORT = 5003;
const int BUFSIZE = 256;

void err_disp(const char* msg, int err_no)
{
    WCHAR* h_mess;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, err_no,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&h_mess, 0, NULL);
    cout << msg;
    wcout << L"  ¿¡·¯ => " << h_mess << endl;
    while (true);
    LocalFree(h_mess);
}

int main()
{
    wcout.imbue(std::locale("korean"));
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 0), &WSAData);
    SOCKET s_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);
    SOCKADDR_IN server_addr;
    ZeroMemory(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(s_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
    listen(s_socket, SOMAXCONN);

    INT addr_size = sizeof(server_addr);
    SOCKET c_socket = WSAAccept(s_socket, reinterpret_cast<sockaddr*>(&server_addr), &addr_size, 0, 0);
    for (;;) {
        char recv_buf[BUFSIZE];
        WSABUF mybuf;
        mybuf.buf = recv_buf;    mybuf.len = BUFSIZE;
        DWORD recv_byte;
        DWORD recv_flag = 0;
        WSARecv(c_socket, &mybuf, 1, &recv_byte, &recv_flag, 0, 0);
        cout << "Client Sent [" << recv_byte << "bytes] : " << recv_buf << endl;

        DWORD sent_byte;
        mybuf.len = recv_byte;
        int ret = WSASend(c_socket, &mybuf, 1, &sent_byte, 0, 0, 0);
        if (SOCKET_ERROR == ret) {
            err_disp("WSASend", WSAGetLastError());
        }
    }
    WSACleanup();
}
