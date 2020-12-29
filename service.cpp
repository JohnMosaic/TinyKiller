#include "service.h"

void GetPidOfService(char* service)
{
	char* part1 = "tasklist /svc /fi \"Services eq ";
	char* part2 = service;
	char* part3 = "\"";
	char* combine = new char[strlen(part1) + strlen(part2) + strlen(part3) + 1];
	strcpy(combine, part1);
	strcat(combine, part2);
	strcat(combine, part3);
	system(combine);
	delete[] combine;
}

WCHAR* GetServiceTagName(DWORD pid, DWORD tid)
{
	ULONG serviceTag = 0;
	WCHAR tagString[MAX_PATH] = { 0 };

    if (GetServiceTag(pid, tid, &serviceTag) == FALSE)
    {
        printf("[?] Get service tag error.\n");
		goto OVER;
    }

    if (GetServiceTagString(pid, serviceTag, tagString, sizeof(tagString)) == FALSE)
    {
        printf("[?] Get service tag string error.\n");
		goto OVER;
    }

OVER:
	return tagString;
}

BOOL GetServiceTag(DWORD processId, DWORD threadId, PULONG pServiceTag)
{
    BOOL success = FALSE;
    NTSTATUS status = 0;
    THREAD_BASIC_INFORMATION threadBasicInfo = { 0 };
    HANDLE process = NULL;
    HANDLE thread = NULL;
    HANDLE subProcessTag = NULL;

    do
    {
		thread = OpenThread(THREAD_ALL_ACCESS, FALSE, threadId);

        if (thread == NULL)
		{
			printf("[?] Open thread error, TID is %d.\n", threadId);
			break;
		}

		status = NtQueryInformationThread(thread, ThreadBasicInformation, &threadBasicInfo, sizeof(threadBasicInfo), NULL);

        if (status != 0)
		{
            printf("[?] Get thread basic informaiton error.\n");
			break;
		}
		
		process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

        if (process == NULL)
		{
            printf("[?] Open process error, PID is %d.\n", processId);
			break;
		}

        // SubProcessTag Offset : x86 = 0xf60 / x64 = 0x1720
		if(IsOS64bit())
		{
			if (!ReadProcessMemory(process, ((PBYTE)threadBasicInfo.pTebBaseAddress + 0x1720), &subProcessTag, sizeof(subProcessTag), NULL))
			{
				printf("[?] Get sub process tag error.\n");
				break;
			}
		}
		else
		{
			if (!ReadProcessMemory(process, ((PBYTE)threadBasicInfo.pTebBaseAddress + 0xf60), &subProcessTag, sizeof(subProcessTag), NULL))
			{
				printf("[?] Get sub process tag error.\n");
				break;
			}
		}

        if (pServiceTag)
		{
            *pServiceTag = (ULONG)subProcessTag;
		}

        success = TRUE;
    }
	while (FALSE);

    if (process)
	{
        CloseHandle(process);
	}

    if (thread)
	{
        CloseHandle(thread);
	}

    return success;
}

BOOL GetServiceTagString(DWORD processId, ULONG tag, PWSTR pBuffer, SIZE_T bufferSize)
{
    BOOL success = FALSE;
    HMODULE advapi32 = NULL;
    FN_I_QueryTagInformation pfnI_QueryTagInformation = NULL;
    SC_SERVICE_TAG_QUERY tagQuery = { 0 };

    do
    {
        advapi32 = LoadLibrary(L"advapi32.dll");

        if (advapi32 == NULL)
		{
            printf("[?] Load \"advapi32.dll\" error.\n");
			break;
		}

        pfnI_QueryTagInformation = (FN_I_QueryTagInformation)GetProcAddress(advapi32, "I_QueryTagInformation");

        if (pfnI_QueryTagInformation == NULL)
		{
            printf("[?] Get function \"I_QueryTagInformation\" address error.\n");
			break;
		}

        tagQuery.processId = processId;
        tagQuery.serviceTag = tag;
        pfnI_QueryTagInformation(NULL, ServiceNameFromTagInformation, &tagQuery);

        if (tagQuery.pBuffer)
        {
            StringCbCopy(pBuffer, bufferSize, (PCWSTR)tagQuery.pBuffer);
            LocalFree(tagQuery.pBuffer);
        }

		success = TRUE;
    }
	while (FALSE);

    if (advapi32)
	{
        FreeLibrary(advapi32);
	}

    return success;
}

void RestartService(char* service)
{
	char* part1 = "net start ";
	char* part2 = service;
	char* combine = new char[strlen(part1) + strlen(part2) + 1];
	strcpy(combine, part1);
	strcat(combine, part2);
	system(combine);
	delete[] combine;
}