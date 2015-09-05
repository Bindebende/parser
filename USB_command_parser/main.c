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
   
    uint8_t valami[128];
    printf("command parser alive\n\r");
    uint32_t i=0;
    uint8_t buffer[buffer_size]={
        start_of_frame,handshake,end_of_frame,
        start_of_frame,acknowledge,end_of_frame,
        start_of_frame,request,end_of_frame,
        start_of_frame,data,end_of_frame
    };
    
    
    
    uint8_t message_queue[buffer_size];
    
   
    
    for(i=0;i<buffer_size;i++)
        message_queue[i]=0;
    
    i=0;
   i= parse(buffer, message_queue);
    
    printf("is valid message%d\n\r",i);
    
    printf("queue:");
    for(i=0;i<buffer_size;i++)
       printf("%d",message_queue[i]);
    
    printf("\n\r");
    flush_buffer(buffer);
    
    
    printf("queue:");
    for(i=0;i<buffer_size;i++)
        printf("%d",buffer[i]);
    return 0;

}





