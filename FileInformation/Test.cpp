#include "FileInformation.h"

int main()
{
	//std::cout << "get_path[" << MOONG::FileInformation::get_path().c_str() << "]\n" << std::endl;
	//std::cout << "get_path[" << MOONG::FileInformation::get_path(MOONG::FileInformation::get_file_handle("C:/Program Files/Google/Chrome/Application/chrome.exe")).c_str() << "]\n" << std::endl;
	//
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//
	//std::cout << "get_file_handle[" << MOONG::FileInformation::get_file_handle() << "]\n" << std::endl;
	//std::cout << "get_file_handle[" << MOONG::FileInformation::get_file_handle("C:/Program Files/Google/Chrome/Application/chrome.exe") << "]\n" << std::endl;
	//
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;

	//SYSTEMTIME creationTime = MOONG::FileInformation::get_creation_time();
	//std::cout << "Year[" << creationTime.wYear << "], month[" << creationTime.wMonth << "], day[" << creationTime.wDay << "], hour[" << creationTime.wHour << "], min[" << creationTime.wMinute << "], sec[" << creationTime.wSecond << "]\n" << std::endl;
	//
	//creationTime = MOONG::FileInformation::get_creation_time("C:/Program Files/Google/Chrome/Application/chrome.exe");
	//std::cout << "Year[" << creationTime.wYear << "], month[" << creationTime.wMonth << "], day[" << creationTime.wDay << "], hour[" << creationTime.wHour << "], min[" << creationTime.wMinute << "], sec[" << creationTime.wSecond << "]\n" << std::endl;

	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;

	//std::cout << "get_name[" << MOONG::FileInformation::get_name().c_str() << "]\n" << std::endl;
	//std::cout << "get_name[" << MOONG::FileInformation::get_name("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe").c_str() << "]\n" << std::endl;
	//std::cout << "get_name[" << MOONG::FileInformation::get_name("C:/Program Files/Google/Chrome/Application/chrome.exe").c_str() << "]\n" << std::endl;

	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;

	//std::cout << "get_name_without_file_extension[" << MOONG::FileInformation::get_name_without_file_extension().c_str() << "]\n" << std::endl;
	//std::cout << "get_name_without_file_extension[" << MOONG::FileInformation::get_name_without_file_extension("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe").c_str() << "]\n" << std::endl;
	//std::cout << "get_name_without_file_extension[" << MOONG::FileInformation::get_name_without_file_extension("C:/Program Files/Google/Chrome/Application/chrome.exe").c_str() << "]\n" << std::endl;
	//
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	//
	//std::cout << "get_folder_name[" << MOONG::FileInformation::get_folder_name().c_str() << "]\n" << std::endl;
	//std::cout << "get_folder_name[" << MOONG::FileInformation::get_folder_name("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe").c_str() << "]\n" << std::endl;
	//std::cout << "get_folder_name[" << MOONG::FileInformation::get_folder_name("C:/Program Files/Google/Chrome/Application/chrome.exe").c_str() << "]\n" << std::endl;

	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;

	//std::cout << "get_version[" << MOONG::FileInformation::get_version().c_str() << "]\n" << std::endl;
	//std::cout << "get_version[" << MOONG::FileInformation::get_version("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe").c_str() << "]\n" << std::endl;
	//std::cout << "get_version[" << MOONG::FileInformation::get_version("C:/Program Files/Google/Chrome/Application/chrome.exe").c_str() << "]\n" << std::endl;

	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;

	//std::cout << "get_size[" << MOONG::FileInformation::get_size() << "]\n" << std::endl;
	//std::cout << "get_size[" << MOONG::FileInformation::get_size("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe") << "]\n" << std::endl;
	//std::cout << "get_size[" << MOONG::FileInformation::get_size("C:/Program Files/Google/Chrome/Application/chrome.exe") << "]\n" << std::endl;

	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;

	std::cout << "is_exist[" << MOONG::FileInformation::is_exist("df") << "]\n" << std::endl;
	std::cout << "is_exist[" << MOONG::FileInformation::is_exist("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe") << "]\n" << std::endl;
	std::cout << "is_exist[" << MOONG::FileInformation::is_exist("C:/Program Files/Google/Chrome/Application/chrome.exe") << "]\n" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	system("pause");

	return 0;
}