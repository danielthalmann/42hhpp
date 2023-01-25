#include <iostream>
#include <string>
#include <typeinfo>

void set(const std::string s) {
    std::cout << " value '" << s << "' : je suis un string" << std::endl;
}
void set(const int i) {
    std::cout << " value '" << i << "'\t : je suis un int" << std::endl;
}
void set(const char * i) {
    (void)(i);
   set (std::string(i));
}
void set(const void* i) {
    (void)(i);
    std::cout << " value '" <<  "'\t : je suis un void *" << std::endl;
}
void set(const bool b) {
    std::cout << " value '" << b << "'\t : je suis un boolean" << std::endl;
}

int main()
{
    //bool b;

    const std::type_info& ti4 = typeid(std::string);
    std::cout << ti4.name() << std::endl;


    const std::type_info& ti3 = typeid(int);
    std::cout << ti3.name() << std::endl;

    const std::type_info& ti = typeid(bool);
    std::cout << ti.name() << std::endl;

    const std::type_info& ti2 = typeid("test");
    std::cout << ti2.name() << std::endl;

    set(true);
    set(1);
    set("tedt");
    set(std::string("text"));
}