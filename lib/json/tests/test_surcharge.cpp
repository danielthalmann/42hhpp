#include <iostream>
#include <string>

void set(const std::string s) {
    std::cout << " value '" << s << "' : je suis un string" << std::endl;
}

void set(const int i) {
    std::cout << " value '" << i << "'\t : je suis un int" << std::endl;
}

void set(const bool b) {
    std::cout << " value '" << b << "'\t : je suis un boolean" << std::endl;
}

int main()
{
    set(1);
    set("text");
    set(std::string("text"));
}