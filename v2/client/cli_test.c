#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include "port.h"
#include "sls.h"
#include "sls_cli.h"
#include "lib.h"
#include <iostream>
using namespace std;
#define BUFLEN 2048
#define MSGS 1  /* number of messages to send */

int main (int argc, char* argv[])
{
	int run = 0;
	if((argc==1)|(argc>3)){
		help();
		return -1;
	}
	else
	{
	// 

		if (strcmp(argv[1],"-p")==0) 
		{
			// set KEY
			//printf("%s\n",argv[2]);
			if (strcmp(argv[2],SLS_APP_KEY_128)==0)
			{
				printf("logging successful\n");
				helpcmd();
				run = 1;

			}
			else
			{
				printf("wrong key\n");
				return -1;
			}
			
		}
		else if (strcmp(argv[1],"-v")==0)
		{
			/* code */
			version();
		}
		else
		{
			printf("wrong format\n");
			help();
		}
	}
// main program

	if(run==1)
	{ /* start run--*/

		while(1)
		{
			string led_id;
			cin >> led_id;
			if(led_id.length() ==4)
				
			else
				c			
		}


	}/* end run*/

return 0;
}
