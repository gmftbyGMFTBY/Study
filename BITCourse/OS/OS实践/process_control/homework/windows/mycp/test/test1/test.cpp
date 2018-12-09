#include <stdio.h>
#include <windows.h>
#include <cstring>

using namespace std;

BOOL IsDirectory(const char *pDir)
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
        printf("%s\n", FindFileData.cFileName);
		return FALSE;
	}
    else {
		FindClose(hFile);
        printf("%s\n", FindFileData.cFileName);
		return TRUE;
	}
}

/*
// delete the file
BOOL DeleteDirectory(const char * DirName)
{
    //	CFileFind tempFind;		//声明一个CFileFind类变量，以用来搜索
	char szCurPath[MAX_PATH];		//用于定义搜索格式
	_snprintf(szCurPath, MAX_PATH, "%s//*.*", DirName);	//匹配格式为*.*,即该目录下的所有文件
	WIN32_FIND_DATAA FindFileData;
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));
	HANDLE hFile = FindFirstFileA(szCurPath, &FindFileData);
	BOOL IsFinded = TRUE;
	while(IsFinded) {
		IsFinded = FindNextFileA(hFile, &FindFileData);	//递归搜索其他的文件
 		if( strcmp(FindFileData.cFileName, ".") && strcmp(FindFileData.cFileName, "..") ) //如果不是"." ".."目录
 		{
			string strFileName = "";
			strFileName = strFileName + DirName + "//" + FindFileData.cFileName;
			string strTemp;
			strTemp = strFileName;
			if( IsDirectory(strFileName.c_str()) ) //如果是目录，则递归地调用 
            {
				printf("目录为:%s/n", strFileName.c_str());
				DeleteDirectory(strTemp.c_str());
			}
			else {
				DeleteFileA(strTemp.c_str());
			}
		}
	}
	FindClose(hFile);
	BOOL bRet = RemoveDirectoryA(DirName);
	if( bRet == 0 ) //删除目录
	{
		printf("删除%s目录失败！/n", DirName);
		return FALSE;
	}
	return TRUE;
}
*/

int main(int argc, char* argv[])
{
    if (IsDirectory(".\\")) {
        printf("Yes\n");
    }
    else {
        printf("No\n");
    }
    return 0;
}