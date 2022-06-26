# DMGC-CPU-01
**TO-DO:**
- Upload pictures
- Upload BOM
- Upload files
- In-text links

[blank board pictures]

The CPU board houses the majority of the electronics in the DMGC. Parts harvested from the original GBC include the CPU, SRAM, crystal oscillator, and EM10 (which could likely be replaced or bypassed with little consequence). Other than the power supply modifications, the new audio circuit, and a handful of omissions like the IR communication and a handful of the LCD pins, the connections and components are mostly copied from the official GBC schematic.
## Board Characteristics
-	Layers: 2
-	Thickness: 1.2 mm
-	Surface Finish: ENIG
## Power Supply
The majority of the crucial power supply circuitry is on the PWR board, but the CPU board still has some portion of power supply interfacing. 

![image](https://user-images.githubusercontent.com/97127539/175816579-b7634287-f633-442b-8511-d9f95f566e3f.png)


*I know the symbols for the fuses and filters are incorrect. I needed an 0603 package for the board and was too lazy to assign the parts the correct symbols. But I guess technically… they are all resistors in some form.*
-	As mentioned on the main readme, the DMGC uses the power switch to control the enable pin on the converters on the PWR board. Therefore, the battery voltage is always connected to the PWR board converter inputs. This way, system current does not pass through the switch, which can be dirty or oxidized and introduce unwanted voltage drops at higher currents. Using the switch to drive the enable line incurs a much smaller voltage drop due to the reduced currents.
-	A downside of connecting the batteries directly to the input of the converter – as soon as the last battery completes the circuit by touching the terminals, the input capacitance is immediately charged up. This causes a considerably large inrush current – up to about 2 A by my measurements. In order to limit this inrush current, I utilize PTC1, a Polyswitch. This is a resettable overcurrent protection device. As current reaches 1 A, the resistance of the PTC will increase until power to the console is essentially cut off. For short bursts, like for the inrush current from the batteries, the resistance will return to it’s normally low value. Nominal operation of the DMGC should only see currents up to 200 mA at worst cases.
-	Furthermore, because the batteries are always connected to at least some of the system, the impedance must be as small as possible to reduce the amount of quiescent current that would drain the batteries. Therefore, the only things connected to the VCC net on any of the boards are capacitors, which should keep battery drainage to a minimum while the console is off.
-	Because there is still a risk of the batteries being short circuited before reaching the PTC on the board, the positive battery terminal is immediately followed by a ~2.5 amp fuse to open the circuit if the batteries are accidentally short circuited. Also, F2 is in series with the output of the DC jack to protect from overcurrents if batteries aren’t being used to power the console.
-	Pins 3 and 4 on the DC jack are normally closed when the AC adapter is not plugged in, and open when it is plugged in. This ensures the batteries and AC adapter cannot power the Game Boy simultaneously.
-	Q1 is a P-channel FET used for reverse polarity protection. This is more efficient than a series diode because while the P-FET is conducting, there is a much smaller voltage drop than if a diode was being used. D1 is reverse polarity protection for the DC jack input, where efficiency is much less important than running on batteries. 
-	R1 connects to the 5 V rail when the power switch is turned off, ensuring quick discharge and reducing the chance of strange operation during a slower power down.
-	U4 is a simple linear regulator for generating the 3.3V supply necessary for the RAM and the CPU core. I considered using a SMPS instead, but the current requirements are so low, it seemed slightly overkill.
-	The filters (EM6, 7, 8, and 10) are likely fine to exclude, but it doesn't hurt to include them just in case some weird high frequency components have the potential to screw something up down the line. I don't really have the capability (or desire) to properly test what effects removing them may have, but I suspect they're mostly for FCC compliance.
-	Finally, there are five wires leading from the CPU board to the PWR board – VCC (battery voltage), VCC_SW (battery voltage after switch), DC_JACK (input from the DC jack), +5V (supply from the PWR board), and a GND reference. I also added test points for each of the three voltages as well for troubleshooting purposes.
## FFC Connector
(Not to be confused with the FCC.) For this build, as mentioned, I'm using the GBC Q5 XL IPS Backlight with OSD kit. It comes with a separate circuit board to properly drive the IPS screen (which I’m calling the “Q5 board”). In order to determine which pins were necessary for the Q5 board, I looked at the cable connected to the board and noted which traces actually go somewhere. The pins in red are unused, the ones in blue are used. The pin names are from the GBC schematic. Some of the unused pins are used for other functions on the connector to connect to the IPS board.

![image](https://user-images.githubusercontent.com/97127539/175816590-79a22d11-6112-4800-8ace-188f5491b4db.png)

 
-	Pin 1 and 2 are connected to the output of the power switch. This is sent to the IPS board, which uses it for battery level detection to control the brightness of the power LED, and has a pad for connection to the OSD kit (after a voltage divider). As the kit is for the GBC, cutting the battery voltage in half simulates 2x AA batteries like the GBC uses.
-	Pins 33 to 35 are used for GND. This just reduces the current through one individual pin on the FFC connector. Probably not necessary, but who knows. Maybe you'd want to put bluetooth or Wi-Fi or a media server on the front display board, I'm not your dad.
-	Pins 38 and 39 are similarly doubled up for the 5 V supply. I wanted to keep some empty space around these pins to reduce the likelihood of shorting something to the power rail when soldering the FCC connector on, specifically the buttons (which are referenced to the 3.3V supply in the CPU).
-	Pins 41 to 48 are used for the face buttons.
-	Pins 49 and 50 are for the speaker.
-	TEST1 is used for GND on this cable, but I kept the ground connection to just a few pins to reduce the chance for ground loops between the CPU and IPS boards. But on the IPS board connector to the Q5 board, this TEST1 pin is connected to GND.
-	The CLS pin isn’t used by this kit, but is by another kit I was considering using. I just forgot to remove the connection.
## Audio Amplifier
The new audio driver on the CPU board is powered by the LM4853. This TI chip is perfectly suited for the Game Boy - it has stereo inputs and headphone outputs, and mono speaker output. Makes it quite easy to implement without extra circuitry shenanigans.

![image](https://user-images.githubusercontent.com/97127539/175816602-0464f2ad-0b2e-4d99-9685-423e78ef2265.png)

-	The four outputs on the right are for the DMGC-HDP board. (This board has the DC blocking capacitors needed for the headphones)
-	The headphone detect pin (HP_SWITCH) is connected to GND when the headphone jack is empty, and is pulled up to 5 V via R36 when headphones are inserted. This switches the output on the audio amplifier between the speakers and headphones. C51 is for debouncing the headphone detection.
-	C18/C19 are DC blocking capacitors and RA1A/RA1B are current limiting resistors, so when the volume is turned all the way down, the S01 and S02 pins aren’t overloaded.
-	C52/C53 are DC blocking capacitors so only the AC audio signal passes to the amplifier.
-	The ratio of R30/R31 and R32/R33 set the amplification of the audio amp - increase R30 and R32 to decrease the output volume. If you pick too low of values, the output will eventually get clipped and sound pretty gross. 47 kΩ seemed to hit a sweet spot for my tastes - louder than the original GBC, but not too loud that the audio clips (or hurts my ears). If you pick 100 kΩ you’ll get output comparable to the original GBC.
-	The shutdown pin should be tied to GND to allow the amp to work. I made two different revisions that tied this to 5 V instead. Oops. (The output on the headphones will just sound really quiet if the chip is shutdown)
-	The speaker output shouldn't need a DC blocking capacitor, as the LM4853 outputs to the speaker as a bridge tied load (BTL). However, I found that if a DC blocking capacitor is not included, a strange issue happens. There’s a very brief moment when plugging the headphones in where the right output channel is shorted to ground (ring and sleeve are connected inside the jack). When this happens, the right output DC blocking cap is connected to GND, and causes a large surge of current from the power supply to charge it up. This can cause a brownout, and the system will reset. I have included a spot for one of these caps in series with the speaker on the IPS board.
-	If you cut the traces (shown below) between the HP-R pads and the HP-L/SPK- pads, and solder a wire from LOUT to HP-L and a wire from ROUT to HP-R (left-most), this will connect the output of the potentiometer directly to the headphone outputs. This is known as the “pro-sound” mod. I won’t use it, but maybe you think it sounds better this way.

[picture of traces to cut]
## CPU Reset
The last major change to the CPU board is the reset IC. I’ve replaced the original PST9135N with a TPS3840DL35. These chips pull the /RESET pin on the CPU low when the voltage supply drops below 3.5 V (/RESET set to low turns off the CPU). The TPS3840DL35 does the same thing. The reason this chip is included is to hold the CPU off while powering down so no random instructions are made while the game is turning off.

R3 and C17 introduces a time delay on the /RESET pin during start-up, to allow the rest of the power supplies to stabilize before letting the CPU operate.

![image](https://user-images.githubusercontent.com/97127539/175816615-ec21e411-9aeb-4349-b123-e396a91f68fb.png)

## Bill of Materials
Lots of parts.
## Resources
-	GBC schematic
-	Rolf, bit9, and nitro2k01’s DMG schematics and layouts
-	TPS3840 datasheet
-	LM4853 datasheet
-	Reverse polarity protection explanation
## License
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

