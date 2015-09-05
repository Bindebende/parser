# parser
In this repsitory I'm doing a messaging mechanism. This library would be part of my project where two embedded device can talk to each other the communication type is doesn't matter. For now this is not a full version it is under development.
how it is works:
- both device can send every type of messages
- it is a point to point request oriented communication 
- both device will send an acknowledge when recive a message then respond if there was a request 
- handshake mode: 
    - this mode is available when the device is boot and in error handling state. In this mode  the device constantly poll the other device and it will escape when the other device sends back an acknowledge.
- error handling: 
    - if the receiver miss the default message time out the transmitter will go back to handshake state 
- the maximum sendable data is defined in message_size which is currently 128bit. 

In the documentation folder you can find the code documentation done with HeaderDoc.