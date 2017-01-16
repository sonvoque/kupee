#ifndef _LIB_H
#define _LIB_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include "port.h"
#include "sls.h"
#include "sls_cli.h"
using namespace std;
void help()
{
	printf("----------------------------------\n");
	printf(" CLI - Light Control System \n");
	printf(" Design by Cuongtv\n");
	printf(" Version 1 \n");
	printf(" Commands: \n");
	printf("\t -h : help\n");
	printf("\t -v: Version \n");
	printf("\t -s [key]: Loggin to System with KEY   \n:");	
	printf("----------------------------------\n");
}
void version()
{
	printf(" CLI - Light Control System \n");
	printf(" Version 1 \n");
	printf(" Design by Kupro \n");
	
}
void helpcmd()
{
	printf("----------------------------------\n");
	printf(" Commands: \n");
	printf("\t -id LED_ID: set LED ID\n");
	printf("define SLS_LED_HELLO \n define SLS_LED_ON\n ");
	printf("\t -t COMMAND_TYPE: COMMAND_TYPE\n");
	printf("\t -key: set apps key key \n");
	printf("----------------------------------\n");
}
int led_mapping(char led_id[])
{
	if(strlen(led_id)==3)

	{
		return atoi(led_id);
	}
	else
	{
		return -1;
	}
}
int convert(const char *hex_str, unsigned char *byte_array, int byte_array_max) {
    int hex_str_len = strlen(hex_str);
    int i = 0, j = 0;
    // The output array size is half the hex_str length (rounded up)
    int byte_array_size = (hex_str_len+1)/2;
    if (byte_array_size > byte_array_max) {
        // Too big for the output array
        return -1;
    }

    if (hex_str_len % 2 == 1){
        // hex_str is an odd length, so assume an implicit "0" prefix
        if (sscanf(&(hex_str[0]), "%1hhx", &(byte_array[0])) != 1){
            return -1;
        }
        i = j = 1;
    }

    for (; i < hex_str_len; i+=2, j++){
        if (sscanf(&(hex_str[i]), "%2hhx", &(byte_array[j])) != 1){
            return -1;
        }
    }
    return byte_array_size;
}
//
void init_socket()
{

}
void send_data()
{

}
void recv_data()
{

}
#endif