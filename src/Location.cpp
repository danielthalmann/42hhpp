#include "Location.hpp"

namespace hhpp {
	Location::Location() {}

	Location::~Location() {}

	Location::Location(std::string path, std::string root) : _path(path), _root(root) {}
}
