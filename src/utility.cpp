#include "utility.hpp"
#include <algorithm>
#include <iostream>

#define PATH_SEPARATOR '/'
namespace utils {
		
	std::vector<std::string> split(std::string str, std::string delimiter) {
		size_t pos;
		std::vector<std::string> vec;

		do {
			pos = str.find(delimiter);
			vec.push_back(str.substr(0, pos));
			str.erase(0, pos + delimiter.length());
		} while (pos != std::string::npos);

		return (vec);
	}

	char** mapStringToArray(const std::map<std::string, std::string> &m)
	{
		char **a;
		int pos, index;

		a = new char*[m.size() + 1];
		a[m.size()] = 0;
		index = 0;

		for (std::map<std::string, std::string>::const_iterator i = m.begin(); i != m.end(); i++)
		{
			int size = i->first.size() + i->second.size() + 1;
			a[index] = new char[size + 1];
			a[index][size] = 0;
			pos = 0;
			for(size_t j = 0; j < i->first.size(); j++) {
				a[index][pos++] = i->first[j]; 
			}
			a[index][pos++] = '=';
			for(size_t j = 0; j < i->second.size(); j++) {
				a[index][pos++] = i->second[j]; 
			}
			++index;
		}
		return a;
	}

	void freeArray(char** a)
	{
		unsigned int i = 0;
		while (a && a[i])
		{
			delete a[i++];
		}
		delete a;	
	}


	bool isNotSpace(unsigned char ch) {
			return !std::isspace(ch);
	}

	// trim from start (in place)
	void ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), isNotSpace));
	}

	// trim from end (in place)
	void rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), isNotSpace).base(), s.end());
	}

	// trim from both ends (in place)
	std::string& trim(std::string &s) {
		rtrim(s);
		ltrim(s);
		return s;
	}

	// trim from both ends (in place)
	std::string path(const std::string& path1, const std::string& path2) {
		
		if (path1.size() == 0) {
			return path2;
		}
		if (path2.size() == 0) {
			return path1;
		}
		if (*(path1.rbegin()) == PATH_SEPARATOR && *(path2.begin()) != PATH_SEPARATOR)
			return path1 + path2;
		else if (*path1.rbegin() != PATH_SEPARATOR && *path2.begin() == PATH_SEPARATOR) {
			if (path2.size() > 1)
				return path1 + path2;
			else
				return path1;
		}
		else if (*path1.rbegin() == PATH_SEPARATOR && *path2.begin() == PATH_SEPARATOR)
			return path1 + path2.substr(1);
		else 
			return path1 + PATH_SEPARATOR + path2;
		
		return path1;
	}

	std::string base64Encode(const unsigned char* s, unsigned int len) {

		if (len == 0)
			return std::string("");

		char encode_table[64] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
		'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
		'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
		'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
		's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
		'3', '4', '5', '6', '7', '8', '9', '+', '/'};

		std::string encode(4 + (4 * len / 3), '\0');
		size_t i = 0, y = 0;
		char a, b, c;
		long int concat_bits;

		std::cout << "len :" << len << std::endl;

		while((i + 2) < len) {
			if (y >= encode.capacity()){
				encode.resize(encode.capacity() * 2, '\0');
			}
			a = s[i++];
			b = s[i++];
			c = s[i++];
			concat_bits = (a << 16) | (b << 8) | c;
			encode[y++] = encode_table[(concat_bits >> 18) & 0x3F];
			encode[y++] = encode_table[(concat_bits >> 12) & 0x3F];
			encode[y++] = encode_table[(concat_bits >> 6) & 0x3F];
			encode[y++] = encode_table[concat_bits & 0x3F];
		}
		if (len - i == 1) {
			if (y >= encode.capacity()){
				encode.resize(encode.capacity() * 2, '\0');
			}
			a = s[i++];
			concat_bits = (a << 16);
			encode[y++] = encode_table[(concat_bits >> 18) & 0x3F];
			encode[y++] = encode_table[(concat_bits >> 12) & 0x3F];
			encode[y++] = '=';
			encode[y++] = '=';
		}
		if (len - i == 2) {
			if (y >= encode.capacity()){
				encode.resize(encode.capacity() * 2, '\0');
			}
			a = s[i++];
			b = s[i++];
			concat_bits = (a << 16) | (b << 8) ;
			encode[y++] = encode_table[(concat_bits >> 18) & 0x3F];
			encode[y++] = encode_table[(concat_bits >> 12) & 0x3F];
			encode[y++] = encode_table[(concat_bits >> 6) & 0x3F];
			encode[y++] = '=';
		}

		encode.resize(y, '\0');
		return encode;
	}

	std::string readFile(std::string path) {
		std::string file;
		char c;
		struct stat fileInfo;
		std::ifstream ifs(path.c_str());

		if (stat(path.c_str(), &fileInfo) != 0)
			throw(std::exception());

		if ((fileInfo.st_mode & S_IFMT) == S_IFDIR)
			throw(std::exception());


		if (!ifs.good() || path.empty())
			throw(std::exception());

		if (ifs.is_open())
		{

			c = ifs.get();

			do {
				file += c;
				c = ifs.get();
			}
			while (!ifs.eof());

			ifs.close();
		}
		else
		{
			throw(std::exception());
		}
		return (file);
	}

	std::string getTime() {
		char buf[1000];
		time_t now = time(0);
		struct tm tm = *gmtime(&now);
		strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
		return (std::string(buf));
	}

	std::string upperKebabCase(std::string str) {
		for (size_t i = 0; i < str.size(); ++i) {
			if (i == 0 || str[i - 1] == ' ' || str[i - 1] == '-')
				str[i] = std::toupper(str[i]);
		}

		return str;
	}

}
