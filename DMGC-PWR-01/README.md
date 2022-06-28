# DMGC-PWR-01

**TO-DO:**

- Upload pictures
- Upload files

[blank board pictures]

The PWR board has gone through a few iterations. Because the system will run with 4x AA batteries or the DC jack input, the range of input voltages is relatively wide - anywhere between ~3.6 V up to ~8.5 V, plus margin. The output voltage must be maintained at 5 V. The logical choice would be a buck-boost converter. Thus, the DMGC-PWR-01 utilizes the TPS630702 (or TPS63070 or TPS630701) – a buck-boost converter with only a few external parts required for operation, that accepts anywhere between 2 V and 16 V to produce a 5 V output.
## Board Characteristics
-	Layers: 2
-	Thickness: 1.2 mm
-	Surface Finish: ENIG
## Connections to the CPU Board
There are five wires that connect to the CPU board power supply circuitry. Pin 1 is the GND reference and pin 2 is the 5 V output from the PWR board. Pin 4, VCC, is the battery input, which is always powered by the batteries if they are present. VCC_SW is the output of the power switch on the CPU board. On the CPU board, pin 3 is connected to the DC jack output, but on the DMGC-PWR-01 I connect this to VCC as well, so that either batteries or the DC jack will power this board. A different revision might utilize the DC jack for something else, such as charging a LiPo battery, which is why I left these pins separate.

![image](https://user-images.githubusercontent.com/97127539/175819465-ad77a108-7477-41d9-8025-9d6307a248aa.png)

The battery voltage, VCC, is applied to the buck-boost input voltage pin, without routing through the power switch on the CPU. Instead, the power switch controls the buck-boost converter’s enable pin.

## Buck-Boost Converter (U2)
The bottom half of the circuit is the entire buck-boost stage. I followed the TPS63070 datasheet for choosing values of the input and output capacitance, the inductor, and the feedback resistors. R8 and R9 set up a voltage divider for setting the output of the adjustable TPS630702 or TPS63070 – if the TPS630701 is used instead, which is a 5 V fixed version, then R8 should be short circuited and R9 can be removed. **If you leave R8 and R9 at the values they are with the fixed 5 V chip, the output will shoot up to ~11V. I strongly recommend testing this power supply board separately from the rest of the system to ensure the 5 V output is correct and steady, without frying anything else downstream.**

The buck-boost chip is activated when the EN pin is high. SJ1 can be soldered such that it is automatically turned on when VCC is applied. This is really only for troubleshooting purposes, as it would activate the Game Boy whenever batteries were plugged in, regardless of what the power switch was doing (unless the CPU board is modified). Normally, it should be connected to the PSU_EN net, which is influenced by two chips – U3 (overvoltage protection) and U1 (undervoltage detection). If no errors are detected in the power supply, then PSU_EN will be pulled high to VCC once the power switch is turned on and C11 is charged up. If either an overvoltage on the 5 V line or an undervoltage on the battery supply is detected, the PSU_EN net is latched off until the power switch is cycled. 

It is important to keep the impedance on the VCC net to a minimum to prevent draining the batteries – therefore, all of the supervisory circuitry is only connected when the power switch is turned on, through the VCC_SW net. This is also crucial for resetting the latching circuit (detailed later).

F1 is a 1 A fuse on the 5 V output, which in hindsight is probably overkill, since the CPU board has protections that will likely always trip first (the 1 A PTC specifically). When testing the PWR board, I shorted the 5 V supply to GND to see if the fuse would pop, and the PTC opened up first every time I tried. But, I have plenty of 1 A fuses lying around, so there’s little reason not to include it just in case, since the TPS63070 chips can output up to 3.6 A.

## Overvoltage Protection (U3)
U3 is a TPS3702 IC. This chip monitors the 5 V output on the SENSE pin. If it’s above a certain value, the output on the OV pin will be pulled low. Otherwise, OV is an open-drain output, so it doesn’t affect the output of the PSU_EN net during normal operation.

The specific part I have chosen is the TPS3702CX50. With the SET pin tied to GND, this sets the overvoltage threshold to 5.45 V. If the supply ever passes this point, then the overvoltage pin will pull PSU_EN low, and the latching circuit will keep it off until the power switch is cycled.

The overvoltage protection is likely overkill as well, as long as the buck-boost circuit is set up correctly and soldered properly. Since the adjustable TPS63070 chips measure the feedback through the FB pin, it will maintain the 5 V as long as no solder bridges or poor solder connections cause the wrong voltage to be measured by the chip (and the rest of the circuit is set up properly). You can omit U3, C9, and C10 to remove the overvoltage detection without impacting the rest of the circuit.
## Undervoltage Detection (U1)
U1 is a TPS3840 chip which monitors the voltage on the batteries via the VDD pin. When it detects the voltage has gone below a specific threshold, the /RESET pin is pulled low. Like the TPS3702, this output is open-drain, so it does not affect the PSU_EN net while not in an error state.

The specific part I chose was the TPS3840DL22. The DL indicates the /RESET is an active-low open-drain output. (PL would indicate active-low push-pull output, PH would indicate active-high push-pull, both of which aren’t suitable for this part). The threshold voltage is determined by the last two numbers, which for my selection is 22 for 2.2 V. Any threshold below ~3.5 V (the point where the 4x series AA batteries are depleted) and above 2 V should be fine to use here, so an alternate part can be chosen if stock of the TPS3840DL22 isn’t available.

The VDD pin isn’t directly powered by the battery voltage. C1 and R7 set up an RC time delay on the battery voltage in order to filter out any power supply glitches. I found that during the start-up sequence, when the IPS screen first turns on, it can draw a lot of current from the batteries causing the supply voltage to dip considerably low. This is normal though! This doesn’t seem to affect the 2.2 V threshold part I have now, but earlier I was using a 3.5 V threshold part, so it would be erroneously tripped during startup with nearly-depleted batteries as the supply would momentarily drop to about 3 V. The current draw of the TPS3840 is less than a microamp, so the voltage drop across R7 is negligible.

The CT pin on this chip introduces a delayed start function, adding somewhat of a power switch debouncing effect. Adding a 100 nF capacitor to this pin will cause the /RESET output to be held low for approximately 62 milliseconds, which will delay the startup of the 5 V supply. This allows VCC_SW to stabilize after flipping the switch on, and allows C1 to be charged up sufficiently to begin proper undervoltage detection.

Note: I made sure to keep the time constant of R5 and C11 on the buck-boost’s enable pin to be greater than or equal to the one made by R7 and C1, because the converter will turn on after its enable pin passes ~800 mV, but the TPS3840 will begin operation after the VDD pin passes ~300 mV. If the time constant of R5 and C11 was much smaller than R7 and C1, the TPS3840 wouldn’t be powered on to keep the enable line low during the start-up delay set by CT, and the buck-boost might be pre-maturely enabled.
## Latching Circuit
The original design of the PWR board had a funny problem. When the undervoltage detection circuit pulled the buck-boost enable pin low to disable the output, this would remove the load from the batteries. When the current draw out of the batteries suddenly dropped to almost nothing, the battery voltage would rise back up. Unfortunately, this voltage would soon pass the undervoltage trip limit, so the /RESET pin on the TPS3840 would be released, starting up the buck-boost again. But this would soon deplete the batteries below the undervoltage trip point as everything powered back up, and the system would shut off again. And… that cycle would repeat. A bootloop! Not the graceful death the original Game Boy experienced when the batteries ran out of juice.

So in order to fix this, I introduced a latching circuit, so that as soon as the batteries died the first time, the system would keep itself shut off until the power switch was cycled. I found this strategy in this very helpful application note from Texas Instruments. (You know, Texas Instruments should have sponsored this project, because I sure do use a lot of their parts)

The latching circuit consists of Q1 through Q4 and R1 through R4. You can read the application note for the full series of events, but basically as soon as the gate of Q2 (the PSU_EN net) is pulled low by the /RESET pin for the first time (after it is released from the time delay startup), Q4 is turned on to conduct and the /MR pin (master reset) is also pulled low. On the TPS3840, whenever /MR is low, /RESET will also automatically be pulled low no matter if VDD is above or below the undervoltage trip point. So even if the voltage on the VDD pin rises back up above the trip limit, /RESET will keep Q4 conducting, which keeps /MR low as well. So the only way to reset the whole thing is to turn the power off and reset the latch. (R6 provides a path to discharge all of the capacitors in the supervisory circuit after power is removed)

## Bill of Materials

Here, I have provided links to components I used personally (or suitable replacements). This BOM is also included in Excel format in the root folder.

| Reference Designators        | Qty | Value/Part Number              | Package    | Description          | Comment                                                              | Source                                                                                                                                     |
|------------------------------|-----|--------------------------------|------------|----------------------|----------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------|
| C3, C4                       | 2   | 22 uF                          | 1206       | Capacitor (MLCC)     | Should be X5R (or better), at least 25V                              | https://www.mouser.com/ProductDetail/Samsung-Electro-Mechanics/CL31A226KAHNNNE?qs=X6jEic%2FHinCdwsjGJII51w%3D%3D                           |
| C1, C5, C6                   | 3   | 10 uF                          | 0603       | Capacitor (MLCC)     | Should be X5R (or better), at least 25V                              | https://www.mouser.com/ProductDetail/Murata-Electronics/GRM188R61E106KA73J?qs=5aG0NVq1C4xEV8YyiSS7mg%3D%3D&countrycode=US&currencycode=USD |
| C7                           | 1   | 47 uF                          | 1206       | Capacitor (MLCC)     | Should be X5R (or better), at least 16V (maybe 10V is ok)            | https://www.mouser.com/ProductDetail/Taiyo-Yuden/EMK316BBJ476ML-T?qs=Zy5V7Kj3rCVVMQaoWTlMmg%3D%3D                                          |
| C8                           | 1   | 100 nF                         | 0603       | Capacitor (MLCC)     |                                                                      | https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10B104KO8NNWC/3887597                                               |
| F1                           | 1   | 1 A                            | 0603       | Fuse                 |                                                                      | https://www.digikey.com/en/products/detail/vishay-beyschlag-draloric-bc-components/MFU0603FF01000P100/1206475                              |
| L1                           | 1   | 1.5 uH                         | 1212       | Inductor             | Saturation current should be at least 2A                             | https://www.mouser.com/ProductDetail/70-IHLP1212BZER1R5M1                                                                                  |
| Q1                           | 1   | MMBT3906                       | SOT23      | PNP BJT              |                                                                      | https://www.digikey.com/en/products/detail/micro-commercial-co/MMBT3906-TP/819631                                                          |
| Q2, Q4                       | 2   | 2N7002                         | SOT23      | N-channel MOSFET     |                                                                      | https://www.digikey.com/en/products/detail/nexperia-usa-inc/2N7002NXBKR/10416553                                                           |
| Q3                           | 1   | MMBT3904                       | SOT23      | NPN BJT              |                                                                      | https://www.digikey.com/en/products/detail/micro-commercial-co/MMBT3904-TP/717280                                                          |
| R1, R4, R5, R6, R9, R10, R11 | 7   | 100 kΩ                         | 0603       | Resistor             | R9 should have at least 1% tolerance                                 | https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100KL/726889                                                                   |
| R2, R3                       | 2   | 10 kΩ                          | 0603       | Resistor             |                                                                      | https://www.digikey.com/en/products/detail/yageo/RC0603FR-0710KL/726880                                                                    |
| R7                           | 1   | 100 Ω                          | 0603       | Resistor             |                                                                      | https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100RL/726888                                                                   |
| R8                           | 1   | 523 kΩ                         | 0603       | Resistor             | At least 1% tolerance. Not needed if using TPS630701                 | https://www.digikey.com/en/products/detail/yageo/RC0603FR-07523KL/727292                                                                   |
| U1                           | 1   | TPS3840DL22                    | SOT23-5    | Supervisory IC       |                                                                      | https://www.mouser.com/ProductDetail/Texas-Instruments/TPS3840DL22DBVR?qs=%252B6g0mu59x7Lf1uRTRhpR2w%3D%3D                                 |
| U2                           | 1   | TPS63070, TPS630701, TPS630702 | 15-VQFN-HR | Buck-boost converter | Might be difficult to find. Check octopart.com. TPS630702 preferred. | https://www.digikey.com/en/products/detail/TPS630702RNMT/296-TPS630702RNMTCT-ND/10435142                                                   |

## Resources
-	<a href="https://www.ti.com/lit/ds/symlink/tps63070.pdf?ts=1647052355945">TPS63070 datasheet</a>
-	<a href="https://www.ti.com/lit/ds/symlink/tps3840.pdf?ts=1656386735143">TPS3840 datasheet</a>
-	<a href="https://www.ti.com/lit/ds/symlink/tps3702.pdf?ts=1656335717520">TPS3702 datasheet</a>
-	<a href="https://www.ti.com/lit/an/snva836a/snva836a.pdf">Latching a Voltage Supervisor Application Note</a>

## License
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.


