#include "Location.hpp"

Location::Location() {}

Location::~Location() {}

Location::Location(std::string path, std::string root) :
				   _path(path), _root(root) {}
