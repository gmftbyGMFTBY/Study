#include<iostream>
#include<cstdio>
#include<windows.h>
#include<tchar.h>
#include<psapi.h>
#include<tlhelp32.h>
#include<shlwapi.h>
#include<iomanip>
#include"conio.h"
#include <string.h>
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "Shlwapi.lib")

using namespace std;

int PIDEXE = 0;

#define WIDTH 10
#define DIV (1024*1024)

// compile error: g++ main.cpp -lpsapi -lshlwapi

// the console get function is admired by someone on the internet

// console_gotxy / console_getxy 函数分贝使使用 3 中系统调用，实现对终端的实时打印预览
// set the console for the terminal
void console_gotoxy(int x, int y)
{
	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursor = { x, y };
	SetConsoleCursorPosition(hc, cursor);
}


// get the console from the terminal
void console_getxy(int& x, int& y)
{
	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hc, &csbi);
	x = csbi.dwCursorPosition.X;
	y = csbi.dwCursorPosition.Y;
}

// open the process and return the handle
HANDLE GetProcessHandle(int ProcessID)
{
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
}

inline bool TestSet(DWORD dwTarget, DWORD dwMask)
{
	return ((dwTarget &dwMask) == dwMask);
}

// get the message about VM on just one 
// hProcess is the process's handle
void WalkVM(HANDLE hProcess)
{
	SYSTEM_INFO si;                     
	ZeroMemory(&si, sizeof(si));		
	GetSystemInfo(&si);                 
	MEMORY_BASIC_INFORMATION mbi;       
	
	// init the buffer space
	ZeroMemory(&mbi, sizeof(mbi));      
	LPCVOID pBlock = (LPVOID)si.lpMinimumApplicationAddress;

	while (pBlock < si.lpMaximumApplicationAddress) {
		if (VirtualQueryEx(hProcess,           
			pBlock,                            
			&mbi,                              
			sizeof(mbi)) == sizeof(mbi)) {
			
			LPCVOID pEnd = (PBYTE)pBlock + mbi.RegionSize;
			TCHAR szSize[MAX_PATH];
			StrFormatByteSize(mbi.RegionSize, szSize, MAX_PATH);

			// show
			cout.fill('0');
			cout << hex << setw(8) << (DWORD)pBlock
				<< "--"
				<< hex << setw(8) << (DWORD)pEnd
				<< (strlen(szSize) == 7 ? " (" : " (") << szSize
				<< ") ";
			
			// show the status about the block in the process
			switch (mbi.State) {
				case MEM_COMMIT:printf(" Committed"); break;
				case MEM_FREE:printf(" Free"); break;
				case MEM_RESERVE:printf(" Reserved"); break;
			}

			// show the type
			switch (mbi.Type) {
				case MEM_IMAGE:printf(", Image"); break;
				case MEM_MAPPED:printf(", Mapped"); break;
				case MEM_PRIVATE:printf(", Private"); break;
			}

			printf("\n");
			// get the next block
			pBlock = pEnd;
		}
	}
}

// get the system message
void ShowProcessAddress()
{
	int lineX = 0, lineY = 0;
	int flag = 0;
	SYSTEM_INFO sys_info;	  // system_info message, save the sys_info
	ZeroMemory(&sys_info, sizeof(sys_info));	// init the sys_info struct
	while (!kbhit())
	{
		// use (win api) to flush buffer
		if (flag == 0) {
			console_getxy(lineX, lineY);
			flag++;
		}
		else {
			console_gotoxy(lineX, lineY);
		}

		// get the system message
		GetSystemInfo(&sys_info);
		printf("Page Size: %d KB\n", sys_info.dwPageSize / 1024);
		printf("Proc_num: %d\n", sys_info.dwNumberOfProcessors);
		printf("Arti_cpu: %d\n", sys_info.dwProcessorType);
		printf("Vm_fineness: %d KB\n", sys_info.dwAllocationGranularity / 1024);
		printf("Min_application: 0x%0.8x\n", sys_info.lpMinimumApplicationAddress);
		printf("Max_application: 0x%0.8x\n", sys_info.lpMaximumApplicationAddress);
		printf("Valiable_vm: %0.2f GB\n", ((DWORD)sys_info.lpMaximumApplicationAddress
			- (DWORD)sys_info.lpMinimumApplicationAddress) / (1024.0*1024.0*1024.0));
		Sleep(1000);
	}
}

// show the meomry
void ShowMemory()
{
	int lineX = 0, lineY = 0;
	int flag = 0;
	MEMORYSTATUS total;
	total.dwLength = sizeof(total);
	while (!kbhit())
	{
		if (flag == 0) {
			console_getxy(lineX, lineY);
			flag++;
		}
		else {
			console_gotoxy(lineX, lineY);
		}
		
		// get the memory 
		GlobalMemoryStatus(&total);
		printf("All memory: %f MB\n", total.dwTotalPhys / DIV);
		printf("Avaliable meomry: %d MB\n", total.dwAvailPhys / DIV);
		printf("Virtual Memory: %f MB\n", (total.dwTotalVirtual / DIV));
		printf("Avaiable VM: %f MB\n", (total.dwAvailVirtual / DIV));
		Sleep(1000);
	}
}

// GET the system
void ShowPerformance()
{
	int lineX = 0, lineY = 0;
	int flag = 0;
	// create the performance information struct
	PERFORMANCE_INFORMATION perfor_info;
	perfor_info.cb = sizeof(perfor_info);

	while (!kbhit())
	{
		// use (win api) to flush
		if (flag == 0) {
			console_getxy(lineX, lineY);
			flag++;
		}
		else {
			console_gotoxy(lineX, lineY);
		}
		GetPerformanceInfo(&perfor_info, sizeof(perfor_info));
		printf("Page Size: %d KB\n", perfor_info.PageSize / 1024);
		printf("All Pages: %d\n", perfor_info.CommitTotal);
		printf("Page limite: %d\n", perfor_info.CommitLimit);
		printf("Memory [page]: %d\n", perfor_info.PhysicalTotal);
		printf("Memory avaliable [page]: %d\n", perfor_info.PhysicalAvailable);
		printf("Memory used: %f GB\n", (perfor_info.PhysicalTotal - perfor_info.PhysicalAvailable)*(perfor_info.PageSize / 1024)*1.0 / DIV);
		printf("Memory avaliable: %f GB\n", perfor_info.PhysicalAvailable*(perfor_info.PageSize / 1024)*1.0 / DIV);
		printf("Memory all: %f GB\n", perfor_info.PhysicalTotal*(perfor_info.PageSize / 1024)*1.0 / DIV);
		printf("Kernel pages: %f\n", perfor_info.KernelTotal);
		printf("Handle number: %f\n", perfor_info.HandleCount);
		printf("Process number: %f\n", perfor_info.ProcessCount);
		printf("Thread number: %f\n", perfor_info.ThreadCount);
		Sleep(1000);
	}
}


// pid = -1, get all the process
void ShowAllProcess(int pid)
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	PROCESS_MEMORY_COUNTERS ppsmemCounter;
	ppsmemCounter.cb = sizeof(ppsmemCounter);
	HANDLE hProcessSnap;

	// get the snapshoot
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	HANDLE hProcess;
	

	// iterate the process handle
	// the first process handle
	BOOL bMore = Process32First(hProcessSnap, &pe32);
	
	printf("The message about process: \n");
	while (bMore) {
		if (pid != -1) {
			if (pid == pe32.th32ProcessID) {
				printf("PName: %s\n", pe32.szExeFile);		// save in pe32 struct
				printf("PID: %d\n", pe32.th32ProcessID);

				printf("ThreadNum: %d\n", pe32.cntThreads);
				
				// get the memory used status about this process
				hProcess = GetProcessHandle(pe32.th32ProcessID);
				GetProcessMemoryInfo(hProcess, &ppsmemCounter, sizeof(ppsmemCounter)); 
				printf("Used: %f KB\n", ppsmemCounter.PagefileUsage / 1024);
				printf("WorkSet [Page used]: %f KB\n", ppsmemCounter.WorkingSetSize / 1024);
			}
			// get the next handle about the process
			bMore = Process32Next(hProcessSnap, &pe32);
		}
		else {
			printf("PName: %s\n", pe32.szExeFile);		// save in pe32 struct
			printf("PID: %d\n", pe32.th32ProcessID);
			printf("ThreadNum: %d\n", pe32.cntThreads);
				
			// get the memory used status about this process
			hProcess = GetProcessHandle(pe32.th32ProcessID);
			GetProcessMemoryInfo(hProcess, &ppsmemCounter, sizeof(ppsmemCounter));//进程内存使用信息（存储于ppsmemCounter中）
			printf("Used: %f KB\n", ppsmemCounter.PagefileUsage / 1024);
			printf("WorkSet [Page used]: %f KB\n", ppsmemCounter.WorkingSetSize / 1024);

			bMore = Process32Next(hProcessSnap, &pe32);
		}
	}
	CloseHandle(hProcessSnap);
}


// search for just one handle by PID
void QuerySingleProcess()
{
	int lineX = 0, lineY = 0;
	int flag = 0;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	HANDLE hProcess;

	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		printf("Can not get the handle of this process, maybe PID is wrong!\n");
		return ;
	}

	printf("Input: ");
	scanf("%d", &PIDEXE);
	hProcess = GetProcessHandle(PIDEXE);

	if (hProcess == INVALID_HANDLE_VALUE) {
		printf("Can not get the handle of this process, maybe PID is wrong!\n");
		return ;
	}

	ShowAllProcess(PIDEXE);
	WalkVM(hProcess);
	Sleep(1000);
	CloseHandle(hProcess);
}

int main()
{
	printf("Begin the process the check the system.\n");
	while (true) {
		int mode = 0;

		printf("1. Process ...\n");
		printf("2. System ...\n");
		printf("3. Memory ...\n");
		printf("4. Detail about all the process ...\n");
		printf("5. Show %d process (a.exe).\n", PIDEXE);
		printf("Cmd: ");
		scanf("%d", &mode);
		switch (mode) {
			case 1: ShowProcessAddress(); break;
			case 2: ShowPerformance(); break;
			case 3: ShowMemory(); break;
			case 4: ShowAllProcess(-1); break;
			// seach for a.exe
			case 5: QuerySingleProcess(); break;
			default: printf("something wrong, input again ...\n");
		}
	}
	return 0;
}
