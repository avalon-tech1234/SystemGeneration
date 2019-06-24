#pragma once

#include <string>

#include <algorithm> 

#include <functional> 

#include <cctype>

#include <locale>





class Utility

{

public:





	// trim from start (in place)

	inline void ltrim(std::string &s) {

		s.erase(s.begin(), std::find_if(s.begin(), s.end(),

			std::not1(std::ptr_fun<int, int>(std::isspace))));

	}



	// trim from end (in place)

	inline void rtrim(std::string &s) {

		s.erase(std::find_if(s.rbegin(), s.rend(),

			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());

	}



	// trim from both ends (in place)

	inline void trim(std::string &s) {

		ltrim(s);

		rtrim(s);

	}



	// trim from start (copying)

	inline std::string ltrim_copy(std::string s) {

		ltrim(s);

		return s;

	}



	// trim from end (copying)

	inline std::string rtrim_copy(std::string s) {

		rtrim(s);

		return s;

	}



	// trim from both ends (copying)

	inline std::string trim_copy(std::string s) {

		trim(s);

		return s;

	}



	inline void trim2(std::string& str)

	{

		size_t beg = str.find('{') + 1, end = str.find('}');

		str = str.substr(beg, end - beg);

	}



};