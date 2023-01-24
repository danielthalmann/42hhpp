#include "Header.hpp"

hhpp::Header::Header() {}
hhpp::Header::~Header() {}

std::string hhpp::Header::get(std::string key) {
	std::map<std::string, std::string>::iterator it;
	it = _params.find(key);
	return (it->second);
}

void hhpp::Header::remove(std::string key) {
	_params.erase(key);
}

void hhpp::Header::removeAll() {
	for (mapStringStringIt it = _params.begin(); it != _params.end(); it++) {
		_params.erase(it->first);
	}
}

void hhpp::Header::append(std::string key, std::string value) {
	_params.insert(std::make_pair(key, value));
}

void hhpp::Header::showParams() {
	for (mapStringStringIt it = _params.begin(); it != _params.end(); it++) {
		std::cout	<< it->first << ": "
					<< it->second << std::endl;
	}
}
