/*******************************************************************************
MIT License

Copyright (c) 2023 Moong

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

// https://github.com/MoongStory/FileInformation

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _FILE_INFO_H_
#define _FILE_INFO_H_

#include <iostream>
#include <Windows.h>

namespace MOONG
{
	class FileInformation
	{
	public:
	protected:
	private:

	public:
		// HANDLE 또는 path를 NULL 또는 빈 문자열로 넘기면 자기 자신을 대상으로 함.
		static const std::string get_path(const HANDLE param_file_handle = NULL);

		static const HANDLE get_file_handle(const std::string& file_path = "");

		static const SYSTEMTIME get_creation_time(const std::string& file_path = "");

		static const std::string get_name(std::string file_path = "");
		static const std::string get_name_without_file_extension(std::string file_path = "");

		static const std::string get_folder_name(std::string file_path = "");

		static const std::string get_version(const std::string param_file_path = "");

		static const LONGLONG get_size(const std::string file_path = "");
	protected:
	private:
	};
}
#endif	// _FILE_INFO_H_