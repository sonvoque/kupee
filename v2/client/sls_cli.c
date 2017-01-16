/*
        demo-udp-03: udp-send: a simple udp client
  send udp messages
  This sends a sequence of messages (the # of messages is defined in MSGS)
  The messages are sent to a port defined in SERVICE_PORT 

        usage:  udp-send

        Paul Krzyzanowski
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include "port.h"
#include "sls.h"
#include "lib.h"
#include "sls_cli.h"  

using namespace std;    
#define MAXBUF  sizeof(cmd_struct_t)  
#define BUFLEN 2048
#define MSGS 1  /* number of messages to send */
// static    int s_sock;
static  int     rev_bytes;
static  struct  sockaddr_in6 rev_sin6;
static  int     rev_sin6len;
static  char    rev_buffer[MAXBUF];
static  int     port;
static  char    dst_ipv6addr[50];
static  char    str_port[5];
static  char    cmd[20];
static  char    arg[32];

static  cmd_struct_pi  tx_cmd, rx_reply;
static  cmd_struct_pi *cmdPtr;
static  char *p;
void input_para( int argc, char* argv[],cmd_struct_pi* tx_cmd_pi, int* port );
void init_cmd() {
  tx_cmd.sfd = SFD;
  tx_cmd.len = sizeof(tx_cmd);
  tx_cmd.seq ++;
  //tx_cmd.cmd = CMD_LED_OFF  ;
  //tx_cmd.type = MSG_TYPE_REQ;
  //tx_cmd.type = MSG_TYPE_REQ;
  tx_cmd.err_code = 0;  
}


/*------------------------------------------------*/
void print_cmd_pi(cmd_struct_pi command) {
  int i;
  printf("SFD=0x%X; \n",command.sfd);
  printf("len=%d; \n",command.len);
  printf("seq=%d; \n",command.seq);
  printf("type=0x%X; \n",command.type);
  printf("cmd=0x%X; \n",command.cmd);
  printf("err_code=0x%X; \n",command.err_code); 
  printf("LED_ID=0x%X; \n",command.led_id);
  printf("data=[");
  for (i=0;i<MAX_CMD_DATA_LEN;i++) 
    printf("0x%02X,",command.arg[i]);
  printf("]\n");
}  

int main(int argc, char* argv[])
{
  
  char str_app_key[32];
  unsigned char byte_array[16];
// Khoi tao cac bien
   input_para(argc,argv,&tx_cmd,&port);

print_cmd_pi(tx_cmd);

  return 0;
}
void input_para( int argc, char* argv[],cmd_struct_pi* tx_cmd, int* port)
{
  char led_id[4];
  /* data */
  if(argc < 4) {
    printf("Specify an IPv6 addr or port number or Cmd \n"), exit(1);
  }
  else if (argc==4) {
    sprintf(led_id,"%s",argv[1]);    
    strcpy(str_port,argv[2]);
    strcpy(cmd,argv[3]);  
    *tx_cmd.led_id=led_mapping(led_id);
    *port = atoi(str_port);
    /* REQ-TYPE*/
    if (strcmp(cmd,SLS_LED_ON)==0) {
      *tx_cmd.cmd = CMD_LED_ON;
      *tx_cmd.type = MSG_TYPE_REQ;
    }
    else if (strcmp(cmd,SLS_LED_OFF)==0) {
      *tx_cmd.cmd = CMD_LED_OFF;    
      *tx_cmd.type = MSG_TYPE_REQ;
     } 
    else if (strcmp(cmd,SLS_GET_LED_STATUS)==0) {
      *tx_cmd.cmd = CMD_GET_LED_STATUS;
      *tx_cmd.type = MSG_TYPE_REQ;
    }
    else if (strcmp(cmd,SLS_GET_NW_STATUS)==0) {
      *tx_cmd.cmd = CMD_GET_NW_STATUS;
      *tx_cmd.type = MSG_TYPE_REQ;
    }
    else if (strcmp(cmd,SLS_GET_GW_STATUS)==0) {
      *tx_cmd.cmd = CMD_GET_GW_STATUS;
      *tx_cmd.type = MSG_TYPE_REQ;
    }
    /*HELLO TYPE*/
    else if (strcmp(cmd,SLS_LED_HELLO)==0) {
      *tx_cmd.cmd = CMD_LED_HELLO;
      *tx_cmd.type = MSG_TYPE_HELLO;
      //printf("HELLO 0x%02X\n", tx_cmd.type);
    }
    else if (strcmp(cmd,SLS_GET_APP_KEY)==0) {
      *tx_cmd.cmd = CMD_GET_APP_KEY;    
      *tx_cmd.type = MSG_TYPE_REQ;
    }
    else if (strcmp(cmd,SLS_LED_REBOOT)==0) {
      *tx_cmd.cmd = CMD_LED_REBOOT;    
      *tx_cmd.type = MSG_TYPE_REQ;
    }    
    else {
      printf("Unknown cmd \n");
      exit(1);
    }  
  }   

  /* cmd with arg */
  else if (argc==5) {
    //sprintf(dst_ipv6addr,"%s",argv[1]);      
    strcpy(str_port,argv[2]);
    sprintf(cmd,"%s",argv[3]);
    sprintf(arg,"%s",argv[4]);
    //sprintf(buffer,argv[2]);

    if (strcmp(cmd,SLS_LED_DIM)==0) {
      tx_cmd.cmd = CMD_LED_DIM;    
      tx_cmd.arg[0] = atoi(arg);
      tx_cmd.type = MSG_TYPE_REQ;      
    }
    else if (strcmp(cmd,SLS_SET_APP_KEY)==0) {
      tx_cmd.cmd = CMD_SET_APP_KEY;    
      tx_cmd.type = MSG_TYPE_HELLO;
      strcpy(str_app_key,arg);
      convert(str_app_key, byte_array, MAX_CMD_DATA_LEN);
      for (int i = 0; i<MAX_CMD_DATA_LEN; i++) {
        tx_cmd.arg[i] = byte_array[i];
      }
    }
    else {
      printf("Unknown cmd \n");
      exit(1);
    }  

    *port = atoi(str_port);
    //sprintf(buffer,"%s %s",cmd,arg);
  } 

};)