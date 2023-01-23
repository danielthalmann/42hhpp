
#include <Json.hpp>

int main()
{
    int ret = 0;

    json::JsonValue *json = json::Json::parse(std::string(" \t \"test string \"  "));

    delete json;

    return ret;

}