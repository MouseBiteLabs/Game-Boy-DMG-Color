# DMGC-IPS-01
**TO-DO:**
- Upload pictures
- Upload files

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

![image](https://user-images.githubusercontent.com/97127539/178794406-ef2e2fb0-8c2c-4575-bcdd-e084d73dbe3b.png)

Half of U1 is used as a buffer, for no reason other than it was available to use. When the power switch on the CPU board is turned on, the input to the buffer is half the battery voltage, from the voltage divider made from R11 and R12, and it feeds into another voltage divider made by R6 and R7 to cut it in half again. The ½ battery voltage is connected to a solder pad for connecting to the Q5 board for battery level indication – since the Q5 kit expects a GBC battery voltage, cutting the 4x AA battery voltage in half will scale the level correctly for proper measurement. 

The ¼ battery voltage is compared with the inverting input (set at 1.112 V via another voltage divider) on the other half of U1. R3 provides hysteresis on the comparator (i.e. Schmitt trigger), and C7 and C8 are for noise filtering. When the combined voltage of the 4x AAs drops below ~4.3 V, the battery level is considered low and the LED will noticeably dim. My testing came up with this voltage as approximately 1 hour of battery left (if at max brightness with headphones in).

The output of the comparator is set to 5V when the battery level is high, which turns on Q1; it is driven to GND when the battery level is low, which turns Q1 off. Therefore, the brightness of the LED during normal power is dictated only by the resistance of R1. When the combined battery voltage drops below the low battery threshold, R2 is placed in series with the LED as well, which dims the LED.


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

Code for the ATTINY85 is included here, however because I wrote this months ago (and forgot to comment it sufficiently...) I have forgotten how some of the code actually works. There's certainly room for improvement. But there *is* a nice startup effect to match the Game Boy Color boot sequence that a friend (jokingly) suggested I include. (If you hold the navigation switch in as you turn on the console, the LEDs will be disabled until power is cycled.)

Discrete LEDs are also an option - an 0603 LED will fit on half of the 4-pin RGB LED pads, from VDD to DO. The pads for this are indicated by the arrows. There are spaces for a resistor for each LED on the back of the board (R22 to R29). If you're using the RGB LEDs, or no LEDs at all, the resistors aren't necessary.
## Bill of Materials

Here, I have provided links to components I used personally (or suitable replacements). This BOM is also included in Excel format in the root folder.

| Reference Designators | Qty | Value/Part Number | Package             | Description                       | Comment                                                   | Source                                                                                                           |
|---------------------|-----|-------------------|---------------------|-----------------------------------|-----------------------------------------------------------|------------------------------------------------------------------------------------------------------------------|
| C1, C2, C7, C8, C24 | 5   | 100 nF            | 0603                | Capacitor (MLCC)                  | Should be X5R (or better), at least 25V                   | https://www.digikey.com/en/products/detail/kemet/C0603C104K4RAC7867/411095                                       |
| C3                  | 1   | 100 uF            | 5mm dia x 11 mm len | Capacitor (Aluminum electrolytic) | Board has space for a 100uF SMD tantalum electrolytic     | https://www.mouser.com/ProductDetail/KEMET/ESK107M025AC3AA?qs=Z46kSA%2FmtFiEo%2F6fDW5ebA%3D%3D                   |
| C4, C5              | 2   | 220 pF            | 0603                | Capacitor (MLCC)                  |                                                           | https://www.mouser.com/ProductDetail/Samsung-Electro-Mechanics/CL10B221KB8NFNC?qs=YCa%2FAAYMW03S2dLM1EfL7A%3D%3D |
| FFC Cable           | 1   | 0151660539        |                     | Flat Flexible Cable               |                                                           | https://www.digikey.com/en/products/detail/molex/0151660539/3281420                                              |
| J1, J2              | 2   |                   |                     | LCD connector                     |                                                           | https://www.digikey.com/en/products/detail/FFC2B17-50-T/2073-FFC2B17-50-TCT-ND/15181672?itemSeq=388086745        |
| LED1                | 1   |                   | 3mm                 | Red LED                           |                                                           | https://www.digikey.com/en/products/detail/151033RS03000/732-5013-ND/4490003?itemSeq=388099998                   |
| LED10-LED17         | 8   | WS2812            | 2020                | RGB LED                           |                                                           | https://www.mouser.com/ProductDetail/Adafruit/4684?qs=DPoM0jnrROWIv9%2FMCIm5vw%3D%3D                             |
| Q1                  | 1   | MMBT3904          | SOT23               | NPN BJT                           |                                                           | https://www.digikey.com/en/products/detail/micro-commercial-co/MMBT3904-TP/717280                                |
| R1, R22-R29         | 9   | 1 kΩ              | 0603                | Resistor                          | R22-R29 optional (only if discrete LEDs for LED10-LED17)  | https://www.digikey.com/en/products/detail/yageo/RC0603FR-071KL/726843                                           |
| R2, R9              | 2   | 510 Ω             | 0603                | Resistor                          |                                                           | https://www.digikey.com/en/products/detail/yageo/RC0603FR-07510RL/727285                                         |
| R3, R5              | 2   | 402 kΩ            | 0603                | Resistor                          |                                                           | https://www.digikey.com/en/products/detail/yageo/RC0603FR-07402KL/727223                                         |
| R4                  | 1   | 100 Ω             | 0603                | Resistor                          |                                                           | https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100RL/726888                                         |
| R6, R7, R11, R12    | 4   | 249 kΩ            | 0603                | Resistor                          |                                                           | https://www.digikey.com/en/products/detail/yageo/RC0603FR-07249KL/727086                                         |
| R8                  | 1   | 100 kΩ            | 0603                | Resistor                          |                                                           | https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100KL/726889                                         |
| R13                 | 1   | 15 kΩ             | 0603                | Resistor                          |                                                           | https://www.digikey.com/en/products/detail/yageo/RC0603FR-1015KL/13694096                                        |
| Speaker             | 1   | 8 Ω                |                     | Speaker                           | Can also used salvaged DMG speaker                        | https://retrogamerepairshop.com/products/funnyplaying-clear-game-boy-dmg-original-speaker?variant=37728957726892 |
| SW1                 | 1   |                   |                     | Navigation switch                 |                                                           | https://www.digikey.com/en/products/detail/sparkfun-electronics/COM-08184/8543391                                |
| U1                  | 1   | LMV358            | SOIC-8              | Op-amp                            |                                                           | https://www.digikey.com/en/products/detail/texas-instruments/LMV358Q1MAX-NOPB/3926679                            |
| U2                  | 1   | ATTINY85          | SOIC-8 (5.3mm wide) | Microcontroller                   | Sometimes stocking issues - might be able to find on eBay | https://www.digikey.com/en/products/detail/microchip-technology/ATTINY85-20SFR/5057266                           |

## Resources
-	<a href="https://gbdev.gg8.se/files/schematics/">Rolf, bit9, and nitro2k01’s DMG schematics and layouts</a>
-	<a href="https://learn.adafruit.com/adafruit-neopixel-uberguide/downloads">Adafruit NeoPixel Resources</a>
-	<a href="https://github.com/HandHeldLegend/gbc-rgb-led-2.0">NiceMitch’s RGB LED flex PCB for GBC</a>
-	<a href="https://www.instructables.com/How-to-Burn-ATTiny85-Using-Arduino-Mega/">Instructables post for programming an ATTINY85 with an Arduino</a>
## License
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.


