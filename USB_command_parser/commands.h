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

#define buffer_size             128
#define message_size            128
#define number_of_mailboxes     16


#define   start_of_frame    0x55
#define   handshake         0x01
#define   request           0x02
#define   data              0x03
#define   acknowledge       0x04
#define   end_of_frame      '\n'

#define   request_id_time              0x05
#define   request_id_date              0x06
#define   request_id_acc               0x07
#define   request_id_mag               0x08
#define   request_id_gyro              0x09
#define   request_id_heading           0x0A
#define   request_id_temp              0x0B
#define   request_id_coordinates       0x0C
#define   request_id_altitude          0x0D
#define   request_id_set_gpio          0x0E
#define   request_id_obd               0x0F
#define   request_id_CAN_filter        0x10



/*!
 @struct mailbox
 @abstract holds one recived frames
 @field message_identifier id of the frame
@field data_ptr points to the buffer array where starts the partcular message

 */
struct mailbox{
    uint32_t message_type;
    uint8_t ack_id;
    char *data_ptr;
};


/*!
 *
 *  @function parse
 *  @abstract This function is to parse the recived bytes.
 *  @param buffer holds the recived bytes. It is an unsigned char array.
 *  @discussion The frame layout:
 *                  |SOF|message_type|id|message|'\0'|EOF|
 *A message_type character. This tells the recievert which kind of message have to parse. 
 *id: which is the id of different messages
 *message: there is a data field 
 *end of frame characters:'\0'|EOF
 *Function will search for it and if it finds the function will parse it will parse the frame in to the message structure. And if there is a message it will flush the whole buffer at the end of the parse.
 *
 *  @var is_valid_message set 1 if there was a message 0 if not. This is also the return value
 *  @var ptr 
 *  @var sof_index holds the value where was the last start of frame character
 *  @var eof_index holds the value where was the last end of frame character
 *
 * @return 1 if it find a valid frame and 0 if not
 */
uint32_t parse(uint8_t *buffer,struct mailbox *ptr);

/*!
 *  @brief  This functiion send mailbox on the desired communication protocol
 *
 *  @param buffer points to the sendable structure
 *  @param fd file descriptor.
 *  @param ptr points to the mailbox array
 *
 *  @return the type of the message
 */
uint32_t send_message(uint32_t fd,  uint8_t *buffer,struct mailbox *ptr);

/*!
 *  @brief  fill's the array with 0's
 *
 *  @param buffer points to the flushable array
 *
 *  @var strln holds the number of character which is in the array and used for indexing the array
 */
void flush_buffer(uint8_t *buffer );

/*!
 *  @brief  this function writes all the recieved datas to the buffer checks the buffer boundries
 *
 *  @param buffer points to the reciever buffer
 *
 *  @var buffer_index holds the value where is the last byte of message 
 *  @var mailbox_index index the mailbox array
 *  @var pointer_data points to the structure data_ptr field
 *
 *  @return buffer_index
 */
uint32_t buffer_writing(uint8_t *buffer,struct mailbox *ptr);


/*!
 *  @brief  uploads the structure with a blank pattern structure to give it a initial value
 *
 *  @param ptr points to the array which holds the mailbox structures
 *
 *  @var blank a blank structure which will be the pattern
 *  @var mailbox_index
 *
 */
void flush_mailboxes(struct mailbox *ptr);

/*!
 *  @brief  prints the elements of the mailboxes to the stdio
 *
 *  @param ptr points to the array which holds the mailbox structures
 *
 *  @var mailbox_index used to index the array which holds the structures
 *
 *
 */
void print_mailboxes(struct mailbox *ptr);

/*!
 *  @brief  execute what was the request and uploads the transmitt mailboxes.
 *
 *  @param rx  points to the array which holds the recive mailbox structures
 *  @param tx  points to the array which holds the transmitt mailbox structures
 */
void request_execute(struct mailbox *rx,struct mailbox *tx );

#endif /* defined(__USB_command_parser__commands__) */












