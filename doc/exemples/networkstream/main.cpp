

#include "NetworkStream.hpp"
#include <fstream>
#include <string>

int main()
{

    NetworkStream stream;
	std::ifstream myfile;
    std::string buffer;

	myfile.open("send.txt", std::ios_base::in);
	if (!myfile.is_open())
	{
		return (1);
	}

    try {
    
        stream.connect("127.0.0.1", 8080);

        std::getline(myfile, buffer);
        stream << buffer;

        stream.close();
    
    } catch (NetworkException::ConnectionFailed &e) {

        std::cout << e.what();
        std::cout << "\n";
    
    } catch (NetworkException::SocketIOError &e) {

        std::cout << e.what();
        std::cout << "\n";

    }
    catch (std::exception &e) {

        std::cout << "autre exception";
        std::cout << e.what();
        std::cout << "\n";

    }

    myfile.close();

    return (0);


}