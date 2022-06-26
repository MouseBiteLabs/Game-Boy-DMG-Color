# DMGC-IPS-01
**TO-DO:**
- Upload pictures
- Upload files
- In-text links
- Upload BOM

[blank board pictures]

The IPS board is in the front of the DMG shell. This holds the IPS screen kit (and has pads for interfacing with it), has the dimmable power LED, button inputs along with pads for optional LEDs, a navigation switch on the side for changing settings on the IPS screen and the backlit buttons, and the speaker.
## Board Characteristics
-	Layers: 2
-	Thickness: 1.2 mm
-	Surface Finish: ENIG
## FFC Connectors
There are two FFC connectors on the board - one to take the input from the CPU board, the other is for the Q5 board to connect to. The former is detailed in the CPU board section, and the latter simply omits a few pins to connect to the Q5 board, such as the speaker and button inputs. Notably, the connector going to the CPU board must be reversed due to the FFC cable connecting it to the CPU board.

![image](https://user-images.githubusercontent.com/97127539/175817051-5b833e8b-1a99-46bd-abc8-d2abbde9cd2a.png)

All of the unused pins on the Q5 board (CLS, R0, G0, and B0) that are populated on the FFC connector are inconsequential, they just don’t go anywhere on the cable.
## Speaker
I detail the operation of the audio amplifier on the CPU board in that corresponding readme. I mention that a DC blocking capacitor needs to be included in series with the speaker output. That’s what C3 is for, a 100 uF capacitor. There are two capacitors called out as C3 – a space for an aluminum electrolytic capacitor, and one for an electrolytic tantalum. I have a ton of aluminums and they’re cheaper, so that’s the one I used. The speaker itself is an aftermarket FunnyPlaying model.
## Power LED and Dimming Circuit
The power LED is a standard 3mm red LED. The circuit detailed here is a simple comparator circuit.

![image](https://user-images.githubusercontent.com/97127539/175817231-b95eaa5c-ca42-4869-9039-e553d6672c4e.png)

Half of U1 is used as a buffer, for no reason other than it was available to use. When the power switch on the CPU board is turned on, the input to the buffer is half the battery voltage, from the voltage divider made from R11 and R12, and it feeds into another voltage divider made by R6 and R7 to cut it in half again. The ½ battery voltage is connected to a solder pad for connecting to the Q5 board for battery level indication – since the Q5 kit expects a GBC battery voltage, cutting the 4x AA battery voltage in half will scale the level correctly for proper measurement. 

The ¼ battery voltage is compared with the inverting input (set at 1.075 V via another voltage divider) on the other half of U1. This means that when the combined voltage of the 4x AAs drops below 4.45 V, the battery level is considered low and the LED will noticeably dim. My testing came up with this voltage as approximately 1 hour of battery left (if at max brightness with headphones in).

The output of the comparator is set to 5V when the battery level is high, which turns on Q1; it is driven to GND when the battery level is low, which turns Q1 off. Therefore, the brightness of the LED during normal power is dictated only by the resistance of R1. When the combined battery voltage drops below the low battery threshold, R2 is placed in series with the LED as well, which dims the LED.

R3 provides hysteresis on the comparator (i.e. Schmitt trigger), and C7 and C8 are for noise filtering.
## Navigation Switch
This takes place where the contrast wheel used to be. Popular DMG IPS kits use this kind of dial for controlling the settings on the display. On the Q5 board, there are two capacitive sensors - one for changing brightness, one for changing the color palette. Instead of using the touch sensors in the DMGC, the navigation switch will toggle these inputs by connecting a series capacitance to ground to simulate a touch. This also has the benefit of not having to modify the driver board in any way, and instead just requiring soldered wires to the board where capacitive sensors were connected.

![image](https://user-images.githubusercontent.com/97127539/175817034-c6ba2a92-8968-4777-850f-0b2ecb9984e5.png)

Rocking up on the dial will toggle the brightness setting, rocking it down will toggle the color palette setting. Rocking up and holding it will toggle the battery level display on the board, and rocking it down and holding it will toggle the pixel grid. Pushing in on the switch grounds the ATTINY85's PB3 pin (which is pulled up externally to 3.3V), if installed.
## Q5 Board Pads
There are six test points at the top of the IPS board for short wires to connect to the Q5 board. The Q5 board includes pads for the select, B, and A buttons for navigation in the OSD. There's also a battery pad, which is for measuring the battery life, as mentioned. And finally, there are two pads for brightness control and color palette swapping, which connect to the capacitive touch sensor inputs on the Q5 board.
## Button LEDs and ATTINY85
One popular feature for Game Boy mods are backlit buttons. On the front PCB I included spaces for eight WS2812B-2020 RGB LEDs. These are controlled via an ATTINY85 with the Adafruit NeoPixel library. 

![image](https://user-images.githubusercontent.com/97127539/175817148-27315e43-d1c2-4014-86f2-ae710ad1446b.png)

There are nine color settings - red, orange, yellow, green, cyan, blue, purple, white, and off. These settings can be manually changed (or additional settings could be appended) by changing the RGB values in the arrays. Pushing in on the navigation switch will toggle between these settings. Pushing and holding it in, and then pressing left or right will change the brightness of the LEDs. The settings are saved every time the brightness or color is changed, and will be reloaded when turning on the Game Boy. This feature was inspired by NiceMitch's RGB LED flex PCB for GBC.

There's also a nice startup effect to match the Game Boy Color boot sequence :)

Discrete LEDs are also an option - an 0603 LED will fit on half of the 4-pin RGB LED pads, from VDD to DO. The pads for this are indicated by the arrows. There are spaces for a resistor for each LED on the back of the board (R22 to R29). If you're using the RGB LEDs, or no LEDs at all, the resistors aren't necessary.
## Bill of Materials
Lots of parts.
## Resources
-	Rolf, bit9, and nitro2k01’s DMG schematics and layouts
-	Adafruit NeoPixel Resources
-	NiceMitch’s RGB LED flex PCB for GBC
## License
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.


