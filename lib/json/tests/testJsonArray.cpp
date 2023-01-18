
#include <Json.hpp>

int main()
{
    int ret = 0;

    json::JsonArray *json = new json::JsonArray();

    json->push("exemple");

    json->putString(0, "autre");

    std::string s = json->at(0)->getString();
    
    if (s.compare("autre") != 0){
        ret = 1;
    }

    json::JsonArray jsArray(*json);

    jsArray = *json;

    delete json;

    return ret;

}