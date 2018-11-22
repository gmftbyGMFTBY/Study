#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

void createdir(char* path)
{
    // create the dir
    if (!CreateDirectory(_T(path), NULL)) {
        printf("create error.\n");
    }
    else {
        printf("create successfully %s.\n", path);
    }
}

void copyfile2(char* source, char* dest)
{
    if(CopyFile(source, dest, FALSE)) {
		printf("Copy successfully %s -> %s!\n", source, dest);
	}
    else {
        printf("Copy failed!\n");
    }
}

void getcurrentpath(char* path)
{
    // return the path with the \ at the end 
    int length;
    GetModuleFileName(NULL, path, MAX_PATH);
    length = strlen(path);
    int flag = 0;
    for (int i = 0; i < length ;i++) {
        if (path[i] == '\\') {
            flag = i;
        }
    }
    path[flag + 1] = '\0';
}

BOOL IsDirectory(char *pDir)
{
    // if can find the first file, this is a dicectory
    // if not, this is a normal file
    // dir - True, file - False

	char szCurPath[500];
	ZeroMemory(szCurPath, 500);
	sprintf(szCurPath, "%s//*", pDir);
	WIN32_FIND_DATAA FindFileData;
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));
    HANDLE hFile = FindFirstFileA(szCurPath, &FindFileData);
    if( hFile == INVALID_HANDLE_VALUE ) {
		FindClose(hFile);
		return FALSE;
	}
    else {
		FindClose(hFile);
		return TRUE;
	}
}

void dir2dir(char* source, char* dest)
{
    char psource[MAX_PATH];
	_snprintf(psource, MAX_PATH, "%s//*", source);
    printf("%s -> %s\n", source, psource);
    // move the dir and the files into the dest dir
	WIN32_FIND_DATAA FindFileData;
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));
	HANDLE hFile = FindFirstFileA(psource, &FindFileData);
	BOOL IsFinded = TRUE;

    while (IsFinded) {
        // find the next file
        IsFinded = FindNextFileA(hFile, &FindFileData);
        if(!(strcmp(FindFileData.cFileName, ".") && strcmp(FindFileData.cFileName, ".."))) {
            continue;
        }
        char pp[MAX_PATH];
        char ww[MAX_PATH];
        _snprintf(pp, MAX_PATH, "%s\\%s", source, FindFileData.cFileName);
        _snprintf(ww, MAX_PATH, "%s\\%s", dest, FindFileData.cFileName);
        if (IsDirectory(pp)) {
            createdir(ww);
            dir2dir(pp, ww);
        }
        else {
            copyfile2(pp, ww);
        }
        // if (IsDirectory())
    }
}

int main(int argc, char* argv[])
{
    // must use the full path
    char path[MAX_PATH];
    memset(path, '\0', sizeof(path));
    char source[MAX_PATH];
    char dest[MAX_PATH];
    int flag = 0;   // 0 - dest dir do not exist, 1 - dest dir exist
    // char dirname[] = "C:\\Users\\GMFTBY\\Desktop\\experiment\\mycp\\test";
    // createdir(dirname);
    getcurrentpath(path);

    // check the source dir exist
    if (!IsDirectory(argv[1])) {
        printf("source do not exist.\n");
        exit(0);
    }

    // check the dest dir exist, if exist move to the dest folder, if not create and move
    strcat(path, argv[1]);
    strcpy(source, path);
    memset(path, '\0', sizeof(path));
    getcurrentpath(path);

    if (IsDirectory(argv[2])) {
        flag = 1;
        strcat(path, argv[2]);
        strcpy(dest, path);
    }
    else {
        // create dir
        strcat(path, argv[2]);
        createdir(path);
        strcpy(dest, path);
        flag = 0;
    }

    printf("%s -> %s\n", source, dest);
    dir2dir(source, dest);
    return 0;
}