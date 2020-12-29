#include "osbit.h"
#include "ntddk.h"
#include <Strsafe.h>

typedef enum _SC_SERVICE_TAG_QUERY_TYPE
{
    ServiceNameFromTagInformation = 1,
    ServiceNameReferencingModuleInformation,
    ServiceNameTagMappingInformation,
} 
SC_SERVICE_TAG_QUERY_TYPE, *PSC_SERVICE_TAG_QUERY_TYPE;

typedef struct _SC_SERVICE_TAG_QUERY
{
    ULONG processId;
    ULONG serviceTag;
    ULONG reserved;
    PVOID pBuffer;
}
SC_SERVICE_TAG_QUERY, *PSC_SERVICE_TAG_QUERY;

typedef struct _THREAD_BASIC_INFORMATION
{
    NTSTATUS exitStatus;
    PVOID pTebBaseAddress;
    CLIENT_ID clientId;
    long dummy[3];
} 
THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

typedef ULONG (WINAPI* FN_I_QueryTagInformation)(PVOID, SC_SERVICE_TAG_QUERY_TYPE, PSC_SERVICE_TAG_QUERY);
typedef long NTSTATUS;

void GetPidOfService(char* service);
WCHAR* GetServiceTagName(DWORD pid, DWORD tid);
BOOL GetServiceTag(DWORD processId, DWORD threadId, PULONG pServiceTag);
BOOL GetServiceTagString(DWORD processId, ULONG tag, PWSTR pBuffer, SIZE_T bufferSize);
void RestartService(char* service);