//
//  main.c
//  USB_command_parser
//
//  Created by Bendegúz Hoffmann on 2015. 05. 14..
//  Copyright (c) 2015. Bendegúz Hoffmann. All rights reserved.
//

#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <inttypes.h>
#include "serial.h"
#include "commands.h"



int main(void)  
{
   
    
    struct mailbox rx_mailbox[number_of_mailboxes];
    
    flush_mailboxes(rx_mailbox);
    
    printf("command parser alive\n\r");
    uint32_t i=0;
    uint8_t buffer[buffer_size]={
        start_of_frame,request,44,0,end_of_frame,
        start_of_frame,request,45,0,end_of_frame,
        start_of_frame,data,46,0,1,2,3,4,end_of_frame,
        start_of_frame,data,47,4,3,2,1,0,end_of_frame,
    };
   
    
    i=0;
   i= parse(buffer, rx_mailbox);
    
    printf("is valid message%d\n\r",i);
    
   // print_mailboxes(rx_mailbox);
    
    copy(rx_mailbox);
    printf("\n\r");
        return 0;

}





