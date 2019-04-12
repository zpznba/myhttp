//StringUtil.cpp

#include "StringUtil.h"
#include <string.h>

void StringUtil::Split(const std::string& str, std::vector<std::string>& v, const char* delimiter/* = "|"*/)//默认参数是 "|"
{
    if (delimiter == NULL || str.empty())
        return;

    std::string buf = str;
    size_t pos = std::string::npos;
    std::string substr;
    int delimiterlength = strlen(delimiter);
    while (true)
    {
        pos = buf.find(delimiter);
        if (pos != std::string::npos)
        {
            substr = buf.substr(0, pos);
            if (!substr.empty())
                v.push_back(substr);
            else
                v.push_back("\r\n");

            buf = buf.substr(pos + delimiterlength);//更新buf，从当前分割字符往后构造新的字串
        }
        else//处理最后一个分隔字符串
        {
            if (!buf.empty())
                v.push_back(buf);
            break;
        }           
    }
}
