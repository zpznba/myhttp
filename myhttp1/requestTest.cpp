//requestTest.cpp
#include <iostream>
#include "request.h"
#include <unordered_map>

using namespace std;

int main(){
    struct http_request request;
    char data[] = "GET / HTTP/1.1\r\nHost:127.0.0.1:9734\r\nUser-Agent:curl/7.54.0\r\nConnection: keep-alive\r\n\r\nmessage=nice to meet you\r\nhhhhh";
    process_request(&request,data);
    cout<<request.method<<endl;
    cout<<request.url<<endl;
    cout<<request.version<<endl;
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