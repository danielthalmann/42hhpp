
#include <iostream>
#include <map>
#include <string>
#include <utility.hpp>

int main()
{
    int ret = 0;
    char **s;

    std::map<std::string, std::string> m;

    m["variable1"] = "1";
    m["variable2"] = "2";
    m["variable3"] = "3";
    
    s = utils::mapStringToArray(m);

    int i = -1;
    while (s && s[++i]) {
        std::cout << s[i] << std::endl;
    }
    utils::freeArray(s);

    return ret;

}