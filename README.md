# DMXtoUSB
3 DMX Universes in a single Arduino Mega
# What is this suposed to be?
The atmega board with the correct RS485 drivers is connected to a PC. The PC can send commands to the Atmega via Serial interface connected to the USB.
The atmega, in turn, will select the appropriate DMX universe, set the correct channel and send all those bytes to the stream.

# How does it work?
The send() function will make sure the serial is correctly configured, will generate the header of the protocol, and start the sending process.
This process is no more than a ISR that will load the serial buffer with the next channel value and stops once it reach the end.
This ISR will be called by the machine when the data is being sent, so, this is a fast way to dump all the data.
The main loop checks the serial with the computeer and if the data was sent to the universes. 
It is worthed to note that, althoug there are many interruptions happening during the DMX part, the processor have a lot of idle time to do other stuff, like controlling NEOPixel lights

# What is next?
 - 1-> make this code cleaner
 - 2-> Add buttons, encoders and other stuf to control the dmx channels and universes.
 - 3-> Maybe a SPI display to handle the feedback to the user. 
 - 4-> Add the NeoPixel lib to handle RGB lights
 - 5-> ???
 
 # Why I stopped?
 Well, I did this in two days and I am tired... so, next week I try something more.
 
 # Was it tested?
 No. No time, nor rs485 drivers. Maybe you can test it?
 

