#include "tidfilter.h"

BOOL ListProcessThreads(DWORD pid, char* charservice)
 {  
    WCHAR service[1024];
	swprintf(service, 1024, L"%hs", charservice);
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

    if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
        printf("[?] Invalid tool help32 snapshot handle.\n");
		return FALSE;
	}

    te32.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(hThreadSnap, &te32))
    {
		CloseHandle(hThreadSnap);   
		printf("[?] Get first thread32 error.\n");
        return FALSE;
    }

    do 
    {
		if (te32.th32OwnerProcessID == pid)
		{
			printf("[+] Query service tag PID-TID is %u-%u\n", pid, te32.th32ThreadID);

			if (wcsicmp(GetServiceTagName(pid, te32.th32ThreadID), service) == 0)
			{
				printf("[*] Get %s thread is %d! Try to kill...\n", charservice, te32.th32ThreadID);
				KillThread(te32.th32ThreadID);
			}
			else
			{ 
				printf("[+] %d is not %s thread.\n", te32.th32ThreadID, charservice);
			}
		}
	}
	while (Thread32Next(hThreadSnap, &te32));

    CloseHandle(hThreadSnap);
    return TRUE;  
}