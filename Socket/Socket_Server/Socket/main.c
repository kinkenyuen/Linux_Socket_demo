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
#include <sys/wait.h>

#define BUF_SIZE 100

int main(int argc, const char * argv[]) {
    /*
     创建socket
     使用字节流方式
     协议采用TCP
     */
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    /*
     socket绑定IP、端口号
     */
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8814);
    bind(server_socket, (const struct sockaddr*)&server_addr, sizeof(server_addr));
    
    /*
     服务端socket开启监听
     */
    listen(server_socket, 20);
    
    /*
     接受客户端请求
    这个过程会进行TCP握手
     */
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    
    /*
     接收客户端数据
     */
    char buffer[BUF_SIZE] = {0};
    while (1) {
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
        read(client_socket, buffer, BUF_SIZE);
        printf("Message form client: %s\n", buffer);
        write(client_socket, buffer, sizeof(buffer));
        close(client_socket);
        memset(buffer, 0, sizeof(buffer));
    }
    
    /*
     关闭socket
     */
    close(server_socket);
    
    return 0;
}
