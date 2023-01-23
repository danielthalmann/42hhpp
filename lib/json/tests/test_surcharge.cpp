#include <iostream>
#include <string>

class obj  {

    public:

    void set(const bool b);
    void set(const char* s);
    void set(const std::string s);
    void set(const int i);
    void set(const float f);
    void set(const double d);

};

void obj::set(const bool b)
{
    std::cout << " value '" << b << "'\t : je suis un boolean" << std::endl;
}

void obj::set(const char* s)
{
    std::cout << " value '" << s << "' : je suis un pointeur" << std::endl;
}

void obj::set(const std::string s)
{
    std::cout << " value '" << s << "' : je suis un string" << std::endl;
}

void obj::set(const int i)
{
    std::cout << " value '" << i << "'\t : je suis un int" << std::endl;
}

void obj::set(const float f)
{
    std::cout << " value '" << f << "'\t : je suis un float" << std::endl;
}

void obj::set(const double d)
{
    std::cout << " value '" << d << "'\t : je suis un double" << std::endl;
}


int main()
{
    obj t;

    std::cout << sizeof(bool) << std::endl;
    std::cout << sizeof("") << std::endl;
    std::cout << sizeof("") << std::endl;

    t.set(true);
    t.set("text");
    t.set(std::string("text"));
    t.set(1.1);
    t.set(1);
    t.set(5.5f);

}