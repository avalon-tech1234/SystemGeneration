#pragma once
#include <string>


class Environment
{
private:
	size_t n;

public:
	std::string run(bool print_or_not = true) const;

	Environment(size_t n) : n(n) {}

};