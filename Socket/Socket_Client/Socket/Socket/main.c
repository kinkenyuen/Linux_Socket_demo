//
//  main.c
//  Socket
//
//  Created by jianqin_ruan on 2021/8/20.
//

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 100

int main(int argc, const char * argv[]) {
    /*
     向服务器socket(特定的IP和端口)发送请求
     connect会进行TCP连接
     */
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8814);
    
    /*
     向服务器socket发送数据
     */
    char bufSend[BUF_SIZE] = {0};
    char bufRecv[BUF_SIZE] = {0};
    while (1) {
        int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
        printf("Input a string : ");
        scanf("%s",bufSend);
        write(client_socket, bufSend, sizeof(bufSend));
        
        read(client_socket, bufRecv, sizeof(bufRecv) - 1);
        printf("Message form server: %s\n", bufRecv);
        memset(bufSend, 0, sizeof(bufSend));
        memset(bufRecv, 0, sizeof(bufRecv));
        close(client_socket);
    }
    return 0;
}
