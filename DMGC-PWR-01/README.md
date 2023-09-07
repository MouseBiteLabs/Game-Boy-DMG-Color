# DMGC-PWR-01

![DMGC-PWR-01_2-0_black](https://user-images.githubusercontent.com/97127539/196013270-510567e9-d96e-467d-9880-b106b62498b9.png)
![DMGC-PWR-01_2-0_ASSEMBLED_black](https://user-images.githubusercontent.com/97127539/196013348-b0da11ba-1f93-4a57-be55-93847c8d9b15.png)

*Note: This image shows v2.0. There is minimal difference between this and v2.3.*

The PWR board has gone through a few iterations. Because the system will run with 4x AA batteries or the DC jack input, the range of input voltages is relatively wide - anywhere between ~4 V up to ~8 V, plus margin. The output voltage must be maintained at 5 V. The logical choice would be a buck-boost converter. Thus, the DMGC-PWR-01 utilizes the TPS630702 (or TPS63070 or TPS630701) – a buck-boost converter with only a few external parts required for operation, that accepts anywhere between 2 V and 16 V to produce a 5 V output.

This board is likely the most complex part of the build. I spent a lot of time tuning the circuit to produce the exact results I wanted with ample protection downstream of the converters.

For a technical explanation of the CPU board, please view the README in the Technical folder.

## Board Characteristics
The zipped folder contains all the gerber files for this board.
-	Layers: 2
-	Thickness: 1.2 mm or smaller
-	Surface Finish: ENIG or HASL

*HASL is acceptable, but might introduce a bit of difficulty soldering the QFN chip owing to the possibly uneven surface compared to an ENIG finish.*

<a href="https://www.etsy.com/listing/1317694018/game-boy-dmgc-pwr-board">**I sell this board on Etsy, so you don't have to buy multiples from board fabricators.**</a>

You can alternatively use the zipped folder at any board fabricator you like. You may also buy the board from PCBWay using this link (disclosure: I receive 10% of the sale value to go towards future PCB orders):

<a href="https://www.pcbway.com/project/shareproject/Game_Boy_DMG_Color_DMGC_PWR_01_f8f2e84a.html"><img src="https://www.pcbway.com/project/img/images/frompcbway-1220.png" alt="PCB from PCBWay" /></a>

## Using in an Original DMG (UNTESTED!)

This board can (probably) be used as a replacement to the original DMG power board, provided you are using an IPS screen that only requires a 5 V output. This board will not supply voltages for the LCD, so it cannot be used in an unmodded DMG.

![image](https://github.com/MouseBiteLabs/Game-Boy-DMG-Color/assets/97127539/ae8cc55e-1ce8-4598-8e4c-e732901c4dc2)

Follow the silkscreen on the back of the board to connect wires to the DMG motherboard, as shown below (image from Gekkio's Game Boy Hardware Database: https://gbhwdb.gekkio.fi/consoles/dmg/). The red wire on the main DMG CPU board indicates pin 1. The blue box on the back of the DMG CPU board indicates the connection for the BAT hole.

![image](https://github.com/MouseBiteLabs/Game-Boy-DMG-Color/assets/97127539/15d7c41d-f7a1-4f1a-9562-7f35d82c0161)

IF you happen to test this (at your own risk!) let me know your results.

## Bill of Materials

Here, I have provided links to components I used personally (or suitable replacements). This BOM is also included in Excel format in the root folder.

| Reference Designators         | Qty | Value/Part Number              | Package    | Description          | Comment                                                                                                                               | Source                                                                                                                                                                                                                                                                                   |
| ----------------------------- | --- | ------------------------------ | ---------- | -------------------- | ------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| C1, C5, C6                    | 3   | 10uF                           | 0603       | Capacitor (MLCC)     | Should be X5R (or better), at least 16V                                                                                               | [https://www.mouser.com/ProductDetail/Murata-Electronics/GRM188R61E106KA73J?qs=5aG0NVq1C4xEV8YyiSS7mg%3D%3D&countrycode=US&currencycode=USD](https://www.mouser.com/ProductDetail/Murata-Electronics/GRM188R61E106KA73J?qs=5aG0NVq1C4xEV8YyiSS7mg%3D%3D&countrycode=US&currencycode=USD) |
| C3, C4                        | 2   | 22uF                           | 1206       | Capacitor (MLCC)     | Should be X5R (or better), at least 16V                                                                                               | [https://www.mouser.com/ProductDetail/Samsung-Electro-Mechanics/CL31A226KAHNNNE?qs=X6jEic%2FHinCdwsjGJII51w%3D%3D](https://www.mouser.com/ProductDetail/Samsung-Electro-Mechanics/CL31A226KAHNNNE?qs=X6jEic%2FHinCdwsjGJII51w%3D%3D)                                                     |
| C7                            | 1   | 47uF                           | 1206       | Capacitor (MLCC)     | Should be X5R (or better), at least 16V                                                                                               | [https://www.mouser.com/ProductDetail/Murata-Electronics/GRM31CR61C476ME44K?qs=QzBtWTOodeVeYV6UhCOqow%3D%3D](https://www.mouser.com/ProductDetail/Murata-Electronics/GRM31CR61C476ME44K?qs=QzBtWTOodeVeYV6UhCOqow%3D%3D)                                                                 |
| C8, C9, C11                   | 3   | 0.1uF                          | 0603       | Capacitor (MLCC)     |                                                                                                                                       | [https://www.mouser.com/ProductDetail/?qs=l5k%252BbMnNDknCtKnMv1oEgA%3D%3D](https://www.mouser.com/ProductDetail/?qs=l5k%252BbMnNDknCtKnMv1oEgA%3D%3D)                                                                                                                                   |
| C10                           | 1   | 0.01uF                         | 0603       | Capacitor (MLCC)     |                                                                                                                                       | [https://www.mouser.com/ProductDetail/KEMET/C0603C103J5RACTU?qs=BimOss5pjlFJEfKhlb7g1g%3D%3D](https://www.mouser.com/ProductDetail/KEMET/C0603C103J5RACTU?qs=BimOss5pjlFJEfKhlb7g1g%3D%3D)                                                                                               |
| F1                            | 1   | 1A                             | 0603       | Fuse                 |                                                                                                                                       | [https://www.mouser.com/ProductDetail/Vishay-Beyschlag/MFU0603FF01000P100?qs=oI046glRurtlP8n%252B3l7CPg%3D%3D](https://www.mouser.com/ProductDetail/Vishay-Beyschlag/MFU0603FF01000P100?qs=oI046glRurtlP8n%252B3l7CPg%3D%3D)                                                             |
| L1                            | 1   | 1.5uH                          | 1212       | Inductor             | Saturation current should be at least 2A                                                                                              | [https://www.mouser.com/ProductDetail/70-IHLP1212BZER1R5M1](https://www.mouser.com/ProductDetail/70-IHLP1212BZER1R5M1)                                                                                                                                                                   |
| Q1                            | 1   | MMBT3906                       | SOT23      | PNP BJT              |                                                                                                                                       | [https://www.mouser.com/ProductDetail/Micro-Commercial-Components-MCC/MMBT3906HE3-TP?qs=HBWAp0VN4Rh%2Ft2ZPx%252BV99A%3D%3D](https://www.mouser.com/ProductDetail/Micro-Commercial-Components-MCC/MMBT3906HE3-TP?qs=HBWAp0VN4Rh%2Ft2ZPx%252BV99A%3D%3D)                                   |
| Q2, Q4, Q5                    | 3   | 2N7002                         | SOT23      | N-channel MOSFET     |                                                                                                                                       | [https://www.mouser.com/ProductDetail/Nexperia/2N7002NXBKR?qs=%252B6g0mu59x7J2ddJstTJGkQ%3D%3D](https://www.mouser.com/ProductDetail/Nexperia/2N7002NXBKR?qs=%252B6g0mu59x7J2ddJstTJGkQ%3D%3D)                                                                                           |
| Q3                            | 1   | MMBT3904                       | SOT23      | NPN BJT              |                                                                                                                                       | [https://www.mouser.com/ProductDetail/Nexperia/MMBT3904VL?qs=cnAQGvEIVkKbCwIpHJoHxQ%3D%3D](https://www.mouser.com/ProductDetail/Nexperia/MMBT3904VL?qs=cnAQGvEIVkKbCwIpHJoHxQ%3D%3D)                                                                                                     |
| Q6                            | 1   | SI1443EDH                      | SOT363     | P-channel MOSFET     |                                                                                                                                       | [https://www.mouser.com/ProductDetail/Vishay-Semiconductors/SI1443EDH-T1-GE3?qs=vlV4ps1%252BrQifVq6ycRxedw%3D%3D](https://www.mouser.com/ProductDetail/Vishay-Semiconductors/SI1443EDH-T1-GE3?qs=vlV4ps1%252BrQifVq6ycRxedw%3D%3D)                                                       |
| R1, R4, R7, R9, R10, R11, R16 | 7   | 100k                           | 0603       | Resistor             | R9 should have at least 1% tolerance                                                                                                  | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100KL?qs=e1ok2LiJcmaihem8Va5%2Fsw%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07100KL?qs=e1ok2LiJcmaihem8Va5%2Fsw%3D%3D)                                                                                           |
| R2, R3, R5, R13, R14          | 5   | 10k                            | 0603       | Resistor             |                                                                                                                                       | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-0710KL?qs=grNVn54RoB%252B3GtjbJj3wJQ%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-0710KL?qs=grNVn54RoB%252B3GtjbJj3wJQ%3D%3D)                                                                                         |
| R15                           | 1   | 1k                             | 0603       | Resistor             |                                                                                                                                       | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-071KL?qs=VU8sRB4EgwApHsk4rF%2F3zg%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-071KL?qs=VU8sRB4EgwApHsk4rF%2F3zg%3D%3D)                                                                                               |
| R8                            | 1   | 523k                           | 0603       | Resistor             | At least 1% tolerance. Not needed if using TPS630701                                                                                  | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07523KL?qs=TkC2zyCLazpzUFWuXe7EHg%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-07523KL?qs=TkC2zyCLazpzUFWuXe7EHg%3D%3D)                                                                                               |
| R12                           | 1   | 20k                            | 0603       | Resistor             |                                                                                                                                       | [https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-0720KL?qs=VU8sRB4EgwCsxfrjtEIKPQ%3D%3D](https://www.mouser.com/ProductDetail/YAGEO/RC0603FR-0720KL?qs=VU8sRB4EgwCsxfrjtEIKPQ%3D%3D)                                                                                                 |
| U1                            | 1   | TPS3840DL35                    | SOT23-5    | Supervisory IC       | Could feasibly use TPS3840DL32 if 35 is out of stock                                                                                  | [https://www.mouser.com/ProductDetail/Texas-Instruments/TPS3840DL35DBVR?qs=7MVldsJ5UawbjRj7dP73rA%3D%3D](https://www.mouser.com/ProductDetail/Texas-Instruments/TPS3840DL35DBVR?qs=7MVldsJ5UawbjRj7dP73rA%3D%3D)                                                                         |
| U2                            | 1   | TPS63070, TPS630701, TPS630702 | 15-VQFN-HR | Buck-boost converter | Might be difficult to find. TPS630702 preferred, but all will work. Check https://octopart.com/search?q=tps63070&currency=USD&specs=0 | [https://www.mouser.com/ProductDetail/Texas-Instruments/TPS630702RNMT?qs=vLWxofP3U2wR9GhA3fXurw%3D%3D](https://www.mouser.com/ProductDetail/Texas-Instruments/TPS630702RNMT?qs=vLWxofP3U2wR9GhA3fXurw%3D%3D)                                                                             |
| U3                            | 1   | TPS3702CX50                    | SOT23-6    | Supervisory IC       | Optional IF you fully test the power board and confirm proper 5V operation                                                            | [https://www.mouser.com/ProductDetail/595-TPS3702CX50DDCR](https://www.mouser.com/ProductDetail/595-TPS3702CX50DDCR)                                                                                                                                                                     |

## Revision History

### v2.3
- Moved some components
- Removed C2 (not needed on previous revisions either)
- Fixed DMG connection silkscreen
- Changed RC time constant for undervoltage detection
- Added test points across the board

### v2.2
- Added F1 back
- Added DMG connections notation on silkscreen

### v2.1
- Moved R12/R13 to front of the board
- Removed F1

### v2.0 (for sale)
- Release version

## License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>. You are able to copy and redistribute the material in any medium or format, as well as remix, transform, or build upon the material for any purpose (even commercial) - but you **must** give appropriate credit, provide a link to the license, and indicate if any changes were made.

©MouseBiteLabs 2022
