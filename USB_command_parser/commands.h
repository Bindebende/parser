//
//  commands.h
//  USB_command_parser
//
//  Created by Bendegúz Hoffmann on 2015. 08. 30..
//  Copyright (c) 2015. Bendegúz Hoffmann. All rights reserved.
//

#ifndef __USB_command_parser__commands__
#define __USB_command_parser__commands__

#include <stdio.h>
#include <inttypes.h>

#define buffer_size 100

/*!
 @struct can_message
 @abstract holds one recived can frame
 @field message_identifier id of the frame
 @field identifier_extension equals to 1 if 2.0B frames that are recieved if equals to 0 it is 2.0A frame
 @field data_length_code 4 bit number which holds how many byte in the message
 @field message the message
 */
struct can_message{
    uint64_t message_identifier;
    uint32_t identifier_extension;
    uint32_t data_length_code;
    uint64_t message;
};




/*!
 *
 *  @function parse
 *  @abstract This function is to parse the recived bytes.
 *  @param buffer holds the recived bytes. It is an unsigned char array.
 *  @discussion Every message start with 0x55 this is not the part of the can frame just indicates that ther is a frame after it. Function will 
 *  search for it and if finds it will parse the can frame in to the can message structure
 *
 *  @var is_valid_message it is set if there is valid can frame and return with this variable
 *  @var i is an index variable
 *  @return 1 if it find a valid frame and 0 if not
 */
uint32_t parse(unsigned char *buffer);

#endif /* defined(__USB_command_parser__commands__) */
