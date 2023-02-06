
#include <iostream>
#include <map>
#include <string>
#include <utility.hpp>

int main()
{
    std::string in = "Man";
    
    std::cout << in << " : " << utils::base64Encode(in) << std::endl;
    in = "exemple";
    std::cout << in << " : " << utils::base64Encode(in) << std::endl;

    return 0;

}