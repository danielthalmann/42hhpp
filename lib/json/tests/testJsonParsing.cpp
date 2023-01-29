
#include <Json.hpp>
#include <iostream>
#include <vector>

int main()
{
    try {

        
        int ret = 0;
        std::string s;

        json::JsonValue *json = json::Json::parse(std::string("\"test string \""));
        s = json->getString();
        if (s.compare("test string ") != 0) {
            std::cout << "string error: '" << s << "'" << std::endl;
            return 1;
        }
        delete json;

        json = json::Json::parse(std::string("\n \t 42  "));
        if (json->getInt() != 42) {
            std::cout << "int error'" << json->getInt() << "'" << std::endl;
            return 1;
        }
        delete json;

        json = json::Json::parse(std::string("\n \t \n null  "));
        if (!json->isNull()) {
            std::cout << " value not null " << std::endl;
            return 1;
        }
        delete json;

        json = json::Json::parse(std::string("\n \t \n true"));
        if (!json->getBool()) {
            std::cout << " value not true  " << std::endl;
            return 1;
        }
        delete json;

        json = json::Json::parse(std::string(" { \"test\" : \t 42, \"test2\" : \"43\", \"test3\" : true, \"test4\": null, \"test5\" : 42.3 } "));

        if (json->at("test")->getInt() != 42) {
            std::cout << "value '" << json->at("test")->getInt() << "'" << std::endl;
            return 1;
        }
        
        if( json->at("test2")->getString() != "43") {
            std::cout << "value '" << json->at("test2")->getString() << "'" << std::endl;
            return 1;
        }
        
        if( json->at("test3")->getBool() != true) {
            std::cout << "value '" << json->at("test3")->getBool() << "'" << std::endl;
            return 1;
        }
        
        if( json->at("test4")->isNull() != true) {
            std::cout << "value '" << json->at("test4")->isNull() << "'" << std::endl;
            return 1;
        }
        
        if( json->at("test5")->getFloat() != 42.3f) {
            std::cout << "value '" << json->at("test5")->getFloat() << "'" << std::endl;
            return 1;
        }

        std::vector<std::string> k = json->keys();

        for (size_t i = 0; i < k.size(); i++)
        {
            std::cout << k[i] << " ";
        }
        


        delete json;

        json = json::Json::parse(std::string(" [ 42, \"43\", true, null, 42.3 ]"));

        if (json->at(0)->getInt() != 42) {
            std::cout << "value '" << json->at(0)->getInt() << "'" << std::endl;
            return 1;
        }
        
        if( json->at(1)->getString() != "43") {
            std::cout << "value '" << json->at(1)->getString() << "'" << std::endl;
            return 1;
        }
        
        if( json->at(2)->getBool() != true) {
            std::cout << "value '" << json->at(2)->getBool() << "'" << std::endl;
            return 1;
        }
        
        if( json->at(3)->isNull() != true) {
            std::cout << "value '" << json->at(3)->isNull() << "'" << std::endl;
            return 1;
        }
        
        if( json->at(4)->getFloat() != 42.3f) {
            std::cout << "value '" << json->at(4)->getFloat() << "'" << std::endl;
            return 1;
        }

        delete json;


        json = json::Json::parse(std::string(" {\"redirect\" : [ {\"path\" : \"no_more_here\",\"destination\" : \"/new_location.html\",\"status\" : 302} ]}"));
        std::cout << "value '" << json->at("redirect")->at(0)->at("path")->getString() << "'";

        if (json->at("redirect")->at(0)->exists("truc") ) {
            return 1;
        }

        delete json;

        return ret;


    } catch (std::exception &e)
    {
        std::cout << "error : " << e.what() << std::endl;
        return 1;
    }

}