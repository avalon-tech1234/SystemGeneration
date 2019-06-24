#pragma once
#include <string>
//#include <sys/types.h>
//#include <sys/stat.h>

namespace filesystem
{
	void create_folder(const std::string& foldername)
	{
		std::wstring ws2(foldername.begin(), foldername.end());
		_wmkdir(&ws2[0]);
	}

	struct stat info;
/*
	// функции folder_exists не используются
	bool folder_exists(const char* foldername)
	{
		if (stat(foldername, &info) != 0)
			return false;
		else if (info.st_mode & S_IFDIR)  // S_ISDIR() doesn't exist on my windows 
			return true;
		else
			return false;
	}
	bool folder_exists(const std::string& foldername)
	{
		return folder_exists(foldername.c_str());
	}
*/
}
