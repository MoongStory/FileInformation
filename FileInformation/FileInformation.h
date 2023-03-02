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
		// handle 값을 NULL을 넘기면 현재 프로세스의 핸들로 동작.
		static const SYSTEMTIME GetCreationTime(const HANDLE handle = NULL);
		static const std::string GetPath(const HANDLE handle = NULL);
		static const std::string GetName(const HANDLE handle = NULL);
		static const std::string GetNameWithoutFileExtension(const HANDLE handle = NULL);

		static const std::string GetFolderName(const HANDLE handle = NULL);

		// file_path를 빈 문자열을 넘기면 현재 프로세스의 버전을 얻음.
		static const std::string GetVersion(const std::string param_file_path = "");

		static const HANDLE GetHandle(const std::string file_name = "");
		static const long GetSize(const std::string file_path = "");
	protected:
	private:
	};
}
#endif	// _FILE_INFO_H_