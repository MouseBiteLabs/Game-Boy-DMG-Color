# DMGC-PWR-02

**TO-DO:**

- Upload pictures
- Upload files
- Test functionality

[blank board pictures]

While putting together a BOM for the DMGC-PWR-01, I realized that the TPS63070, TPS630701, and TPS630702 were out of stock in most places. Luckily, I had picked up a handful to use when they were in stock last. But I figured I should make an alternate option with more common chips. So the DMGC-PWR-02 is an alternate option to the DMGC-PWR-01, **but I would personally use the -01 if the parts are available.**

Because the system will run with 4x AA batteries or the DC jack input, the range of input voltages is relatively wide - anywhere between ~3.6 V up to ~8.5 V, plus margin. The output voltage must be maintained at 5 V. The logical choice would be a buck-boost converter. However, I was unable to locate any simple buck-boost converters that met my criteria (other than the TPS63070), so I instead opted for a bit of an unorthodox solution as a backup option – separate buck and boost converters. The input voltage will buck down to 3.3 V using the TPS62056, and then boost up to 5 V using the TPS61202.

## Board Characteristics
-	Layers: 2
-	Thickness: 1.2 mm
-	Surface Finish: ENIG

## Connections to the CPU Board
There are five wires that connect to the CPU board power supply circuitry. Pin 1 is the GND reference and pin 2 is the 5 V output from the PWR board. Pin 4, VCC, is the battery input, which is always powered by the batteries if they are present. VCC_SW is the output of the power switch on the CPU board. On the CPU board, pin 3 is connected to the DC jack output, but on the DMGC-PWR-02 I connect this to VCC as well, so that either batteries or the DC jack will power this board. A different revision might utilize the DC jack for something else, such as charging a LiPo battery, which is why I left these pins separate.

![image](https://user-images.githubusercontent.com/97127539/175819569-3407084e-0a9b-49e3-b0d0-022bb81526bd.png)

The battery voltage, VCC, is applied to the TPS62056 input voltage pin, without routing through the power switch on the CPU. Instead, the power switch controls the buck converter’s enable pin.

## Buck Converter (U1)
The first stage of the board is the buck converter, TPS62056. This chip has a wide input range – up to 10 V – that makes it suitable for the possible input voltages that could be applied. The maximum output is only 800 mA (at 3.3V that’s ~2.6 W), but power measurements detailed on the main readme show maximum power draw is only approximately 800 mW, so I believe this converter should work fine. I simply followed the datasheet’s suggestions for the buck circuit; it was pretty straightforward. This chip is a fixed buck converter, so the feedback pin is directly tied to the output (connected to the inductor L1). 

One interesting addition to this board over the DMGC-PWR-01 is the critical battery level indicator. The LBI pin is the low battery indicator input to the converter, and controls the LBO pin – this open-drain output will pull low when the LBI pin measures too low of an input voltage. Q5 is a PNP transistor, so doing this will turn on LED1. On the DMGC-IPS-01, I set the low battery power LED dimming circuit to trip at 4.45 V; on this board, I chose 4 V as the threshold. This indicates the batteries are going to die very soon – a similar function to the GBA SP’s blinking red light when the battery level is critically low. The only downside to this system is that you’d only see this indicator if the DMG shell you chose was translucent or transparent.

The enable pin for the buck converter is connected to the PSU_EN net, which is influenced by the power switch (VCC_SW). If U3, the undervoltage detection IC, detects an undervoltage condition, the enable pin to the buck converter will be turned off. If no errors are detected, PSU_EN will be pulled high to VCC once the power switch is turned on and C11 is charged up. If an undervoltage on the battery supply is ever detected, the PSU_EN net is latched off until the power switch is cycled.

It is important to keep the impedance on the VCC net to a minimum to prevent draining the batteries – therefore, all of the supervisory circuitry is only connected when the power switch is turned on, through the VCC_SW net. This is also crucial for resetting the latching circuit (detailed later). The only other impedance that loads down the batteries is the voltage divider set by R8 and R9, but at ~20 microamps maximum, this did not seem to be of much concern.

## Boost Converter (U2)
Like the buck converter before it, I just followed the datasheet for the TPS61202. This chip is the 5 V fixed output version of the TPS61200 boost converter. This was also fairly straightforward to design. 

F1 is a 1 A fuse on the 5 V output, which in hindsight is probably overkill, since the CPU board has protections that will likely always trip first (the 1 A PTC specifically). When testing the DMGC-PWR-01 board, I shorted the 5 V supply to GND to see if the fuse would pop, and the PTC opened up first every time I tried. But, I have plenty of 1 A fuses lying around, so there’s little reason not to include it just in case.

## Undervoltage Detection (U3)
U3 is a TPS3840 chip which monitors the voltage on the batteries via the VDD pin. When it detects the voltage has gone below a specific threshold, the /RESET pin is pulled low. This output is open-drain, so it does not affect the PSU_EN net while not in an error state.

The specific part I chose was the TPS3840DL22. The DL indicates the /RESET is an active-low open-drain output. (PL would indicate active-low push-pull output, PH would indicate active-high push-pull, both of which aren’t suitable for this part). The threshold voltage is determined by the last two numbers, which for my selection is 22 for 2.2 V. Any threshold below ~3.5 V (the point where the 4x series AA batteries are depleted) and above 2 V should be fine to use here, so an alternate part can be chosen if stock of the TPS3840DL22 isn’t available.

The VDD pin isn’t directly powered by the battery voltage. C1 and R7 set up an RC time delay on the battery voltage in order to filter out any power supply glitches. I found that during the start-up sequence, when the IPS screen first turns on, it can draw a lot of current from the batteries causing the supply voltage to dip considerably low. This is normal though! This doesn’t seem to affect the 2.2 V threshold part I have now, but earlier I was using a 3.5 V threshold part, so it would be erroneously tripped during startup with nearly-depleted batteries as the supply would momentarily drop to about 3 V. The current draw of the TPS3840 is less than a microamp, so the voltage drop across R7 is negligible.

The CT pin on this chip introduces a delayed start function, adding somewhat of a power switch debouncing effect. Adding a 100 nF capacitor to this pin will cause the /RESET output to be held low for approximately 62 milliseconds, which will delay the startup of the 5 V supply. This allows VCC_SW to stabilize after flipping the switch on, and allows C1 to be charged up sufficiently to begin proper undervoltage detection.

Note: I made sure to keep the time constant of R5 and C11 on the TPS62056’s enable pin to be greater than or equal to the one made by R7 and C1, because the TPS62056 will turn on after its enable pin passes ~1.3 V, but the TPS3840 will begin operation after the VDD pin passes ~300 mV. If the time constant of R5 and C11 was much smaller than R7 and C1, the TPS3840 wouldn’t be powered on to keep the enable line low during the start-up delay set by CT, and the buck-boost might be pre-maturely enabled.

## Latching Circuit
The original design of the PWR board had a funny problem. When the undervoltage detection circuit pulled the buck-boost enable pin low to disable the output, this would remove the load from the batteries. When the current draw out of the batteries suddenly dropped to almost nothing, the battery voltage would rise back up. Unfortunately, this voltage would soon pass the undervoltage trip limit, so the /RESET pin on the TPS3840 would be released, starting up the buck-boost again. But this would soon deplete the batteries below the undervoltage trip point as everything powered back up, and the system would shut off again. And… that cycle would repeat. A bootloop! Not the graceful death the original Game Boy experienced when the batteries ran out of juice.

So in order to fix this, I introduced a latching circuit, so that as soon as the batteries died the first time, the system would keep itself shut off until the power switch was cycled. I found this strategy in <a href="https://www.ti.com/lit/an/snva836a/snva836a.pdf">this very helpful application note from Texas Instruments</a>.

The latching circuit consists of Q1 through Q4 and R1 through R4. You can read the application note for the full series of events, but basically as soon as the gate of Q2 (the PSU_EN net) is pulled low by the /RESET pin for the first time (after it is released from the time delay startup), Q4 is turned on to conduct and the /MR pin (master reset) is also pulled low. On the TPS3840, whenever /MR is low, /RESET will also automatically be pulled low no matter if VDD is above or below the undervoltage trip point. So even if the voltage on the VDD pin rises back up above the trip limit, /RESET will keep Q4 conducting, which keeps /MR low as well. So the only way to reset the whole thing is to turn the power off and reset the latch. (R6 provides a path to discharge all of the capacitors in the supervisory circuit after power is removed)

## Bill of Materials

Here, I have provided links to components I used personally (or suitable replacements). This BOM is also included in Excel format in the root folder.

| Reference Designators | Qty | Value/Part Number | Package  | Description      | Comment                                         | Source                                                                                                                                     |
|-----------------------|-----|-------------------|----------|------------------|-------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------|
| C1, C3, C5            | 3   | 10 uF             | 0603     | Capacitor (MLCC) | Should be X5R (or better), at least 25V         | https://www.mouser.com/ProductDetail/Murata-Electronics/GRM188R61E106KA73J?qs=5aG0NVq1C4xEV8YyiSS7mg%3D%3D&countrycode=US&currencycode=USD |
| C2, C8                | 2   | 100 nF            | 0603     | Capacitor (MLCC) |                                                 | https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10B104KO8NNWC/3887597                                               |
| C4, C7                | 2   | 22 uF             | 1206     | Capacitor (MLCC) | Should be X5R (or better), at least 25V         | https://www.mouser.com/ProductDetail/Samsung-Electro-Mechanics/CL31A226KAHNNNE?qs=X6jEic%2FHinCdwsjGJII51w%3D%3D                           |
| C6                    | 1   | 1 uF              | 0603     | Capacitor (MLCC) | Should be X5R (or better), at least 25V         | https://www.digikey.com/en/products/detail/kemet/C0603C105K4RAC7867/2199788                                                                |
| F1                    | 1   | 1 A               | 0603     | Fuse             |                                                 | https://www.digikey.com/en/products/detail/vishay-beyschlag-draloric-bc-components/MFU0603FF01000P100/1206475                              |
| L1                    | 1   | 10 uH             | 1212     | Inductor         | At least 0.8 A saturation current               | https://www.digikey.com/en/products/detail/murata-electronics/LQH3NPZ100MJRL/9887679                                                       |
| L3                    | 1   | 2.2 uH            | 1212     | Inductor         | At least 1 A saturation current                 | https://www.mouser.com/ProductDetail/81-LQH3NPN2R2MMEL                                                                                     |
| LED1                  | 1   |                   | 0603     | Red LED          |                                                 | https://www.digikey.com/en/products/detail/rohm-semiconductor/SML-D12U1WT86/5843853                                                        |
| Q1, Q5                | 2   | MMBT3906          | SOT23    | PNP BJT          |                                                 | https://www.digikey.com/en/products/detail/micro-commercial-co/MMBT3906-TP/819631                                                          |
| Q2, Q4                | 2   | 2N7002            | SOT23    | N-channel MOSFET |                                                 | https://www.digikey.com/en/products/detail/nexperia-usa-inc/2N7002NXBKR/10416553                                                           |
| Q3                    | 1   | MMBT3904          | SOT23    | NPN BJT          |                                                 | https://www.digikey.com/en/products/detail/micro-commercial-co/MMBT3904-TP/717280                                                          |
| R1, R4, R6, R9, R11   | 5   | 100 kΩ            | 0603     | Resistor         |                                                 | https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100KL/726889                                                                   |
| R2, R3, R5, R10       | 4   | 10 kΩ             | 0603     | Resistor         |                                                 | https://www.digikey.com/en/products/detail/yageo/RC0603FR-0710KL/726880                                                                    |
| R7                    | 1   | 100 Ω             | 0603     | Resistor         |                                                 | https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100RL/726888                                                                   |
| R8                    | 1   | 232 kΩ            | 0603     | Resistor         |                                                 | https://www.digikey.com/en/products/detail/yageo/RC0603FR-07232KL/727072                                                                   |
| R12                   | 1   | 1 kΩ              | 0603     | Resistor         |                                                 | https://www.digikey.com/en/products/detail/yageo/RC0603FR-071KL/726843                                                                     |
| U1                    | 1   | TPS62056          | VSSOP-10 | Buck converter   | Might be difficult to find. Check octopart.com. | https://www.mouser.com/ProductDetail/Texas-Instruments/TPS62056DGS?qs=Gse6rAGbi7%252BfbVYUmz7rjA%3D%3D                                     |
| U2                    | 1   | TPS61202          | VSON-10  | Boost converter  | Might be difficult to find. Check octopart.com. | https://www.mouser.com/ProductDetail/Texas-Instruments/TPS61202DSCT?qs=WxL8HmPi5r5Jg6NZNBKShQ%3D%3D                                        |
| U3                    | 1   | TPS3840DL22       | SOT23-5  | Supervisory IC   |                                                 | https://www.mouser.com/ProductDetail/Texas-Instruments/TPS3840DL22DBVR?qs=%252B6g0mu59x7Lf1uRTRhpR2w%3D%3D                                 |

## Resources
-	<a href="https://www.ti.com/lit/ds/slvs432f/slvs432f.pdf?ts=1656303563615">TPS62056 datasheet</a>
-	<a href="https://www.ti.com/lit/ds/symlink/tps61200.pdf?ts=1656303585503">TPS61202 datasheet</a>
-	<a href="https://www.ti.com/lit/ds/symlink/tps3840.pdf?ts=1656386735143">TPS3840 datasheet</a>
-	<a href="https://www.ti.com/lit/an/snva836a/snva836a.pdf">Latching a Voltage Supervisor Application Note</a>

## License
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.



