#include <stdio.h>
#include <windows.h>
#include <iostream>

using namespace std;

// create a clone process and set the id
HANDLE startclone(char* some)
{
    // get the name of the exe
    TCHAR szFilename[MAX_PATH];
    GetModuleFileName(NULL, szFilename, MAX_PATH);

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));

    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;

    BOOL bCreateOk = CreateProcess(
        NULL,
        some,
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi);
    if (bCreateOk) {
        return pi.hProcess;
    }
    else {
        return INVALID_HANDLE_VALUE;
    }
}

int main(int argc, char* argv[])
{
    SYSTEMTIME system1;
    SYSTEMTIME system2;

    if (argc == 1) {
        printf("Please add the name of the execute.\n");
        exit(0);
    }
    else {
        GetSystemTime(&system1);
        HANDLE hchild = startclone(argv[1]);
        if (hchild != INVALID_HANDLE_VALUE) {
            WaitForSingleObject(hchild, INFINITE);
            printf("The child process had quit.\n");
            GetSystemTime(&system2);
            printf("Cost: %d (s) %d (ms)\n", (system2.wSecond - system1.wSecond), (system2.wMilliseconds - system1.wMilliseconds));
        }
        else {
            printf("Create child process failed.\n");
        }
    }
    return 0;
}