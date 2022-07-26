# DMGC-IPS-01

![image](https://user-images.githubusercontent.com/97127539/180129119-8bb84143-6f4e-4875-b3c3-675d98bbcf43.png)
![image](https://user-images.githubusercontent.com/97127539/180912167-1ed4864c-d77d-4482-bf83-c783f309239a.png)

*This specific board is v1.2, which only has minor differences from the updated v1.3 (some minor bodge fixes)*

The IPS board is in the front of the DMG shell. This holds the IPS screen kit (and has pads for interfacing with it), has the dimmable power LED, button inputs along with pads for optional LEDs, a navigation switch on the side for changing settings on the IPS screen and the backlit buttons, and the speaker.

## Board Characteristics

The zipped folder contains all the gerber files for this board.
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

![image](https://user-images.githubusercontent.com/97127539/180365287-b848c999-a118-487a-aea3-46d1e5c0d590.png)

Half of U1 is used as a buffer, for no reason other than it was available to use. When the power switch on the CPU board is turned on, the input to the buffer is half the battery voltage, from the voltage divider made from R11 and R12, and it feeds into another voltage divider made by R6 and R7 to cut it in half again. C6 is for noise filtering. The ½ battery voltage is connected to a solder pad for connecting to the Q5 board for battery level indication – since the Q5 kit expects a GBC battery voltage, cutting the 4x AA battery voltage in half will scale the level correctly for proper measurement. 

The ¼ battery voltage is compared with the inverting input (set at 1.112 V via another voltage divider) on the other half of U1. R3 provides hysteresis on the comparator circuit (i.e. Schmitt trigger), and C7 and C8 are for noise filtering. When the combined voltage of the 4x AAs drops below ~4.35 V, the battery level is considered low and the LED will noticeably dim. My testing came up with this voltage as approximately 30 to 45 minutes of playtime left if at max brightness with headphones in, testing from fully charged batteries. If you reduce screen brightness or reduce the volume, you might get more time out of the batteries.

The output of the comparator circuit is set to 5V when the battery level is high, which turns on Q1; it is driven to GND when the battery level is low, which turns Q1 off. Therefore, the brightness of the LED during normal power is dictated only by the resistance of R1. When the combined battery voltage drops below the low battery threshold, R2 is placed in series with the LED as well, which dims the LED. I played around with these values to find values that didn't hurt my eyes for normal brightness, and produced a noticeably dimmed power LED.

## Navigation Switch
This takes place where the contrast wheel used to be. Popular DMG IPS kits use this kind of dial for controlling the settings on the display. On the Q5 board, there are two capacitive touch sensors - one for changing brightness, one for changing the color palette. Instead of using the touch sensors in the DMGC, the navigation switch will toggle these inputs by connecting a series capacitance to ground to simulate a touch. This also has the benefit of not having to modify the driver board in any way, and instead just requiring soldered wires to the board where capacitive sensors were connected.

![image](https://user-images.githubusercontent.com/97127539/179892312-2037ac53-8394-4e16-a0ad-1f3e53fa8b06.png)

Rocking up on the dial will toggle the brightness setting, rocking it down will toggle the color palette setting. Rocking up and holding it will toggle the battery level display on the board, and rocking it down and holding it will toggle the pixel grid. Pushing in on the switch grounds the ATTINY85's PB3 pin (which is pulled up externally to 3.3V), if installed.

## Q5 Board Pads
There are six test points at the top of the IPS board for short wires to connect to the Q5 board. The Q5 board includes pads for the select, B, and A buttons for navigation in the OSD. There's also a battery pad, which is for measuring the battery life, as mentioned. And finally, there are two pads for brightness control and color palette swapping, which connect to the capacitive touch sensor inputs on the Q5 board.

## Button LEDs and ATTINY85
One popular feature for Game Boy mods are backlit buttons. On the front PCB I included spaces for eight WS2812B-2020 RGB LEDs. These are controlled via an ATTINY85 with the Adafruit NeoPixel library. 

![image](https://user-images.githubusercontent.com/97127539/179892408-eaa9b55a-16b3-4a5e-b21f-08dbbbba21d7.png)

*Note that if you do not wish to include LEDs for the buttons, you don't need to populate any of the parts shown in this screenshot.*

There are nine color settings - red, orange, yellow, green, cyan, blue, purple, white, and off. These settings can be manually changed (or additional settings could be appended) by changing the RGB values in the arrays. Pushing in on the navigation switch will toggle between these settings. Pushing and holding it in, and then pressing left or right will change the brightness of the LEDs. The settings are saved every time the brightness or color is changed, and will be reloaded when turning on the Game Boy. This feature was inspired by NiceMitch's RGB LED flex PCB for GBC.

Code for the ATTINY85 is included here, however because I wrote this months ago (and forgot to comment it sufficiently...) I have forgotten how some of the code actually works. There's certainly room for improvement. But there *is* a nice startup effect to match the Game Boy Color boot sequence that a friend (jokingly) suggested I include.

If you hold the navigation switch in as you turn on the console, the LEDs will be disabled until power is cycled. (This is probably more for my benefit as I used it while testing very discharged batteries to skip the start-up LED sequence)

Discrete LEDs are also an option - an 0603 LED will fit on half of the 4-pin RGB LED pads, from VDD to DO. The pads for this are indicated by the arrows. The picture below shows which pads to use for discrete LEDs (view of the D-pad) - the A indicates the anode of the diode. There are spaces for a resistor for each LED on the back of the board (R22 to R29). If you're using the RGB LEDs, or no LEDs at all, the resistors aren't necessary.

![image](https://user-images.githubusercontent.com/97127539/180103597-06642f10-77f8-44f2-84d5-dac01b80fdf1.png)

## Q5 IPS Screen Bracket
I designed a bracket for holding the screen in place. This is placed between the screen and the DMGC-IPS-01 board. Assembly notes are located in the root folder's README, and the model is available for download above.

![image](https://user-images.githubusercontent.com/97127539/179893357-2857c4a3-07b2-433d-b50c-6ba5824419b2.png)

## Bill of Materials

Here, I have provided links to components I used personally (or suitable replacements). This BOM is also included in Excel format in the root folder.

| Reference Designators   | Qty | Value/Part Number | Package             | Description                       | Comment                                                                        | Source                                                                                                                                                                                                                               |
| ----------------------- | --- | ----------------- | ------------------- | --------------------------------- | ------------------------------------------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| C1, C2, C6, C7, C8, C24 | 6   | 100nF             | 0603                | Capacitor (MLCC)                  | Should be X5R (or better), at least 16V                                        | [https://www.digikey.com/en/products/detail/kemet/C0603C104K4RAC7867/411095](https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10B104KO8NNWC/3887597?s=N4IgTCBcDaIMIBkCMAGAQqgLAaQPIA4A5QgdThAF0BfIA)           |
| C3                      | 1   | 100uF             | 5mm dia x 11 mm len | Capacitor (Aluminum electrolytic) | Board has space for a 100uF SMD tantalum electrolytic instead                  | [https://www.mouser.com/ProductDetail/KEMET/ESK107M025AC3AA?qs=Z46kSA%2FmtFiEo%2F6fDW5ebA%3D%3D](https://www.mouser.com/ProductDetail/KEMET/ESK107M025AC3AA?qs=Z46kSA%2FmtFiEo%2F6fDW5ebA%3D%3D)                                     |
| C4, C5                  | 2   | 220pF             | 0603                | Capacitor (MLCC)                  |                                                                                | [https://www.mouser.com/ProductDetail/Samsung-Electro-Mechanics/CL10B221KB8NFNC?qs=YCa%2FAAYMW03S2dLM1EfL7A%3D%3D](https://www.mouser.com/ProductDetail/Samsung-Electro-Mechanics/CL10B221KB8NFNC?qs=YCa%2FAAYMW03S2dLM1EfL7A%3D%3D) |
| FFC Cable               | 1   | 0151660539‎       |                     | Flat Flexible Cable               |                                                                                | [https://www.digikey.com/en/products/detail/molex/0151660539/3281420](https://www.digikey.com/en/products/detail/molex/0151660539/3281420)                                                                                           |
| J1, J2                  | 2   | FFC2B17-50-T      |                     | LCD connector                     |                                                                                | [https://www.digikey.com/en/products/detail/FFC2B17-50-T/2073-FFC2B17-50-TCT-ND/15181672?itemSeq=388086745](https://www.digikey.com/en/products/detail/FFC2B17-50-T/2073-FFC2B17-50-TCT-ND/15181672?itemSeq=388086745)               |
| LED1                    | 1   | 151033RS03000     | 3mm                 | Red LED                           |                                                                                | [https://www.digikey.com/en/products/detail/151033RS03000/732-5013-ND/4490003?itemSeq=388099998](https://www.digikey.com/en/products/detail/151033RS03000/732-5013-ND/4490003?itemSeq=388099998)                                     |
| LED10-LED17             | 8   | WS2812            | 2020                | RGB LED                           | Link leads to a 10-pack. Discrete 0603-size LEDs can be used instead           | [https://www.mouser.com/ProductDetail/Adafruit/4684?qs=DPoM0jnrROWIv9%2FMCIm5vw%3D%3D](https://www.mouser.com/ProductDetail/Adafruit/4684?qs=DPoM0jnrROWIv9%2FMCIm5vw%3D%3D)                                                         |
| Q1                      | 1   | 2N7002            | SOT23               | N-channel MOSFET                  |                                                                                | [https://www.digikey.com/en/products/detail/nexperia-usa-inc/2N7002NXBKR/10416553](https://www.digikey.com/en/products/detail/nexperia-usa-inc/2N7002NXBKR/10416553)                                                                 |
| R1                      | 1   | 1k                | 0603                | Resistor                          |                                                                                | [https://www.digikey.com/en/products/detail/yageo/RC0603FR-071KL/726843](https://www.digikey.com/en/products/detail/yageo/RC0603FR-071KL/726843)                                                                                     |
| R22-R29                 | 8   | 10k               | 0603                | Resistor                          | Only if using discrete LEDs for LED10-LED17 (adjust resistance for brightness) | [https://www.digikey.com/en/products/detail/yageo/RC0603FR-0710KL/726880](https://www.digikey.com/en/products/detail/yageo/RC0603FR-0710KL/726880)                                                                                   |
| R2, R6, R7              | 3   | 18k               | 0603                | Resistor                          |                                                                                | [https://www.digikey.com/en/products/detail/yageo/RC0603FR-1018KL/13694163](https://www.digikey.com/en/products/detail/yageo/RC0603FR-1018KL/13694163)                                                                               |
| R3, R5, R11, R12        | 4   | 402k              | 0603                | Resistor                          |                                                                                | [https://www.digikey.com/en/products/detail/yageo/RC0603FR-07402KL/727223](https://www.digikey.com/en/products/detail/yageo/RC0603FR-07402KL/727223)                                                                                 |
| R4                      | 1   | 100               | 0603                | Resistor                          |                                                                                | [https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100RL/726888](https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100RL/726888)                                                                                 |
| R8, R10                 | 2   | 100k              | 0603                | Resistor                          |                                                                                | [https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100KL/726889](https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100KL/726889)                                                                                 |
| R9                      | 1   | 510               | 0603                | Resistor                          |                                                                                | [https://www.digikey.com/en/products/detail/yageo/RC0603FR-07510RL/727285](https://www.digikey.com/en/products/detail/yageo/RC0603FR-07510RL/727285)                                                                                 |
| R13                     | 1   | 15k               | 0603                | Resistor                          |                                                                                | [https://www.digikey.com/en/products/detail/yageo/RC0603FR-1015KL/13694096](https://www.digikey.com/en/products/detail/yageo/RC0603FR-1015KL/13694096)                                                                               |
| Speaker                 | 1   | 8Ω                |                     | Speaker                           | Can also used salvaged DMG speaker                                             | [https://retrogamerepairshop.com/products/funnyplaying-clear-game-boy-dmg-original-speaker?variant=37728957726892](https://retrogamerepairshop.com/products/funnyplaying-clear-game-boy-dmg-original-speaker?variant=37728957726892) |
| SW1                     | 1   |                   |                     | Navigation switch                 |                                                                                | [https://www.digikey.com/en/products/detail/sparkfun-electronics/COM-08184/8543391](https://www.digikey.com/en/products/detail/sparkfun-electronics/COM-08184/8543391)                                                               |
| U1                      | 1   | LMV358M           | SOIC-8              | Op-amp                            |                                                                                | [https://www.digikey.com/en/products/detail/texas-instruments/LMV358Q1MAX-NOPB/3926679](https://www.digikey.com/en/products/detail/texas-instruments/LMV358Q1MAX-NOPB/3926679)                                                       |
| U2                      | 1   | ATTINY85          | SOIC-8 (5.3mm wide) | Microcontroller                   | Only if using NeoPixels (might need to buy the ATTINY from eBay or AliEx)      | [https://www.digikey.com/en/products/detail/microchip-technology/ATTINY85-20SFR/5057266](https://www.digikey.com/en/products/detail/microchip-technology/ATTINY85-20SFR/5057266)                                                     |

## Revision History

### v1.3

- Fixed Schmitt trigger circuit for power LED dimming

### v1.2

- Release version

## Resources
-	<a href="https://gbdev.gg8.se/files/schematics/">Rolf, bit9, and nitro2k01’s DMG schematics and layouts</a>
-	<a href="https://learn.adafruit.com/adafruit-neopixel-uberguide/downloads">Adafruit NeoPixel Resources</a>
-	<a href="https://github.com/HandHeldLegend/gbc-rgb-led-2.0">NiceMitch’s RGB LED flex PCB for GBC</a>
-	<a href="https://www.instructables.com/How-to-Burn-ATTiny85-Using-Arduino-Mega/">Instructables post for programming an ATTINY85 with an Arduino</a>

## License
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

©MouseBiteLabs 2022
