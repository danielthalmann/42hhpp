
#include <Json.hpp>
#include <iostream>

int main()
{
    int ret = 0;

    std::cout << std::endl << "json::JsonArray *json = new json::JsonArray()" << std::endl;
    json::JsonArray *json = new json::JsonArray();

    std::cout << "json->push(\"exemple\");" << std::endl;
    json->push(std::string("exemple"));

    std::cout << "json->put(0, \"autre\");" << std::endl;
    json->put(0, "autre");

    std::cout << "std::string s = json->at(0)->getString();" << std::endl;
    std::string s = json->at(0)->getString();
    
    std::cout << s << std::endl;
    if (s.compare("autre") != 0){
        ret = 1;
    }

    std::cout << "json::JsonArray jsArray(*json);" << std::endl;
    json::JsonArray jsArray(*json);

    jsArray = *json;

    delete json;

    return ret;

}