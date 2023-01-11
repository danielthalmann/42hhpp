

#include "NetworkStream.hpp"
#include <fstream>
#include <string>

int main(int argc, char **argv)
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
    
        if (argc > 1 && std::string(argv[1]).compare("server") == 0)
        {
            stream.listen("127.0.0.1", 8080);
            NetworkStream streamClient;
            stream.accept(streamClient);

            while (!streamClient.eof())
            {
                streamClient >> buffer;
                std::cout << buffer;
            }
            
            streamClient << "ok";

            stream.close();

        } else {

            stream.connect("127.0.0.1", 8080);

            std::getline(myfile, buffer);
            stream << buffer;

            stream.close();
        }

    
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