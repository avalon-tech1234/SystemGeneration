#pragma once
#include "Environment.h"
#include <vector>
#include "BOOL.h"

// основной класс для тестирования корректности работы программы

class MainTesting
{
	size_t n;
	std::string foldername;

public:
	void test_system_generation(BOOL b) const;

	void test_system_generation() const
	{
		test_system_generation(3);
	}

	MainTesting(size_t n, std::string foldername) : n(n), foldername(foldername) {}

};

