#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>

// the temporarity string for the buffer
char pause[10];

#define ID_M        0

// producer id
#define ID_P_FROM   1
#define ID_P_TO     2

// customer id
#define ID_C_FROM   3
#define ID_C_TO     5

#define PROCESS_NUM 5

// the number of the tasks for producers and customers
#define WORKS_P     12
#define WORKS_C     8

// the size of the buffer and the name of the share memory
#define LETTER_NUM  6
#define SHM_NAME    "BUFFER"

struct mybuffer
{
    char text[LETTER_NUM][10];
    // the point (w - producer, r - constomer) for the buffer
    int head;
    int tail;
    int is_empty;
};

// share memory
struct sharemem
{
    struct mybuffer data;
    int index;          // the process index of the share memory
    HANDLE semEmpty;
    HANDLE semFull;
};

// file mapping object
static HANDLE hMapping;

// handle save the subprocess
static HANDLE hs[PROCESS_NUM + 1];

// get the randint from 0 ~ 5000
int get_random()
{
    int t;
    srand((unsigned)(GetCurrentProcessId() + time(NULL)));
    t = rand() % 5000;
    return t;
}

// get the random character
char get_letter()
{
    char a;
    srand(time(NULL));
    a = (char)((char)(rand() % 26) + 'A');
    return a;
}

// clone the main process
void StartClone(int nCloneID)
{
    char szFilename[MAX_PATH];
    char szCmdLine[MAX_PATH];
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    GetModuleFileName(NULL, szFilename, MAX_PATH);
    sprintf(szCmdLine, "\"%s\" %d", szFilename, nCloneID);
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    // create the subprocess
    BOOL bCreateOK = CreateProcess(
            szFilename, 
            szCmdLine, 
            NULL, 
            NULL, 
            FALSE, 
            0, 
            NULL, 
            NULL, 
            &si, 
            &pi);
    // add the handle into the [hs]
    hs[nCloneID] = pi.hProcess;
    return;
}

// create the share memory
HANDLE MakeSharedFile()
{
    // create the file mapping object
    HANDLE hMapping = CreateFileMapping(
            INVALID_HANDLE_VALUE, 
            NULL, 
            PAGE_READWRITE, 
            0, 
            sizeof(struct sharemem),        // the size is the [sharemem]
            SHM_NAME);                      // get the share memory a name, to open later
    if (hMapping != INVALID_HANDLE_VALUE) {
        // create successfully
        // create the hole on the file mapping object
        LPVOID pData = MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if (pData != NULL) {
            // use sharemem to init this space memory
            ZeroMemory(pData, sizeof(struct sharemem));
        }
        // close the hole
        UnmapViewOfFile(pData);
    }
    return hMapping;
}

int main(int argc, char * argv[])
{
    int i, j, k;
    int pindex = 1;         // the subprocess index 
    int nClone = ID_M;      // the id of the current process
    char lt[10];
    SYSTEMTIME systime;

    // the spare argument as the index for the subprocess
    if (argc > 1) {
        // the main process do not execute this line, nClone = 0;
        sscanf(argv[1], "%d", &nClone);
    }

    // run main process and init the share memory
    if (nClone == ID_M) {
        // create and init the share memory
        hMapping = MakeSharedFile();

        // create the hole of the share memory
        HANDLE hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, SHM_NAME);
        LPVOID pFile = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        // get the file of the share memory
        if (pFile != NULL) {
            struct sharemem * shm = (struct sharemem *)(pFile);
            // init the point of the buffer
            shm->data.head = 0;
            shm->data.tail = 0;
            shm->index = 0;
            // create the semaphore for the share memory, [full, empty]
            shm->semEmpty = CreateSemaphore(NULL, LETTER_NUM, LETTER_NUM, "SEM_EMPTY");
            shm->semFull = CreateSemaphore(NULL, 0, LETTER_NUM, "SEM_FULL");
            // close
            UnmapViewOfFile(pFile);
            pFile = NULL;
        }
        else {
            printf("Error on OpenFileMapping.\n");
        }
        CloseHandle(hFileMapping);

        // create the subprocesses by cloning the main process, give the pindex as the flag of the subprocess
        while (pindex <= PROCESS_NUM) {
            StartClone(pindex++);
        }

        printf("Over the initation and create the processes.\n");

        // wait for subprocesses and begin the pro_con problem.
        for (k = 1; k < PROCESS_NUM + 1; k++) {
            WaitForSingleObject(hs[k], INFINITE);
            CloseHandle(hs[k]);
        }
    }
    // producer 1 <= id <= 2
    else if (nClone >= ID_P_FROM && nClone <= ID_P_TO) {
        // open the share meomry and return the pFile as the handle
        HANDLE hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, SHM_NAME);
        LPVOID pFile = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if (pFile != NULL) {
            struct sharemem * shm = (struct sharemem *)(pFile);

            // open the created semaphore 
            shm->semEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS ,FALSE, "SEM_EMPTY");
            shm->semFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS ,FALSE, "SEM_FULL");
            for (i = 0; i < WORKS_P; i++) {
                // P(empty)
                WaitForSingleObject(shm->semEmpty, INFINITE);


                Sleep(get_random());
                shm->index++;
                sprintf(pause, "pro %d: %d\n", nClone, shm->data.tail);
                strcpy(shm->data.text[shm->data.tail], pause);
                shm->data.tail = (shm->data.tail + 1) % LETTER_NUM;
                shm->data.is_empty = 0;
                printf("%s\n", pause);


                // V(full)
                ReleaseSemaphore(shm->semFull, 1, NULL);
            }
            UnmapViewOfFile(pFile);
            pFile = NULL;
        }
        else {
            printf("Error on OpenFileMapping.\n");
        }
        CloseHandle(hFileMapping);
        printf("Producer %d process ends.\n", nClone - ID_M);
    }
    // consumer  3 <= id <= 5
    else if (nClone >= ID_C_FROM && nClone <= ID_C_TO) {
        HANDLE hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, SHM_NAME);
        LPVOID pFile = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if (pFile != NULL) {
            struct sharemem * shm = (struct sharemem *)(pFile);
            shm->semEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS,FALSE,"SEM_EMPTY");
            shm->semFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS,FALSE,"SEM_FULL");
            for (i = 0; i < WORKS_C; i++) {
                // P(full)
                WaitForSingleObject(shm->semFull, INFINITE);


                Sleep(get_random());
                shm->index++;
                strcpy(lt, shm->data.text[shm->data.head]);
                printf("\t\tcon %d: %d\n", nClone, shm->data.head);
                shm->data.head = (shm->data.head + 1) % LETTER_NUM;
                shm->data.is_empty = (shm->data.head == shm->data.tail);

                
                // V(empty)
                ReleaseSemaphore(shm->semEmpty, 1, NULL);
            }
            UnmapViewOfFile(pFile);
            pFile = NULL;
        }
        else {
            printf("Error on OpenFileMapping.\n");
        }
        CloseHandle(hFileMapping);
        printf("Consumer %d process ends.\n", nClone - ID_P_TO);
    }

    // close the mapping and exit
    CloseHandle(hMapping);
    hMapping = INVALID_HANDLE_VALUE;
    return 0;
}