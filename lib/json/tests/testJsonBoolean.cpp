
#include <JsonBoolean.hpp>

int main()
{
    int ret = 0;

    json::JsonBoolean *json = new json::JsonBoolean();

    json->set(true);
    bool s = json->getBool();

    json::JsonBoolean jsBool(*json);

    jsBool = false;

    if (!s){
        ret = 1;
    }

    delete json;

    return ret;

}