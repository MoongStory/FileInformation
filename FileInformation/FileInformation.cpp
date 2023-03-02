#include "FileInformation.h"

#include <sstream>
#include <string>

#include <Psapi.h>	// GetProcessImageFileNameA
#pragma comment(lib, "Psapi.lib")

#pragma comment(lib, "Comdlg32.lib")	// GetFileTitle

#pragma comment(lib,"version.lib")		// GetFileVersionInfo

#include <strsafe.h>

const SYSTEMTIME MOONG::FileInformation::GetCreationTime(const HANDLE handle/* = NULL*/)
{
	SYSTEMTIME local_time = { 0 };

	HANDLE process_handle = NULL;

	if (handle == NULL)
	{
		process_handle = MOONG::FileInformation::GetHandle(MOONG::FileInformation::GetName());
		if (process_handle == INVALID_HANDLE_VALUE)
		{
			return local_time;
		}
	}
	else
	{
		process_handle = handle;
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

const std::string MOONG::FileInformation::GetPath(const HANDLE handle/* = NULL*/)
{
	DWORD process_id = GetCurrentProcessId();
	HANDLE process_handle = NULL;
	
	if (handle == NULL)
	{
#if _MSC_VER > 1200
		process_handle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, process_id);
#else
		process_handle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, process_id);
#endif
	}
	else
	{
		process_handle = handle;
	}

	char file_path[MAX_PATH] = { 0 };
	DWORD buffer_size = sizeof(file_path);

	if (process_handle)
	{
#if _MSC_VER > 1200
		if (QueryFullProcessImageNameA(process_handle, 0, file_path, &buffer_size))
#else
		if (GetProcessImageFileNameA(process_handle, file_path, buffer_size))
#endif
		{
			// ¼º°ø
		}

		CloseHandle(process_handle);
	}

	return file_path;
}

const std::string MOONG::FileInformation::GetName(const HANDLE handle/* = NULL*/)
{
#if _MSC_VER > 1200
	char drive[_MAX_DRIVE] = { 0 };
	char dir[_MAX_DIR] = { 0 };
	char file_name[_MAX_FNAME] = { 0 };
	char file_extension[_MAX_EXT] = { 0 };

	_splitpath_s(MOONG::FileInformation::GetPath(handle).c_str(), drive, sizeof(drive), dir, sizeof(dir), file_name, sizeof(file_name), file_extension, sizeof(file_extension));

	return std::string(file_name) + std::string(file_extension);
#else
	char file_name[MAX_PATH] = {0};
	
	GetFileTitleA(MOONG::FileInformation::GetFilePath(handle).c_str(), file_name, sizeof(file_name));

	return file_name;
#endif
}

const std::string MOONG::FileInformation::GetNameWithoutFileExtension(const HANDLE handle/* = NULL*/)
{
	std::string file_name = MOONG::FileInformation::GetName(handle);

	return file_name.substr(0, file_name.find('.'));
}

const std::string MOONG::FileInformation::GetFolderName(const HANDLE handle/* = NULL*/)
{
	std::string folder_name = MOONG::FileInformation::GetPath(handle);

	folder_name = folder_name.substr(0, folder_name.find_last_of('\\'));

	folder_name = folder_name.substr(folder_name.find_last_of('\\') + 1);
	
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

const HANDLE MOONG::FileInformation::GetHandle(const std::string file_name)
{
	return CreateFileA(file_name.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

const long MOONG::FileInformation::GetSize(const std::string file_path)
{
	return 0;
}
