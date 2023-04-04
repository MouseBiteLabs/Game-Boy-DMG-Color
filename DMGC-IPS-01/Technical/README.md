# Technical Design Document

This write-up serves as a technical explainer for the DMGC-IPS-01. This board is mainly responsible for user interface.

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

## Navigation Switch
This takes place where the contrast wheel used to be. On the Q5 board, there are two capacitive touch sensors - one for changing brightness, one for changing the color palette. Instead of using the touch sensors in the DMGC, the navigation switch will toggle these inputs by connecting a series capacitance to ground to simulate a touch. This also has the benefit of not having to modify the driver board in any way, and instead just requiring soldered wires to the board where capacitive sensors were connected.

![image](https://user-images.githubusercontent.com/97127539/196016754-8daa1414-55d6-4baf-b579-997d016ffe82.png)

Rocking up on the dial will toggle the brightness setting, rocking it down will toggle the color palette setting. Rocking up and holding it will toggle the battery level display on the screen, and rocking it down and holding it will toggle the pixel grid. Pushing in on the switch grounds the ATTINY85's PB3 pin (which is pulled up externally to 3.3V), if installed. Using the code I provide in the main IPS folder, pushing in will advance to the next color of the button LEDs, and holding it while pressing left or right on the D-pad will change the brightness of the LEDs.

## Q5 Board Pads
There are six test points at the top of the IPS board for short wires to connect to the Q5 board. The Q5 board includes pads for the select, B, and A buttons for navigation in the OSD. There's also a battery pad, which is for measuring the battery life, as mentioned. And finally, there are two pads for brightness control and color palette swapping, which connect to the capacitive touch sensor inputs on the Q5 board. Before installation, stripped wires should be soldered to these corresponding pads on the Q5 board, so they may be soldered to the IPS board after assembly.

![image](https://user-images.githubusercontent.com/97127539/184361799-70131a36-ccb9-49c3-a647-12fdbeec042c.png)

## Button LEDs and ATTINY85
One popular feature for Game Boy mods are backlit buttons. On the front PCB I included spaces for eight WS2812B-2020 RGB LEDs. These are controlled via an ATTINY85 with the Adafruit NeoPixel library. You can program the ATTINY in any number of ways, but I added pads for <a href="https://www.mouser.com/ProductDetail/200-TSM10601TSH">kinked header pins</a> to hopefully make it a bit easier. You may want to tape off these pins with kapton tape, but they should not interfere with any component on the CPU board when assembled if installed correctly.

![image](https://user-images.githubusercontent.com/97127539/196017477-729896fd-b926-4b42-8206-e60e46865483.png)

There are nine color settings - red, orange, yellow, green, cyan, blue, purple, white, and off. These settings can be changed in the code (or additional settings could be appended) by changing the RGB values in the arrays. Pushing in on the navigation switch will toggle between these settings. Pushing and holding it in, and then pressing left or right will change the brightness of the LEDs. The settings are saved every time the brightness or color is changed, and will be reloaded when turning on the Game Boy. This feature was inspired by NiceMitch's RGB LED flex PCB for GBC.

Code for the ATTINY85 is located in the main IPS folder, however because I wrote this months ago (and forgot to comment it sufficiently...) I have forgotten how some of the code actually works. There's certainly room for improvement (and some really dumb inclusions). But there *is* a nice startup effect to match the Game Boy Color boot sequence that a friend (jokingly) suggested I include. *Are you happy, Mike?*

*NOTE: If you are programming the ATTINY after it is already soldered to the IPS board, be sure to disconnect the ribbon cable going to the CPU board and the ribbon cable going to the Q5 kit.*

If you hold the navigation switch in as you turn on the console, the LEDs will be disabled until power is cycled. (This is probably more for my benefit as I used it while testing very discharged batteries to skip the start-up LED sequence)

Always-on discrete LEDs are also an option - an 0603 LED will fit on half of the 4-pin RGB LED pads, from VDD to DO. The pads for this are indicated by the arrows. The picture below shows which pads to use for discrete LEDs (view of the D-pad) - the A indicates the anode of the diode. There are spaces for a resistor for each LED on the back of the board (R22 to R29, circled in red below). If you're using the RGB LEDs, or no LEDs at all, the resistors aren't necessary.

![image](https://user-images.githubusercontent.com/97127539/204422623-57abeab7-5053-45d7-bc14-ba01a4393fed.png)

## Q5 IPS Screen Bracket
I designed a bracket for holding the screen in place. This is placed between the screen and the DMGC-IPS-01 board. The model is available for download in the main IPS board folder. <a href="https://funnyplaying.com/products/dmg-retro-pixel-ips-lcd-holder">It is similar to Funnyplaying's model.</a>

![image](https://user-images.githubusercontent.com/97127539/179893357-2857c4a3-07b2-433d-b50c-6ba5824419b2.png)

## Resources
-	<a href="https://gbdev.gg8.se/files/schematics/">Rolf, bit9, and nitro2k01’s DMG schematics and layouts</a>
-	<a href="https://learn.adafruit.com/adafruit-neopixel-uberguide/downloads">Adafruit NeoPixel Resources</a>
-	<a href="https://github.com/HandHeldLegend/gbc-rgb-led-2.0">NiceMitch’s RGB LED flex PCB for GBC</a>
-	<a href="https://www.instructables.com/How-to-Burn-ATTiny85-Using-Arduino-Mega/">Instructables post for programming an ATTINY85 with an Arduino</a>

## License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>. You are able to copy and redistribute the material in any medium or format, as well as remix, transform, or build upon the material for any purpose (even commercial) - but you **must** give appropriate credit, provide a link to the license, and indicate if any changes were made.

©MouseBiteLabs 2022
