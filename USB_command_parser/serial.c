//  Based on http://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
//  just few modifications
//
//  Created by Bendegúz Hoffmann on 2015. 07. 07..
//  Copyright (c) 2015. Bendegúz Hoffmann. All rights reserved.
//

#include "serial.h"

#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


int set_interface_attribs (int fd, int speed, int parity)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
        printf("error %s from tcgetattr\n", strerror(errno));
        return -1;
    }
    
    cfsetospeed (&tty, speed);
    cfsetispeed (&tty, speed);
    
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS7;     // 7-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo,
    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 5;            // read 5 inputs then return
    tty.c_cc[VTIME] = 1;            // 0.1 seconds read timeout
    
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
    
    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
    // enable reading
    tty.c_cflag |= (PARENB | PARODD);      // parity on
    tty.c_cflag |= parity;
    tty.c_cflag |= CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    
    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
        
        printf("error %s from tcsetattr\n", strerror(errno));
        return -1;
    }
    return 0;
}



/*! \brief set the blocking type
 *
 *  @p fd is the file which is open
 *  @p should_block
 *
 *  A read() is satisfied when either VMIN characters have been transferred to the caller's buffer, or when VTIME tenths expire between characters. Since this timer is not started until
 *  the first character arrives, this call can block indefinitely if the serial line is idle. This is the most common mode of operation, and we consider VTIME to be an intercharacter
 *  timeout, not an overall one. This call should never return zero bytes read.
 *
 *
 *  @return void
 */
void set_blocking (int fd, int should_block)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
        printf("error %s from tcgetattr\n", strerror(errno));
        
        return;
    }
    
    tty.c_cc[VMIN]  = 7;                                                    /* this is the minimum size of ibis frames */
    tty.c_cc[VTIME] = 1;         // 0.1 seconds read timeout
    
    if (tcsetattr (fd, TCSANOW, &tty) != 0)
        printf("error %s setting term attributes\n", strerror(errno));
}