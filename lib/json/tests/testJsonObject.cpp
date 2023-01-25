
#include <Json.hpp>
#include <iostream>

int main()
{
    int ret = 0;

    //std::cout << "json::JsonObject *json = new json::JsonObject()" << std::endl;
    json::JsonObject *json = new json::JsonObject();

    //std::cout << "json->put(\"test\", 1);" << std::endl;
    json->put("test", 1);
    //std::cout << "json->put(\"test\", 2);" << std::endl;
    json->put("test", 2);

    // std::string s = json->at("test")->getString();

    json::JsonValue *j;
    if ((j = json->at("test")) == 0){
        ret = 1;
    } else {
        if (j->getInt() != 2){
            ret = 1;
        }
    }

    json::JsonObject jsObject(*json);

    jsObject = *json;

    delete json;

    return ret;

}