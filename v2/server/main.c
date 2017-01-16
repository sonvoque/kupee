#include <mysql.h> 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#include "sls.h"
#include "sls_cli.h"
#include "lib_mysql.h"
#define BUFSIZE 2048
#define MAXBUF  sizeof(cmd_struct_t)
#define SERVICE_PORT	21234	/* hard-coded port number */
// Bien cho IPV6 sock
static  int     rev_bytes;
static  struct  sockaddr_in6 rev_sin6;
static  int     rev_sin6len;
static  char    rev_buffer[MAXBUF];
static  int     port = 3000;
static  char    dst_ipv6addr[50];
static  char    str_port[5] = "3000";
static  char    cmd[20];
static  char    arg[32];

static  cmd_struct_t  tx_cmd, rx_reply;
static  cmd_struct_t *cmdPtr;
static  char *p;
//
static  cmd_struct_t   pi_rx_reply;
static  cmd_struct_t *pi_cmdPtr;
static  char *pi_p; 

// FUNCTION
void print_cmd(cmd_struct_t command); // In thong tin cua lenh dieu khien
void mapping (char *dst_ipv6addr, char* led_id );
void ip6_send_cmd(
					cmd_struct_t *tx_cmd, // lenh gui di
					cmd_struct_t *rx_cmd, // 
					int port, 
					char * ip6_addr
					);

int int main(int argc, char const *argv[])
{

// Socket IPV4
    struct sockaddr_in pi_myaddr;	/* our address */
	struct sockaddr_in pi_remaddr;	/* remote address */
	socklen_t pi_addrlen = sizeof(pi_remaddr);		/* length of addresses */
	int pi_recvlen;			/* # bytes received */
	int pi_fd;				/* our socket */
	int pi_msgcnt = 0;			/* count # of messages we received */
	unsigned char pi_buf[BUFSIZE];	/* receive buffer */
  /* create a UDP socket */

	if ((pi_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
		return 0;
	}

	/* bind the socket to any valid IP address and a specific port */

	memset((char *)&pi_myaddr, 0, sizeof(pi_myaddr));
	pi_myaddr.sin_family = AF_INET;
	pi_myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	pi_myaddr.sin_port = htons(SERVICE_PORT);

	if (bind(pi_fd, (struct sockaddr *)&pi_myaddr, sizeof(pi_myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}
// while loop-------------------------------
  while(1)
  {


  }	
// end while loop-------------------------------

	return 0;
}
//
/*------------------------------------------------*/
void print_cmd(cmd_struct_t command) {
  int i;
  printf("SFD=0x%X; ",command.sfd);
  printf("len=%d; ",command.len);
  printf("seq=%d; ",command.seq);
  printf("type=0x%X; ",command.type);
  printf("cmd=0x%X; ",command.cmd);
  printf("err_code=0x%X; ",command.err_code); 
  printf("data=[");
  for (i=0;i<MAX_CMD_DATA_LEN;i++) 
    printf("0x%02X,",command.arg[i]);
  printf("]\n");
} 
// Gui du du lieu qua IPV6
void ip6_send_cmd(cmd_struct_t *tx_cmd,cmd_struct_t *tx_cmd,int port, char * ip6_addr)
{

}