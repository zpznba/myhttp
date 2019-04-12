//request.cpp
#include "request.h"
#include "StringUtil.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

//我们收到的GET请求数据包一般格式如下：
/*
    GET /register.do?p={%22username%22:%20%2213917043329%22,%20%22nickname%22:%20%22balloon%22,%20%22password%22:%20%22123%22} HTTP/1.1\r\n
    Host: 120.55.94.78:12345\r\n
    Connection: keep-alive\r\n
    Upgrade-Insecure-Requests: 1\r\n
    User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.146 Safari/537.36\r\n
    Accept-Encoding: gzip, deflate\r\n
    Accept-Language: zh-CN, zh; q=0.9, en; q=0.8\r\n
    \r\n
*/
void process_request(struct http_request * request,char* http_data){
    
    string inbuf = http_data;
    //检查是否以\r\n\r\n结束，如果不是说明包头不完整，退出
    /*string end = inbuf.substr(inbuf.length() - 4);
    if (end != "\r\n\r\n")
       return;
    */
    //以\r\n分割每一行
    std::vector<string> lines;
    StringUtil::Split(inbuf, lines, "\r\n");
    if (lines.size() < 1 || lines[0].empty())
    {
        return;
    }
    /*
    for(int i = 0;i < lines.size();++i){
        cout<<lines[i]<<endl;
    }
    */
    //解析header
    std::vector<string> chunk;
    StringUtil::Split(lines[0],chunk," ");
    //chunk中至少有三个字符串：GET+url+HTTP版本号
    if (chunk.size() < 3)
    {
        return;
    }
    request->method = chunk[0];
    request->url = chunk[1];
    request->version = chunk[2];
    //逐行读出headers，并存储
    int i = 1;
    std::vector<string> header_content;
    for(i = 1;lines[i] != "\r\n";++i){
        //cout<<lines[i]<<endl;
        StringUtil::Split(lines[i],header_content,":");
        string content;
        size_t pos = std::string::npos; 
        pos = lines[i].find(":");
        content = lines[i].substr(pos + 1,lines[i].size()-pos-1);
        //cout<<header_content[0]<<endl;
        //cout<<content<<endl;
        request->headers.insert(pair<string,string>(header_content[0],content));
        header_content.clear();
        
    }
    //解析body
    for(i = i+1; i < lines.size(); ++i){
        request->body += lines[i];
        if( i != lines.size()-1)
            request->body += "\r\n";  
    }
}