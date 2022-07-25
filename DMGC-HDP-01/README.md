# DMGC-HDP-01

**TO-DO:**

- Upload assembled board picture

![image](https://user-images.githubusercontent.com/97127539/180582438-4e3d7694-0597-42bd-ab3b-f34e2c34e663.png)

*These board scans are for v1.1, which only has minor differences from the updated v1.2*

This little board is quite simple. You can transplant all of the parts from the original DMG headphone board to this one. This board also uses an original DMG headphone jack. Modifications to the circuit would be required to use an off-the-shelf jack.

## Board Characteristics
The zipped folder contains all the gerber files for this board.
-	Layers: 2
-	Thickness: 1.2 mm
-	Surface Finish: HASL

## Circuit Overview

![image](https://user-images.githubusercontent.com/97127539/179897524-bd74a364-c584-42a9-b284-9659ea163933.png)

On the top of the board: pin 1 is the left output, pin 2 is the right output, pin 3 is the GND reference, and pin 4 is the headphone detect pin which is normally connected to GND through the headphone jack (when headphones are placed in the jack, pin 4 will be disconnected from GND).

R1 and R2 are included to pull down the negative sides of the DC blocking capacitors C1 and C2 when headphones are not connected – without them, the outputs would be floating. This will prevent inrush current during headphone insertion, which I have seen cause issues with the LM4853 in the past.

## Using the Original DMG Headphone Board

You can easily use the original DMG board instead of ordering this one, just be sure to put 1 kΩ resistors from the right output and left output to ground. Otherwise, when plugging in headphones, the system might shut itself off.

![image](https://user-images.githubusercontent.com/97127539/180674925-899182a6-bb51-4ddf-804c-e71c3ef99e59.png)

## Bill of Materials

All of the parts from the original headphone board can be transplanted here (except the two 1k resistors). You can even use the original headphone board if you want, just add the 1k resistors as indicated on the schematic. This BOM is also included in Excel format in the root folder.

| Reference Designators | Qty | Value/Part Number | Package | Description                       | Comment                                            | Source                                                                 |
|-----------------------|-----|-------------------|---------|-----------------------------------|----------------------------------------------------|------------------------------------------------------------------------|
| C1, C2                | 2   | 100 uF            |         | Capacitor (Aluminum electrolytic) | Panasonic ECE-A0JKA101 might be a good replacement | Salvaged (DMG)                                                         |
| L1, L2, L3            | 3   | 33 uH             |         | Filter                            |                                                    | Salvaged (DMG)                                                         |
| JACK                  | 1   |                   |         | Headphone jack                    |                                                    | Salvaged (DMG)                                                         |
| R1, R2                | 2   | 1 kΩ              | 0603    | Resistor                          |                                                    | https://www.digikey.com/en/products/detail/yageo/RC0603FR-071KL/726843 |

## Revision History

### v1.2

- Tented a single via

### v1.1

- Release version

## Resources
-	<a href="https://gbdev.gg8.se/files/schematics/">Rolf, bit9, and nitro2k01’s DMG schematics and layouts</a>
## License
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.


