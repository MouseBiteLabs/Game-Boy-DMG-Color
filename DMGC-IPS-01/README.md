# DMGC-IPS-01

![DMGC-IPS-01_2-3_scan](https://user-images.githubusercontent.com/97127539/212456708-4a70f93c-80a2-43e3-9a98-edb6a8041518.jpg)
![DMGC-IPS-01_2-0_ASSEMBLED](https://user-images.githubusercontent.com/97127539/197367472-31a2fdb9-6a8e-41a7-8fdc-138f91f944bb.jpg)

*The image above of the assembled board is of v2.0, not the current revision of v2.3. The differences are very minor, see below.*

The IPS board is in the front of the DMG shell. This holds the IPS screen kit (and has pads for interfacing with it), has the dimmable power LED, button inputs along with pads for optional LEDs, a navigation switch on the side for changing settings on the IPS screen and the backlit buttons, and the speaker.

For a technical explanation of the CPU board, please view the README in the Technical folder.

## Board Characteristics

The zipped folder contains all the gerber files for this board.
-	Layers: 2
-	Thickness: 1.2 mm
-	Surface Finish: ENIG or HASL (SEE NOTE!)

*ENIG is required for reliable button press detection; you can use HASL if you are using tactile switches.*

<a href="https://www.etsy.com/listing/1331663235/game-boy-dmgc-ips-board">**I sell this board on Etsy, so you don't have to buy multiples from board fabricators.**</a>

You can alternatively use the zipped folder at any board fabricator you like. You may also buy the board from PCBWay using this link (disclosure: I receive 10% of the  sale value to go towards future PCB orders):

<a href="https://www.pcbway.com/project/shareproject/Game_Boy_DMG_Color_DMGC_IPS_01_82a454c9.html"><img src="https://www.pcbway.com/project/img/images/frompcbway-1220.png" alt="PCB from PCBWay" /></a>

## Customization Options

This section will explain all of the different customization options available on this board while assembling.

### Tactile Switches

Version 2.0 introduced the option for including tactile switches for the buttons, much like the Game Boy Advance SP had. If you do not wish to use these kinds of buttons, the button contacts are still set up to act just like the regular set up with membranes.

![image](https://user-images.githubusercontent.com/97127539/197367604-69478124-7a7e-4d84-897d-eac90462ccb7.png)

In this image, tactile switches are on the left, and pads for simple membranes are on the right. Either method for button presses works perfectly fine. But make sure you put them in the correct way. The little "wings" on the switches should be oriented where there is blank board space.

If you're doing tactile switches on the start and select buttons, you should do a trace cut as indicated where the white lines are pointing. If you don't, the membranes can still activate the start/select buttons on the exposed area without actuating the tactile switch. You may also want to tape over the exposed copper not underneath the switches while soldering them on to avoid getting stray solder on the exposed traces and ruin the A E S T H E T I C.

![image](https://user-images.githubusercontent.com/97127539/212601374-e33e4c9e-bb8b-460e-9545-4cd10e7bbc5f.png)

### Power LED Brightness

Increase the value of R1 to decrease the brightness of the power LED during normal battery levels. Increase the value of R2 to decrease the brightness of the power LED during low battery levels. It is suggested to try changing resistances in ~5 kΩ increments.

### Backlit Buttons

There are a few different avenues to take with respect to the button LEDs. You can use the RGB NeoPixels, discrete always-on LEDs, or none at all.

1) **No Button LEDs:** You do not need to populate LED10-LED17, R9, R22-R29, C2, or U2. Carry on.

2) **Always-on Single Color Backlit Buttons:** If you only want backlit buttons with non-controllable LEDs, you can omit R9, C2, and U2. 

You must isntead install R22-R29, as well as the discrete 0603 LEDs. An 0603 LED will fit on half of the 4-pin RGB LED pads, from VDD to DO. The pads for this are indicated by the arrows. The picture below shows which pads to use for discrete LEDs (view of the D-pad) - the A indicates the anode of the diode. There are spaces for a resistor for each LED on the back of the board (R22 to R29, circled in red below). If you're using the RGB LEDs, or no LEDs at all, the resistors aren't necessary. R22-R29 control the brightness of the LEDs, so keep in mind a higher resistance means lower brightness.

![image](https://user-images.githubusercontent.com/97127539/204422623-57abeab7-5053-45d7-bc14-ba01a4393fed.png)

3) **RGB Backlit Buttons:** If you would like RGB LEDs behind the buttons, you must install LED10-LED17, R9, C2, and U2. Do not populate R22-R29.

When you solder the LEDs on, I recommend taping off the button contacts to make sure you don't get solder on them. It won't damage them to the point of non-function, but it can potentially reduce their useful lifetime and accurate detection depending on the severity. (But more importantly, it's not A E S T H E T I C)

![image](https://user-images.githubusercontent.com/97127539/189253688-58df639c-7d75-41a7-a5bc-b63455be2266.png)

If you install the LEDs and determine they just aren't for you, but don't want want to spend time removing the LEDs themsleves, then bridging the solder pad labeled "NEOPIXEL DISABLE" will ground the navigation switch push function, preventing the LEDs from turning on at all.

#### Programming the ATTINY85

An easy way to program the ATTINY with the code for the backlit buttons is to use an Arduino Uno or Arduino Mega. Check out these tutorials for how to program ATTINY chips with them:

-	<a href="https://www.instructables.com/How-to-Burn-ATTiny85-Using-Arduino-Mega/">Instructables post for programming an ATTINY85 with an Arduino Mega</a>
-	<a href="https://www.instructables.com/How-to-Program-an-Attiny85-From-an-Arduino-Uno/">Instructables post for programming an ATTINY85 with an Arduino Uno</a>

The code is provided above (the .ino file) and you will likely need to install Adafruit's NeoPixel library as well to get it to compile correctly. That can be found here:

- <a href="https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation">Installing Adafruit's NeoPixel Library to Arduino IDE</a>

If you're programming the ATTINY while it's installed on the IPS board, be sure to remove the cables from J1 and J2, otherwise your Arduino will attempt to backfeed the Gameboy and/or the IPS screen kit.

You can use the 7-pin connector on the side of the IPS board to connect to the ATTINY if it's already on the PCB. (You don't need the 3.3V pin to program, it's there for helping you develop your own ATTINY code if you want to use it)

![image](https://github.com/MouseBiteLabs/Game-Boy-DMG-Color/assets/97127539/a97c10c5-b4f5-4180-91f4-f4a405cafcff)

**NOTE: VERSION DIFFERENCE**

On the v2.0 and v2.1 boards, pins 1 and 8 are flipped! And the 3.3V pin does not exist.

![image](https://github.com/MouseBiteLabs/Game-Boy-DMG-Color/assets/97127539/9d8de0d7-d491-436b-957c-0831eabe584b)

### Adding Reset Button Functionality

- If you are using the push function of the navigation switch to reset the console instead of controlling the button LEDs (see more info on the CPU README), then **make sure to remove R10.** You will not have the ability to control Neopixel LEDs with this change (without other code/hardware modifications).
- If you are using the rock down function of the navigation switch to reset the console instead of controlling the Q5 palette setting (see more info on the CPU README), then **make sure to remove C5.** You will not have the ability to use the palette swap function of the Q5 kit with this change (but who really cares, amirite?)

![image](https://user-images.githubusercontent.com/97127539/212698838-54887abe-b375-4d92-8055-f685bbe7f395.png)

![image](https://user-images.githubusercontent.com/97127539/212698813-adca871d-f0ee-4811-bd3e-451bd55554b8.png)

### Alternate OSD Controls

You don't need to use the SEL, A, and B pads at the top of the board for the OSD controls. You can alternatively use the button pads in the middle of the board instead. For example, if you intend to use LSDJ on the DMGC, you might run into a conflict with pressing A + B + Select. This is a specific combination for control in LSDJ. So instead for OSD control, you can run wires down to the middle of the board. Instead of A, B, and Select, you could pick A, B, and Start for example. Just keep in mind you have to press all three at the same time to open the menu, so don't pick Left and Right as two of the inputs, for example.

![image](https://user-images.githubusercontent.com/97127539/198910151-42c03aed-8008-4fe5-9ae2-14c5da2cadfb.png)

## Bill of Materials

Here, I have provided links to components I used personally (or suitable replacements). This BOM is also included in Excel format in the root folder.

| Reference Designators   | Qty | Value/Part Number | Package             | Description                       | Comment                                                                                                                            | Source                                                                                                                                                                                                                               |
| ----------------------- | --- | ----------------- | ------------------- | --------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| B1-B8                   | 8   | SKRRABE010        |                     | Tactile switch                    | Optional, can be omitted if you don't want clicky SP-style buttons (SKRRAA is less clicky, SKRRAC is more clicky)                  | [https://www.mouser.com/ProductDetail/688-SKRRAB](https://www.mouser.com/ProductDetail/688-SKRRAB)                                                                                                                                   |
| C1, C2, C6, C7, C8, C24 | 6   | 0.1uF             | 0603                | Capacitor (MLCC)                  | Should be X5R (or better), at least 16V                                                                                            | [https://www.mouser.com/ProductDetail/?qs=l5k%252BbMnNDknCtKnMv1oEgA%3D%3D](https://www.mouser.com/ProductDetail/?qs=l5k%252BbMnNDknCtKnMv1oEgA%3D%3D)                                                                               |
| C3                      | 1   | 100uF             |                     | Capacitor (Aluminum electrolytic) | Board has space for a 100uF SMD tantalum electrolytic instead                                                                      | [https://www.mouser.com/ProductDetail/KEMET/ESK107M010AC3AA?qs=9RUIYXQlAdBiO30krUyznA%3D%3D](https://www.mouser.com/ProductDetail/KEMET/ESK107M010AC3AA?qs=9RUIYXQlAdBiO30krUyznA%3D%3D)                                             |
| C4, C5                  | 2   | 100pF             | 0603                | Capacitor (MLCC)                  |                                                                                                                                    | [https://www.mouser.com/ProductDetail/YAGEO/CC0603JPNPO9BN101?qs=7s%252B3O6pAiyAo%2FUxNqKltRA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/CC0603JPNPO9BN101?qs=7s%252B3O6pAiyAo%2FUxNqKltRA%3D%3D)                             |
| C9, C10                 | 2   | 27pF              | 0603                | Capacitor (MLCC)                  |                                                                                                                                    | [https://www.mouser.com/ProductDetail/603-C0603FRNPO9BN270](https://www.mouser.com/ProductDetail/603-C0603FRNPO9BN270)                                                                                                               |
| FFC Cable               | 1   | 15020-0541        |                     | Flat Flexible Cable               | Gold plated preferred, but alternate part can work too. Note that 15020-0541 must be bent in the proper direction for good fitment | [https://www.mouser.com/ProductDetail/Molex/15020-0541?qs=pwzmk436yFR5fXbQvbR%2F1w%3D%3D](https://www.mouser.com/ProductDetail/Molex/15020-0541?qs=pwzmk436yFR5fXbQvbR%2F1w%3D%3D)                                                   |
| J1, J2                  | 2   | 62684-502100AHLF  |                     | FFC connector                     |                                                                                                                                    | https://www.mouser.com/ProductDetail/?qs=HL%252BYNjdyZ0vzwc9E0QYY2g%3D%3D                                                                                                                                                            |
| J3                      | 1   | TSM-107-01-T-SH   |                     | Surface Mount Terminal Strip      | Optional for assembly, only helpful for programming the ATTINY                                                                     | [https://www.mouser.com/ProductDetail/200-TSM10701TSH](https://www.mouser.com/ProductDetail/200-TSM10601TSH)                                                                                                                         |
| LED1                    | 1   | 151033RS03000     | 3mm                 | Red LED                           |                                                                                                                                    | [https://www.mouser.com/ProductDetail/Wurth-Elektronik/151033RS03000?qs=LlUlMxKIyB1%252BAw6bWFN43w%3D%3D](https://www.mouser.com/ProductDetail/Wurth-Elektronik/151033RS03000?qs=LlUlMxKIyB1%252BAw6bWFN43w%3D%3D)                   |
| LED10-LED17             | 8   | WS2812            | 2020                | RGB LED                           | Link leads to a 10-pack. Discrete 0603-size LEDs can be used instead                                                               | [https://www.mouser.com/ProductDetail/Adafruit/4684?qs=DPoM0jnrROWIv9%2FMCIm5vw%3D%3D](https://www.mouser.com/ProductDetail/Adafruit/4684?qs=DPoM0jnrROWIv9%2FMCIm5vw%3D%3D)                                                         |
| Q1                      | 1   | 2N7002            | SOT23               | N-channel MOSFET                  |                                                                                                                                    | [https://www.mouser.com/ProductDetail/Nexperia/2N7002NXBKR?qs=%252B6g0mu59x7J2ddJstTJGkQ%3D%3D](https://www.mouser.com/ProductDetail/Nexperia/2N7002NXBKR?qs=%252B6g0mu59x7J2ddJstTJGkQ%3D%3D)                                       |
| R1, R14                 | 2   | 10k               | 0603                | Resistor                          |                                                                                                                                    | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-0710KL?qs=grNVn54RoB%252B3GtjbJj3wJQ%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-0710KL?qs=grNVn54RoB%252B3GtjbJj3wJQ%3D%3D)                                     |
| R22-R29                 | 8   | 10k               | 0603                | Resistor                          | Only if using discrete LEDs for LED10-LED17 (adjust resistance for brightness)                                                     | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-0710KL?qs=grNVn54RoB%252B3GtjbJj3wJQ%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-0710KL?qs=grNVn54RoB%252B3GtjbJj3wJQ%3D%3D)                                     |
| R2, R6, R7              | 3   | 18k               | 0603                | Resistor                          |                                                                                                                                    | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1018KL?qs=qpJ%252B%252B%252Bdg6p1T2VMMxU7GeA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1018KL?qs=qpJ%252B%252B%252Bdg6p1T2VMMxU7GeA%3D%3D)                     |
| R3, R5, R11, R12        | 4   | 402k              | 0603                | Resistor                          |                                                                                                                                    | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07402KL?qs=e5TEs1AaK9ZgNZ9JLlILuQ%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07402KL?qs=e5TEs1AaK9ZgNZ9JLlILuQ%3D%3D)                                           |
| R4                      | 1   | 100               | 0603                | Resistor                          |                                                                                                                                    | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100RL?qs=NEN%2FsE%2FLsvPIwIWKCOS4%2FA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100RL?qs=NEN%2FsE%2FLsvPIwIWKCOS4%2FA%3D%3D)                               |
| R8, R10                 | 2   | 100k              | 0603                | Resistor                          |                                                                                                                                    | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100KL?qs=e1ok2LiJcmaihem8Va5%2Fsw%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100KL?qs=e1ok2LiJcmaihem8Va5%2Fsw%3D%3D)                                       |
| R9                      | 1   | 510               | 0603                | Resistor                          |                                                                                                                                    | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07510RL?qs=gt6vzsuosg04lV7mPQHzdw%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07510RL?qs=gt6vzsuosg04lV7mPQHzdw%3D%3D)                                           |
| R13                     | 1   | 15k               | 0603                | Resistor                          |                                                                                                                                    | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1015KL?qs=EiqXWrxQq61HhvsANs7j4w%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1015KL?qs=EiqXWrxQq61HhvsANs7j4w%3D%3D)                                             |
| Speaker                 | 1   | 8Ω                |                     | Speaker                           | Can also used salvaged DMG speaker                                                                                                 | [https://retrogamerepairshop.com/products/funnyplaying-clear-game-boy-dmg-original-speaker?variant=37728957726892](https://retrogamerepairshop.com/products/funnyplaying-clear-game-boy-dmg-original-speaker?variant=37728957726892) |
| SW1                     | 1   | COM-08184         |                     | Navigation switch                 |                                                                                                                                    | [https://www.mouser.com/ProductDetail/SparkFun/COM-08184?qs=WyAARYrbSnYOIhcg6ARCiQ%3D%3D](https://www.mouser.com/ProductDetail/SparkFun/COM-08184?qs=WyAARYrbSnYOIhcg6ARCiQ%3D%3D)                                                   |
| U1                      | 1   | LMV358            | SOIC-8              | Op-amp                            |                                                                                                                                    | [https://www.mouser.com/ProductDetail/Texas-Instruments/LMV358IDR?qs=EIjG%252BN7kn%252BmCHnTyCQRw3Q%3D%3D](https://www.mouser.com/ProductDetail/Texas-Instruments/LMV358IDR?qs=EIjG%252BN7kn%252BmCHnTyCQRw3Q%3D%3D)                 |
| U2                      | 1   | ATTINY85          | SOIC-8 (5.3mm wide) | Microcontroller                   | Only if using NeoPixels (might need to buy the ATTINY from eBay or AliEx)                                                          | [https://www.mouser.com/ProductDetail/556-ATTINY85V10SU](https://www.mouser.com/ProductDetail/556-ATTINY85V10SU)                                                                                                                     |

## Revision History

### v2.4 (PLANNED)

- Added desensitizing capacitors (C9, C10) to reduce accidental touch inputs on IPS kit

### v2.3 (for sale)

- Moved R9 to avoid interference with post
- Moved warning text
- Added more power LED polarity indication

### v2.2

- Removed start button from PB5 on ATTINY85, added pull-up resistor
- Added 3.3V connection to programming header
- Added option for larger tactile switch on start/select
- Expanded pads for tactile switches for easier soldering

### v2.1

- Fixed cosmetic error in A button tstop layer
- Added options for start/select tactile switches
- Added warning about programming on silkscreen text
- Added trace that connects to a test pad on the CPU board for the rock-down function of the navigation dial
- ~~Connected start button to PB5 on ATTINY85~~ Reworked

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

## License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>. You are able to copy and redistribute the material in any medium or format, as well as remix, transform, or build upon the material for any purpose (even commercial) - but you **must** give appropriate credit, provide a link to the license, and indicate if any changes were made.

©MouseBiteLabs 2022
