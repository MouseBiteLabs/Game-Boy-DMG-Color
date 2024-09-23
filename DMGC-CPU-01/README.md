# DMGC-CPU-01

![DMGC-CPU-01_2-3_scan](https://user-images.githubusercontent.com/97127539/212452961-b9c53a46-5c29-4012-afe8-3af43f842dfc.jpg)
![DMGC-CPU-01_2-0_ASSEMBLED](https://user-images.githubusercontent.com/97127539/197366878-ae154a5e-c2df-48f9-88fb-2e1cacaa1770.jpg)

*The image above of the assembled board is of v2.0, not the current revision of v2.4. The differences in appearance are minor, see below.*

The CPU board houses the majority of the electronics in the DMGC. Parts harvested from the original GBC include the CPU, SRAM, and crystal oscillator. EM10 may be transferred as well, but a good enough replacement is included in the BOM if you need a new part. The power supply modifications, the new audio circuit, and a handful of omissions like the IR communication and some of the now-unnecessary LCD pins differentiate this build from the original GBC. But many connections and component values are pulled from the official GBC schematic (linked below).

For a technical explanation of the CPU board, please view the README in the Technical folder.

## Board Characteristics
The zipped folder contains all the gerber files for this board. 

-	Layers: 2
-	Thickness: 1.2 mm
-	Surface Finish: ENIG or HASL
-   **NOTE: When ordering PCBs, add this note to the order: "The file milling.gbr contains outlines for plated slots. Please add plated slots on the PCB according to this layer."**

*HASL will work, but will potentially be more difficult for soldering fine-pitch parts like the CPU and FFC connector.*

<a href="https://www.etsy.com/listing/1317688422/game-boy-dmgc-cpu-board">**I sell this board on Etsy, so you don't have to buy multiples from board fabricators.**</a>

You can alternatively use the zipped folder at any board fabricator you like. You may also buy the board from PCBWay using this link (disclosure: I receive 10% of the  sale value to go towards future PCB orders):

<a href="https://www.pcbway.com/project/shareproject/Game_Boy_DMG_Color_DMGC_CPU_01_2f5c743d.html"><img src="https://www.pcbway.com/project/img/images/frompcbway-1220.png" alt="PCB from PCBWay" /></a> 

## Customization Options

This section will explain all of the different customization options available on this board while assembling.

### Adjusting Volume Range

You can adjust the maximum volume coming out of the speakers and headphones by modifying R30 and R32 values. Increase R30 and R32 to decrease the maximum volume; decrease R30 and R32 to increase the maximum volume. Choose the same values for both of these resistors, otherwise you'll have lopsided audio channels. After some trial and error, here's my approximations of some different values of resistors:
- Choosing 100 kΩ for a gain of ~0.18 will yield about the same volume as a stock GBC. 
- Using 47 kΩ seemed to hit a sweet spot for my tastes for a gain of ~0.38 - not too loud, not too quiet.
- The lowest value I tried out was 33 kΩ, but this was *considerably* loud. It also began to have an actual impact in the battery voltage. I suspect values lower than about 20 kΩ will greatly reduce battery life.

### Pro-Sound Output

Added in version 2.0, opposite of the regular headphone outputs, are a set of audio outputs denoted as "pre-pot audio." The left and right channels connect directly to the VR1-S01 and VR1-S02 nodes, which allows you to grab the audio unfiltered, unamplified, right from the GBC CPU (through a protection resistor/capacitor combo). This is colloquailly known as the "pro-sound" mod, and is typically used in conjunction with a *second* audio jack. Audiophiles like to use this raw output with their audio equipment (note that using the pro-sound output as input to an external amplifier does not disable the speaker or headphones - the potentiometer still controls volume for those audio outputs). You could use this jack for headphones if you want (and it will disable the speaker), but it will always be one volume - about as loud as the original GBC at max volume. The audio coming out of these pins does sound incredibly clean - check out the recordings in the root folder. These outputs should make the system compatible with any pro-sound headphone boards, <a href="https://www.retromodding.com/products/gameboy-pcb-mount-pro-sound-v3">like this one.</a>

### Adding Reset Button Functionality

Version 2.0 also introduces a test pad labelled "RST" that connects directly to the /RESET pin. If this pin is pulled to GND, when it's released it the system will reset back to the boot screen. If you wire this pad to a button that connects the pad to GND when pressed, you basically have added a reset button to your DMGC. 

There are also pads near the FFC connector that are added labelled "PUSH" and "ROCK DOWN". These connect to the rocker switch on the DMGC-IPS-01 board (version 2.0 and later). The PUSH pad becomes connected to GND when the rocker switch is pushed in and floats when not pressed (as long as you remove R10 on the DMGC-IPS-01 board). The ROCK_DOWN pad connects to GND when the rocker switch is rocked down, and floats when not pressed (as long as you remove C5 on the DMGC-IPS-01 board).

In a normal configuration, pushing in on the rocker switch will control the button LEDs, and rocking down will swap the Q5 color settings, but if you don't want to use one of these features, then adding a wire from the PUSH or ROCK DOWN pad to RST pad will turn the rocker switch into a reset button for the system for that specific action and replace its normal function.

**CAUTION: Remember to remove R10 or C5 on the IPS board if you plan to use this feature!!!**

![image](https://user-images.githubusercontent.com/97127539/212701220-f6f169aa-ac0d-43c7-b2bb-800e9bb0fbe5.png)

![image](https://user-images.githubusercontent.com/97127539/212701236-c7038fb0-1e24-4f0d-ba9c-39718c1c74f7.png)

## Bill of Materials

Here, I have provided links to components I used personally (or suitable replacements). This BOM is also included in Excel format in the root folder.

| Reference Designators                       | Qty | Value/Part Number | Package     | Description        | Comment                                                                 | Source                                                                                                                                                                                                                                                                                                                           |
| ------------------------------------------- | --- | ----------------- | ----------- | ------------------ | ----------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| +,-                                         | 2   |                   |             | Battery terminals  | Can be salvaged from DMG instead                                        | [https://retrogamerepairshop.com/collections/dmg-power/products/game-boy-dmg-original-high-quality-replacement-battery-contact-terminals?variant=37893135794348](https://retrogamerepairshop.com/collections/dmg-power/products/game-boy-dmg-original-high-quality-replacement-battery-contact-terminals?variant=37893135794348) |
| C1                                          | 1   | 18pF              | 0603        | Capacitor (MLCC)   | Should be X5R (or better); at least 1% tolerance; at least 16V          | [https://www.mouser.com/ProductDetail/YAGEO/CC0603FRNPO9BN180?qs=vTakOoo5QyL0KzYUzHPSUw%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/CC0603FRNPO9BN180?qs=vTakOoo5QyL0KzYUzHPSUw%3D%3D)                                                                                                                                     |
| C2                                          | 1   | 27pF              | 0603        | Capacitor (MLCC)   | Should be X5R (or better); at least 1% tolerance; at least 16V          | [https://www.mouser.com/ProductDetail/603-C0603FRNPO9BN270](https://www.mouser.com/ProductDetail/603-C0603FRNPO9BN270)                                                                                                                                                                                                           |
| C4                                          | 1   | 22pF              | 0603        | Capacitor (MLCC)   |                                                                         | [https://www.mouser.com/ProductDetail/YAGEO/CC0603JRNPO9BN220?qs=vTakOoo5QyIVMYOUTI%2F4zA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/CC0603JRNPO9BN220?qs=vTakOoo5QyIVMYOUTI%2F4zA%3D%3D)                                                                                                                                 |
| C5, C6, C7                                  | 3   | 100pF             | 0603        | Capacitor (MLCC)   |                                                                         | [https://www.mouser.com/ProductDetail/YAGEO/CC0603JPNPO9BN101?qs=7s%252B3O6pAiyAo%2FUxNqKltRA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/CC0603JPNPO9BN101?qs=7s%252B3O6pAiyAo%2FUxNqKltRA%3D%3D)                                                                                                                         |
| C9, C10, C29, C33, C41, C45                 | 6   | 0.01uF            | 0603        | Capacitor (MLCC)   | Should be X5R (or better), at least 16V                                 | [https://www.mouser.com/ProductDetail/KEMET/C0603C103J5RACTU?qs=BimOss5pjlFJEfKhlb7g1g%3D%3D](https://www.mouser.com/ProductDetail/KEMET/C0603C103J5RACTU?qs=BimOss5pjlFJEfKhlb7g1g%3D%3D)                                                                                                                                       |
| C16, C17, C18, C19, C39, C40, C48, C49, C51 | 9   | 1uF               | 0603        | Capacitor (MLCC)   | Should be X5R (or better), at least 16V                                 | [https://www.mouser.com/ProductDetail/KEMET/C0603C105K4RACTU?qs=STjISULpmtZNMAZGR4X39Q%3D%3D](https://www.mouser.com/ProductDetail/KEMET/C0603C105K4RACTU?qs=STjISULpmtZNMAZGR4X39Q%3D%3D)                                                                                                                                       |
| C24, C28, C43, C52, C53                     | 5   | 0.1uF             | 0603        | Capacitor (MLCC)   | Should be X5R (or better), at least 16V                                 | [https://www.mouser.com/ProductDetail/?qs=l5k%252BbMnNDknCtKnMv1oEgA%3D%3D](https://www.mouser.com/ProductDetail/?qs=l5k%252BbMnNDknCtKnMv1oEgA%3D%3D)                                                                                                                                                                           |
| C47                                         | 1   | 150pF             | 0603        | Capacitor (MLCC)   |                                                                         | [https://www.mouser.com/ProductDetail/KEMET/C0603C151J5GACTU?qs=V6nSPVTm7vxbAvL0weNH%252BQ%3D%3D](https://www.mouser.com/ProductDetail/KEMET/C0603C151J5GACTU?qs=V6nSPVTm7vxbAvL0weNH%252BQ%3D%3D)                                                                                                                               |
| D1                                          | 1   | PMEG2010AEH       | SOD-123     | Schottky diode     | Most schottky diodes should be suitable (at least 1A, 16V)              | [https://www.mouser.com/ProductDetail/?qs=LOCUfHb8d9u7lcjEnyhX1g%3D%3D](https://www.mouser.com/ProductDetail/?qs=LOCUfHb8d9u7lcjEnyhX1g%3D%3D)                                                                                                                                                                                   |
| DC                                          | 1   |                   |             | DC jack            |                                                                         | Salvaged (DMG)                                                                                                                                                                                                                                                                                                                   |
| EM6-EM8                                     | 3   | FBMH2012HM221-T   | 0805        | Filter             |                                                                         | https://mou.sr/3YT6y8F                                                                                                                     |
| EM9                                         | 1   | BLM18BD102SN1D    | 0603        | Filter             |                                                                         | [https://www.mouser.com/ProductDetail/Murata-Electronics/BLM18BD102SN1D?qs=h3IWXJJGQQWi4eZyJq6ScQ%3D%3D](https://www.mouser.com/ProductDetail/Murata-Electronics/BLM18BD102SN1D?qs=h3IWXJJGQQWi4eZyJq6ScQ%3D%3D)                                                                                                                 |
| EM10                                        | 1   | 744235601         |             | Common mode filter | Can be salvaged from GBC instead                                        | [https://www.mouser.com/ProductDetail/Wurth-Elektronik/744235601?qs=BXmE%252BJ0Y7xYO4MPd53j2NQ%3D%3D](https://www.mouser.com/ProductDetail/Wurth-Elektronik/744235601?qs=BXmE%252BJ0Y7xYO4MPd53j2NQ%3D%3D)                                                                                                                       |
| F1                                          | 1   | 2.5A              | 1206        | Fuse               |                                                                         | [https://www.mouser.com/ProductDetail/Panasonic/ERB-RG2R50V?qs=Z3CaLxJiOJK8SjHyp%252BdV%2FQ%3D%3D](https://www.mouser.com/ProductDetail/Panasonic/ERB-RG2R50V?qs=Z3CaLxJiOJK8SjHyp%252BdV%2FQ%3D%3D)                                                                                                                             |
| F2                                          | 1   | 1A                | 1206        | Fuse               |                                                                         | [https://www.mouser.com/ProductDetail/Littelfuse/0466001.NR?qs=ar9f0rk5DXDy6tpNfF8WnQ%3D%3D](https://www.mouser.com/ProductDetail/Littelfuse/0466001.NR?qs=ar9f0rk5DXDy6tpNfF8WnQ%3D%3D)                                                                                                                                         |
| FB1                                         | 1   | BLA31AG601SN4D    | 1206        | Ferrite Bead       |                                                                         | [https://www.mouser.com/ProductDetail/Murata-Electronics/BLA31AG601SN4D?qs=2ahBf5rJw09FDcUVkQibEg%3D%3D](https://www.mouser.com/ProductDetail/Murata-Electronics/BLA31AG601SN4D?qs=2ahBf5rJw09FDcUVkQibEg%3D%3D)                                                                                                                 |
| P1                                          | 1   |                   |             | Cart connector     | Can be salvaged from DMG instead                                        | [https://www.aliexpress.com/item/3256802533298738.html?spm=a2g0o.order_list.0.0.5ee21802yek6HF](https://www.aliexpress.com/item/3256802533298738.html?spm=a2g0o.order_list.0.0.5ee21802yek6HF)                                                                                                                                   |
| P2                                          | 1   |                   |             | Link port          |                                                                         | Salvaged (DMG)                                                                                                                                                                                                                                                                                                                   |
| P3                                          | 1   | 62684-502100AHLF  |             | FFC connector      |                                                                         | [https://www.mouser.com/ProductDetail/?qs=HL%252BYNjdyZ0vzwc9E0QYY2g%3D%3D](https://www.mouser.com/ProductDetail/?qs=HL%252BYNjdyZ0vzwc9E0QYY2g%3D%3D)                                                                                                                                                                           |
| PTC1                                        | 1   | 1.1A Hold         | 1206        | Resettable Fuse    |                                                                         | [https://www.mouser.com/ProductDetail/Littelfuse/1206L110THYR?qs=CPcc0c%2Fon9HuH5Zb2mgbPg%3D%3D](https://www.mouser.com/ProductDetail/Littelfuse/1206L110THYR?qs=CPcc0c%2Fon9HuH5Zb2mgbPg%3D%3D)                                                                                                                                 |
| Q1                                          | 1   | SI1443EDH         | SOT363      | P-channel MOSFET   |                                                                         | [https://www.mouser.com/ProductDetail/Vishay-Semiconductors/SI1443EDH-T1-GE3?qs=vlV4ps1%252BrQifVq6ycRxedw%3D%3D](https://www.mouser.com/ProductDetail/Vishay-Semiconductors/SI1443EDH-T1-GE3?qs=vlV4ps1%252BrQifVq6ycRxedw%3D%3D)                                                                                               |
| R1                                          | 1   | 1k                | 0603        | Resistor           |                                                                         | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-071KL?qs=VU8sRB4EgwApHsk4rF%2F3zg%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-071KL?qs=VU8sRB4EgwApHsk4rF%2F3zg%3D%3D)                                                                                                                                       |
| R3, R31, R33                                | 3   | 18k               | 0603        | Resistor           |                                                                         | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1018KL?qs=qpJ%252B%252B%252Bdg6p1T2VMMxU7GeA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1018KL?qs=qpJ%252B%252B%252Bdg6p1T2VMMxU7GeA%3D%3D)                                                                                                                 |
| R25                                         | 1   | 1.5M              | 0603        | Resistor           | Recommended at least 1% tolerance                                       | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-071M5L?qs=VU8sRB4EgwAP38Z8qzPx9Q%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-071M5L?qs=VU8sRB4EgwAP38Z8qzPx9Q%3D%3D)                                                                                                                                         |
| R26                                         | 1   | 5.6k              | 0603        | Resistor           |                                                                         | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-075K6L?qs=2cAdsCoAWRHvOVv%2Fp%252BkS0g%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-075K6L?qs=2cAdsCoAWRHvOVv%2Fp%252BkS0g%3D%3D)                                                                                                                             |
| R27                                         | 1   | 100               | 0603        | Resistor           |                                                                         | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100RL?qs=NEN%2FsE%2FLsvPIwIWKCOS4%2FA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100RL?qs=NEN%2FsE%2FLsvPIwIWKCOS4%2FA%3D%3D)                                                                                                                           |
| R36                                         | 1   | 100k              | 0603        | Resistor           |                                                                         | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100KL?qs=e1ok2LiJcmaihem8Va5%2Fsw%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100KL?qs=e1ok2LiJcmaihem8Va5%2Fsw%3D%3D)                                                                                                                                   |
| R30, R32                                    | 2   | 47k               | 0603        | Resistor           |                                                                         | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1047KL?qs=EiqXWrxQq600ZhhpLJs%252BtA%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-1047KL?qs=EiqXWrxQq600ZhhpLJs%252BtA%3D%3D)                                                                                                                                 |
| RA1A, RA1B                                  | 2   | 510               | 0603        | Resistor           |                                                                         | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07510RL?qs=gt6vzsuosg04lV7mPQHzdw%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07510RL?qs=gt6vzsuosg04lV7mPQHzdw%3D%3D)                                                                                                                                       |
| RA3A-RA3D                                   | 4   | 270               | 0603        | Resistor           |                                                                         | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07270RL?qs=diQw95jMAePl%252BPNr4oNP6Q%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07270RL?qs=diQw95jMAePl%252BPNr4oNP6Q%3D%3D)                                                                                                                               |
| SW1                                         | 1   |                   |             | Power switch       |                                                                         | Salvaged (DMG)                                                                                                                                                                                                                                                                                                                   |
| U1                                          | 1   | GBC CPU           | QFP-128     | CPU                |                                                                         | Salvaged (GBC)                                                                                                                                                                                                                                                                                                                   |
| U2                                          | 1   | LH52256CVTXIZ     | TSOP-28     | RAM                | Replacement: https://mou.sr/3f8G0Mi                                     | Salvaged (GBC)                                                                                                                                                                                                                                                                                                                   |
| U3                                          | 1   | LM4853            | VSSOP-10    | Audio amplifier    |                                                                         | [https://www.mouser.com/ProductDetail/Texas-Instruments/LM4853MM-NOPB?qs=QbsRYf82W3F2psFI2da2Dw%3D%3D](https://www.mouser.com/ProductDetail/Texas-Instruments/LM4853MM-NOPB?qs=QbsRYf82W3F2psFI2da2Dw%3D%3D)                                                                                                                     |
| U4                                          | 1   | NCP161ASN330T1G   | SOT23-5     | LDO                | Can also use TLV70233QDBVRQ1, probably                                  | [https://www.mouser.com/ProductDetail/863-NCP161ASN330T1G](https://www.mouser.com/ProductDetail/863-NCP161ASN330T1G)                                                                                                                                                                                                             |
| U6                                          | 1   | TPS3840DL35       | SOT23-5     | Supervisory IC     | Could feasibly use TPS3840DL37 or 40 if 35 is out of stock              | [https://www.mouser.com/ProductDetail/Texas-Instruments/TPS3840DL35DBVR?qs=7MVldsJ5UawbjRj7dP73rA%3D%3D](https://www.mouser.com/ProductDetail/Texas-Instruments/TPS3840DL35DBVR?qs=7MVldsJ5UawbjRj7dP73rA%3D%3D)                                                                                                                 |
| VR1                                         | 1   | 10k               |             | Volume wheel       | Can be salvaged from DMG instead                                        | [https://aliexpi.com/qg1M](https://aliexpi.com/qg1M)                                                                                                                                                                                                                                                                             |
| X1                                          | 1   | 8.388608MHz       | 7.5X5-4-PAD | Crystal oscillator | Potential replacement (not very space-friendly): https://mou.sr/3D5AUbH | Salvaged (GBC)                                                                                                                                                                                                                                                                                                                   |

## Revision History

### v2.5
- Added space for adding <a href="https://shop.insidegadgets.com/product/gba-clockxcontrol/">ClockxControl by insideGadgets</a>

### v2.4
- Changed some reference designators for more consistency to source PCBs
- Expanded slot for FFC to feed through to back of board

### v2.3

- Nudge volume dial to better center it in the shell

### v2.2

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

## License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>. You are able to copy and redistribute the material in any medium or format, as well as remix, transform, or build upon the material for any purpose (even commercial) - but you **must** give appropriate credit, provide a link to the license, and indicate if any changes were made.

©MouseBiteLabs 2022
