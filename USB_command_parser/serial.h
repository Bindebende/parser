//
//  serial.h
//  USB_command_parser
//
//  Created by Bendegúz Hoffmann on 2015. 07. 18..
//  Copyright (c) 2015. Bendegúz Hoffmann. All rights reserved.
//

#ifndef __USB_command_parser__serial__
#define __USB_command_parser__serial__

#include <stdio.h>

#define buffer_size 100


int set_interface_attribs (int, int, int );

void set_blocking (int fd, int should_block);



#endif /* defined(__USB_command_parser__serial__) */
