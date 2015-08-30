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


/**
 *  @struct can_message
 *
 *
 *
 */
struct can_message{
    uint64_t message_identifier;
    uint32_t identifier_extension;
    uint32_t data_length_code;
    uint64_t message;
    uint32_t cyclic_redundancy_check;
    
};

#endif /* defined(__USB_command_parser__commands__) */
