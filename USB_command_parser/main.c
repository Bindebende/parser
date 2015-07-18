//
//  main.c
//  USB_command_parser
//
//  Created by Bendegúz Hoffmann on 2015. 05. 14..
//  Copyright (c) 2015. Bendegúz Hoffmann. All rights reserved.
//

#include <stdio.h>
#include "serial.h"
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


int main(void)  
{

    uint32_t i=0;

    #ifdef __APPLE__                                                                                           /* os specific code                             */

    // /dev/cu.usbmodem0F003091
  char *portname = "/dev/cu.usbmodem0F003091";

     #elif __linux
     char *portname = "/dev/ttyUSB1";
     #endif

    int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        printf("error opening %s: %s\n", portname,strerror(errno));
        return -1;
    }


    set_interface_attribs (fd, B115200, 0);                                                                     /* set speed to 115,200 bps, 8n1 (no parity)    */
   set_blocking (fd, 1);                                                                                       /* set no blocking

    // write (fd, "hello!\n", 7);                                                                                  /* send 7 character greeting                    */

   usleep ((7 + 25) * 100);                                                                                    /* sleep enough to transmit the 7 plus          */
                                                                                                                /*receive 25:  approx 100 uS per char transmit  */
    char buf [60];
    long n = 0;

    while(1)
    {
        n=read (fd, buf, sizeof buf);                                                                        /* read up to 100 characters if ready to read   */

       if(n<0)
            printf("there is some error in the reading process\n");

        printf("buffer:");

        for(i=0;i<8;i++)
        {
            printf("%c",buf[i]);
            if(buf[i]==1 || buf[i]==2) break;
        }
        printf("\n");
    }
    return 0;

}





