# Troubleshooting and Testing

Here is where I will collect some troubleshooting advice. I may expand the sections as time goes on for specific board troubleshooting advice. For now, this should cover most issues.

## Suggested Testing Before Final Assembly

This is the order of testing I usually go in when assembling a DMGC. I recommend testing boards as you go *before* you completely connect everything together and put into the DMG shell. This way you can easily catch errors early on, making troubleshooting easier, and lowering the chance for catastrophic mistakes. I'm not going to give detailed troubleshooting instructions here, just some general tips, mostly for catching power issues. This should cover the most common issues.

*If you're taking on this project in the first place, I expect you'll be able to take troubleshooting further than what I detail here ;D*

### 1) Testing the output of the power switch

If you place the CPU board (by itself) in the DMG shell and insert batteries, or use the DC jack, you can check the voltage with a multimeter on the VCC and SW holes that go to the PWR board. VCC should *always* read the battery or DC jack voltage, and SW should read zero when the power switch is off, and the same voltage as VCC when the power switch is on.

If VCC does not read any voltage (and you're using batteries), measure the voltage right at the battery terminals and check if it's zero there as well - sometimes using NiMH batteries in DMG shells causes poor contact with the battery tabs, because some NiMH batteries have shallower positive terminals than alkalines.

Also, check the orientation of Q1. If it's backwards, you will be shorting the battery terminals together. In this case, you would read voltage across the battery terminals, but not on VCC itself.

If SW doesn't read a voltage with the switch on, your power switch is potentially damaged or too dirty/oxidized.

### 2) Testing DMGC-PWR-01

*This step assumes you have the correct voltages on VCC and SW from step 1.*

This step will test the 5 V output of the PWR board. Connect the PWR board to the CPU board with the requisite five wires (they should measure ~2.25"), but remove the 5 V wire from the CPU board side. This way, you can apply the input voltage (battery or DC jack) to the PWR board without powering the rest of the CPU board.
Place the CPU board in the back DMG shell and insert batteries, or use the DC jack input. Turn the power switch on, and check with a multimeter that the 5 V wire indeed reads 5 V.

If you get something else, check these things:
- Check for good solder joints on all parts.
- Check the orientation of Q6. Pins 1, 2, 5, and 6 should all have continuity, and should not have continuity with pins 3 and 4. It's a small part with hard to read markings, so it might be backwards.
- Are you using TPS630701? If you are, make sure you have shorted R8 with a solder bridge, and didn't actually include a resistor there. You also don't need R9 in the circuit, but it won't hurt to include it. If you don't short R8 and you use the TPS630701, your output will shoot past 5 V.
- Check the resistance across R9, or the pads of R9. If it's short circuited, that means you likely have a solder bridge from U2's feedback pin to GND (which would cause the output to shoot higher than 5 V). Also check for continuity across R13. If it's shorted, that means you have shorted the enable pin to GND, which will always keep U2 off.
	- Generally, U2 is usually at the heart of most problems, at least as far as I've seen. It's a difficult chip to solder properly. If you detect any shorts, reflow U2 with flux, or consider removing it completely and resoldering it.
- If you don't have a short across R8 or R9 and you're using the TPS63070 or TPS630702, check the resistance values of these resistors. If they are wrong, you can get the incorrect voltage on the 5V output.
- Check the orientation of U3. Also, if it's easy to do, try removing U3 completely and checking the output again with the power switch on. If the output now reads *above* 5 V, then double check R8 and R9 mentioned earlier.

### 3) Testing DMGC-CPU-01

*This step assumes you have a stable 5 V coming out of the PWR board.*

First, without the batteries or DC jack inserted, do a resistance check on the 5 V pad on the CPU board to GND. When the power switch is off, it should read 1 kΩ. When the power switch is on, you should get a higher resistance, tens or hundreds of kΩ. If you get a very low resistance in either position, you have a short circuit somewhere on the CPU board, and the PWR board will shut off. If you don't have that issue, connect the 5 V wire to the CPU board.

**NOTE: Trim all five wire stubs poking out of the CPU board holes so they are flush against the CPU board after soldering them in. If the stubs stick out too far, they can touch the IPS board's navigation dial metal shielding and short circuit.**

Turn power on, and do a voltage check on the CPU board's 5 V pad and 3.3 V pad to verify you're getting 5 V and 3.3 V, respectively. If you don't, this could point to a solder bridge somewhere on the CPU board, or a dead part. (Hopefully it's not your CPU!)

### 4) Testing operation of the IPS kit

*This step assumes you have a stable 5 V and 3.3 V supply on the CPU board.*

Before testing anything, if you have a stock Game Boy Color, consider testing the kit in that before using it here. These kits can come defective.

Did you know you can connect the Q5 IPS kit to the CPU board directly, without the DMGC-IPS-01? Well, you can. Plug it into the FFC connector, J1, and make sure no metallic surface is shorting between the kit's board or the back of the display and the CPU board. Turn power on, and you should get the GBC splash screen.

You can test a game at this point too. If you put a game in the cart slot, it should start to run normally. If you get a garbled logo, or it otherwise doesn't start up properly, then you might have a dirty cart slot or poor connection from the cart connector to the CPU.

If the screen doesn't turn on at all - no backlight or anything - check to make sure your 5 V output is still at 5 V. If it's not, then turn off power, remove the screen kit, and test again to see if the 5 V output comes back. Again, if you have a working GBC to test with, you should check to see if the kit does the same thing there.

If you get a garbled image, or no image at all (but the screen still lights up), check these things:

- Make sure the bales of the FFC connectors are in all the way, and the cable is seated all the way in. Try to clean out any flux that might be hiding inside the connector.
- Check for solder bridges on all the pins of the CPU, FFC connector, and RAM. *Note that some adjacent pins are supposed to be connected together on the FFC connector - check the schematic.*
- Check to make sure all legs of the CPU, FFC, and RAM have a good connection to the board. Missing any one of these pins could cause the screen to not work.
- Once again, try the IPS kit inside an actual Game Boy Color, if you have one available to test.

If you still have problems with the IPS kit not working properly, you can continue to step 5 to check the audio output. This might point you to a problem elsewhere on the CPU board.

### 5) Testing DMGC-HDP-01 and audio output

*This step assumes you have a stable 5 V and 3.3 V supply on the CPU board.*

As mentioned in the previous step, you can check this without a screen kit installed. **If you do not include the screen kit, the audio will likely sound a bit distorted. This is normal.**

Connect the headphone board to the CPU board with the four requisite wires (they should measure ~2.6"). Then, you can plug in headphones to the headphone jack to see if the CPU is operating normally. Make sure the volume dial isn't turned all the way down. If you're unsure which way turns the volume up, just put it somewhere in the middle.

When you turn the power on, you should hear the GBC start-up chime. If you don't:

- Do a resistance check between the HP and GND pins on the audio board (or on the connections on the CPU board). When headphones are removed, you should read a short circuit. When headphones are plugged in, you shouldn't - you can read anywhere from 1 kΩ to something higher (depending on the type of headphone board you're using). If this check fails, you likely have a dirty or damaged headphone jack (especially if it's a salvaged DMG jack).
- Check the resistances of the volume dial pins.
	- Check the resistance between pins VR1-S01 and RIN, and then again for VR1-S02 and LIN. You should read a resistance between 0 and 10 kΩ depending on where the volume dial is. Reading 0 ohms means maximum volume, 10 kΩ is minimum volume.
	- Check the resistance from VR1-S01 to GND, and VR1-S02 to GND. This should be 10 kΩ.
	- Getting any resistance higher than 10 kΩ means you have a damaged or dirty volume dial.
- Check your soldering around U3 on the CPU board, and make sure all the correct parts are included and placed in the right positions.
- Check to make sure there are no solder bridges on the CPU or anywhere else on the CPU board, and make sure there are solid connections on each leg of the CPU to the board. Some crucial pins may be lifted.
- If you have the parts, you can check the audio out of the pro-sound output. If you get sound out of the pro-sound outputs, but not the regular headphone outputs, then you have an issue somewhere between the CPU and the headphone board. Follow the schematic to troubleshoot.
- You can solder a DMG speaker, in series with a 100 uF capacitor, to the back of the DMG board (pads SPK+ and SPK-). Make sure HP is connected to GND. You should get audio out of the speaker this way.

If you can't get an image on the IPS screen, and you also still cannot get audio output from the headphone jack, then you likely have some kind of issue with the CPU - not necessarily a dead CPU, but something that affects it, like a solder bridge, lifted pin, wrong part value, or a damaged part.

### 6) Testing DMGC-IPS-01

*This step assumes the IPS kit works on the CPU board.*

At this point, you have the majority of systems tested on the build. The IPS board doesn't have much else to test. Note that when testing the IPS board outside of the shell, you *need to make sure you aren't short circuiting anything between the IPS and CPU boards.* So if you're going to place the board on top of the CPU board for testing, make sure you put a piece of paper or non-conductive material between the boards. Or, just keep the IPS board off of the CPU board.

Make sure the power LED turns on when you turn the power on (did you put it in backwards?) and make sure you get a good image on the screen kit. If the image appears garbled, or doesn't appear at all, do the checks I mentioned in the CPU board troubleshooting sections:

- Check for any solder bridges on the two FFC connectors. When checking for shorts, some adjacent pins on the connectors are supposed to be connected - check the schematic. 
- Check for any lifted pins or poor solder joints on the FFC connector pins. The connectors themselves sometimes have the pins lifted a bit when you place them on the board, so you might have to bend them down a bit before soldering. You can even check for continuity from the pin to the board using a meter - it's small and tight, but can be helpful.
- Make sure the cables are inserted in the connectors all the way and the bales are pressed in all the way. Clean out any leftover flux that might be inside the connectors when you soldered them on.

At this point you should also have the speaker installed. If after turning the system on, you don't get any sound, check the HP and GND pins on the headphone board or CPU board - the HP pin should be shorted to GND when headphones are not inserted. If the HP pin is not shorted to GND, then the speaker won't output any sound. You have a dirty or damaged headphone jack - clean or replace. You can manually short HP to GND with a wire to check the audio output of the speaker if you'd like.
