
#include <Json.hpp>
#include <iostream>

int main()
{
    try {

        
        int ret = 0;
        std::string s;

        json::JsonValue *json = json::Json::parse(std::string(" \t \"test string \"  "));
        s = json->getString();
        if (s.compare("test string ") == 0) {
            std::cout << "string error: '" << s << "'" << std::endl;
            return 1;
        }
        delete json;

        json = json::Json::parse(std::string(" \t 42  "));
        if (json->getInt() != 42) {
            std::cout << "int error'" << json->getInt() << "'" << std::endl;
            return 1;
        }
        delete json;

        json = json::Json::parse(std::string(" { \"test\" : \t 42 } "));

        std::cout << "value '" << json->at("test")->getInt() << "'" << std::endl;

        delete json;


        return ret;
    }catch (std::exception &e)
    {
        
    }

}