# Technical Design Document

This write-up serves as a technical explainer for the DMGC-CPU-01. This board houses the CPU and all associated main functions of the DMGC.

## Power Supply
The majority of the crucial power supply circuitry is on the PWR board, but the CPU board still has some portion of power supply interfacing. 

![image](https://user-images.githubusercontent.com/97127539/179893945-078252b8-437a-4313-877e-8917228ab814.png)

(I know the symbols for the fuses and filters are incorrect. I needed an 0603 package for the board and was too lazy to assign the parts the correct symbols. But I guess technically… they are all resistors in some form.)

-	As mentioned on the main README, the DMGC uses the power switch to control the enable pin on the converters on the PWR board. Therefore, the battery voltage is always connected to the PWR board converter inputs. This way, system current does not pass through the switch, which can be dirty or oxidized and introduce unwanted voltage drops at higher currents.
-	A downside of connecting the batteries directly to the input of the converter – as soon as the last battery completes the circuit by touching the terminals, the input capacitance is immediately charged up. This causes a considerably large inrush current – up to about 2 A by my measurements. In order to limit this inrush current, I utilize PTC1, a Polyswitch. This is a resettable overcurrent protection device. As current reaches 1 A, the resistance of the PTC will increase until power to the console is essentially cut off. For short bursts, like for the inrush current from the batteries, the resistance will quickly return to its normally low value. Nominal operation of the DMGC should only see currents up to 250 mA at worst cases - meaning the voltage drop across the PTC under normal operation will be negligible.
-	Furthermore, because the batteries are always connected to at least some of the system, the current draw while the switch is off must be as small as possible to reduce the amount of quiescent current that would drain the batteries. Only capacitors and high impedance loads are therefore connected to the VCC line on the CPU and PWR boards.
-	Because there is still a risk of the batteries being short circuited before reaching the PTC on the board, the positive battery terminal is immediately followed by a ~2.5 amp fuse to open the circuit if the batteries are accidentally short circuited. Also, F2 is in series with the output of the DC jack to protect from overcurrents if batteries aren’t being used to power the console.
-	Pins 3 and 4 on the DC jack are normally closed when the AC adapter is not plugged in, and open when it is plugged in. This ensures the batteries and AC adapter cannot power the Game Boy simultaneously, and prevent accidental backfeeding into the opposing power source.
-	Q1 is a P-channel FET used for reverse polarity protection. This is more efficient than a series diode because while the P-FET is conducting, there is a much smaller voltage drop than if a diode was being used. D1 is reverse polarity protection for the DC jack input, where efficiency is much less important than running on batteries. 
-	R1 connects to the 5 V rail when the power switch is turned off, ensuring quick discharge and reducing the chance of strange operation during a slower power down.
-	U4 is a simple linear regulator for generating the 3.3 V supply necessary for the RAM and the CPU core. I considered using a SMPS instead, but the current requirements are so low, it seemed slightly overkill.
-	The filters (EM6, 7, 8, and 10) are likely fine to exclude, but it doesn't hurt to include them just in case some weird high frequency components have the potential to screw something up down the line. I don't really have the capability (or desire) to properly test what effects removing them may have, but I suspect they're mostly for FCC compliance.
-	Finally, there are five wires leading from the CPU board to the PWR board – VCC (battery voltage), SW (battery voltage after switch), DC (input from the DC jack), 5V (supply from the PWR board), and a GND reference. I also added test points for each of the three voltages as well for troubleshooting purposes.

## FFC Connector

For this build, as mentioned, I'm using the GBC Q5 XL IPS Backlight with OSD kit. It comes with a separate circuit board to properly drive the IPS screen (which I’m henceforth calling the “Q5 board”). In order to determine which pins were necessary for the Q5 board, I looked at the cable connected to the board and noted which traces actually go somewhere. The pins in red are unused, the ones in blue are used. The pin names are from the GBC schematic. Some of the unused pins are used for other functions on the connector to connect to the IPS board.

![image](https://user-images.githubusercontent.com/97127539/196016168-a3d0321a-0d49-4150-9fe4-bc5f5dac4a82.png)

-	Pin 1 and 2 are connected to the output of the power switch. This is sent to the IPS board, which uses it for battery level detection to control the brightness of the power LED, and has a pad for connection to the OSD kit (after a voltage divider). As the kit is for the GBC, cutting the battery voltage in half simulates 2x AA batteries like the GBC uses.
-	Pins 33 and 34 are used for GND. This just reduces the current through one individual pin on the FFC connector. Probably not necessary, but who knows. Maybe you'd want to put bluetooth or Wi-Fi or a media server on the front display board, I'm not your dad.
-	Pins 38 and 39 are similarly doubled up for the 5 V supply. I wanted to keep some empty space around these pins to reduce the likelihood of shorting something to the power rail when soldering the FCC connector on, specifically the buttons (which are referenced to the 3.3 V supply in the CPU).
-	Pins 41 to 48 are used for the face buttons.
-	Pins 49 and 50 are for the speaker.
-	TEST1 is used for GND on this cable, but I kept the ground connection to just a few pins to reduce the chance for ground loops between the CPU and IPS boards. But on the IPS board connector to the Q5 board, this TEST1 pin is connected to GND.
-   Pin 4 connects to a test pad called PUSH. This pad connects to the rocker switch on the IPS board through the FFC, specifically the push-in function of the rocker switch. You can use this for all sorts of shenanigans if you want to try being clever with it.
-	The CLS and LP pins aren’t used by this kit, but is by another kit that is potentially usable.

## Audio Amplifier
The new audio driver on the CPU board is powered by the LM4853. This TI chip is perfectly suited for the Game Boy - it has stereo inputs and headphone outputs, and mono speaker output. Makes it quite easy to implement without extra circuitry shenanigans.

![image](https://user-images.githubusercontent.com/97127539/196014076-dc2daf51-1e44-411c-b78f-dc869343b168.png)

-	The four outputs on the right are for the DMGC-HDP board. (This board has the DC blocking capacitors needed for the headphones)
-	The headphone detect pin (HP_SWITCH) is connected to GND when the headphone jack is empty, and is pulled up to 5 V via R36 when headphones are inserted. This switches the output on the audio amplifier between the speakers and headphones. C51 is for debouncing the headphone detection.
-	C18/C19 are DC blocking capacitors and RA1A/RA1B are current limiting resistors, so when the volume is turned all the way down, the S01 and S02 pins aren’t overloaded.
-	C52/C53 are DC blocking capacitors so only the AC audio signal passes to the amplifier.
-	The ratio of R30/R31 and R32/R33 set the amplification of the audio amp - increase R30 and R32 to decrease the output volume.
    - The audio gain has quite a large effect on the power draw of the system when using the speaker. I did not do any tests with an audio gain greater than ~0.6. A sufficiently larger gain than this will drain batteries faster if the volume is turned up.
-	The shutdown pin should be tied to GND to allow the amp to work. I made two different revisions that tied this to 5 V instead. Oops. (The output on the headphones will sound really quiet and the speaker won't work if the chip is shutdown)
-	The speaker output *shouldn't* need a DC blocking capacitor, as the LM4853 outputs to the speaker as a bridge tied load (BTL). However, I found that if a DC blocking capacitor is not included, a strange issue is possible in specific situations. There’s a very brief moment when plugging the headphones in where the right output channel is shorted to ground (ring and sleeve are connected inside the jack). When this happens, the right output DC blocking cap is connected to GND, and causes a large surge of current from the power supply to charge it up. In my testing, this sometimes would cause a brownout, causing the power supply to shut off. So I have included a spot for one of these caps in series with the speaker on the IPS board.
-	Added in version 2.0, opposite of the regular headphone outputs, are another set of audio outputs that are completely optional. These are denoted as "pre-pot audio," and include a left, right, and ground connection. The left and right connect directly to the VR1-S01 and VR1-S02 nets, which allows you to grab the audio unfiltered, unamplified, right from the GBC CPU (through a protection resistor/capacitor combo). This is colloquailly known as the "pro-sound" mod, and is typically used in conjunction with a *second* audio jack. Audiophiles like to use this raw output with their audio equipment (note that using the pro-sound output as input to an external amplifier does not disable the speaker or headphones - the potentiometer still controls volume for those audio outputs). You could use this jack for headphones if you want (and it will disable the speaker), but it will always be one volume - about as loud as the original GBC at max volume. The audio coming out of these pins does sound incredibly clean - check out the recordings in the root folder. 

## CPU Reset
The last major change to the CPU board is the reset IC. I’ve replaced the original PST9135N with a TPS3840DL35. These chips pull the /RESET pin on the CPU low when the voltage supply drops below 3.5 V (/RESET set to low turns off the CPU). The TPS3840DL35 does the same thing. The reason this chip is included is to hold the CPU off while powering down so no random instructions are made while the game is turning off.

R3 and C17 introduces a time delay on the /RESET pin during start-up, to allow the rest of the power supplies to stabilize before letting the CPU operate. This is called a "power-on reset" circuit, and I used values that the original GBC schematic used. (The DMG, GBC, and GBA all use the same odd 18 ms time constant!)

As described in the main CPU README, you can modify the board to manually reset the DMGC by pulling the /RESET pin to GND with the rocker switch.

![image](https://user-images.githubusercontent.com/97127539/196014140-c814788d-86aa-4e9f-ad44-4304cce65992.png)

## Resources
-	<a href="https://console5.com/techwiki/images/e/e6/Nintendo_GBC_Schematic.png">GBC schematic</a>
-	<a href="https://gbdev.gg8.se/files/schematics/">Rolf, bit9, and nitro2k01’s DMG schematics and layouts</a>
-	<a href="https://www.ti.com/lit/ds/symlink/lm4853.pdf?ts=1656384256966&ref_url=https%253A%252F%252Fwww.google.com%252F">LM4853 datasheet</a>
-	<a href="https://www.youtube.com/watch?v=IrB-FPcv1Dc&ab_channel=Afrotechmods">Reverse polarity protection explanation</a>

## License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>. You are able to copy and redistribute the material in any medium or format, as well as remix, transform, or build upon the material for any purpose (even commercial) - but you **must** give appropriate credit, provide a link to the license, and indicate if any changes were made.

©MouseBiteLabs 2022
