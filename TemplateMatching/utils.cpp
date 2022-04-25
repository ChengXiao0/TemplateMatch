#include "utils.h"
#pragma comment(lib, "User32.lib")
using namespace std;

vector<string> imgList(string path)
{
    vector<string> list;
    WIN32_FIND_DATA ffd;
    LARGE_INTEGER filesize;
    TCHAR szDir[MAX_PATH];
    size_t length_of_arg;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    _tprintf(TEXT("\nTarget directory is %s\n\n"), path.c_str());
    StringCchCopy(szDir, MAX_PATH, path.c_str());
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

    // Find the first file in the directory.

    hFind = FindFirstFile(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
    {
    }

    // List all the files in the directory with some info about them.

    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            //_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
        }
        else
        {
            filesize.LowPart = ffd.nFileSizeLow;
            filesize.HighPart = ffd.nFileSizeHigh;
            //_tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
            string filename = ffd.cFileName;
            list.push_back(filename);
        }
    } while (FindNextFile(hFind, &ffd) != 0);
    FindClose(hFind);
    return list;
}