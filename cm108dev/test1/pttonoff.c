/*
 * =====================================================================================
 *
 *       Filename:  atest.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  13.01.2013 03:58:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  _john (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include <stdlib.h>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <linux/hidraw.h>

#define PATHNAM "/dev/hidraw0"

int fd;
unsigned int ptt_bitnum = 4;


	int 
cm108_open(void)
{

	printf("cm108:cm108_open called \n");

	fd = open(PATHNAM, O_RDWR);

	if (fd < 0) {
		printf("cm108:Opening device \"%s\": %s\n", PATHNAM, strerror(errno));
		return -5;
	}
	printf("cm108:Checking for cm108 (or compatible) device \n");
	return 0;
}

int cm108_close(void)
{
	printf("close called \n");
	return close(fd);
}


int cm108_ptt_set(int pttx)
{

        printf("cm108:cm108_ptt_set called \n");

		// Build a packet for CM108 HID to turn GPIO bit on or off.
		// Packet is 4 bytes, preceded by a 'report number' byte
		// 0x00 report number
		// Write data packet (from CM108 documentation)
		// byte 0: 00xx xxxx     Write GPIO
		// byte 1: xxxx dcba     GPIO3-0 output values (1=high)
		// byte 2: xxxx dcba     GPIO3-0 data-direction register (1=output)
		// byte 3: xxxx xxxx     SPDIF

		printf("cm108:cm108_ptt_set bit number %d to state %d\n",
			ptt_bitnum, pttx ? 1 : 0);

		char out_rep[] = {
			0x00, // report number
			// HID output report
			0x00,
			(pttx) ? (1 << ptt_bitnum) : 0, // set GPIO
			1 << ptt_bitnum, // Data direction register (1=output)
			0x00
		};

		ssize_t nw;

		if (fd == -1)
			return -33;

		// Send the HID packet
		nw = write(fd, out_rep, sizeof(out_rep));
		if (nw < 0) {
			return -3;
		}

		return 0;
}




int main(int argc, const char *argv[])
{

	int i;
	int ret;

	ret = cm108_open();
	if (ret)
		return ret;
	
	for(i=0;i<4;i++){
		cm108_ptt_set(1);
		sleep(1);
		cm108_ptt_set(0);
		sleep(1);
	}

	return cm108_close();
}
