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
        start_of_frame,handshake,end_of_frame,
        start_of_frame,acknowledge,end_of_frame,
        start_of_frame,request,end_of_frame,
        start_of_frame,data,end_of_frame
    };
   
    
    i=0;
   i= parse(buffer, rx_mailbox);
    
    printf("is valid message%d\n\r",i);
    
    printf("mailboxes:");
    for(i=0;i<number_of_mailboxes ;i++)
       printf("%d",rx_mailbox[i]);
    
    printf("\n\r");
        return 0;

}





