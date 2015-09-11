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
   
    
    struct mailbox rx_mailbox[number_of_mailboxes],tx_mailbox[number_of_mailboxes];
    
    flush_mailboxes(rx_mailbox);
    flush_mailboxes(tx_mailbox);
    
    
    printf("command parser alive\n\r");
    uint32_t i=0;
    uint8_t rxbuffer[buffer_size]={
        start_of_frame,request,request_id_altitude,0,'\0',end_of_frame,
        start_of_frame,request,request_id_date,0,'\0',end_of_frame,
        start_of_frame,data,47,'5','1','2','3','4','\0',end_of_frame,
        start_of_frame,data,47,'4','3','2','1','\0',end_of_frame,
        start_of_frame,data,48,'3','2','1','\0',end_of_frame,
    };
   
    uint8_t txbuffer[buffer_size];
    flush_buffer(txbuffer);
    
    i=0;
   i= parse(rxbuffer, rx_mailbox);
    
    printf("is valid message%d\n\r",i);
    
    request_execute(rx_mailbox,tx_mailbox);
    
    print_mailboxes(rx_mailbox);
    
    buffer_writing(txbuffer, tx_mailbox);
    
    for(i; i<buffer_size;i++)printf("tx:%c\n\r",txbuffer[i]);
    printf("\n\r");
        return 0;

}





