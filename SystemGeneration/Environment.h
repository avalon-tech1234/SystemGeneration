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

public:

	Environment(int n, std::string foldername);

	void run(bool print_or_not = true);
	void test();
	void silent_run()
	{
		run(true);
		clean();
	}

};