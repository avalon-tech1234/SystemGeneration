#pragma once
#include <string>



void create_folder(const std::string& foldername)
{
	std::wstring ws2(foldername.begin(), foldername.end());
	_wmkdir(&ws2[0]);
}


