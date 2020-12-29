#include "privilege.h"

BOOL AdjustSelfPrivilege()  
 {  
    HANDLE hToken;
    TOKEN_PRIVILEGES NewState;
    LUID luidPrivilegeLUID;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken) || !LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luidPrivilegeLUID))
    {   
        printf("[?] Open process's token error.\n");
        return FALSE;
    }

    NewState.PrivilegeCount = 1;
    NewState.Privileges[0].Luid = luidPrivilegeLUID;
    NewState.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(hToken, FALSE, &NewState, NULL, NULL, NULL))
    {  
        printf("[?] Adjust token privilege error.\n");
        return FALSE;
    }

	printf("[!] Adjust sedebug privilege done.\n");
    return TRUE;
}