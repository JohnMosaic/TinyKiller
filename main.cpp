#include "usage.h"
#include "osbit.h"
#include "killer.h"
#include "privilege.h"
#include "tidfilter.h"

int main(int argc, char* argv[])
{
	if(5 == argc)
	{
		if(!stricmp(argv[1], "-PID") && !stricmp(argv[3], "-BSVC"))
		{
			BOOL bRet = AdjustSelfPrivilege();

			if(bRet)
			{ 
				bRet = IsOS64bit();

				if (bRet) 
				{
					printf("[+] The operating system architecture is x64.\n");
				}
				else
				{
					printf("[+] The operating system architecture is x86.\n");
				}

				ListProcessThreads(atoi(argv[2]), argv[4]);
			}
			else
			{
				printf("[?] Bypass the %s service error.\n", argv[4]);
			}
		}
		else
		{
			printf("\nSyntax error in parameters!\n");
		}
	}
	else if(4 == argc)
	{
		printf("\nSyntax error in parameters!\n");
	}
	else if(3 == argc)
	{
		if(!stricmp(argv[1], "-GSVC"))
		{
			GetPidOfService(argv[2]);
		}
		else if(!stricmp(argv[1], "-PID"))
		{
			BOOL bRet = AdjustSelfPrivilege();

			if(bRet)
			{ 
				KillProcess(atoi(argv[2]));
			}
		}
		else if(!stricmp(argv[1], "-TID"))
		{
			BOOL bRet = AdjustSelfPrivilege();

			if(bRet)
			{ 
				KillThread(atoi(argv[2]));
			}
		}
		else if(!stricmp(argv[1], "-RSVC"))
		{
			RestartService(argv[2]);
		}
		else
		{
			printf("\nSyntax error in parameters!\n");
		}
	}
	else if(2 == argc)
	{
		if(!stricmp(argv[1], "-HELP"))
		{
			UsageHelp();
		}
		else
		{
			printf("\nSyntax error in parameters!\n");
		}
	}
	else
	{
		UsageHelp();
	}

	return 0;
}