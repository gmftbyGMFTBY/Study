#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) 
{
    SYSTEM_INFO si;
    ZeroMemory(&si, sizeof(si));
    GetSystemInfo(&si);

    TCHAR szpagesize[MAX_PATH];

    DWORD dwMemSize = (DWORD)si.lpMaximumApplicationAddress - (DWORD)si.lpMinimumApplicationAddress;
    TCHAR szMemSize[MAX_PATH];

    printf("Virtual memory page size: %d\n", si.dwPageSize);
    printf("Minimum application address: %ld\n", (DWORD)si.lpMinimumApplicationAddress);
    printf("Maximum application address: %ld\n", (DWORD)si.lpMaximumApplicationAddress);
    printf("Total available virtual memory: %d\n", dwMemSize);
    return 0;
}