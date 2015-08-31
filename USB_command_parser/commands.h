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

#define buffer_size     100
#define message_size    128


enum message_modes{

    handshake=  0x01,
    request=    0x02,
    data=       0x03,
    acknowledge=0x04,
};




/*!
 @struct message
 @abstract holds one recived frames
 @field message_identifier id of the frame
 @field message_data holds the recived data or commands
 */
struct command_message{
    uint32_t message_type;
    uint8_t message_data[128];
};



/*!
 @struct can_message
 @abstract holds one recived can frame
 @field message_identifier id of the frame
 @field message the message
 */
struct can_message{
    uint64_t message_identifier;
    uint64_t message;
};




/*!
 *
 *  @function parse
 *  @abstract This function is to parse the recived bytes.
 *  @param buffer holds the recived bytes. It is an unsigned char array.
 *  @discussion Every message start with message_type filed. This tells the recievert which kind of message have to parse. Function will
 *  search for it and if it finds the function will parse it will parse the frame in to the message structure
 *
 *  @var is_valid_message it is set if there is valid can frame and return with this variable
 *  @var i is an index variable
 *  @return 1 if it find a valid frame and 0 if not
 */
uint32_t parse(unsigned char *buffer);

#endif /* defined(__USB_command_parser__commands__) */
