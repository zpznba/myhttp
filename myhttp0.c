#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>



int main() {
    int server_sockfd = 0;
    int client_sockfd = 0;
    int server_len, client_len;
    struct sockaddr_in server_address,client_address;
    //创建套接字
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0); //协议族信息，套接字数据传输方式为面向消息的TCP
    //初始化服务器地址信息 sockaddr_in
    server_address.sin_family = AF_INET;//地址族
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);  // 监听本机所有IP
    server_address.sin_port = htons(10000);    //  设置端口号，注意这里的 htons 方法（主机序转网络序，s指的是short）
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    listen(server_sockfd, 5);//设置同时监听最大个数，其实就是队列长度
    while(1) {
        char buffer[5000];
        char send_str[] = "hello world !\n";  // 准备给连接过来的客户端发送的字符串
        client_len = sizeof(client_address);
        //accept的第一个参数是监听套接字，相当于门卫的功能；后两个都是客户端的地址信息
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);//会新创建一个套接字传给client_sockfd
        read(client_sockfd, buffer, 5000);    // 接收客户端传来的字符，存到buffer中
        printf("%s", buffer);     //  打印我们接收到的字符
        write(client_sockfd, send_str, sizeof(send_str)/sizeof(send_str[0]));   // 向客户端发送数据，这里的 read write 和 和文件读写时没什么区别
        close(client_sockfd);
    }
}