
#include <Json.hpp>

int main()
{

    json::JsonValue *json = json::Json::parse("test");

    delete json;

    return 0;

}