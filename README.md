# UniFixHM
为Vnsi edit编辑器提供包括Unicode编码文本文件支持

Provides support for the Vnsi edit editor including Unicode-encoded text files

中文说明参见“说明_中文.txt”

The author's native language is Chinese, and this description is an AI-generated translation

#################################

#0 Quick Start: For General Users

If you are not a developer, you can follow these steps to quickly use this patch without reading the rest:

a. Copy version.dll to vnsiedit.exe in the same directory

b. Run VNIS Edit again, and the patch will take effect (it may trigger an antivirus alarm, please allow it to run).



#################################

#1 Project Overview

This project, named UniFixHM, is a Unicode patch provided for VNIS Edit. Here is its detailed description:

HM NIS Edit (also known as VNIS Edit) is an open-source software designed to provide an easy-to-use GUI editor for NSIS.

It was originally developed by Hector Mauricio Rodriguez Segura from Costa Rica, using Delphi 5 and designed for the Win32 system. Since 2005, no updates have been released for this software.

The purpose of UniFixHM is to solve the problem of HM NIS Edit being unable to correctly open Unicode encoded files due to its age.

Because the development environment of the software is too outdated, the author cannot recompile its source code, so a more redundant patch method was adopted to achieve this function.



#################################

#2 Basic Information

Compilation System: Windows LTSC 2019; Version number 10.0.17763.5206

IDE: Visual Studio 2022 Community Edition

Main Language: C++

Operating Environment: Windows XP or newer versions

Libraries Used: C++ Standard Library, Windows API Library, Detours (Detours included in the project files)



#################################

#3 Functional Implementation

This patch sets hooks on WINAPI ReadFile, WriteFile, and SetFilePointer by hooking the WinAPI, and inserts code to support Unicode encoding.

A function with the prefix "DT_" followed by the winapi function name is a hook function of the corresponding winapi that takes over the work of the corresponding winapi, which is briefly described below:


DT_ReadFile: Check if it is an NSIS script file, if so, check its encoding and transcoding, otherwise it will be processed as normal.

DT_WriteFile: Converts the data output from the editor to UTF-8 encoding and writes to the BOM and transcoded data.

DT_SetFilePointer: Check whether it is a NSIS script file and it is an operation to get the file size, if so, return the size of the transcoded data instead of the file size, otherwise it will be processed according to the normal process.



#################################

#4 Main document description:

│ UniFixHM.sln		Main project file

│ version.dll		A compiled example file

└─ UniFixHM			Main project folder

      Conv.cpp		Encoding conversion implementation
      
      Conv.h 		Encoding conversion definitions
      
      dllmain.cpp		DLL main file: Defines the DLL entry point
      
      hook.cpp		Hook implementation
      
      hook.h		Hook definitions



#################################

#5 Author

This project is developed by 3-5105.

Contact email: h0910262022@163.com

Any valuable opinions, criticisms, and suggestions are welcome.



#################################

#6 License

Uses the MIT License
