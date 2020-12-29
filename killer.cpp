#include "killer.h"

void KillThread(DWORD tid)
{
    HANDLE hThread = OpenThread(THREAD_TERMINATE, FALSE, tid);

    if (TerminateThread(hThread, 0) == 0)
	{
        printf("[?] Terminate thread %d error.\n", tid);
	}
    else
	{
        printf("[!] Terminate thread %d done!\n", tid);
	}

    CloseHandle(hThread);
}

void KillProcess(DWORD pid)
{
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);

	if (TerminateProcess(hProcess, 4) == 0)
	{
        printf("[?] Terminate process %d error.\n", pid);
	}
    else
	{
        printf("[!] Terminate process %d done!\n", pid);
	}

    CloseHandle(hProcess);
}