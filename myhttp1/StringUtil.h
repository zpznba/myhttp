//StringUtil.h

#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__
#include <string>
#include <vector>

class StringUtil
{
private:
    StringUtil() = delete;
    ~StringUtil() = delete;
    StringUtil(const StringUtil& rhs) = delete;
    StringUtil& operator=(const StringUtil& rhs) = delete;

public:
    static void Split(const std::string& str, std::vector<std::string>& v, const char* delimiter = "|");
};


#endif //!__STRING_UTIL_H__