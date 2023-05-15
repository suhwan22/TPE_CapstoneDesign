#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;
    char *hello = "Hello from client";
    char buffer[BUFFER_SIZE] = {0};

    // Winsock 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    // 소켓 생성
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
             printf("Could not create socket : %d", WSAGetLastError());
    }

    // 서버의 주소와 포트 설정
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 서버에 연결
    if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Connect failed with error code : %d", WSAGetLastError());
        return 1;
    }

    // 서버로 메시지 전송
    send(client_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // 서버로부터 데이터 수신
    recv(client_socket, buffer, BUFFER_SIZE, 0);
    printf("Received message: %s\n", buffer);

    // 소켓 닫기
    closesocket(client_socket);
    WSACleanup();

    return 0;
}