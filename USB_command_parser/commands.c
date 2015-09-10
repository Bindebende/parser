//
//  commands.c
//  USB_command_parser
//
//  Created by Bendegúz Hoffmann on 2015. 08. 30..
//  Copyright (c) 2015. Bendegúz Hoffmann. All rights reserved.
//

#include "commands.h"
#include <inttypes.h>
#include <string.h>

uint32_t parse(uint8_t *buffer,struct mailbox *ptr)
{
    static uint32_t mailbox_index=0;
    uint32_t is_valid_message=0;
    uint32_t sof_index=0;
    uint32_t eof_index=0;
    
    
    for(sof_index=0; sof_index<buffer_size;sof_index++ )                                        /* iterating through the buffer                                                         */
    {
        if (buffer[sof_index]==start_of_frame)                                                  /* looking for start of frame character                                                 */
        {
            for(eof_index=sof_index; eof_index<buffer_size;eof_index++ )                        /* iterating through the buffer                                                         */
            {
                if ((buffer[eof_index]==end_of_frame)&&(eof_index>sof_index))                   /* looking for end of frame character                                                   */
                {
                    is_valid_message=1;                                                         /* means we have a message                                                              */
                    if(buffer[sof_index+1]==request)                                            /* sort the different type of mailbox                                                   */
                    {
                        ptr[mailbox_index].message_type=buffer[sof_index+1];
                            ptr[mailbox_index].ack_id=buffer[sof_index+2];
                            
                        ptr[mailbox_index].data_ptr=&buffer[sof_index+3];
                        mailbox_index++;
                        
                    }
                    else                                                                        /* data frame                                                                           */
                    {
                        ptr[mailbox_index].message_type=buffer[sof_index+1];
                            ptr[mailbox_index].ack_id=buffer[sof_index+2];
                        ptr[mailbox_index].data_ptr=&buffer[sof_index+3];
                            mailbox_index++;
                           
                        
                    }
                  
                    mailbox_index&=(number_of_mailboxes-1);
                    break;                                                                      /* find the whole message we can brake from it and iterrating to find the next sof  */
                }
                
            }
            
        }
        
    }
    
    if(is_valid_message)flush_buffer(buffer);
    return is_valid_message;
}

uint32_t send_message(uint32_t fd, uint32_t type, uint8_t *buffer,struct mailbox *ptr)
{
    uint32_t i;
    
    for(i=0;i<number_of_mailboxes;i++)
    {
    
        
        
    }

    return 0;
}

void flush_buffer(uint8_t *buffer )
{
    int32_t strln=0;
    uint8_t *old_buffer=buffer;

    for(;*old_buffer!='\0'; old_buffer++);

    for(strln=(old_buffer-buffer);strln>=0;strln--)
        buffer[strln]=0;
}



void flush_mailboxes(struct mailbox *ptr)
{
    struct mailbox blank;                                                   /* declare a blank structure which will be the pattern  */
    uint32_t i=0;
    
    blank.message_type=0;                                                   /* the two elements of the structure will be equal to zero   */
    
        
        blank.data_ptr="uzenet";
    
    for(i=0;i<number_of_mailboxes;i++) *(ptr+i)=blank;                       /* copy the pattern structure to the array which n number of structure in it  */
}


void print_mailboxes(struct mailbox *ptr)
{
    uint32_t i=0;
    
    for(;i<number_of_mailboxes;i++)
    {
       if(ptr[i].message_type!=0)   // only prints the mailboxes which holds a message
       {
           
           printf("mailbox%d:\n\r",i);
           if(request==ptr[i].message_type)printf("request id:%d\r\n",ptr[i].ack_id);
           
            else
            {
                printf("data id:%d message:",ptr[i].ack_id);
                char *temp=ptr[i].data_ptr;
                
                while(!(*temp==end_of_frame))
                printf("%c",*temp++);
                
               
            }
        printf("\n\r");
       }

    }
    
}


uint32_t buffer_writing(uint8_t *buffer,struct mailbox *ptr )
{
    //this function writes all the recieved datas to the buffer checks the buffer boundries
    
    static uint32_t buffer_index=0;
    uint32_t mailbox_index=0;
    
    for(;mailbox_index<number_of_mailboxes;mailbox_index++){
        
        for(;buffer_index<buffer_size;buffer_index++){
            buffer_index&=buffer_size-1;
            
            buffer[buffer_index++]=start_of_frame;
            buffer[buffer_index++]=ptr[mailbox_index].message_type;
            buffer[buffer_index++]=ptr[mailbox_index].ack_id;
//            strcpy(buffer[buffer_index++],ptr[mailbox_index].data_ptr);
            buffer[buffer_index++]=end_of_frame;
        }
        
    }
    return  buffer_index;
}


