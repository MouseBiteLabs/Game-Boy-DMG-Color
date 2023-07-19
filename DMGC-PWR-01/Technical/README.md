# Technical Design Document

This write-up serves as a technical explainer for the DMGC-PWR-01. This board is the powerhouse of the cell.

## Schematic and CPU Board Interfacing

There are five wires that connect to the CPU board power supply circuitry. Pin 1 is the GND reference and pin 2 is the 5 V output from the PWR board. Pin 4, VCC, is the input voltage, which is always powered from the CPU board. SW is the output of half the power switch on the CPU board - connected to VCC when on, floating when off (ultimately tied to GND through R16 on the PWR board). On the CPU board, pin 3 is connected to the DC jack output, but on this board I connect this to VCC as well, so that either batteries or the DC jack will power this board. A different revision might utilize the DC jack for something else, such as charging a LiPo battery, which is why I left these pins separate.

![image](https://github.com/MouseBiteLabs/Game-Boy-DMG-Color/assets/97127539/7b807e4d-9cdc-43d2-9089-be53a827e335)

The battery voltage, VCC, is applied to the buck-boost input voltage pin, without routing through the power switch on the CPU. Instead, the power switch controls the buck-boost converter’s enable pin through a load switch circuit.

## Buck-Boost Converter (U2)

U2 can be TPS63070, TPS630701, or TPS630702. TPS630701 is a fixed 5 V buck-boost, while the other two have adjustable output via a voltage divider. The only difference between TPS63070 and TPS630702 is that the latter has an output discharge function - when the output is disabled, a low impedance (~200 Ω) is connected to the rail internally to quickly discharge the output capacitors. If you have a choice, I would recommend using the TPS630702 over the other two, and the TPS630701 over the TPS63070 just because it's a bit more convenient (and foolproof) to use the fixed output version of the chip. But any three of them will work perfectly fine.

The bottom third of the schematic is the entire buck-boost stage. I followed the TPS63070 datasheet for choosing values of the input and output capacitance, the inductor, and the feedback resistors. R8 and R9 set up a voltage divider for setting the output of the adjustable TPS630702 or TPS63070 – if the TPS630701 is used instead, which is the 5 V fixed output version, then R8 should be short circuited and R9 can be removed. **If you leave R8 and R9 at the values they are with the fixed 5 V chip, the output will shoot up to ~11V. I strongly recommend testing this power supply board separately from the rest of the system to ensure the 5 V output is correct and steady, without frying anything else downstream.**

The buck-boost chip is activated when the EN pin is higher than 800 mV (there is an internal ~70 microsecond delay before activation after this voltage is reached). This pin is controlled by the PSU_EN net, which is influenced by two chips – U3 (overvoltage protection) and U1 (undervoltage detection). If no errors are detected in the power supply, then PSU_EN will pull up to VCC_LATCH and activate U2. If either an overvoltage on the 5 V line or an undervoltage on the battery supply is detected, the PSU_EN net is pulled to GND and latched off until the power switch is cycled. R5, R12, and R13 set up voltage dividers that ensure if the EN pin passes 800 mV, the gate-source voltage on Q2 will be at least 2.4 V, meaning the latching circuit will be set up before the 5 V supply is generated (VGSth of Q2 is ~2.1 V, max). R13 also ensures the EN pin is pulled to GND when the power switch is turned off. Detailed operation on the PSU_EN net can be found below. 

F1 is a 1 A fuse on the 5 V output, which in hindsight is probably overkill, since the CPU board has protections that will likely always trip first (the 1 A PTC specifically). When testing the PWR board, I shorted the 5 V supply to GND to see if the fuse would pop, and the PTC opened up first every time I tried. But, I have plenty of 1 A fuses lying around, so there’s little reason not to include it just in case, since the TPS63070 chips can output up to 3.6 A. A fuse could prevent a feed-the-fault type of error, however rare that scenario likely is.

## Overvoltage Protection (U3)

Onto the protection circuitry - let's get the easy one out of the way first. U3 is a TPS3702 IC. This chip monitors the 5 V output on the SENSE pin. If it’s above a certain value, the output on the OV pin will be pulled low. Otherwise, OV is left floating (it's an open-drain output), so it doesn’t affect the output of the PSU_EN net during normal operation.

The specific part I have chosen is the TPS3702CX50. With the SET pin tied to GND, this sets the overvoltage threshold to 5.45 V. If the supply ever passes this point, then the overvoltage pin will pull PSU_EN low, and the latching circuit will keep it off until the power switch is cycled.

The overvoltage protection is likely overkill as well, as long as the buck-boost circuit is set up correctly and soldered properly. Since the adjustable TPS63070 chips measure the feedback through the FB pin, it will maintain the 5 V as long as no solder bridges or poor solder connections cause the wrong voltage to be measured by the chip (assuming the rest of the circuit is set up properly). You can omit U3, C9, and C10 to remove the overvoltage detection without impacting the operation of rest of the circuit.

## Undervoltage Detection (U1)

U1 is a TPS3840 chip which monitors the voltage on the batteries via the VDD pin. When it detects the voltage has gone below a specific threshold, the /RESET pin is pulled low. This output is open-drain, so it does not affect the PSU_EN net while not in an error state.

The specific part I chose was the TPS3840DL35. The DL indicates the /RESET is an active-low open-drain output. (PL would indicate active-low push-pull output, PH would indicate active-high push-pull, both of which aren’t suitable for my specific application). The threshold voltage is determined by the last two numbers, which for my selection is 35 for 3.5 V. I chose this threshold based on the guidelines from <a href="https://data.energizer.com/pdfs/nickelmetalhydride_appman.pdf">this application note from Energizer.</a> This documentation recommends using a voltage cutoff of ~75% of nominal voltage for a pack of NiMH AA batteries (what I will most commonly be using in my personal console). Nominal voltage of a NiMH AA battery is 1.2 V, so for four of them in series, the 75% level is 3.6 V. So the 3.5 V cutoff is close enough, and as a bonus, it's a part used on the CPU board already.

The VDD pin of U1 isn’t directly powered by the battery voltage. C1 and R7 on the battery voltage filter out any fast power supply transients. I found that during the start-up sequence, the loads on the 5 V supply will draw a considerable amount of current from the batteries, causing their voltage to dip about a volt max (this is normal, and the PTC on the CPU board does not drop the supply more than a few tens of millivolts). Furthermore, loud audio can introduce kHz range ripple on the battery voltage when their charge is low, so the low pass filter will smooth that out. It's not important for undervoltage lockout to occur immediately after the 3.5 V threhold is passed during a transient event, so this doesn't negatively impact performance or protection while the console is being used. Also, the current draw of the TPS3840 is less than a microamp, so the voltage drop across R7 is negligible and it also won't have any perceptible impact to battery life despite always being connected to the batteries.

The CT pin on this chip introduces a delayed start function. Adding a 1 uF capacitor to this pin will cause the /RESET output to be held low for approximately 620 milliseconds no matter what the supply voltage is. This is really only useful in the event you put the batteries in while the power switch is already on, because the delay only applies the first time power is applied to the chip. The wait period lets all the input capacitors charge up sufficiently and allows enough time for the input undervoltage latch to be set up before trying to generate the 5 V supply.

You might be asking - why am I including external input undervoltage detection on this board? Can't you just put a voltage divider on the enable pin of U2? Well...

## Latching Circuit

The original design of the PWR board had a funny problem, and didn't include the undervoltage lockout chip or latching circuitry. When the buck-boost enable pin was pulled low to disable the output once the batteries discharged enough, everything would turn off and thus remove the load from the batteries. When the current draw out of the batteries suddenly dropped to almost nothing, the battery voltage would rise back up, as expected. Unfortunately, this voltage would soon re-enable the buck-boost chip, starting up the 5 V supply. But... that would increase the load on the batteries, the voltage would drop below the enable pin threshold, and the system would shut off again. And that cycle would repeat. A bootloop! Not the graceful death the original Game Boy experienced when the batteries ran out of juice.

So in order to fix this, I introduced the undervoltage detection chip along with a latching circuit, so that as soon as the batteries died the *first* time, the system would keep itself shut off until the power switch was cycled. I found this strategy in <a href="https://www.ti.com/lit/an/snva836a/snva836a.pdf">this very helpful application note from Texas Instruments</a>. (You know, Texas Instruments should have sponsored this project, because I sure do use a lot of their parts)

The latching circuit consists of Q1 through Q4 and R1 through R4. You can read the application note for the full series of events, but basically turning on Q2 with a sufficient gate-source voltage sets up the latch. The next time the gate of Q2 (the PSU_EN net) is pulled to GND by the /RESET pin, Q4 is turned on to conduct and the /MR pin (master reset) is also pulled low. On the TPS3840, whenever /MR is low, /RESET will also automatically be pulled low no matter if VCC is above or below the undervoltage trip point. So even if the voltage rises back up above the trip limit, /RESET will keep Q4 conducting, which keeps /MR low as well. So the only way to reset the whole thing is to turn the power switch off and reset the latch.

## Load Switch

VCC is applied to the latching circuit through a load switch circuit, rather than the power switch directly. The power switch, which is connected to the SW net, controls the gate-source voltage of Q5, an N-channel FET. R15 and C11 set up an RC delay for switch debouncing, and R16 is a pull-down resistor for when the power switch is turned off. R14 is a pull-up resistor that keeps Q6, a P-channel FET, off whenever Q5 is off. When the power switch is turned on, Q5 conducts and pulls the gate of Q6 to GND. This allows the battery voltage VCC to turn on the latching circuit. Furthermore, if PSU_EN is not being pulled to GND by the supervisory ICs (if the battery voltage is higher than 3.5 V), then the enable pin of the buck-boost will pass the 800 mV threshold needed to turn on the 5 V supply (after a built-in 70 microsecond delay).

The benefit to using a load switch instead of the power switch directly is the contact resistance of the 30+ year old power switches is no longer a factor in operation. One common issue in old Game Boys is a voltage drop across a dirty power switch, because the entire system current flows through the switch. Sometimes, if the switch is particularly oxidized or dirty, the entire Game Boy could fail to turn on. Instead of having to clean out a power switch, a non-trivial task (especially for a DMG), a dirty power switch will still be able to properly control Q5, as long as contact resistance isn't higher than like, 100 kΩ. (And in that case, increase R16 to like 1 MΩ, and you might be ok!)

## Resources
-	<a href="https://www.ti.com/lit/ds/symlink/tps63070.pdf?ts=1647052355945">TPS63070 datasheet</a>
-	<a href="https://www.ti.com/lit/ds/symlink/tps3840.pdf?ts=1656386735143">TPS3840 datasheet</a>
-	<a href="https://www.ti.com/lit/ds/symlink/tps3702.pdf?ts=1656335717520">TPS3702 datasheet</a>
-	<a href="https://www.ti.com/lit/an/snva836a/snva836a.pdf">Latching a Voltage Supervisor Application Note</a>
-	<a href="https://data.energizer.com/pdfs/nickelmetalhydride_appman.pdf">Nickel Metal Hydride (NiMH) Handbook and Application Manual</a>

## License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>. You are able to copy and redistribute the material in any medium or format, as well as remix, transform, or build upon the material for any purpose (even commercial) - but you **must** give appropriate credit, provide a link to the license, and indicate if any changes were made.

©MouseBiteLabs 2022
