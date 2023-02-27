#include "FileInformation.h"

int main()
{
	SYSTEMTIME creationTime = MOONG::FileInformation::GetFileCreationTime();
	std::cout << "Year[" << creationTime.wYear << "], month[" << creationTime.wMonth << "], day[" << creationTime.wDay << "], hour[" << creationTime.wHour << "], min[" << creationTime.wMinute << "], sec[" << creationTime.wSecond << "]\n" << std::endl;

	std::cout << "file path[" << MOONG::FileInformation::GetFilePath().c_str() << "]\n" << std::endl;

	std::cout << "file name[" << MOONG::FileInformation::GetFileName().c_str() << "]\n" << std::endl;

	std::cout << "file name without file extension[" << MOONG::FileInformation::GetFileNameWithoutFileExtension().c_str() << "]\n" << std::endl;

	std::cout << "file version[" << MOONG::FileInformation::GetFileVersion().c_str() << "]\n" << std::endl;

	std::cout << "folder name[" << MOONG::FileInformation::GetFolderName().c_str() << "]\n" << std::endl;

	system("pause");

	return 0;
}