#include "FileInformation.h"

#include "../../StringTool/StringTool/StringTool.h"

#include <sstream>
#include <string>

#include <Psapi.h>	// GetProcessImageFileNameA
#pragma comment(lib, "Psapi.lib")

#pragma comment(lib, "Comdlg32.lib")	// GetFileTitle

#pragma comment(lib,"version.lib")		// GetFileVersionInfo

#include <strsafe.h>

#ifndef _countof
	#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

const SYSTEMTIME MOONG::FileInformation::get_creation_time(const std::string file_path/* = ""*/)
{
	SYSTEMTIME local_time = { 0 };

	HANDLE process_handle = MOONG::FileInformation::get_file_handle(file_path);
	if(process_handle == INVALID_HANDLE_VALUE)
	{
		return local_time;
	}
	
	FILETIME creation_time = { 0 };
	FILETIME last_access_time = { 0 };
	FILETIME last_write_time = { 0 };
	
	GetFileTime(process_handle, &creation_time, &last_access_time, &last_write_time);

	CloseHandle(process_handle);
	
	SYSTEMTIME system_time = { 0 };
	FileTimeToSystemTime(&creation_time, &system_time);
	SystemTimeToTzSpecificLocalTime(NULL, &system_time, &local_time);
	
	return local_time;
}

const std::string MOONG::FileInformation::get_path(const HANDLE param_file_handle/* = NULL*/)
{
	char output[MAX_PATH + 1] = { 0 };

	HANDLE file_handle = NULL;

	if (NULL == param_file_handle)
	{
		char self_path[MAX_PATH] = { 0 };
		GetModuleFileNameA(NULL, self_path, sizeof(self_path));
		file_handle = CreateFileA(self_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (file_handle == INVALID_HANDLE_VALUE)
		{
			return std::string("open fail[") + std::string(self_path) + std::string("]");
		}
	}
	else
	{
		file_handle = param_file_handle;
	}

	HANDLE hFileMap = NULL;

	// Get the file size.
	DWORD dwFileSizeHi = 0;
	DWORD dwFileSizeLo = GetFileSize(file_handle, &dwFileSizeHi);

	if (dwFileSizeLo == 0 && dwFileSizeHi == 0)
	{
		return "Cannot map a file with a length of zero.";
	}

	// Create a file mapping object.
	hFileMap = CreateFileMapping(file_handle,
		NULL,
		PAGE_READONLY,
		0,
		1,
		NULL);

	// param_file_handle이 NULL일때만 CloseHandle 해야되나...?
	CloseHandle(file_handle);

	if (hFileMap)
	{
		// Create a file mapping to get the file name.
		void* pMem = MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 1);

		if (pMem)
		{
			if (GetMappedFileNameA(GetCurrentProcess(),
				pMem,
				output,
				MAX_PATH))
			{
				// Translate path with device name to drive letters.
				char szTemp[512] = { 0 };

				if (GetLogicalDriveStringsA(_countof(szTemp) - 1, szTemp))
				{
					char szName[MAX_PATH] = { 0 };
					char szDrive[3] = " :";
					bool bFound = FALSE;
					char* p = szTemp;

					do
					{
						// Copy the drive letter to the template string
						*szDrive = *p;

						// Look up each device name
						if (QueryDosDeviceA(szDrive, szName, MAX_PATH))
						{
							size_t uNameLen = strlen(szName);

							if (uNameLen < MAX_PATH)
							{
								bFound = _strnicmp(output, szName, uNameLen) == 0 && *(output + uNameLen) == '\\';

								if (bFound)
								{
									StringCchPrintfA(output,
										_countof(output),
										"%s%s",
										szDrive,
										output + uNameLen);
								}
							}
						}

						// Go to the next NULL character.
						while (*p++);
					} while (!bFound && *p); // end of string
				}
			}
			
			UnmapViewOfFile(pMem);
		}

		CloseHandle(hFileMap);
	}

	return output;
}

const std::string MOONG::FileInformation::get_directory(std::string file_path/* = ""*/)
{
	if (file_path.length() <= 0)
	{
		file_path = MOONG::FileInformation::get_path();
	}

	if (MOONG::StringTool::find_index_rightmost(file_path, "\\/") == std::string::npos)
	{
		return std::string();
	}

	return MOONG::StringTool::cut_right_keep_origin(file_path.length() <= 0 ? MOONG::FileInformation::get_path() : file_path, "\\/");
}

const std::string MOONG::FileInformation::get_extension(std::string file_path/* = ""*/)
{
	if (file_path.length() <= 0)
	{
		file_path = MOONG::FileInformation::get_path();
	}

	MOONG::StringTool::cut_left(file_path, "\\/");

	size_t index = MOONG::StringTool::find_index_rightmost(file_path, '.');

	if (index == std::string::npos)
	{
		return std::string();
	}

	return file_path.substr(index + 1);
}

const std::string MOONG::FileInformation::get_name(const std::string file_path/* = ""*/)
{
	return MOONG::StringTool::pop_right_keep_origin(file_path.length() <= 0 ? MOONG::FileInformation::get_path() : file_path, "\\/");
}

const std::string MOONG::FileInformation::get_name_without_extension(const std::string file_path/* = ""*/)
{
	return MOONG::StringTool::cut_right_keep_origin(MOONG::FileInformation::get_name(file_path), ".");
}

const std::string MOONG::FileInformation::get_folder_name(const std::string file_path/* = ""*/)
{
	std::string folder_name = file_path.length() <= 0 ? MOONG::FileInformation::get_path() : file_path;

	folder_name = folder_name.substr(0, MOONG::StringTool::find_index_rightmost(folder_name, "\\/"));

	folder_name = folder_name.substr(MOONG::StringTool::find_index_rightmost(folder_name, "\\/") + 1);
	
	return std::string(folder_name);
}

const std::string MOONG::FileInformation::get_version(const std::string param_file_path/* = ""*/)
{
	std::string file_path = "";

	if (param_file_path.empty() == true)
	{
		file_path = MOONG::FileInformation::get_path();
	}
	else
	{
		file_path = param_file_path;
	}

	DWORD ver_info_size = GetFileVersionInfoSizeA(file_path.c_str(), 0);
	if (ver_info_size == 0)
	{
		return std::string();
	}

	char file_version[64] = { 0 };

	char* ver_info = new char[ver_info_size];
	if (ver_info)
	{
		if (GetFileVersionInfoA(file_path.c_str(), 0, ver_info_size, ver_info) != 0)
		{
			VS_FIXEDFILEINFO* fixed_file_info = NULL;
			UINT buf_len = 0;

			if (VerQueryValueA(ver_info, "\\", (LPVOID*)&fixed_file_info, &buf_len) != 0)
			{
				WORD major_ver = 0, minor_ver = 0, build_num = 0, revision_num = 0;

				major_ver = HIWORD(fixed_file_info->dwFileVersionMS);
				minor_ver = LOWORD(fixed_file_info->dwFileVersionMS);
				build_num = HIWORD(fixed_file_info->dwFileVersionLS);
				revision_num = LOWORD(fixed_file_info->dwFileVersionLS);

				StringCchPrintfA(file_version, sizeof(file_version), "%d.%d.%d.%d", major_ver, minor_ver, build_num, revision_num);
			}
		}

		delete[] ver_info;
	}

	return file_version;
}

const HANDLE MOONG::FileInformation::get_file_handle(const std::string file_path/* = ""*/)
{
	if(file_path.length() <= 0)
	{
		return CreateFileA(MOONG::FileInformation::get_path().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	return CreateFileA(file_path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

const LONGLONG MOONG::FileInformation::get_size(const std::string file_path/* = ""*/)
{
	LARGE_INTEGER file_size = {0};

	HANDLE file_handle = MOONG::FileInformation::get_file_handle(file_path);

	GetFileSizeEx(file_handle, &file_size);

	CloseHandle(file_handle);

	return file_size.QuadPart;
}

const bool MOONG::FileInformation::is_exist(const std::string file_path)
{
	HANDLE handle = CreateFileA(file_path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == handle)
	{
		return false;
	}

	CloseHandle(handle);

	return true;
}
