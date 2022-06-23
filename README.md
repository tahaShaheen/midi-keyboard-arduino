______________________________________________________________________________________________________
# midi-keyboard-arduino
Converting my 61 key keyboard to MIDI
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Keys that are next to each other are still not detected together. 
That's a problem for another day. 
I'll solve it when I need to press neighbouring keys. 
______________________________________________________________________________________________________


Instructions for the code
==========================

1) https://medium.com/@mero11.gh/midi-fying-an-old-casio-digital-keyboard-6a9ae9f3092b
2) https://www.instructables.com/How-to-Make-Midi-Keyboard-Using-Arduino/
3) https://www.instructables.com/Arduino-Easy-Midi-Keyboard/

To play the keyboard with MIDI without updating firmware
==========================================================
1) hairless MIDI
2) loopMIDI

MIDI baudrate is 31250.

Instructions here
-------------------
1) https://projectgus.github.io/hairless-midiserial/

"NB: To convey Windows MIDI data from one bit of software to another, you’ll need a Virtual MIDI passthrough driver. We recommend loopMIDI, or there is alternatively the older MIDI Yoke (MIDI Yoke is not recomended for Vista or newer.)"

2) http://www.tobias-erichsen.de/software/loopmidi.html

Updating firware
=================

Firmware used:
--------------
1) https://github.com/kuwatay/mocolufa

I used the .hex file in the HEX folder. 

Instructions for updating firware
---------------------------------
1) https://support.arduino.cc/hc/en-us/articles/4408887452434-Flash-USB-to-serial-firmware-in-DFU-mode#install-libusb-win32

Software used in Windows
------------------------
1) https://www.microchip.com/en-us/development-tool/flip

FLIP 3.4.x for Windows (Java Runtime Environment included)	



TO REPROGRAM ARDUINO'S ATMEGA CHIP
==================================
This is to update the program.


1) http://morecatlab.akiba.coocan.jp/lab/index.php/aruino/midi-firmware-for-arduino-uno-moco/?lang=en
Before connecting Uno to PC, install a jumper between pin4 and pin6 on ICSP connector (this is the USB connector ICSP not the Mega ICSP) for Mega8u2/16U2. With the jumper, Arduino-serial mode is initiated. You can use Arduino IDE to program mega328 on Uno.

There's a picture on the website. Look at it for help.
