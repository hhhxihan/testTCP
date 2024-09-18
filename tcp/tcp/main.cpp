#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef int socklen_t;

#define SERVER_ADDRESS "127.0.0.1"
#define PORT 8081
#define MAX_BUFFER_SIZE 1024

int main()
{
    // 初始化 Winsock 库
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        fprintf(stderr, "Failed to initialize Winsock\n");
        return EXIT_FAILURE;
    }

    char buffer[MAX_BUFFER_SIZE];
    SOCKET server_socket, client_socket = 0;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t addrlen = sizeof(sockaddr_in);

    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    int a;
    scanf_s("%d", &a);

    printf("start bind\n");
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("start listen\n");
    listen(server_socket, 5);

    client_socket = accept(server_socket, NULL, NULL);
    // client_socket=accept(server_socket,(sockaddr *)&client_addr,&addrlen);
    printf("connect success\n");
    printf("%d", client_socket);


    long long num_bytes_received;
    while (1) {
        while ((num_bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {//接受信息
            buffer[num_bytes_received] = '\0';  // Null-terminate the received data
            // Send the same message back to the client
            //send(client_socket, buffer, num_bytes_received, 0); //发送信息
        }
    }
    

    scanf_s("%d", &a);
    closesocket(client_socket);  //关闭连接
    closesocket(server_socket);  //关闭listen

    return 0;
}