# DMGC-IPS-01

![DMGC-IPS-01_2-0_scan](https://user-images.githubusercontent.com/97127539/197367471-2bdfcaa6-c19a-4c33-977c-d3e0061d932d.jpg)
![DMGC-IPS-01_2-0_ASSEMBLED](https://user-images.githubusercontent.com/97127539/197367472-31a2fdb9-6a8e-41a7-8fdc-138f91f944bb.jpg)

The IPS board is in the front of the DMG shell. This holds the IPS screen kit (and has pads for interfacing with it), has the dimmable power LED, button inputs along with pads for optional LEDs, a navigation switch on the side for changing settings on the IPS screen and the backlit buttons, and the speaker.

## Board Characteristics

The zipped folder contains all the gerber files for this board.
-	Layers: 2
-	Thickness: 1.2 mm
-	Surface Finish: ENIG 

*ENIG is required for reliable button press detection.*

<a href="https://www.etsy.com/listing/1331663235/game-boy-dmgc-ips-board">**I sell this board on Etsy, so you don't have to buy multiples from board fabricators.**</a>

You can atlernatively use the zipped folder at any board fabricator you like. You may also buy the board from PCBWay using this link (disclosure: I receive 10% of the  sale value to go towards future PCB orders):

<a href="https://www.pcbway.com/project/shareproject/Game_Boy_DMG_Color_DMGC_IPS_01_82a454c9.html"><img src="https://www.pcbway.com/project/img/images/frompcbway-1220.png" alt="PCB from PCBWay" /></a>

## Optional Tactile Buttons
Version 2.0 introduced the option for including tactile switches for the buttons, much like the Game Boy Advance SP had. I did not however bother to add switches for start and select, due to the mismatched geometry (and you don't press them *that* often). If you do not wish to use these kinds of buttons, the button contacts are still set up to act just like the regular set up with membranes.

![image](https://user-images.githubusercontent.com/97127539/197367604-69478124-7a7e-4d84-897d-eac90462ccb7.png)
In this image, tactile switches are on the left, and pads for simple membranes are on the right. Either method for button presses works perfectly fine.

## FFC Connectors
There are two FFC connectors on the board - one to take the input from the CPU board, the other is for the Q5 board to connect to. The former is detailed in the CPU board section, and the latter simply omits a few pins to connect to the Q5 board, such as the speaker and button inputs. Notably, the connector going to the CPU board must be reversed due to the FFC cable connecting it to the CPU board.

![image](https://user-images.githubusercontent.com/97127539/196016635-e2304038-f734-4f08-a687-dbfb725eb1d6.png)

## Speaker
I detail the operation of the audio amplifier on the CPU board in that corresponding README. I mention that a DC blocking capacitor needs to be included in series with the speaker output. That’s what C3 is for, a 100 uF capacitor. There are two capacitors called out as C3 – a space for an aluminum electrolytic capacitor, and one for an electrolytic tantalum (or other surface mount varieties - do you fancy yourself a film cap?). The surface mount pad is size 3528, sized up for compatibility with many different types of SMT capacitor sizes. If you install the through-hole electrolytic, bend it down into the notch on the board. I have a ton of aluminums and they’re cheaper, so that’s the one I used. The speaker itself is an aftermarket FunnyPlaying model.

![image](https://user-images.githubusercontent.com/97127539/185511435-2cb1f5ca-924b-4827-beea-9865a0716af6.png)

## Power LED and Dimming Circuit
The power LED is a standard 3mm red LED. For low power detection, I used a simple Schmitt trigger circuit.

![image](https://user-images.githubusercontent.com/97127539/184360221-3d7121eb-2985-441e-ae19-26c8ac55e4d1.png)

When the power switch on the CPU board is turned on, the input to the buffer (U1B) is half the battery voltage, from the voltage divider made from R11 and R12 (C6 is for noise filtering purposes). This output is connected to the Q5 board's BATT solder pad for battery level indication. Since the Q5 kit expects a GBC battery voltage, which uses 2x AA batteries, cutting the 4x AA battery voltage in half will scale it properly. The Q5 board itself uses a voltage divider for scaling the battery voltage, so the voltage on the BATT pad must be from a low impedance source so as not to ruin the scaling factor - therefore, it must come off of the op-amp output itself, rather than the voltage divider.

The ½ battery voltage is then cut in half again via the voltage divider made by R6 and R7. The ¼ battery voltage is compared with the inverting input on the other half of U1. R3 provides hysteresis on the comparator circuit (i.e. Schmitt trigger), and C7 and C8 are for noise filtering (can likely be omitted). When the combined voltage of the 4x AAs drops below ~4.35 V, the battery level is considered low and the LED will noticeably dim. My testing came up with this voltage as approximately 30 to 45 minutes of playtime left if at max brightness with headphones in, testing from fully charged batteries.

The output of the op-amp is set at 5 V when the battery level is high, which turns on Q1; it is driven to GND when the battery level is low, which turns Q1 off. Therefore, the brightness of the LED during normal power is dictated only by the resistance of R1. When the combined battery voltage drops below the low battery threshold, R2 is placed in series with the LED as well, which dims the LED. I played around with these values to find ones that didn't burn my retinas for normal brightness, and produced a noticeably dimmed power LED when the low voltage detection is tripped.

If you want to decrease the brightness of the LED, increase resistance values of R1 and/or R2 (increase R1 to decrease brightness for both normal and low battery levels, R2 to decrease brightness for only low battery level).

## Navigation Switch
This takes place where the contrast wheel used to be. On the Q5 board, there are two capacitive touch sensors - one for changing brightness, one for changing the color palette. Instead of using the touch sensors in the DMGC, the navigation switch will toggle these inputs by connecting a series capacitance to ground to simulate a touch. This also has the benefit of not having to modify the driver board in any way, and instead just requiring soldered wires to the board where capacitive sensors were connected.

![image](https://user-images.githubusercontent.com/97127539/196016754-8daa1414-55d6-4baf-b579-997d016ffe82.png)

Rocking up on the dial will toggle the brightness setting, rocking it down will toggle the color palette setting. Rocking up and holding it will toggle the battery level display on the screen, and rocking it down and holding it will toggle the pixel grid. Pushing in on the switch grounds the ATTINY85's PB3 pin (which is pulled up externally to 3.3V), if installed. Using the code I provide above, pushing in will advance to the next color of the button LEDs, and holding it while pressing left or right on the D-pad will change the brightness of the LEDs.

If you are using the push function of the navigation switch to reset the console instead of controlling the button LEDs (see more info on the CPU README), then make sure to remove R10.

Bridging the solder pad labeled "NEOPIXEL DISABLE" will ground the navigation switch push function, which will prevent the LEDs from turning on at all.

## Q5 Board Pads
There are six test points at the top of the IPS board for short wires to connect to the Q5 board. The Q5 board includes pads for the select, B, and A buttons for navigation in the OSD. There's also a battery pad, which is for measuring the battery life, as mentioned. And finally, there are two pads for brightness control and color palette swapping, which connect to the capacitive touch sensor inputs on the Q5 board. Before installation, stripped wires should be soldered to these corresponding pads on the Q5 board, so they may be soldered to the IPS board after assembly.

![image](https://user-images.githubusercontent.com/97127539/184361799-70131a36-ccb9-49c3-a647-12fdbeec042c.png)

Note: If you intend to use LSDJ on the DMGC, you might run into a conflict with pressing A + B + Select. This is a specific combination for control in LSDJ. You don't *have* to use those pads at the top for the button inputs for the OSD. You can run wires down to the middle of the board instead. Instead of A, B, and Select, you could pick A, B, and Start for example. Just keep in mind you have to press all three at the same time to open the menu, so don't pick Left and Right as two of the inputs.

![image](https://user-images.githubusercontent.com/97127539/198910151-42c03aed-8008-4fe5-9ae2-14c5da2cadfb.png)

## Button LEDs and ATTINY85
One popular feature for Game Boy mods are backlit buttons. On the front PCB I included spaces for eight WS2812B-2020 RGB LEDs. These are controlled via an ATTINY85 with the Adafruit NeoPixel library. You can program the ATTINY in any number of ways, but I added pads for <a href="https://www.mouser.com/ProductDetail/200-TSM10601TSH">kinked header pins</a> to hopefully make it a bit easier.

![image](https://user-images.githubusercontent.com/97127539/196017477-729896fd-b926-4b42-8206-e60e46865483.png)

*Note that if you do not wish to include LEDs for the buttons, you don't need to populate any of the parts shown in this screenshot.*

There are nine color settings - red, orange, yellow, green, cyan, blue, purple, white, and off. These settings can be changed in the code (or additional settings could be appended) by changing the RGB values in the arrays. Pushing in on the navigation switch will toggle between these settings. Pushing and holding it in, and then pressing left or right will change the brightness of the LEDs. The settings are saved every time the brightness or color is changed, and will be reloaded when turning on the Game Boy. This feature was inspired by NiceMitch's RGB LED flex PCB for GBC.

Code for the ATTINY85 is included here, however because I wrote this months ago (and forgot to comment it sufficiently...) I have forgotten how some of the code actually works. There's certainly room for improvement (and some really dumb inclusions). But there *is* a nice startup effect to match the Game Boy Color boot sequence that a friend (jokingly) suggested I include. *Are you happy, Mike?*

*NOTE: If you are programming the ATTINY after it is already soldered to the IPS board, be sure to disconnect the ribbon cable going to the CPU board and the ribbon cable going to the Q5 kit.*

If you hold the navigation switch in as you turn on the console, the LEDs will be disabled until power is cycled. (This is probably more for my benefit as I used it while testing very discharged batteries to skip the start-up LED sequence)

Always-on discrete LEDs are also an option - an 0603 LED will fit on half of the 4-pin RGB LED pads, from VDD to DO. The pads for this are indicated by the arrows. The picture below shows which pads to use for discrete LEDs (view of the D-pad) - the A indicates the anode of the diode. There are spaces for a resistor for each LED on the back of the board (R22 to R29). If you're using the RGB LEDs, or no LEDs at all, the resistors aren't necessary.

![image](https://user-images.githubusercontent.com/97127539/180103597-06642f10-77f8-44f2-84d5-dac01b80fdf1.png)

Oh, and when you solder the LEDs on, I recommend taping off the button contacts to make sure you don't get solder on them. It won't damage them to the point of non-function, but it can potentially reduce their useful lifetime and accurate detection depending on the severity. (But more importantly, it's not A E S T H E T I C)

![image](https://user-images.githubusercontent.com/97127539/189253688-58df639c-7d75-41a7-a5bc-b63455be2266.png)

## Q5 IPS Screen Bracket
I designed a bracket for holding the screen in place. This is placed between the screen and the DMGC-IPS-01 board. The model is available for download above. <a href="https://funnyplaying.com/products/dmg-retro-pixel-ips-lcd-holder">It is similar to Funnyplaying's model.</a>

![image](https://user-images.githubusercontent.com/97127539/179893357-2857c4a3-07b2-433d-b50c-6ba5824419b2.png)

## Bill of Materials

Here, I have provided links to components I used personally (or suitable replacements). This BOM is also included in Excel format in the root folder.

| Reference Designators   | Qty | Value/Part Number | Package             | Description                       | Comment                                                                        | Source                                                                                                                                                                                                                               |
| ----------------------- | --- | ----------------- | ------------------- | --------------------------------- | ------------------------------------------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| B1-B6                   | 6   | SKRRAAE010        |                     | Tactile switch                    | Optional, can be omitted if you don't want clicky SP-style buttons             | [https://www.mouser.com/ProductDetail/688-SKRRAA](https://www.mouser.com/ProductDetail/688-SKRRAA)
| C1, C2, C6, C7, C8, C24 | 6   | 100nF             | 0603                | Capacitor (MLCC)                  | Should be X5R (or better), at least 16V                                        | [https://www.mouser.com/ProductDetail/?qs=l5k%252BbMnNDknCtKnMv1oEgA%3D%3D](https://www.mouser.com/ProductDetail/?qs=l5k%252BbMnNDknCtKnMv1oEgA%3D%3D)                                                                               |
| C3                      | 1   | 100uF             |                     | Capacitor (Aluminum electrolytic) | Board has space for a 100uF SMD tantalum electrolytic instead                  | [https://www.mouser.com/ProductDetail/KEMET/ESK107M010AC3AA?qs=9RUIYXQlAdBiO30krUyznA%3D%3D](https://www.mouser.com/ProductDetail/KEMET/ESK107M010AC3AA?qs=9RUIYXQlAdBiO30krUyznA%3D%3D)                                             |
| C4, C5                  | 2   | 220pF             | 0603                | Capacitor (MLCC)                  |                                                                                | [https://www.mouser.com/ProductDetail/Samsung-Electro-Mechanics/CL10B221KB8NFNC?qs=YCa%2FAAYMW03S2dLM1EfL7A%3D%3D](https://www.mouser.com/ProductDetail/Samsung-Electro-Mechanics/CL10B221KB8NFNC?qs=YCa%2FAAYMW03S2dLM1EfL7A%3D%3D) |
| FFC Cable               | 1   | 0151660539‎       |                     | Flat Flexible Cable               |                                                                                | [https://www.mouser.com/ProductDetail/Molex/15166-0539?qs=N2VrfF4LzQecTCOx4K2VYA%3D%3D](https://www.mouser.com/ProductDetail/Molex/15166-0539?qs=N2VrfF4LzQecTCOx4K2VYA%3D%3D)                                                       |
| J1, J2                  | 2   | FFC2B17-50-T      |                     | LCD connector                     |                                                                                | [https://www.mouser.com/ProductDetail/GCT/FFC2B17-50-T?qs=TuK3vfAjtkWT79JbRBZamg%3D%3D](https://www.mouser.com/ProductDetail/GCT/FFC2B17-50-T?qs=TuK3vfAjtkWT79JbRBZamg%3D%3D)                                                       |
| J3                      | 1   | TSM-106-01-T-SH   |                     | Surface Mount Terminal Strip      | Optional for assembly, only helpful for programming the ATTINY                 | [https://www.mouser.com/ProductDetail/200-TSM10601TSH](https://www.mouser.com/ProductDetail/200-TSM10601TSH)
| LED1                    | 1   | 151033RS03000     | 3mm                 | Red LED                           |                                                                                | [https://www.mouser.com/ProductDetail/Wurth-Elektronik/151033RS03000?qs=LlUlMxKIyB1%252BAw6bWFN43w%3D%3D](https://www.mouser.com/ProductDetail/Wurth-Elektronik/151033RS03000?qs=LlUlMxKIyB1%252BAw6bWFN43w%3D%3D)                   |
| LED10-LED17             | 8   | WS2812            | 2020                | RGB LED                           | Link leads to a 10-pack. Discrete 0603-size LEDs can be used instead           | [https://www.mouser.com/ProductDetail/Adafruit/4684?qs=DPoM0jnrROWIv9%2FMCIm5vw%3D%3D](https://www.mouser.com/ProductDetail/Adafruit/4684?qs=DPoM0jnrROWIv9%2FMCIm5vw%3D%3D)                                                         |
| Q1                      | 1   | 2N7002            | SOT23               | N-channel MOSFET                  |                                                                                | [https://www.mouser.com/ProductDetail/Nexperia/2N7002NXBKR?qs=%252B6g0mu59x7J2ddJstTJGkQ%3D%3D](https://www.mouser.com/ProductDetail/Nexperia/2N7002NXBKR?qs=%252B6g0mu59x7J2ddJstTJGkQ%3D%3D)                                       |
| R1                      | 1   | 5.6k              | 0603                | Resistor                          |                                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-075K6L?qs=2cAdsCoAWRHvOVv%2Fp%252BkS0g%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-075K6L?qs=2cAdsCoAWRHvOVv%2Fp%252BkS0g%3D%3D)                                 |
| R22-R29                 | 8   | 10k               | 0603                | Resistor                          | Only if using discrete LEDs for LED10-LED17 (adjust resistance for brightness) | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-0710KL?qs=grNVn54RoB%252B3GtjbJj3wJQ%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-0710KL?qs=grNVn54RoB%252B3GtjbJj3wJQ%3D%3D)                                     |
| R2, R6, R7              | 3   | 18k               | 0603                | Resistor                          |                                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1018KL?qs=qpJ%252B%252B%252Bdg6p1T2VMMxU7GeA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1018KL?qs=qpJ%252B%252B%252Bdg6p1T2VMMxU7GeA%3D%3D)                     |
| R3, R5, R11, R12        | 4   | 402k              | 0603                | Resistor                          |                                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07402KL?qs=e5TEs1AaK9ZgNZ9JLlILuQ%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07402KL?qs=e5TEs1AaK9ZgNZ9JLlILuQ%3D%3D)                                           |
| R4                      | 1   | 100               | 0603                | Resistor                          |                                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100RL?qs=NEN%2FsE%2FLsvPIwIWKCOS4%2FA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100RL?qs=NEN%2FsE%2FLsvPIwIWKCOS4%2FA%3D%3D)                               |
| R8, R10                 | 2   | 100k              | 0603                | Resistor                          |                                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100KL?qs=e1ok2LiJcmaihem8Va5%2Fsw%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100KL?qs=e1ok2LiJcmaihem8Va5%2Fsw%3D%3D)                                       |
| R9                      | 1   | 510               | 0603                | Resistor                          |                                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07510RL?qs=gt6vzsuosg04lV7mPQHzdw%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07510RL?qs=gt6vzsuosg04lV7mPQHzdw%3D%3D)                                           |
| R13                     | 1   | 15k               | 0603                | Resistor                          |                                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1015KL?qs=EiqXWrxQq61HhvsANs7j4w%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1015KL?qs=EiqXWrxQq61HhvsANs7j4w%3D%3D)                                             |
| Speaker                 | 1   | 8Ω                |                     | Speaker                           | Can also used salvaged DMG speaker                                             | [https://retrogamerepairshop.com/products/funnyplaying-clear-game-boy-dmg-original-speaker?variant=37728957726892](https://retrogamerepairshop.com/products/funnyplaying-clear-game-boy-dmg-original-speaker?variant=37728957726892) |
| SW1                     | 1   |                   |                     | Navigation switch                 |                                                                                | [https://www.mouser.com/ProductDetail/SparkFun/COM-08184?qs=WyAARYrbSnYOIhcg6ARCiQ%3D%3D](https://www.mouser.com/ProductDetail/SparkFun/COM-08184?qs=WyAARYrbSnYOIhcg6ARCiQ%3D%3D)                                                   |
| U1                      | 1   | LMV358            | SOIC-8              | Op-amp                            |                                                                                | [https://www.mouser.com/ProductDetail/Texas-Instruments/LMV358IDR?qs=EIjG%252BN7kn%252BmCHnTyCQRw3Q%3D%3D](https://www.mouser.com/ProductDetail/Texas-Instruments/LMV358IDR?qs=EIjG%252BN7kn%252BmCHnTyCQRw3Q%3D%3D)                 |
| U2                      | 1   | ATTINY85          | SOIC-8 (5.3mm wide) | Microcontroller                   | Only if using NeoPixels (might need to buy the ATTINY from eBay or AliEx)      | [https://www.mouser.com/ProductDetail/Microchip-Technology-Atmel/ATTINY85-20SF?qs=TZi4OKKi7fW1ThDnq1lPVA%3D%3D](https://www.mouser.com/ProductDetail/Microchip-Technology-Atmel/ATTINY85-20SF?qs=TZi4OKKi7fW1ThDnq1lPVA%3D%3D)       |

## Revision History

### v2.1 (PLANNED)

- Fix cosmetic error in A button tstop layer
- Explore options for start/select tactile switches
- Add warning about programming on silkscreen text
- Add trace that connects to a test pad on the CPU board for the rock-down function of the navigation dial

### v2.0

- Made board/part measurements more accurate
- Added option for tactile switches for D-pad and A/B buttons
- Added extra ground and LP line on FFC connectors for potential use with another IPS kit
- Added optional solder pad to disable NeoPixel LEDs permanently
- Added pads for kinked header pins to program the ATTINY85 easier
- Added plated vias for potential Micro JST connector for the speaker

### v1.3

- Fixed Schmitt trigger circuit for power LED dimming
- Moved Q5 battery detection (BATT) to op-amp output instead of voltage divider output

### v1.2

- Release version

## Resources
-	<a href="https://gbdev.gg8.se/files/schematics/">Rolf, bit9, and nitro2k01’s DMG schematics and layouts</a>
-	<a href="https://learn.adafruit.com/adafruit-neopixel-uberguide/downloads">Adafruit NeoPixel Resources</a>
-	<a href="https://github.com/HandHeldLegend/gbc-rgb-led-2.0">NiceMitch’s RGB LED flex PCB for GBC</a>
-	<a href="https://www.instructables.com/How-to-Burn-ATTiny85-Using-Arduino-Mega/">Instructables post for programming an ATTINY85 with an Arduino</a>

## License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>. You are able to copy and redistribute the material in any medium or format, as well as remix, transform, or build upon the material for any purpose (even commercial) - but you **must** give appropriate credit, provide a link to the license, and indicate if any changes were made.

©MouseBiteLabs 2022
