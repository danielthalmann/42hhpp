#ifndef NETWORKBUFFER_HPP
#define NETWORKBUFFER_HPP

#include "NetworkException.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>

#define NETWORK_BUFFER_LENGTH 256
#define LISTEN_CONNECTION_LENGTH 5

/**
 * @brief 
 * 
 *  Buffer output
 * ┌───┬───┬───┬───┬───┐
 * │   │   │   │   │   │
 * └───┴───┴───┴───┴───┘
 *   ▲           ▲       ▲
 *   │           │       │
 *
 * pbase()     pptr()  epptr()
 *
 *  Buffer input
 * ┌───┬───┬───┬───┬───┐
 * │   │   │   │   │   │
 * └───┴───┴───┴───┴───┘
 *   ▲           ▲       ▲
 *   │           │       │
 *
 * eback()     gptr()  egptr()
 *
 */
class NetworkBuffer : public std::streambuf
{

public:
	NetworkBuffer();
	~NetworkBuffer();

	/**
	 * @brief Set the Socket
	 * 
	 * @param s 
	 */
	void setSocket (int s);

	/**
	 * @brief Get the Socket
	 * 
	 * @return int 
	 */
	int getSocket ();

	/**
	 * @brief Set the Connection status
	 * 
	 * @param c true / false
	 */
	void setConnected(bool c);

	/**
	 * @brief Is connected
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isConnected();

	/**
	 * @brief  Is listened
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isListened();

	/**
	 * @brief listen for network connection
	 * 
	 * @param ip_addr 
	 * @param port 
	 */
	void startListen(const char *ip_addr, int port);


	/**
	 * @brief connect to computer network
	 * 
	 * @param ip_addr 
	 * @param port 
	 */
	void startConnection(const char *ip_addr, int port);


	/**
	 * @brief close connection
	 * 
	 */
	void closeConnection();

protected:
	
	/**
	 * @brief Put area 
	 * 
	 *  xsputn
	 *  	writes multiple characters to the output sequence
	 *  	(virtual protected member function of std::basic_streambuf<CharT,Traits>)
	 * 
	 *  overflow
	 *  	writes characters to the associated output sequence from the put area
	 *  	(virtual protected member function of std::basic_streambuf<CharT,Traits>)
	 * 
	 *  pbasepptrepptr
	 *  	returns a pointer to the beginning, current character and the end of the put area
	 *  	(protected member function)
	 * 
	 *  pbump
	 *  	advances the next pointer of the output sequence
	 *  	(protected member function)
	 * 
	 *  setp
	 *  	repositions the beginning, next, and end pointers of the output sequence
	 *  	(protected member function)
	 * 
	 */

	/**
	 * @brief writes multiple characters to the output sequence
	 * 
	 * @param buffer 
	 * @param size 
	 * @return std::streamsize 
	 */
	virtual std::streamsize xsputn(const char* buffer, std::streamsize size);
	
	
	/**
	 * @brief Get area 
	 * 
	 *  showmanyc
	 *  	obtains the number of characters available for input in the associated input sequence, if known
	 *  	(virtual protected member function of std::basic_streambuf<CharT,Traits>)
	 * 
	 *  underflow
	 *  	reads characters from the associated input sequence to the get area
	 *  	(virtual protected member function of std::basic_streambuf<CharT,Traits>)
	 * 
	 *  uflow
	 *  	reads characters from the associated input sequence to the get area and advances the next pointer
	 *  	(virtual protected member function of std::basic_streambuf<CharT,Traits>)
	 * 
	 *  xsgetn
	 *  	reads multiple characters from the input sequence
	 *  	(virtual protected member function of std::basic_streambuf<CharT,Traits>)
	 * 
	 *  ebackgptregptr
	 *  	returns a pointer to the beginning, current character and the end of the get area
	 *  	(protected member function)
	 * 
	 *  gbump
	 *  	advances the next pointer in the input sequence
	 *  	(protected member function)
	 * 
	 *  setg
	 *  	repositions the beginning, next, and end pointers of the input sequence
	 *  	(protected member function)
	 */

	/**
	 * @brief 
	 * 
	 * @return std::streambuf::int_type 
	 */
	virtual std::streambuf::int_type underflow();

private:
	int			_socket;
	char* 		_inputbuffer;  // a buffer for the input data
	char* 		_outputbuffer; // a buffer for the output data
	bool 		_connected;
	bool		_listened;
	
private:

};

#endif