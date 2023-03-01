#include "utility.hpp"
#include <algorithm>
#include <iostream>
#include <cctype>

#define PATH_SEPARATOR '/'
namespace utils
{

	std::vector<std::string> split(std::string str, std::string delimiter)
	{
		size_t pos;
		std::vector<std::string> vec;

		do
		{
			pos = str.find(delimiter);
			vec.push_back(str.substr(0, pos));
			str.erase(0, pos + delimiter.length());
		} while (pos != std::string::npos);

		return (vec);
	}

	char **mapStringToArray(const std::map<std::string, std::string> &m)
	{
		char **a;
		int pos, index;

		a = new char *[m.size() + 1];
		a[m.size()] = 0;
		index = 0;

		for (std::map<std::string, std::string>::const_iterator i = m.begin(); i != m.end(); i++)
		{
			int size = i->first.size() + i->second.size() + 1;
			a[index] = new char[size + 1];
			a[index][size] = 0;
			pos = 0;
			for (size_t j = 0; j < i->first.size(); j++)
			{
				a[index][pos++] = i->first[j];
			}
			a[index][pos++] = '=';
			for (size_t j = 0; j < i->second.size(); j++)
			{
				a[index][pos++] = i->second[j];
			}
			++index;
		}
		return a;
	}

	void freeArray(char **a)
	{
		unsigned int i = 0;
		while (a && a[i])
		{
			delete a[i++];
		}
		delete a;
	}


	bool isNotSpace(unsigned char ch)
	{
		return !std::isspace(ch);
	}

	// trim from start (in place)
	void ltrim(std::string &s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), isNotSpace));
	}

	// trim from end (in place)
	void rtrim(std::string &s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), isNotSpace).base(), s.end());
	}

	// trim from both ends (in place)
	std::string &trim(std::string &s)
	{
		rtrim(s);
		ltrim(s);
		return s;
	}

	// trim from both ends (in place)
	std::string path(const std::string &path1, const std::string &path2)
	{

		if (path1.size() == 0)
		{
			return path2;
		}
		if (path2.size() == 0)
		{
			return path1;
		}
		if (*(path1.rbegin()) == PATH_SEPARATOR && *(path2.begin()) != PATH_SEPARATOR)
			return path1 + path2;
		else if (*path1.rbegin() != PATH_SEPARATOR && *path2.begin() == PATH_SEPARATOR)
		{
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

	std::string readFile(std::string path)
	{
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

			do
			{
				file += c;
				c = ifs.get();
			} while (!ifs.eof());

			ifs.close();
		}
		else
		{
			throw(std::exception());
		}
		return (file);
	}

	std::string getTime()
	{
		char buf[1000];
		time_t now = time(0);
		struct tm tm = *gmtime(&now);
		strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
		return (std::string(buf));
	}

	std::string upperKebabCase(std::string str)
	{
		for (size_t i = 0; i < str.size(); ++i)
		{
			if (i == 0 || str[i - 1] == ' ' || str[i - 1] == '-')
				str[i] = std::toupper(str[i]);
		}

		return str;
	}

    std::string toUpper(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(), ::toupper);
        return s;
    }

} // namespace utils
