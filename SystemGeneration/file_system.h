#pragma once
#include <string>
#include <experimental/filesystem>

namespace filesystem
{
	void create_folder(const std::string& foldername)
	{
		std::wstring ws2(foldername.begin(), foldername.end());
		_wmkdir(&ws2[0]);
	}

}
