# DMXtoUSB
3 DMX Universes in a single Arduino Mega
# What is this suposed to be?
The atmega board with the correct RS485 drivers is connected to a PC. The PC can send commands to the Atmega via Serial interface connected to the USB.
The atmega, in turn, will select the appropriate DMX universe, set the correct channel and send all those bytes to the stream.

# How does it work?
The send() function will make sure the serial is correctly configured, will generate the header of the protocol, and start the sending process.
This process is no more than a ISR that will load the serial buffer with the next channel value and stops once it reach the end.
This ISR will be called by the machine when the data is being sent, so, this is a fast way to dump all the data.
The main loop makes waits until the "send" process is finished and then process all the information in Serial memory. 
It is worthed to note that, althoug there are many interruptions happening during the DMX part, the processor har a lot of idle time to do other stuff.

