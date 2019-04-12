#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sstream>
#include <iostream>
#include "request.h"


using namespace std;


#define BUFFER_SIZE 512

void getRequest(int client_sockfd){
    char buffer[BUFFER_SIZE];
    struct http_request request;
    memset(buffer,0,BUFFER_SIZE);
    int message_len = 0;
    if((message_len = recv(client_sockfd,buffer,BUFFER_SIZE,0)) == -1){
        cout<<"error handling incoming request!";
        return;
    }
    process_request(&request,buffer);//将接收到的请求发给process_request()函数进行逐行处理
    cout<<"Method:"<<request.method<<endl;
    cout<<"Url:"<<request.url<<endl;
    cout<<"Version:"<<request.version<<endl;
    //打印headers
    unordered_map<string,string> headers_map;
    unordered_map<string,string>::iterator m_iter;
    headers_map = request.headers;
    for(m_iter =headers_map.begin();m_iter != headers_map.end() ;m_iter++){
        //第一个元素iter->first  第二个元素 iter->second
        cout << m_iter->first <<":"<< m_iter -> second << endl;
    }
    cout<<request.body<<endl;
}
void handleAccept(int server_sockfd){
    
    struct sockaddr_in client_address;
    int client_sockfd = 0;
    socklen_t client_len=sizeof(client_address);
    //accept的第一个参数是监听套接字，相当于门卫的功能；后两个都是客户端的地址信息
    client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);//会新创建一个套接字传给client_sockfd
    getRequest(client_sockfd);
    close(client_sockfd);
}

int main() {
    int server_sockfd = 0;
    
    int server_len;
    struct sockaddr_in server_address;
    //创建套接字
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0); //协议族信息，套接字数据传输方式为面向消息的TCP
    //初始化服务器地址信息 sockaddr_in
    server_address.sin_family = AF_INET;//地址族
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);  // 监听本机所有IP
    server_address.sin_port = htons(10000);    //  设置端口号，注意这里的 htons 方法（主机序转网络序，s指的是short）
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    listen(server_sockfd, 5);//设置同时监听最大个数，其实就是队列长度
    while(true) {
        handleAccept(server_sockfd);
    }
}