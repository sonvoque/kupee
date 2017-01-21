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
#include "sls_cli.h"        
#define MAXBUF  sizeof(cmd_struct_t)
#define BUFLEN 2048
#define MSGS 1	/* number of messages to send */

static  int     rev_bytes;
static  struct  sockaddr_in6 rev_sin6;
static  int     rev_sin6len;
static  char    rev_buffer[MAXBUF];
static  int     port;
static  char    server[50];
static  char    str_port[5];
static  char    cmd[20];
static  char    arg[32];
static uint8_t node_id;

static  cmd_struct_t  tx_cmd, rx_reply;
static  cmd_struct_t *cmdPtr;
static  char *p;
void init_cmd() {
  tx_cmd.sfd = SFD;
  tx_cmd.len = node_id;
  tx_cmd.seq ++;
  //#ifdef _TEST_
	//tx_cmd.cmd = CMD_LED_OFF	;
	//tx_cmd.type = MSG_TYPE_REQ;
  //tx_cmd.type = MSG_TYPE_REQ;
	//#endif
  tx_cmd.err_code = 0;  
}


/*------------------------------------------------*/
void print_cmd(cmd_struct_t command) {
  int i;
  printf("SFD=0x%X; ",command.sfd);
  printf("node_id=%d; ",command.len);
  printf("seq=%d; ",command.seq);
  printf("type=0x%X; ",command.type);
  printf("cmd=0x%X; ",command.cmd);
  printf("err_code=0x%X; ",command.err_code); 
  printf("data=[");
  for (i=0;i<MAX_CMD_DATA_LEN;i++) 
    printf("0x%02X,",command.arg[i]);
  printf("]\n");
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
int main(int argc, char* argv[])
{
	//char *server="192.168.1.11";
	char buffer[MAXBUF];
  	char str_app_key[32];
  	unsigned char byte_array[16];

  	struct sockaddr_in myaddr, remaddr;
	int fd, i, slen=sizeof(remaddr);
	char buf[BUFLEN];	/* message buffer */
	int recvlen;		/* # bytes in acknowledgement message */
	//
if(argc < 5) {
    printf("Specify an IPv6 addr or port number or Cmd \n"), exit(1);
	}
	else if (argc==5) {
		sprintf(server,"%s",argv[1]);      
		strcpy(str_port,argv[2]);
		node_id = (uint8_t)atoi(argv[3]);

		strcpy(cmd,argv[4]);  
		port = atoi(str_port);
		sprintf(buffer,"%s",cmd);

		tx_cmd.len = node_id;
		/* REQ-TYPE*/
		if (strcmp(cmd,SLS_LED_ON)==0) {
		  tx_cmd.cmd = CMD_LED_ON;
		  tx_cmd.type = MSG_TYPE_REQ;
		}
		else if (strcmp(cmd,SLS_LED_OFF)==0) {
		  tx_cmd.cmd = CMD_LED_OFF;    
		  tx_cmd.type = MSG_TYPE_REQ;
		 } 
		else if (strcmp(cmd,SLS_GET_LED_STATUS)==0) {
		  tx_cmd.cmd = CMD_GET_LED_STATUS;
		  tx_cmd.type = MSG_TYPE_REQ;
		}
		else if (strcmp(cmd,SLS_GET_NW_STATUS)==0) {
		  tx_cmd.cmd = CMD_GET_NW_STATUS;
		  tx_cmd.type = MSG_TYPE_REQ;
		}
		else if (strcmp(cmd,SLS_GET_GW_STATUS)==0) {
		  tx_cmd.cmd = CMD_GET_GW_STATUS;
		  tx_cmd.type = MSG_TYPE_REQ;
		}
		/*HELLO TYPE*/
		else if (strcmp(cmd,SLS_LED_HELLO)==0) {
		  tx_cmd.cmd = CMD_LED_HELLO;
		  tx_cmd.type = MSG_TYPE_HELLO;
		  //printf("HELLO 0x%02X\n", tx_cmd.type);
		}
		else if (strcmp(cmd,SLS_GET_APP_KEY)==0) {
		  tx_cmd.cmd = CMD_GET_APP_KEY;    
		  tx_cmd.type = MSG_TYPE_REQ;
		}
		else if (strcmp(cmd,SLS_LED_REBOOT)==0) {
		  tx_cmd.cmd = CMD_LED_REBOOT;    
		  tx_cmd.type = MSG_TYPE_REQ;
		}    
		else {
		  printf("Unknown cmd \n");
		  exit(1);
		}  
	}		


  /* cmd with arg */
	else if (argc==6)	{

	    sprintf(server,"%s",argv[1]); 
	    strcpy(str_port,argv[2]);
			node_id = (uint8_t)atoi(argv[3]);

	    sprintf(cmd,"%s",argv[4]);
	    sprintf(arg,"%s",argv[5]);
			//sprintf(buffer,argv[2]);

			tx_cmd.len = node_id;

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

	    port = atoi(str_port);
	   	sprintf(buffer,"%s %s",cmd,arg);
	}	
  
  //
  //prepare_cmd();
	//
	init_cmd() ;

		/* change this to use a different server */

	/* create a socket */

	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		printf("socket created\n");

	/* bind it to all local addresses and pick any port number */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}       

	/* now define remaddr, the address to whom we want to send messages */
	/* For convenience, the host address is expressed as a numeric IP address */
	/* that we will convert to a binary format via inet_aton */

	memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(port);
	if (inet_aton(server, &remaddr.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	/* now let's send the messages */

	for (i=0; i < MSGS; i++) {
		//printf("Tx-CMD\n");
		printf("Sending numbytes= %d\n ", sizeof(tx_cmd));
		print_cmd(tx_cmd);		
		printf("...\n");
		printf(".....\n");
		printf(".......\n");

		//printf("Sending packet %d to %s port %d\n", i, server, SERVICE_PORT);
		//sprintf(buf, "This is packet %d %d", i,2*i);

		if (sendto(fd, &tx_cmd, sizeof(tx_cmd), 0, (struct sockaddr *)&remaddr, slen)==-1) {
			perror("sendto");
			exit(1);
		}
		printf("..........Done\n");

		/* now receive an acknowledgement from the server */
		rev_bytes = recvfrom(fd, rev_buffer,MAXBUF, 0, (struct sockaddr *)&remaddr, &slen);
                if (recvlen >= 0) {
                    printf("Got REPLY (%d bytes):\n",rev_bytes);
				    p = (char *) (&rev_buffer);
				    cmdPtr = (cmd_struct_t *)p;
				    rx_reply = *cmdPtr;
				    print_cmd(*cmdPtr);

                }
        //

	}
	close(fd);
	return 0;
}
