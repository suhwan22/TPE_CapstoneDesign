#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET server_socket, new_socket;
    struct sockaddr_in server, client;
    int addrlen = sizeof(client);
    char buffer[BUFFER_SIZE] = {0};
    char *hello = "Hello from server";

    // Winsock 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    // 소켓 생성
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    // 서버의 주소와 포트 설정
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // 소켓에 주소와 포트 바인딩
    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
    }

    // 소켓을 수신 대기 상태로 전환
    listen(server_socket, 3);

    // 클라이언트로부터의 연결 요청 대기
    if ((new_socket = accept(server_socket, (struct sockaddr *)&client, &addrlen)) == INVALID_SOCKET)
    {
        printf("Accept failed with error code : %d", WSAGetLastError());
    }

    // 클라이언트로부터 데이터 수신
    recv(new_socket, buffer, BUFFER_SIZE, 0);
    printf("Received message: %s\n", buffer);

    // 클라이언트로 데이터 전송
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // 클라이언트와 연결 종료
    closesocket(new_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}