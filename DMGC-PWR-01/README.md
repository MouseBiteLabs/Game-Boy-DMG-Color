# DMGC-PWR-01

**TO-DO:**

- Update BOM
- Make sure this makes sense, lol
- Upload pictures
- Upload source files and gerber zip

[blank board pictures]

The PWR board has gone through a few iterations. Because the system will run with 4x AA batteries or the DC jack input, the range of input voltages is relatively wide - anywhere between ~4 V up to ~8 V, plus margin. The output voltage must be maintained at 5 V. The logical choice would be a buck-boost converter. Thus, the DMGC-PWR-01 utilizes the TPS630702 (or TPS63070 or TPS630701) – a buck-boost converter with only a few external parts required for operation, that accepts anywhere between 2 V and 16 V to produce a 5 V output.

This board is likely the most complex part of the build. I spent a lot of time tuning the circuit to produce the exact results I wanted with ample protection downstream of the converters. Unfortunately, at the time of writing, the buck-boost converter chips are not easily sourced. I have begun development of a DMGC-PWR-02 board that will use more commonly-found chips. But feel free to design your own if you'd like ;D

## Board Characteristics
The zipped folder contains all the gerber files for this board.
-	Layers: 2
-	Thickness: 1.2 mm
-	Surface Finish: ENIG

## Connections to the CPU Board
There are five wires that connect to the CPU board power supply circuitry. Pin 1 is the GND reference and pin 2 is the 5 V output from the PWR board. Pin 4, VCC, is the battery input, which is always powered by the batteries if they are present. VCC_SW is the output of the power switch on the CPU board. On the CPU board, pin 3 is connected to the DC jack output, but on this board I connect this to VCC as well, so that either batteries or the DC jack will power this board. A different revision might utilize the DC jack for something else, such as charging a LiPo battery, which is why I left these pins separate.

![image](https://user-images.githubusercontent.com/97127539/180590265-a73ace4a-d27c-4602-bf98-8baf16e3594f.png)

The battery voltage, VCC, is applied to the buck-boost input voltage pin, without routing through the power switch on the CPU. Instead, the power switch controls the buck-boost converter’s enable pin.

## Buck-Boost Converter (U2)

U2 can be TPS63070, TPS630701, or TPS630702. TPS630701 is a fixed 5 V buck-boost, while the other two have adjustable output via a voltage divider. The only difference between TPS63070 and TPS630702 is that the latter has an output discharge function - when the output is disabled, a low impedance (~200 Ω) is connected to the rail internally to quickly discharge the output capacitors. If you have a choice, I would recommend using the TPS630702 over the other two, and the TPS630701 over the TPS63070 just because it's a bit more convenient (and foolproof) to use the fixed output version of the chip. But any three of them will work perfectly fine. They don't like to be in stock very often from what I've seen - check stocks on octopart.com. I have been lucky and found a few random instances of Digikey or Mouser getting in a handful of the chips (or, more likely, finding extra parts lying around in their warehouses). At the time of writing, it appears Newark and Texas Instruments themselves have some available for purchase.

The bottom half of the circuit is the entire buck-boost stage. I followed the TPS63070 datasheet for choosing values of the input and output capacitance, the inductor, and the feedback resistors. R8 and R9 set up a voltage divider for setting the output of the adjustable TPS630702 or TPS63070 – if the TPS630701 is used instead, which is the 5 V fixed output version, then R8 should be short circuited and R9 can be removed. **If you leave R8 and R9 at the values they are with the fixed 5 V chip, the output will shoot up to ~11V. I strongly recommend testing this power supply board separately from the rest of the system to ensure the 5 V output is correct and steady, without frying anything else downstream.**

The buck-boost chip is activated when the EN pin is high. This pin is connected to the PSU_EN net, which is influenced by two chips – U3 (overvoltage protection) and U1 (undervoltage detection). If no errors are detected in the power supply, then PSU_EN will be pulled high to VCC once the power switch is turned on and C11 is charged up. If either an overvoltage on the 5 V line or an undervoltage on the battery supply is detected, the PSU_EN net is latched off until the power switch is cycled. The PSU_EN net is crucial for the proper operation of the power board, and will be explained in greater detail below.

It is important to keep the impedance on the VCC net to a minimum to prevent draining the batteries – therefore, all of the supervisory circuitry is only connected when the power switch is turned on, through the VCC_SW net. This is also crucial for resetting the latching circuit (detailed later).

F1 is a 1 A fuse on the 5 V output, which in hindsight is probably overkill, since the CPU board has protections that will likely always trip first (the 1 A PTC specifically). When testing the PWR board, I shorted the 5 V supply to GND to see if the fuse would pop, and the PTC opened up first every time I tried. But, I have plenty of 1 A fuses lying around, so there’s little reason not to include it just in case, since the TPS63070 chips can output up to 3.6 A.

## Overvoltage Protection (U3)

Onto the protection circuitry - let's get the easy one out of the way first. U3 is a TPS3702 IC. This chip monitors the 5 V output on the SENSE pin. If it’s above a certain value, the output on the OV pin will be pulled low. Otherwise, OV is an open-drain output, so it doesn’t affect the output of the PSU_EN net during normal operation.

The specific part I have chosen is the TPS3702CX50. With the SET pin tied to GND, this sets the overvoltage threshold to 5.45 V. If the supply ever passes this point, then the overvoltage pin will pull PSU_EN low, and the latching circuit will keep it off until the power switch is cycled.

The overvoltage protection is likely overkill as well, as long as the buck-boost circuit is set up correctly and soldered properly. Since the adjustable TPS63070 chips measure the feedback through the FB pin, it will maintain the 5 V as long as no solder bridges or poor solder connections cause the wrong voltage to be measured by the chip (and the rest of the circuit is set up properly). You can omit U3, C9, and C10 to remove the overvoltage detection without impacting the rest of the circuit.

## Undervoltage Detection (U1)

U1 is a TPS3840 chip which monitors the voltage on the batteries via the VDD pin. When it detects the voltage has gone below a specific threshold, the /RESET pin is pulled low. This output is open-drain, so it does not affect the PSU_EN net while not in an error state.

The specific part I chose was the TPS3840DL35. The DL indicates the /RESET is an active-low open-drain output. (PL would indicate active-low push-pull output, PH would indicate active-high push-pull, both of which aren’t suitable for my specific application). The threshold voltage is determined by the last two numbers, which for my selection is 35 for 3.5 V. I chose this threshold based on the guidelines from <a href="https://data.energizer.com/pdfs/nickelmetalhydride_appman.pdf">this application note from Energizer.</a> This documentation recommends using a voltage cutoff of ~75% of nominal voltage for a pack of NiMH AA batteries (what I will most commonly be using in my personal console). Nominal voltage of a NiMH AA battery is 1.2 V, so for four of them in series, the 75% level is 3.6 V. So the 3.5 V cutoff is close enough, and as a bonus, it's a part used on the CPU board already.

The VDD pin of U1 isn’t directly powered by the battery voltage. C1 and R7 on the battery voltage filter out any fast power supply transients. I found that during the start-up sequence, when the IPS screen first turns on, it can draw a lot of current from the batteries causing the supply voltage to dip about a volt max (this is normal, and the PTC on the CPU board does not drop the supply more than a few tens of millivolts). Also, the current draw of the TPS3840 and latching circuit is at worst a few microamps, so the voltage drop across R7 is negligible.

The CT pin on this chip introduces a delayed start function, adding somewhat of a power switch debouncing effect. Adding a 100 nF capacitor to this pin will cause the /RESET output to be held low for approximately 62 milliseconds, which will delay the startup of the 5 V supply. This allows VCC_SW to stabilize after flipping the switch on, and allows C1 to be charged up sufficiently to begin proper undervoltage detection.

You might be asking - why am I including external undervoltage detection on this board? Can't you just put a voltage divider on the enable pin of U2?

## Latching Circuit

The original design of the PWR board had a funny problem, and didn't include the undervoltage lockout chip or latching circuitry. When the buck-boost enable pin was pulled low to disable the output once the batteries discharged enough, everything would turn off and thus remove the load from the batteries. When the current draw out of the batteries suddenly dropped to almost nothing, the battery voltage would rise back up, as expected. Unfortunately, this voltage would soon re-enable the buck-boost chip, starting up the 5 V supply. But... that would increase the load on the batteries, the voltage would drop below the enable pin threshold, and the system would shut off again. And that cycle would repeat. A bootloop! Not the graceful death the original Game Boy experienced when the batteries ran out of juice.

So in order to fix this, I introduced the undervoltage detection chip along with a latching circuit, so that as soon as the batteries died the *first* time, the system would keep itself shut off until the power switch was cycled. I found this strategy in <a href="https://www.ti.com/lit/an/snva836a/snva836a.pdf">this very helpful application note from Texas Instruments</a>. (You know, Texas Instruments should have sponsored this project, because I sure do use a lot of their parts)

The latching circuit consists of Q1 through Q4 and R1 through R4. You can read the application note for the full series of events, but basically turning on Q2 with a sufficient gate-source voltage sets up the latch. The next time the gate of Q2 (the PSU_EN net) is pulled to GND by the /RESET pin, Q4 is turned on to conduct and the /MR pin (master reset) is also pulled low. On the TPS3840, whenever /MR is low, /RESET will also automatically be pulled low no matter if VDD is above or below the undervoltage trip point. So even if the voltage on the VDD pin rises back up above the trip limit, /RESET will keep Q4 conducting, which keeps /MR low as well. So the only way to reset the whole thing is to turn the power off and reset the latch.

I found the latching circuit supply on R1 and Q1 needed to have the same heavy filter (from R7 and C1) that the TPS3840 does, otherwise the power switch bouncing would prematurely latch the enable line off all the time. The values for C1, R7, C11, R5, R12, and R13 are all intertwined and important to pick properly.

## Part Value Selection

Constraints:
- U1 activates when VDD passes 400 mV after a ~220 microsecond delay. U2 begins operation 70 microseconds after the EN pin passes 800 mV. The gate-source threshold voltage of Q2 is 2.1 V (at 250 uA through the drain).
- C1/R7 must be chosen such that the start-up power draw does not cause the detected battery voltage to dip below 3.5 V. 
  - A time constant of 1 ms was chosen. 
  - R7 was chosen to be 100 ohms to allow for sufficient current for U1 and the latching circuit.
- C11/R5 must be chosen such that the time constant does not allow for U2 to be enabled before U1 can begin operation. Doing so would set up the latching circuit early as PSU_EN is applied to the base of Q2. After this, as soon as U1 activates, /RESET would pull low and the latching circuit would be prematurely tripped.
  - A time constant of 10 ms was chosen.
  - R5 was chosen to be 10k to reduce the voltage drop on PSU_EN caused by a voltage divider with R12 + R13, which are 300k total.
- The voltage on the base of Q2 must reach the gate-source threshold voltage *before* U2 is enabled. If not, at low battery voltages, the latch will never be set up during start-up. Instead of disabling the converter the first time the undervoltage point is tripped, it will instead rapidly bootloop since the latch does not hold it off.
  - The gate-source threshold voltage of the 2N7002 is 2.1 V (this allows 250 uA through the drain; the latch only requires ~6 uA worst case). A divider ratio of 1:3 was chosen, so that when the enable pin of U2 passes the 800 mV threshold, the gate-source voltage on Q2 will be 2.4 V, ensuring the latch is set up when the converter begins operation.

### Start-up Sequence

1) Power switch is turned on, and VCC_SW is (roughly) equal to VCC.
2) C1 begins to charge through R7, and C11 begins to charge through R5. The time constant of C1 and R7 is crucially less than C11 and R5.
3) The 400 mV threshold of U1 is passed, and ~220 microseconds later /RESET (pin 1) is pulled low. The voltage across C11 is still low at this point, but it is shorted to GND.
4) C2 causes a 62 ms delay (after VDD passes 3.5 V) to allow for VCC_SW and C1 to stabilize. After this delay, /RESET is released, and C11 begins charging again. 
5) The gate-source voltage of Q2 passes VGS(th) of 2.1 V, and the latching circuitry is set up. The next time U1_VDD drops below 3.5 V, the latching circuitry will pull /MR to GND and latch PSU_EN off until the power switch is cycled.
6) The 800 mV threshold of the EN pin on U1 is passed, and after a 70 microsecond delay, the buck-boost is finally enabled. VCC_SW will experience a brief dip due to the large current draw, which is filtered on U1_VDD through R7 and C1 to prevent premature latching.

## Bill of Materials

Here, I have provided links to components I used personally (or suitable replacements). This BOM is also included in Excel format in the root folder.

| Reference Designators          | Qty | Value/Part Number              | Package    | Description          | Comment                                                                                | Source                                                                                                                                                                                                                                                                                   |
| ------------------------------ | --- | ------------------------------ | ---------- | -------------------- | -------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| C1, C5, C6                     | 3   | 10uF                           | 0603       | Capacitor (MLCC)     | Should be X5R (or better), at least 16V                                                | [https://www.mouser.com/ProductDetail/Murata-Electronics/GRM188R61E106KA73J?qs=5aG0NVq1C4xEV8YyiSS7mg%3D%3D&countrycode=US&currencycode=USD](https://www.mouser.com/ProductDetail/Murata-Electronics/GRM188R61E106KA73J?qs=5aG0NVq1C4xEV8YyiSS7mg%3D%3D&countrycode=US&currencycode=USD) |
| C2, C8, C9, C11                | 4   | 100nF                          | 0603       | Capacitor (MLCC)     |                                                                                        | [https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10B104KO8NNWC/3887597](https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10B104KO8NNWC/3887597)                                                                                             |
| C3, C4                         | 2   | 22uF                           | 1206       | Capacitor (MLCC)     | Should be X5R (or better), at least 16V                                                | [https://www.mouser.com/ProductDetail/Samsung-Electro-Mechanics/CL31A226KAHNNNE?qs=X6jEic%2FHinCdwsjGJII51w%3D%3D](https://www.mouser.com/ProductDetail/Samsung-Electro-Mechanics/CL31A226KAHNNNE?qs=X6jEic%2FHinCdwsjGJII51w%3D%3D)                                                     |
| C7                             | 1   | 47uF                           | 1206       | Capacitor (MLCC)     | Should be X5R (or better), at least 16V (maybe 10V is ok)                              | [https://www.mouser.com/ProductDetail/Taiyo-Yuden/EMK316BBJ476ML-T?qs=Zy5V7Kj3rCVVMQaoWTlMmg%3D%3D](https://www.mouser.com/ProductDetail/Taiyo-Yuden/EMK316BBJ476ML-T?qs=Zy5V7Kj3rCVVMQaoWTlMmg%3D%3D)                                                                                   |
| C10                            | 1   | 1uF                            | 0603       | Capacitor (MLCC)     |                                                                                        | [https://www.digikey.com/en/products/detail/kemet/C0603C105K4RAC7867/2199788](https://www.digikey.com/en/products/detail/kemet/C0603C105K4RAC7867/2199788)                                                                                                                               |
| F1                             | 1   | 1A                             | 0603       | Fuse                 |                                                                                        | [https://www.digikey.com/en/products/detail/vishay-beyschlag-draloric-bc-components/MFU0603FF01000P100/1206475](https://www.digikey.com/en/products/detail/vishay-beyschlag-draloric-bc-components/MFU0603FF01000P100/1206475)                                                           |
| L1                             | 1   | 1.5uH                          | 1212       | Inductor             | Saturation current should be at least 2A                                               | [https://www.mouser.com/ProductDetail/70-IHLP1212BZER1R5M1](https://www.mouser.com/ProductDetail/70-IHLP1212BZER1R5M1)                                                                                                                                                                   |
| Q1                             | 1   | MMBT3906                       | SOT23      | PNP BJT              |                                                                                        | [https://www.digikey.com/en/products/detail/micro-commercial-co/MMBT3906-TP/819631](https://www.digikey.com/en/products/detail/micro-commercial-co/MMBT3906-TP/819631)                                                                                                                   |
| Q2, Q4                         | 2   | 2N7002                         | SOT23      | N-channel MOSFET     |                                                                                        | [https://www.digikey.com/en/products/detail/nexperia-usa-inc/2N7002NXBKR/10416553](https://www.digikey.com/en/products/detail/nexperia-usa-inc/2N7002NXBKR/10416553)                                                                                                                     |
| Q3                             | 1   | MMBT3904                       | SOT23      | NPN BJT              |                                                                                        | [https://www.digikey.com/en/products/detail/micro-commercial-co/MMBT3904-TP/717280](https://www.digikey.com/en/products/detail/micro-commercial-co/MMBT3904-TP/717280)                                                                                                                   |
| R1, R4, R9, R10, R11, R12, R13 | 7   | 100k                           | 0603       | Resistor             | R9 should have at least 1% tolerance                                                   | [https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100KL/726889](https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100KL/726889)                                                                                                                                     |
| R2, R3                         | 2   | 10k                            | 0603       | Resistor             |                                                                                        | [https://www.digikey.com/en/products/detail/yageo/RC0603FR-0710KL/726880](https://www.digikey.com/en/products/detail/yageo/RC0603FR-0710KL/726880)                                                                                                                                       |
| R5                             | 1   | 18k                            | 0603       | Resistor             |                                                                                        | [https://www.digikey.com/en/products/detail/yageo/RC0603FR-1018KL/13694163](https://www.digikey.com/en/products/detail/yageo/RC0603FR-1018KL/13694163)                                                                                                                                   |
| R7                             | 1   | 100                            | 0603       | Resistor             |                                                                                        | [https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100RL/726888](https://www.digikey.com/en/products/detail/yageo/RC0603FR-07100RL/726888)                                                                                                                                     |
| R8                             | 1   | 523k                           | 0603       | Resistor             | At least 1% tolerance. Not needed if using TPS630701                                   | [https://www.digikey.com/en/products/detail/yageo/RC0603FR-07523KL/727292](https://www.digikey.com/en/products/detail/yageo/RC0603FR-07523KL/727292)                                                                                                                                     |
| U1                             | 1   | TPS3840DL35                    | SOT23-5    | Supervisory IC       |                                                                                        | [https://www.mouser.com/ProductDetail/Texas-Instruments/TPS3840DL35DBVR?qs=7MVldsJ5UawbjRj7dP73rA%3D%3D](https://www.mouser.com/ProductDetail/Texas-Instruments/TPS3840DL35DBVR?qs=7MVldsJ5UawbjRj7dP73rA%3D%3D)                                                                         |
| U2                             | 1   | TPS63070, TPS630701, TPS630702 | 15-VQFN-HR | Buck-boost converter | Might be difficult to find. Check octopart.com. TPS630702 preferred, but all will work | [https://octopart.com/search?q=tps63070&currency=USD&specs=0](https://octopart.com/search?q=tps63070&currency=USD&specs=0)                                                                                                                                                               |
| U3                             | 1   | TPS3702CX50DDCT                | SOT23-6    | Supervisory IC       | Optional                                                                               | [https://www.digikey.com/en/products/detail/texas-instruments/TPS3702CX50DDCT/5250202](https://www.digikey.com/en/products/detail/texas-instruments/TPS3702CX50DDCT/5250202)                                                                                                             |

## Resources
-	<a href="https://www.ti.com/lit/ds/symlink/tps63070.pdf?ts=1647052355945">TPS63070 datasheet</a>
-	<a href="https://www.ti.com/lit/ds/symlink/tps3840.pdf?ts=1656386735143">TPS3840 datasheet</a>
-	<a href="https://www.ti.com/lit/ds/symlink/tps3702.pdf?ts=1656335717520">TPS3702 datasheet</a>
-	<a href="https://www.ti.com/lit/an/snva836a/snva836a.pdf">Latching a Voltage Supervisor Application Note</a>
-	<a href="https://data.energizer.com/pdfs/nickelmetalhydride_appman.pdf">Nickel Metal Hydride (NiMH) Handbook and Application Manual</a>

## License
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.
