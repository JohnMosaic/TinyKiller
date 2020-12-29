#include "usage.h"

void UsageHelp(void)
{
	printf("\n");
	printf("+---------------------------- Follow these helps! ----------------------------+\n");
	printf("|                                                                             |\n");
	printf("| [+] Option1: Get the PID of eventlog service process.                       |\n");
	printf("|              Bypass the eventlog service.                                   |\n");
	printf("|              Do what you want to do.                                        |\n");
	printf("|              Kill the eventlog service process.                             |\n");
	printf("|              Restart the eventlog service.                                  |\n");
	printf("| [+] Option2: Bypass some other services according to the steps above.       |\n");
	printf("| [+] Option3: Kill a thread.                                                 |\n");
	printf("| [+] Option4: Kill a process.                                                |\n");
	printf("|                                                                             |\n");
	printf("+-------------- Instructions --------------+---- Type ----+----- Example -----+\n");
	printf("|                                          |              |                   |\n");
	printf("| Show these helps                         | -HELP NULL   | eg:-HELP          |\n");
	printf("| Get a PID based on the service name      | -GSVC string | eg:-GSVC eventlog |\n");
	printf("| Bypass a service based on the PID & name | -PID  DWORD  | eg:-PID 1288      |\n");
	printf("|                                          | -BSVC string |    -BSVC eventlog |\n");
	printf("| Kill a process based on the PID          | -PID  DWORD  | eg:-PID 1288      |\n");
	printf("| Kill a thread based on the TID           | -TID  DWORD  | eg:-TID 1156      |\n");
	printf("| Restart a service based ont the name     | -RSVC string | eg:-RSVC eventlog |\n");
	printf("|                                          |              |                   |\n");
	printf("+--------- Enjoy the tiny killer! ---------+--------------+-------------------+\n");
}