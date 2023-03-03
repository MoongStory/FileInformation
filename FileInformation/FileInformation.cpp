#include "FileInformation.h"

#include "../../StringTool/StringTool/StringTool.h"

#include <sstream>
#include <string>

#include <Psapi.h>	// GetProcessImageFileNameA
#pragma comment(lib, "Psapi.lib")

#pragma comment(lib, "Comdlg32.lib")	// GetFileTitle

#pragma comment(lib,"version.lib")		// GetFileVersionInfo

#include <strsafe.h>

const SYSTEMTIME MOONG::FileInformation::GetCreationTime(const std::string& file_path/* = ""*/)
{
	SYSTEMTIME local_time = { 0 };

	HANDLE process_handle = MOONG::FileInformation::GetFileHandle(file_path);
	if(process_handle == INVALID_HANDLE_VALUE)
	{
		return local_time;
	}
	
	FILETIME creation_time = { 0 };
	FILETIME last_access_time = { 0 };
	FILETIME last_write_time = { 0 };
	
	GetFileTime(process_handle, &creation_time, &last_access_time, &last_write_time);
	
	SYSTEMTIME system_time = { 0 };
	FileTimeToSystemTime(&creation_time, &system_time);
	SystemTimeToTzSpecificLocalTime(NULL, &system_time, &local_time);
	
	return local_time;
}

const std::string MOONG::FileInformation::GetPath(const HANDLE param_file_handle/* = NULL*/)
{
	char output[MAX_PATH + 1] = { 0 };

	HANDLE file_handle = NULL;

	if (NULL == param_file_handle)
	{
		char self_path[MAX_PATH] = { 0 };
		GetModuleFileNameA(NULL, self_path, sizeof(self_path));
		file_handle = CreateFileA(self_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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

const std::string MOONG::FileInformation::GetName(std::string file_path/* = ""*/)
{
	return MOONG::StringTool::pop_right_keep_origin(file_path.length() <= 0 ? MOONG::FileInformation::GetPath() : file_path, "\\/");
}

const std::string MOONG::FileInformation::GetNameWithoutFileExtension(std::string file_path/* = ""*/)
{
	std::string file_name = MOONG::FileInformation::GetName(file_path);

	return MOONG::StringTool::cut_right(file_name, ".");
}

const std::string MOONG::FileInformation::GetFolderName(std::string file_path/* = ""*/)
{
	std::string folder_name = file_path.length() <= 0 ? MOONG::FileInformation::GetPath() : file_path;

	folder_name = folder_name.substr(0, MOONG::StringTool::find_index_rightmost(folder_name, "\\/"));

	folder_name = folder_name.substr(MOONG::StringTool::find_index_rightmost(folder_name, "\\/") + 1);
	
	return std::string(folder_name);
}

const std::string MOONG::FileInformation::GetVersion(const std::string param_file_path/* = ""*/)
{
	std::string file_path;
	if (param_file_path.empty() == true)
	{
		file_path = MOONG::FileInformation::GetPath();
	}
	else
	{
		file_path = param_file_path;
	}

	DWORD ver_info_size = GetFileVersionInfoSizeA(file_path.c_str(), 0);
	if (ver_info_size == 0)
	{
		return std::string("");
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

const HANDLE MOONG::FileInformation::GetFileHandle(const std::string& file_path/* = ""*/)
{
	if(file_path.length() <= 0)
	{
		return CreateFileA(MOONG::FileInformation::GetPath().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	return CreateFileA(file_path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

const LONGLONG MOONG::FileInformation::GetSize(const std::string file_path/* = ""*/)
{
	LARGE_INTEGER file_size = {0};

	GetFileSizeEx(MOONG::FileInformation::GetFileHandle(file_path), &file_size);

	return file_size.QuadPart;
}
