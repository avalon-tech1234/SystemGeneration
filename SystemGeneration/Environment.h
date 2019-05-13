#pragma once
#include <string>


class Environment
{
private:
	size_t n;

public:
	std::string run() const;

	Environment(size_t n) : n(n) {}

};