#include "FileInformation.h"

int main()
{
	std::cout << "GetPath[" << MOONG::FileInformation::GetSelfPath().c_str() << "]\n" << std::endl;
	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	
	std::cout << "GetHandle[" << MOONG::FileInformation::GetFileHandle() << "]\n" << std::endl;
	std::cout << "GetHandle[" << MOONG::FileInformation::GetFileHandle("C:/Program Files/Google/Chrome/Application/chrome.exe") << "]\n" << std::endl;
	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	SYSTEMTIME creationTime = MOONG::FileInformation::GetCreationTime();
	std::cout << "Year[" << creationTime.wYear << "], month[" << creationTime.wMonth << "], day[" << creationTime.wDay << "], hour[" << creationTime.wHour << "], min[" << creationTime.wMinute << "], sec[" << creationTime.wSecond << "]\n" << std::endl;
	
	creationTime = MOONG::FileInformation::GetCreationTime("C:/Program Files/Google/Chrome/Application/chrome.exe");
	std::cout << "Year[" << creationTime.wYear << "], month[" << creationTime.wMonth << "], day[" << creationTime.wDay << "], hour[" << creationTime.wHour << "], min[" << creationTime.wMinute << "], sec[" << creationTime.wSecond << "]\n" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "GetName[" << MOONG::FileInformation::GetName().c_str() << "]\n" << std::endl;
	std::cout << "GetName[" << MOONG::FileInformation::GetName("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe").c_str() << "]\n" << std::endl;
	std::cout << "GetName[" << MOONG::FileInformation::GetName("C:/Program Files/Google/Chrome/Application/chrome.exe").c_str() << "]\n" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "GetNameWithoutFileExtension[" << MOONG::FileInformation::GetNameWithoutFileExtension().c_str() << "]\n" << std::endl;
	std::cout << "GetNameWithoutFileExtension[" << MOONG::FileInformation::GetNameWithoutFileExtension("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe").c_str() << "]\n" << std::endl;
	std::cout << "GetNameWithoutFileExtension[" << MOONG::FileInformation::GetNameWithoutFileExtension("C:/Program Files/Google/Chrome/Application/chrome.exe").c_str() << "]\n" << std::endl;
	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	
	std::cout << "GetFolderName[" << MOONG::FileInformation::GetFolderName().c_str() << "]\n" << std::endl;
	std::cout << "GetFolderName[" << MOONG::FileInformation::GetFolderName("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe").c_str() << "]\n" << std::endl;
	std::cout << "GetFolderName[" << MOONG::FileInformation::GetFolderName("C:/Program Files/Google/Chrome/Application/chrome.exe").c_str() << "]\n" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "GetVersion[" << MOONG::FileInformation::GetVersion().c_str() << "]\n" << std::endl;
	std::cout << "GetVersion[" << MOONG::FileInformation::GetVersion("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe").c_str() << "]\n" << std::endl;
	std::cout << "GetVersion[" << MOONG::FileInformation::GetVersion("C:/Program Files/Google/Chrome/Application/chrome.exe").c_str() << "]\n" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "GetSize[" << MOONG::FileInformation::GetSize() << "]\n" << std::endl;
	std::cout << "GetSize[" << MOONG::FileInformation::GetSize("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe") << "]\n" << std::endl;
	std::cout << "GetSize[" << MOONG::FileInformation::GetSize("C:/Program Files/Google/Chrome/Application/chrome.exe") << "]\n" << std::endl;

	system("pause");

	return 0;
}