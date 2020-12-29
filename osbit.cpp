#include "osbit.h"

BOOL IsOS64bit()
{
	SYSTEM_INFO si; 
	GetNativeSystemInfo(&si); 

	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) 
	{
		//printf("[+] The operating system architecture is x64.\n");
		return TRUE;
	}
	else
	{
		//printf("[+] The operating system architecture is x86.\n");
		return FALSE;
	}
}