# DMGC-CPU-01

![2_2_boardscan](https://user-images.githubusercontent.com/97127539/206723811-57bf4f08-8761-46ff-b492-dbb67e0f9df1.jpg)
![DMGC-CPU-01_2-0_ASSEMBLED](https://user-images.githubusercontent.com/97127539/197366878-ae154a5e-c2df-48f9-88fb-2e1cacaa1770.jpg)

*The image above of the assembled board is of v2.0, not the current revision of v2.1. The differences in appearance are minor, see below.*

The CPU board houses the majority of the electronics in the DMGC. Parts harvested from the original GBC include the CPU, SRAM, and crystal oscillator. EM10 may be trasnferred as well, but a good enough replacement is included in the BOM if you need a new part. The power supply modifications, the new audio circuit, and a handful of omissions like the IR communication and some of the now-unnecessary LCD pins differentiate this build from the original GBC. But many connections and component values are pulled from the official GBC schematic (linked below).

## Board Characteristics
The zipped folder contains all the gerber files for this board. 

-	Layers: 2
-	Thickness: 1.2 mm
-	Surface Finish: ENIG or HASL
-   **NOTE: When ordering PCBs, add this note to the order: "The file milling.gbr contains outlines for plated slots. Please add plated slots on the PCB according to this layer."**

*HASL will work, but will potentially be more difficult for soldering fine-pitch parts like the CPU and FFC connector.*

<a href="https://www.etsy.com/listing/1317688422/game-boy-dmgc-cpu-board">**I sell this board on Etsy, so you don't have to buy multiples from board fabricators.**</a>

You can atlernatively use the zipped folder at any board fabricator you like. You may also buy the board from PCBWay using this link (disclosure: I receive 10% of the  sale value to go towards future PCB orders):

<a href="https://www.pcbway.com/project/shareproject/Game_Boy_DMG_Color_DMGC_CPU_01_2f5c743d.html"><img src="https://www.pcbway.com/project/img/images/frompcbway-1220.png" alt="PCB from PCBWay" /></a> 

## Customization Options

This section will briefly mention all of the different customization options you have on this board while assembling. More detail on implementing the options are in further sections.

- **Maximum Volume:** Increase R30 and R32 to decrease the maximum output volume. 100 kΩ will yield approximately the same volume as a stock GBC. Values below 20 kΩ are not recommended due to power draw considerations.
- **Navigation Dial Push-in as Reset Button:** Solder a wire from the PUSH pad to the RST pad. Make sure you do not populate R10 on the DMGC-IPS-01.

## Power Supply
The majority of the crucial power supply circuitry is on the PWR board, but the CPU board still has some portion of power supply interfacing. 

**NOTE: When assembling the DMGC, I *highly* recommend assembling the PWR board and the following components first. Then, power on the console with batteries or external supply *without any other devices on the CPU board* to make sure the PWR board is assembled correctly. Check with a multimeter or oscilloscope to make sure the 5 V and 3.3 V supplies are correct and steadily providing the correct voltage. If there is an error in assembly on the PWR board, the voltage could be too high and damage parts -- like the CPU!**

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
    - If the EM10 from the GBC donor board has a fifth pin in the middle, just bend it up so it doesn't touch any of the nearby pads. It is an unused pin.
-	Finally, there are five wires leading from the CPU board to the PWR board – VCC (battery voltage), SW (battery voltage after switch), DC (input from the DC jack), 5V (supply from the PWR board), and a GND reference. I also added test points for each of the three voltages as well for troubleshooting purposes.

**Note: NiMH batteries that I have used have a shallower positive tab than normal alkaline AAs. This can cause poor contact with the battery contacts in the battery compartment. Keep the positive contact on the CPU board as close to the battery bay as possible, meaning install it at the very bottom of the mounting hole on the CPU board. If, when using NiMH batteries in the system, the power doesn't turn on - try using alkalines or the DC jack input to check for operation. It might not be powering on due to poor contact of the NiMHs with the battery contacts on the CPU board or in the battery bay. Reseating the batteries can solve the issue.**

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
-	The ratio of R30/R31 and R32/R33 set the amplification of the audio amp - increase R30 and R32 to decrease the output volume. 47 kΩ seemed to hit a sweet spot for my tastes for a gain of 0.38. This is louder than the original GBC, but not too loud that the audio quality is impacted. If you pick 100 kΩ you’ll get output comparable to the original GBC. 
    - The audio gain has quite a large effect on the power draw of the system when using the speaker. I did not do any tests with an audio gain greater than ~0.6. A sufficiently larger gain than this will drain batteries faster if the volume is turned up.
-	The shutdown pin should be tied to GND to allow the amp to work. I made two different revisions that tied this to 5 V instead. Oops. (The output on the headphones will sound really quiet and the speaker won't work if the chip is shutdown)
-	The speaker output *shouldn't* need a DC blocking capacitor, as the LM4853 outputs to the speaker as a bridge tied load (BTL). However, I found that if a DC blocking capacitor is not included, a strange issue is possible in specific situations. There’s a very brief moment when plugging the headphones in where the right output channel is shorted to ground (ring and sleeve are connected inside the jack). When this happens, the right output DC blocking cap is connected to GND, and causes a large surge of current from the power supply to charge it up. In my testing, this sometimes would cause a brownout, causing the power supply to shut off. So I have included a spot for one of these caps in series with the speaker on the IPS board.
-	Added in version 2.0, opposite of the regular headphone outputs, are another set of audio outputs that are completely optional. These are denoted as "pre-pot audio," and include a left, right, and ground connection. The left and right connect directly to the VR1-S01 and VR1-S02 nets, which allows you to grab the audio unfiltered, unamplified, right from the GBC CPU (through a protection resistor/capacitor combo). This is colloquailly known as the "pro-sound" mod, and is typically used in conjunction with a *second* audio jack. Audiophiles like to use this raw output with their audio equipment (note that using the pro-sound output as input to an external amplifier does not disable the speaker or headphones - the potentiometer still controls volume for those audio outputs). You could use this jack for headphones if you want (and it will disable the speaker), but it will always be one volume - about as loud as the original GBC at max volume. The audio coming out of these pins does sound incredibly clean - check out the recordings in the root folder. These outputs should make the system compatible with any pro-sound headphone boards, <a href="https://www.retromodding.com/products/gameboy-pcb-mount-pro-sound-v3">like this one.</a>

## CPU Reset
The last major change to the CPU board is the reset IC. I’ve replaced the original PST9135N with a TPS3840DL35. These chips pull the /RESET pin on the CPU low when the voltage supply drops below 3.5 V (/RESET set to low turns off the CPU). The TPS3840DL35 does the same thing. The reason this chip is included is to hold the CPU off while powering down so no random instructions are made while the game is turning off.

R3 and C17 introduces a time delay on the /RESET pin during start-up, to allow the rest of the power supplies to stabilize before letting the CPU operate. This is called a "power-on reset" circuit, and I used values that the original GBC schematic used. (The DMG, GBC, and GBA all use the same odd 18 ms time constant!)

![image](https://user-images.githubusercontent.com/97127539/196014140-c814788d-86aa-4e9f-ad44-4304cce65992.png)

### Adding a Reset Button

Version 2.0 introduces a test pad labelled "RST" that connects directly to the /RESET pin. If this pin is pulled to GND, when it's released it the system will reset back to the boot screen. If you wire this pad to a button that connects the pad to GND when pressed, you basically have added a reset button to your DMGC. 

There is also a pad near the FFC connector that was added labelled "PUSH" that connects to the rocker switch on the DMGC-IPS-01 board (version 2.0 and later). This pad becomes connected to GND when the rocker switch is pushed in (as long as you remove R10 on the DMGC-IPS-01 board). In a normal configuration, pushing in on the rocker switch will control the button LEDs, but if you are not using these LEDs, then adding a wire from the PUSH to RST pads will turn the rocker switch into a reset button when it's pressed in (rocking up and down retains normal function). 

## Errors

The silkscreen text indicating the pins of the link port is incorrect. SOUT and GND should be flipped. The actual pins are connected correctly, so this is only a cosmetic issue. It will be fixed on the next update.
![image](https://user-images.githubusercontent.com/97127539/197369269-57a89500-8915-40cf-90f6-10fd6513bb74.png)

## Bill of Materials

Here, I have provided links to components I used personally (or suitable replacements). This BOM is also included in Excel format in the root folder.

| Reference Designators                       | Qty | Value/Part Number | Package     | Description        | Comment                                                        | Source                                                                                                                                                                                                                                                                                                                           |
| ------------------------------------------- | --- | ----------------- | ----------- | ------------------ | -------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| +,-                                         | 2   |                   |             | Battery terminals  | Can be salvaged from DMG instead                               | [https://retrogamerepairshop.com/collections/dmg-power/products/game-boy-dmg-original-high-quality-replacement-battery-contact-terminals?variant=37893135794348](https://retrogamerepairshop.com/collections/dmg-power/products/game-boy-dmg-original-high-quality-replacement-battery-contact-terminals?variant=37893135794348) |
| C1                                          | 1   | 18pF              | 0603        | Capacitor (MLCC)   | Should be X5R (or better); at least 1% tolerance; at least 16V | [https://www.mouser.com/ProductDetail/YAGEO/CC0603FRNPO9BN180?qs=vTakOoo5QyL0KzYUzHPSUw%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/CC0603FRNPO9BN180?qs=vTakOoo5QyL0KzYUzHPSUw%3D%3D)                                                                                                                                     |
| C2                                          | 1   | 27pF              | 0603        | Capacitor (MLCC)   | Should be X5R (or better); at least 1% tolerance; at least 16V | [https://www.mouser.com/ProductDetail/603-C0603FRNPO9BN270](https://www.mouser.com/ProductDetail/603-C0603FRNPO9BN270)                                                                                                                                                                                                           |
| C4                                          | 1   | 22pF              | 0603        | Capacitor (MLCC)   |                                                                | [https://www.mouser.com/ProductDetail/YAGEO/CC0603JRNPO9BN220?qs=vTakOoo5QyIVMYOUTI%2F4zA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/CC0603JRNPO9BN220?qs=vTakOoo5QyIVMYOUTI%2F4zA%3D%3D)                                                                                                                                 |
| C5, C6, C7                                  | 3   | 100pF             | 0603        | Capacitor (MLCC)   |                                                                | [https://www.mouser.com/ProductDetail/YAGEO/CC0603JPNPO9BN101?qs=7s%252B3O6pAiyAo%2FUxNqKltRA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/CC0603JPNPO9BN101?qs=7s%252B3O6pAiyAo%2FUxNqKltRA%3D%3D)                                                                                                                         |
| C9, C10, C29, C33, C41, C45                 | 6   | 10nF              | 0603        | Capacitor (MLCC)   | Should be X5R (or better), at least 16V                        | [https://www.mouser.com/ProductDetail/KEMET/C0603C103J5RACTU?qs=BimOss5pjlFJEfKhlb7g1g%3D%3D](https://www.mouser.com/ProductDetail/KEMET/C0603C103J5RACTU?qs=BimOss5pjlFJEfKhlb7g1g%3D%3D)                                                                                                                                       |
| C16, C17, C18, C19, C39, C40, C48, C49, C51 | 9   | 1uF               | 0603        | Capacitor (MLCC)   | Should be X5R (or better), at least 16V                        | [https://www.mouser.com/ProductDetail/KEMET/C0603C105K4RACTU?qs=STjISULpmtZNMAZGR4X39Q%3D%3D](https://www.mouser.com/ProductDetail/KEMET/C0603C105K4RACTU?qs=STjISULpmtZNMAZGR4X39Q%3D%3D)                                                                                                                                       |
| C24, C28, C43, C52, C53                     | 5   | 100nF             | 0603        | Capacitor (MLCC)   | Should be X5R (or better), at least 16V                        | [https://www.mouser.com/ProductDetail/?qs=l5k%252BbMnNDknCtKnMv1oEgA%3D%3D](https://www.mouser.com/ProductDetail/?qs=l5k%252BbMnNDknCtKnMv1oEgA%3D%3D)                                                                                                                                                                           |
| C47                                         | 1   | 150pF             | 0603        | Capacitor (MLCC)   |                                                                | [https://www.mouser.com/ProductDetail/KEMET/C0603C151J5GACTU?qs=V6nSPVTm7vxbAvL0weNH%252BQ%3D%3D](https://www.mouser.com/ProductDetail/KEMET/C0603C151J5GACTU?qs=V6nSPVTm7vxbAvL0weNH%252BQ%3D%3D)                                                                                                                               |
| D1                                          | 1   | PMEG2010AEH       | SOD-123     | Schottky diode     | Most schottky diodes should be suitable (at least 1A, 16V)     | [https://www.mouser.com/ProductDetail/?qs=LOCUfHb8d9u7lcjEnyhX1g%3D%3D](https://www.mouser.com/ProductDetail/?qs=LOCUfHb8d9u7lcjEnyhX1g%3D%3D)                                                                                                                                                                                   |
| DCJACK                                      | 1   |                   |             | DC jack            |                                                                | Salvaged (DMG)                                                                                                                                                                                                                                                                                                                   |
| EM6-EM8                                     | 3   | FBMH2012HM221-T   | 0805        | Filter             |                                                                | [https://www.mouser.com/ProductDetail/Taiyo-Yuden/FBMH2012HM221-T?qs=I6KAKw0tg2yIAV1HVl6Cew%3D%3D](https://www.mouser.com/ProductDetail/Taiyo-Yuden/FBMH2012HM221-T?qs=I6KAKw0tg2yIAV1HVl6Cew%3D%3D)                                                                                                                             |
| EM9                                         | 1   | BLM18BD102SN1D    | 0603        | Filter             |                                                                | [https://www.mouser.com/ProductDetail/Murata-Electronics/BLM18BD102SN1D?qs=h3IWXJJGQQWi4eZyJq6ScQ%3D%3D](https://www.mouser.com/ProductDetail/Murata-Electronics/BLM18BD102SN1D?qs=h3IWXJJGQQWi4eZyJq6ScQ%3D%3D)                                                                                                                 |
| EM10                                        | 1   |                   |             | Common mode filter | Replacement: https://mou.sr/3FiMvXw                            | Salvaged (GBC)                                                                                                                                                                                                                                                                                                                   |
| EXT                                         | 1   |                   |             | Link port          |                                                                | Salvaged (DMG)                                                                                                                                                                                                                                                                                                                   |
| F1                                          | 1   | 2.5A              | 1206        | Fuse               |                                                                | [https://www.mouser.com/ProductDetail/Panasonic/ERB-RG2R50V?qs=Z3CaLxJiOJK8SjHyp%252BdV%2FQ%3D%3D](https://www.mouser.com/ProductDetail/Panasonic/ERB-RG2R50V?qs=Z3CaLxJiOJK8SjHyp%252BdV%2FQ%3D%3D)                                                                                                                             |
| F2                                          | 1   | 1A                | 0603        | Fuse               |                                                                | [https://www.mouser.com/ProductDetail/Vishay-Beyschlag/MFU0603FF01000P100?qs=oI046glRurtlP8n%252B3l7CPg%3D%3D](https://www.mouser.com/ProductDetail/Vishay-Beyschlag/MFU0603FF01000P100?qs=oI046glRurtlP8n%252B3l7CPg%3D%3D)                                                                                                     |
| FB1                                         | 1   | BK32164W601-T     | 1206        | Ferrite Bead       | Alternate: BLA31AG601SN4D                                      | [https://www.mouser.com/ProductDetail/Taiyo-Yuden/BK32164W601-T?qs=I6KAKw0tg2yLD7JT86KwVg%3D%3D](https://www.mouser.com/ProductDetail/Taiyo-Yuden/BK32164W601-T?qs=I6KAKw0tg2yLD7JT86KwVg%3D%3D)                                                                                                                                 |
| J1                                          | 1   | FFC2B17-50-T      |             | LCD connector      |                                                                | [https://www.mouser.com/ProductDetail/GCT/FFC2B17-50-T?qs=TuK3vfAjtkWT79JbRBZamg%3D%3D](https://www.mouser.com/ProductDetail/GCT/FFC2B17-50-T?qs=TuK3vfAjtkWT79JbRBZamg%3D%3D)                                                                                                                                                   |
| P1                                          | 1   |                   |             | Cart connector     | Can be salvaged from DMG instead                               | [https://www.aliexpress.com/item/3256802533298738.html?spm=a2g0o.order\_list.0.0.5ee21802yek6HF](https://www.aliexpress.com/item/3256802533298738.html?spm=a2g0o.order_list.0.0.5ee21802yek6HF)                                                                                                                                  |
| PTC1                                        | 1   | 1.1A Hold         | 1206        | Resettable Fuse    |                                                                | [https://www.mouser.com/ProductDetail/Littelfuse/1206L110THYR?qs=CPcc0c%2Fon9HuH5Zb2mgbPg%3D%3D](https://www.mouser.com/ProductDetail/Littelfuse/1206L110THYR?qs=CPcc0c%2Fon9HuH5Zb2mgbPg%3D%3D)                                                                                                                                 |
| Q1                                          | 1   | SI1443EDH         | SOT363      | P-channel MOSFET   |                                                                | [https://www.mouser.com/ProductDetail/Vishay-Semiconductors/SI1443EDH-T1-GE3?qs=vlV4ps1%252BrQifVq6ycRxedw%3D%3D](https://www.mouser.com/ProductDetail/Vishay-Semiconductors/SI1443EDH-T1-GE3?qs=vlV4ps1%252BrQifVq6ycRxedw%3D%3D)                                                                                               |
| R1                                          | 1   | 1k                | 0603        | Resistor           |                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-071KL?qs=VU8sRB4EgwApHsk4rF%2F3zg%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-071KL?qs=VU8sRB4EgwApHsk4rF%2F3zg%3D%3D)                                                                                                                                       |
| R3, R31, R33                                | 3   | 18k               | 0603        | Resistor           |                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1018KL?qs=qpJ%252B%252B%252Bdg6p1T2VMMxU7GeA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1018KL?qs=qpJ%252B%252B%252Bdg6p1T2VMMxU7GeA%3D%3D)                                                                                                                 |
| R25                                         | 1   | 1.5M              | 0603        | Resistor           | Recommended at least 1% tolerance                              | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-071M5L?qs=VU8sRB4EgwAP38Z8qzPx9Q%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-071M5L?qs=VU8sRB4EgwAP38Z8qzPx9Q%3D%3D)                                                                                                                                         |
| R26                                         | 1   | 5.6k              | 0603        | Resistor           |                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-075K6L?qs=2cAdsCoAWRHvOVv%2Fp%252BkS0g%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-075K6L?qs=2cAdsCoAWRHvOVv%2Fp%252BkS0g%3D%3D)                                                                                                                             |
| R27                                         | 1   | 100               | 0603        | Resistor           |                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100RL?qs=NEN%2FsE%2FLsvPIwIWKCOS4%2FA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100RL?qs=NEN%2FsE%2FLsvPIwIWKCOS4%2FA%3D%3D)                                                                                                                           |
| R36                                         | 1   | 100k              | 0603        | Resistor           |                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100KL?qs=e1ok2LiJcmaihem8Va5%2Fsw%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100KL?qs=e1ok2LiJcmaihem8Va5%2Fsw%3D%3D)                                                                                                                                   |
| R30, R32                                    | 2   | 47k               | 0603        | Resistor           |                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1047KL?qs=EiqXWrxQq600ZhhpLJs%252BtA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1047KL?qs=EiqXWrxQq600ZhhpLJs%252BtA%3D%3D)                                                                                                                                 |
| RA1A, RA1B                                  | 2   | 510               | 0603        | Resistor           |                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07510RL?qs=gt6vzsuosg04lV7mPQHzdw%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07510RL?qs=gt6vzsuosg04lV7mPQHzdw%3D%3D)                                                                                                                                       |
| RA3A-RA3D                                   | 4   | 270               | 0603        | Resistor           |                                                                | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07270RL?qs=diQw95jMAePl%252BPNr4oNP6Q%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07270RL?qs=diQw95jMAePl%252BPNr4oNP6Q%3D%3D)                                                                                                                               |
| SW1                                         | 1   |                   |             | Power switch       |                                                                | Salvaged (DMG)                                                                                                                                                                                                                                                                                                                   |
| U1                                          | 1   | GBC CPU           | QFP-128     | CPU                |                                                                | Salvaged (GBC)                                                                                                                                                                                                                                                                                                                   |
| U2                                          | 1   | LH52256CVTXIZ     | TSOP-28     | RAM                | Potential replacement: https://mou.sr/3f8G0Mi                  | Salvaged (GBC)                                                                                                                                                                                                                                                                                                                   |
| U3                                          | 1   | LM4853            | VSSOP-10    | Audio amplifier    |                                                                | [https://www.mouser.com/ProductDetail/Texas-Instruments/LM4853MM-NOPB?qs=QbsRYf82W3F2psFI2da2Dw%3D%3D](https://www.mouser.com/ProductDetail/Texas-Instruments/LM4853MM-NOPB?qs=QbsRYf82W3F2psFI2da2Dw%3D%3D)                                                                                                                     |
| U4                                          | 1   | NCP161ASN330T1G   | SOT23-5     | LDO                | Can also use TLV70233QDBVRQ1, probably                         | [https://www.mouser.com/ProductDetail/863-NCP161ASN330T1G](https://www.mouser.com/ProductDetail/863-NCP161ASN330T1G)                                                                                                                                                                                                             |
| U6                                          | 1   | TPS3840DL35       | SOT23-5     | Supervisory IC     | Could feasibly use TPS3840DL37 or 40 if 35 is out of stock     | [https://www.mouser.com/ProductDetail/Texas-Instruments/TPS3840DL35DBVR?qs=7MVldsJ5UawbjRj7dP73rA%3D%3D](https://www.mouser.com/ProductDetail/Texas-Instruments/TPS3840DL35DBVR?qs=7MVldsJ5UawbjRj7dP73rA%3D%3D)                                                                                                                 |
| VR1                                         | 1   | 10k               |             | Volume wheel       | Can be salvaged from DMG instead                               | [https://aliexpi.com/qg1M](https://aliexpi.com/qg1M)                                                                                                                                                                                                                                                                             |
| X1                                          | 1   | 8.388608MHz       | 7.5X5-4-PAD | Crystal oscillator | Potential replacement (not very space-friendly): https://mou.sr/3D5AUbH | Salvaged (GBC)                                                                                                                                                                                                                                                                                                                   |

## Revision History

### v2.3 (PLANNED)

- Nudge volume dial to better center it in the shell.

### v2.2 (for sale)

- Added more clearance on screwhole on cart connector
- Adjusted screwhole placement near power switch
- Removed unnecessary vestigal dots on X1 and EM10 silkscreen
- Fixed tstop layer offset on SRAM package
- Added CLK1/2 on backside silkscreen
- Adjusted X1 through-hole location
- Nudged volume dial out a bit
- Add note about trimming wire stubs on PWR board connections
- Cleaned up some trace layouts/silkscreen

### v2.1

- Fixed silkscreen text error on link port
- Added through-holes for potential crystal oscillator replacement
- Added test pad that connects to the rock-down function of the navigation dial on the IPS board
- Moved version number text above cart connector footprint

### v2.0

- Changed holes to slots where applicable
- Made board/part measurements more accurate
- Added dedicated output pins for pro-sound output next to the negative battery tab
- Updated crystal oscillator footprint to allow for later crystal packages
- Added a test pad that connects to the push-in trigger for the rocker switch on the IPS board
- Added a test pad connected to the reset line on the CPU for potential mods (pull to GND to reset the Game Boy)
- Added LP line from CPU to FFC connector for potential use with another IPS kit

### v1.3

- Added test points to back of the board
- Shifted FFC connector down a few mm

### v1.2

- Release version

## Resources
-	<a href="https://console5.com/techwiki/images/e/e6/Nintendo_GBC_Schematic.png">GBC schematic</a>
-	<a href="https://gbdev.gg8.se/files/schematics/">Rolf, bit9, and nitro2k01’s DMG schematics and layouts</a>
-	<a href="https://www.ti.com/lit/ds/symlink/lm4853.pdf?ts=1656384256966&ref_url=https%253A%252F%252Fwww.google.com%252F">LM4853 datasheet</a>
-	<a href="https://www.youtube.com/watch?v=IrB-FPcv1Dc&ab_channel=Afrotechmods">Reverse polarity protection explanation</a>

## License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>. You are able to copy and redistribute the material in any medium or format, as well as remix, transform, or build upon the material for any purpose (even commercial) - but you **must** give appropriate credit, provide a link to the license, and indicate if any changes were made.

©MouseBiteLabs 2022
