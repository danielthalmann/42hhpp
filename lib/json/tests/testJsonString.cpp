
#include <JsonString.hpp>

int main()
{
    int ret = 0;

    json::JsonString *json = new json::JsonString();

    json->set("exemple");
    std::string s = json->getString();

    json::JsonString jsString(*json);

    jsString = "salut";

    if (s.compare("exemple") != 0){
        ret = 1;
    }

    delete json;

    return ret;

}