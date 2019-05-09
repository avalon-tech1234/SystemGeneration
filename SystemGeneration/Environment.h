#pragma once

class Environment
{
private:
	size_t n;

public:
	void run() const;

	Environment(size_t n) : n(n) {}

};