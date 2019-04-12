//request.h
#ifndef __REQUEST__
#define __REQUEST__


#include <string>
#include <unordered_map>

using namespace std; 

struct http_request{
    string method;
    string url;
    string version;
    unordered_map<string,string> headers;
    string body;
};

void process_request(struct http_request * request,char* http_data);

#endif