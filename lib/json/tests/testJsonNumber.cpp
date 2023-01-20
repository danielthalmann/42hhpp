
#include <JsonNumber.hpp>

int main()
{
    int ret = 0;

    json::JsonNumber *json = new json::JsonNumber();

    json->set(4);
    int i = json->getInt();
    if (i != 4){
        ret = 1;
    }

    json::JsonNumber jsNumber(*json);

    jsNumber.set(55.5f);

    if (json->getFloat() != 4.0f){
        ret = 1;
    }

    delete json;

    return ret;

}