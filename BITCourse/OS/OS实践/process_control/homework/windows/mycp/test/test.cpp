#include <iostream>
#include <windows.h>

using namespace std;

void copySelf()
{
	char szSelfName[MAX_PATH] ;
	char szDestName[MAX_PATH] ;
	char szSystemPath[MAX_PATH] ;
	char szWindowPath[MAX_PATH] ;
	GetModuleFileName(NULL,szSelfName,MAX_PATH);
	printf("%s\n", szSelfName);
	strcpy(szDestName,"C:\\Users\\GMFTBY\\Desktop\\experiment\\mycp");
	strcat(szDestName,"\\va_test.exe");
	if(CopyFile(szSelfName,szDestName,FALSE)) {
		printf("Copy!");
	}
}

int main()
{
	copySelf();
	return 0;
}
