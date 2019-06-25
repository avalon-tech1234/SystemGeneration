#pragma once
#include <string>
#include "BOOL.h"
#include <vector>

#include "Reader.h"
#include "Writer.h"
#include "Transformation.h"

#include "EnvironmentLowLevel.h"


class Environment : EnvironmentLowLevel
{

private:
	void test();
	void clean();

public:

	Environment(int n, std::string foldername);

	void run(bool test_or_not, bool clean_or_not, bool print_or_not);

};