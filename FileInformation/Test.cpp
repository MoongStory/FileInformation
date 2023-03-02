#include "FileInformation.h"

int main()
{
	SYSTEMTIME creationTime = MOONG::FileInformation::GetCreationTime();
	std::cout << "Year[" << creationTime.wYear << "], month[" << creationTime.wMonth << "], day[" << creationTime.wDay << "], hour[" << creationTime.wHour << "], min[" << creationTime.wMinute << "], sec[" << creationTime.wSecond << "]\n" << std::endl;

	std::cout << "GetPath[" << MOONG::FileInformation::GetPath().c_str() << "]\n" << std::endl;

	std::cout << "GetName[" << MOONG::FileInformation::GetName().c_str() << "]\n" << std::endl;

	std::cout << "GetNameWithoutFileExtension[" << MOONG::FileInformation::GetNameWithoutFileExtension().c_str() << "]\n" << std::endl;

	std::cout << "GetVersion[" << MOONG::FileInformation::GetVersion().c_str() << "]\n" << std::endl;

	std::cout << "GetFolderName[" << MOONG::FileInformation::GetFolderName().c_str() << "]\n" << std::endl;

	std::cout << "GetHandle[" << MOONG::FileInformation::GetHandle(MOONG::FileInformation::GetName()) << "]\n" << std::endl;
	std::cout << "GetHandle[" << MOONG::FileInformation::GetHandle("C:/Program Files/Google/Chrome/Application/chrome.exe") << "]\n" << std::endl;

	creationTime = MOONG::FileInformation::GetCreationTime(MOONG::FileInformation::GetHandle("C:/Program Files/Google/Chrome/Application/chrome.exe"));
	std::cout << "Year[" << creationTime.wYear << "], month[" << creationTime.wMonth << "], day[" << creationTime.wDay << "], hour[" << creationTime.wHour << "], min[" << creationTime.wMinute << "], sec[" << creationTime.wSecond << "]\n" << std::endl;

	system("pause");

	return 0;
}