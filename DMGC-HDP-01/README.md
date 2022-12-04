# DMGC-HDP-01

![image](https://user-images.githubusercontent.com/97127539/197369125-de12c47d-8e7d-44e5-8a83-9c06892fa89d.png)

*The image above is of v2.0, not the current revision of v2.1. The differences are very minor.*

This little board is quite simple. You can transplant all of the parts from the original DMG headphone board to this one. This board also uses an original DMG headphone jack. Modifications to the circuit would be required to use an off-the-shelf jack.

## Board Characteristics
The zipped folder contains all the gerber files for this board.
-	Layers: 2
-	Thickness: 1.2 mm or 1.6 mm
-	Surface Finish: HASL
- **NOTE: When ordering PCBs, add this note to the order: "The file milling.gbr contains outlines for plated slots. Please add plated slots on the PCB according to this layer."**

<a href="https://www.etsy.com/listing/1331671237/game-boy-dmgc-hdp-board-headphone-board">**I sell this board on Etsy, so you don't have to buy multiples from board fabricators.**</a>

You can alternatively use the zipped folder at any board fabricator you like. You may also buy the board from PCBWay using this link (disclosure: I receive 10% of the  sale value to go towards future PCB orders):

<a href="https://www.pcbway.com/project/shareproject/Game_Boy_DMG_Color_DMGC_HDP_01_bdacd78d.html"><img src="https://www.pcbway.com/project/img/images/frompcbway-1220.png" alt="PCB from PCBWay" /></a>

## Circuit Overview

![image](https://user-images.githubusercontent.com/97127539/197369045-dd0a85d2-1ccb-44ef-8f6c-d4758343486b.png)

On the top of the board: pin 1 is the left output, pin 2 is the right output, pin 3 is the GND reference, and pin 4 is the headphone detect pin which is normally connected to GND through the headphone jack (when headphones are placed in the jack, pin 4 will be disconnected from GND).

R1 and R2 are included to pull down the negative sides of the DC blocking capacitors C1 and C2 when headphones are not connected – without them, the outputs would be floating. This will prevent inrush current during headphone insertion, which I have seen cause issues with the LM4853 in the past.

On v2.1, C1 and C2 can be replaced with tantalum electrolytic capacitors if you would like - the pads are for size 1411 (3528 metric).

## Using the Original DMG Headphone Board

You can easily use the original DMG board instead of ordering this one, just be sure to put 1 kΩ resistors from the right output and left output to ground. Otherwise, when plugging in headphones, the system might shut itself off.

![image](https://user-images.githubusercontent.com/97127539/180674925-899182a6-bb51-4ddf-804c-e71c3ef99e59.png)

## Bill of Materials

All of the parts from the original headphone board can be transplanted here (except the two 1k resistors). You can even use the original headphone board if you want, just add the 1k resistors as indicated on the schematic. This BOM is also included in Excel format in the root folder.

| Reference Designators | Qty | Value/Part Number | Package | Description                       | Comment                                            | Source                                                                 |
|-----------------------|-----|-------------------|---------|-----------------------------------|----------------------------------------------------|------------------------------------------------------------------------|
| C1, C2                | 2   | 100 uF            |         | Capacitor (Aluminum electrolytic) | Replacement: https://www.mouser.com/ProductDetail/Panasonic/ECE-A0JKA101I?qs=WYPlz5ezODCWQbvWRFj8Mg%3D%3D | Salvaged (DMG)                                                         |
| L1, L2, L3            | 3   | 3.3 uH            |         | Filter                            | Surface mount replacement: https://www.mouser.com/ProductDetail/Murata-Electronics/BLM18BD102SN1D?qs=h3IWXJJGQQWi4eZyJq6ScQ%3D%3D | Salvaged (DMG)                                                         |
| JACK                  | 1   |                   |         | Headphone jack                    |                                                    | Salvaged (DMG)                                                         |
| R1, R2                | 2   | 1 kΩ              | 0603    | Resistor                          |                                                    | https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-071KL?qs=VU8sRB4EgwApHsk4rF%2F3zg%3D%3D |

## Revision History

### v2.1

- Add surface mount pads for tantalum capacitors, size 1411 (3528 metric)

### v2.0

- Changed holes to slots where applicable
- Made board/part measurements more accurate
- Added pads for SMT inductors for L1-L3

### v1.2

- Tented a single via

### v1.1

- Release version

## Resources
-	<a href="https://gbdev.gg8.se/files/schematics/">Rolf, bit9, and nitro2k01’s DMG schematics and layouts</a>

## License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>. You are able to copy and redistribute the material in any medium or format, as well as remix, transform, or build upon the material for any purpose (even commercial) - but you **must** give appropriate credit, provide a link to the license, and indicate if any changes were made.

©MouseBiteLabs 2022
