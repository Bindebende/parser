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

uint32_t send_message(uint32_t fd, uint8_t *buffer,struct mailbox *ptr)
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
    uint32_t mailbox_index=0;
    
    blank.message_type=0;                                                   
    blank.data_ptr=NULL;
    
    for(;mailbox_index<number_of_mailboxes;mailbox_index++) *(ptr+mailbox_index)=blank;                       /* copy the pattern structure to the array which n number of structure in it  */
}

uint32_t buffer_writing(uint8_t *buffer,struct mailbox *ptr )
{
    //this function writes all the recieved datas to the buffer checks the buffer boundries
    
    static uint32_t buffer_index=0;
    uint32_t mailbox_index=0;
    char *pointer_data=0;
    
   
    for(;mailbox_index<number_of_mailboxes;mailbox_index++)
    {
        if(ptr[mailbox_index].message_type!=0)
        {
            buffer_index&=buffer_size-1;
            
            buffer[buffer_index++]=start_of_frame;
            buffer[buffer_index++]=ptr[mailbox_index].message_type;
            buffer[buffer_index++]=ptr[mailbox_index].ack_id;
            pointer_data=ptr[mailbox_index].data_ptr;
            
            while(*pointer_data)
                buffer[buffer_index++]=*pointer_data++;
            
            buffer[buffer_index++]='\0';
            buffer[buffer_index++]=end_of_frame;
        }
        
    }
    return  buffer_index;
}

void request_execute(struct mailbox *ptr)
{
    uint32_t mailbox_index=0;
    
    for(;mailbox_index<number_of_mailboxes;mailbox_index++)
    {
       if(ptr[mailbox_index].message_type==request)
       {
           switch(ptr[mailbox_index].ack_id)
           {
                case request_id_time:break;
                case request_id_date:printf("succes\n\r");break;
                case request_id_acc:break;
                case request_id_mag:break;
                case request_id_gyro:break;
                case request_id_heading:break;
                case request_id_temp:break;
                case request_id_coordinates:break;
                case request_id_altitude:printf("succes\n\r");break;
                case request_id_set_gpio:break;
                case request_id_obd:break;
                case request_id_CAN_filter:break;
           
           
           }
       }
    
    }
    

}



void print_mailboxes(struct mailbox *ptr)
{
    uint32_t mailbox_index=0;
    
    for(;mailbox_index<number_of_mailboxes;mailbox_index++)
    {
        if(ptr[mailbox_index].message_type!=0)   // only prints the mailboxes which holds a message
        {
            
            printf("mailbox%d:\n\r",mailbox_index);
            if(request==ptr[mailbox_index].message_type)printf("request id:%d\r\n",ptr[mailbox_index].ack_id);
            
            else
            {
                printf("data id:%d message:",ptr[mailbox_index].ack_id);
                char *temp=ptr[mailbox_index].data_ptr;
                
                while(!(*temp==end_of_frame))
                    printf("%c",*temp++);
                
                
            }
            printf("\n\r");
        }
        
    }
    
}


