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
            char rx_buffer[100]={0,0,0,0x55,1,0,0,1,1,1,1,0,1,0,1,0,1,1,' ',1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,' ','e','n','y','i','k','e', };
                                     //start|   id                       |  | message
    uint32_t id=0;
    uint64_t message=0;
    
    sscanf(rx_buffer+4,"%u %llu",&id,&message);
    
    printf("id:%d message:%llu\n",id,message );
    
    return 0;

}





