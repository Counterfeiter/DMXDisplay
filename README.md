DMX Display C-Project
==============

A little 16 x 2 character display with two RS485 inputs (or outputs). Firmware is written to receive DMX protocol and uses the first 3 + 32 bytes from the DMX stream.
It's possible to implement the atmel flip bootloader and update the firmware over USB.

License
--------------
GPLv2

Software
--------------
Atmel Studio 6.2

ToDo
--------------
- DMX output ?

Use
--------------
- see my other github projects for free schematic and board design (pinning)
- input DMX: 250 kbaud 8N2 - break + first byte always zero

DMX Display Protocol
--------------
- first byte is command or versions byte - must always be 0x01
- second byte defines the display contrast 0x00 to 0xFF
- thrid byte defines the brightness of the background LEDs
- following 32 bytes are ASCII char's to display, start is top left