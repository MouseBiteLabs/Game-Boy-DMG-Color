# Game Boy DMG Color
**TO-DO:**
- Include pictures
- Update power draw measurements
- Upload gerber files
- Record audio output
- Generate audio spectrum plots
- Upload bracket .stl file
- Add copyright

[Picture of DMGC]

This is my design for an original Game Boy (model name DMG) with native Game Boy Color support, and a handful of improved features! This is an original creation - newly designed PCBs, with only some necessary components harvested from an original Game Boy and Game Boy Color (no hardware emulation – this project uses the original CPU). Here are the project goals:
-	An original Game Boy aesthetic, using the original Game Boy shell and external parts (link port, volume wheel, power switch, etc.), but with the capability of playing Game Boy and Game Boy Color games.
-	A nice, large IPS screen – the GBC Q5 XL IPS Backlight with OSD kit – with brightness and color palette control via the "navigation switch" housed where the contrast wheel used to be. (I will refer to the PCB attached to the Q5 screen as the “Q5 board”)
-	A modernized, efficient switch mode power supply that, with 4x NiMH AA batteries, can yield more than 17 hours of gameplay at normal settings (AKA, the way I normally play it - maximum brightness and headphones). 
-	Louder, warmer sound through a modern audio amplifier.
-	The option for backlit buttons, with multiple color modes and settings.
-	No externally viewable case modifications, outside of trimming the DMG power switch cover for Game Boy Color game compatibility.

In order to maintain the feel and weight of the original DMG model, this console uses 4x AAs instead of a rechargeable battery, as many modern Game Boy modders are wont to use (it also retains the option to use an original DMG AC adapter). I find it easier to have eight NiMH batteries - four for use, four for recharging - instead of being tethered to a USB cable. Plus, I have a bunch of eneloops for which I need to justify the purchase.

The code name for this project is DMGC. This console uses four PCBs, just as the original DMG model did - a CPU board (DMGC-CPU-01), display board (DMGC-IPS-01), power board (DMGC-PWR-01), and headphone jack board (DMGC-HDP-01). The power board could be absorbed into the main CPU board, however I opted to keep it separate. This stays more in line with the goal of keeping the project close to the original design, as well as provides the opportunity of designing different power supplies with different features (i.e. LiPo charging) or designs that use different parts depending on availability. In fact, I have designed a DMGC-PWR-02 for that very reason.

Next to an original DMG… one can really see the improvements!

[picture of DMGC next to DMG]

## Disclaimer

**Before I go any further, please read this important disclaimer.**

I made this project first and foremost **for my own consumption**. All of the features I have included are things I personally wanted. I have tried my hardest to make the project modular, if others would like to improve or change things easily, and I have also tried very hard to make the design somewhat less prone to potential errors during assembly (such as spacing out power pins on the FFC connectors). But in the end, every decision I made was for what I wanted the final product to be, with my skill level in mind.

This project is fully open-sourced under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International license. Schematics, gerbers, and the BOM are provided in the various folders. But if you choose to build this project yourself, be warned - this is a considerably advanced, and expensive build. **You are 100% liable for any damage done to your property or yourself. I am not responsible for any damage or loss of property incurred while attempting this project, or after completion of the project.** While I am confident in this design, I cannot claim full compatibility with every system configuration. And there may be latent issues that have yet to crop up. I will update this page if I encounter any, and if you see anything I may have missed, or some dubious design choice, feel free to ask questions or comment as such. Corrections are welcome. However, I **will not** obligate myself to providing tech support.

**Do not attempt this project if you are uncomfortable or inexperienced with detailed electronics troubleshooting, or are not proficient in soldering.**

[pictures of the four blank circuit boards]

## Bill of Materials

This is the high-level BOM for my specific build. Each folder for each board will contain detailed BOMs near the bottom of each readme that contain all of the electronic components needed for each circuit board. Note that some parts may be out of stock at these links, but many (such as the IPS kit) can be found at alternate other retailers online. Parts that deviate from the ones listed here (like different shell designs) might necessitate different fitment modifications.

- Original Game Boy Color console
  -	U1 - CGB CPU (I used version B, I expect any revision except for E, which has a different pinout, will work)
  - U2 - LH52256CVTXIZ
  - X1 – 8.388 MHz crystal oscillator
  - EM10
- Original Game Boy DMG console
  -	VR1 – Volume dial
  -	SW1 – Power switch
  -	P1 – Cartridge connector
  -	EXT port
  -	DC jack
  -	Headphone board components (importantly the headphone jack)
-	<a href="https://retrogamerepairshop.com/products/game-boy-color-q5-ips-backlight-with-osd?variant=37646279213228">GBC Q5 XL IPS Backlight with OSD</a>
-	<a href="https://retrogamerepairshop.com/collections/dmg-lenses/products/funnyplaying-dmg-q5-ips-lens?variant=39626455187628">FunnyPlaying DMG Q5 IPS Lens (black)</a>
-	Custom designed 3D-printed IPS bracket
-	<a href="https://retrogamerepairshop.com/collections/game-boy-dmg-shells/products/game-boy-dmg-original-new-shells-factory-a?variant=32530346967114">Game Boy DMG Shell – Factory A (Midnight Blue)</a>
-	<a href="https://store.kitsch-bent.com/products/silicone-buttons?variant=40627510771907">Kitsch-Bent clear silicone DMG buttons</a>

## Assembly Pictures
Here are some pictures of the assembly process. Detailed images of the circuit boards are shown in their respective folders.

[picture of back half of shell, with boards, no wires]

I measured the wires going to the PWR and HDP boards after placing them in the back shell, removed all of the circuit boards from the shell, and soldered the wires in separately to avoid melting plastic.

[picture of front half of shell, empty, no lens, from behind]

As per instructions on a similar Q5 IPS kit, I very carefully cut 1 mm of plastic around the border of the viewing port, and trimmed any extra plastic to make the surface underneath the lens smooth. I used black marker to color in the edges of the newly cut plastic, so they would not be as easily visible at an angle. Then I placed the lens in, keeping my greasy fingers off of the viewing area.

[picture of front half of shell with lens and screen, from behind]

I trimmed two posts off of the shell so the Q5 screen would fit flush against it. I placed the screen, backed with the 3D printed bracket, into the front half of the shell without getting any fingerprints on the lens or screen. 

[picture of bracket]

Once the bracket was placed and flush with the shell, I put the buttons in and placed the IPS screen over top, slid the Q5 screen FFC into the connector on the PCB (making sure it fit without any added stress on any connections), and secured it all in place.

[picture of two halves, ready to be assembled, with FFC on the CPU board]

I put a game in the cartridge slot to keep the CPU board in place easier while assembling. After that, it was just a matter of connecting the FFC to both the CPU and IPS screens, tucking it under the boards ensuring no kinks or sharp bends, and screwing it together.
## Auxilliary Controls
### Q5 XL IPS Backlight with OSD
-	Select + A + B: Open the OSD menu
-	Select + A: Enter
-	Select + B: Exit
-	A: Increase
-	B: Decrease

### Navigation Switch
-	Rock up: Advance screen brightness setting
-	Rock up/Hold: Toggle on-screen battery indicator
-	Rock down: Advance screen color pallete setting
-	Rock down/Hold: Toggle on-screen pixel grid
-	Push in: Toggle button LED colors
-	Push in/Hold + D-pad Left: Decrease button LED brightness
-	Push in/Hold + D-Pad Right: Increase button LED brightness
-	Push in/Hold when turning on power switch: Skip start-up color sequence

## Power Draw Measurements
For these tests, I’m using four eneloop pro NiMH AA batteries (total of ~11800 mWh), and the audio gain is set to ~0.4 (see CPU board for more detail on this gain value).

| Test Criteria | Power Draw | Estimated Battery Life |
| ------------- | ------------- | ------------- |
| IPS max brightness, NeoPixel LEDs max brightness, speaker volume 100%, Everdrive X5	| 800 mW	| 14.8 hr |
| IPS max brightness, NeoPixel LEDs off, speaker volume 100%, Everdrive X5 | 770 mW	| 15.3 hr |
| IPS max brightness, NeoPixel LEDs off, headphones, Everdrive X5	| 680 mW	| 17.4 hr |
| IPS max brightness, NeoPixel LEDs off, headphones, original cartridge | 670 mW	| 17.6 hr |
| IPS min brightness, NeoPixel LEDs off, headphones, original cartridge	| 500 mW	| 23.6 hr |

## Audio Recordings and Spectrum
I mentioned the sound of the DMGC is "warmer" than an original GBC. I connected the headphone jack to my computer's microphone input, and used Audacity to obtain line out recordings. Then I graphed the spectrum using Audacity's "plot spectrum" analysis tool. I'm not an audiophile, but I do think it sounds nicer. Listen for yourself:

### Original GBC Audio
[file]
### DMGC Audio
[file]

### Original GBC Spectrum
[spectrum]
### DMGC Audio Spectrum
[spectrum]

## Possible Additions/Changes
Want to improve this project? Maybe try one of these things (because I probably won’t):
- The obvious addition to the build is a LiPo battery with proper battery management. In order to keep the OEM feel, the DC jack could be repurposed to charge the battery instead. With the advent of affordable rechargeable AAs, the appeal of the AC adapter is diminished, so this would be a good repurposing. However, the maximum output current of most DMG AC adapters is rated for ~200mA at ~6V, so charging would be considerably slower than, say, USB-C charging. I have seen cables that convert the DC jack to a USB-A connector, however.
- A popular option for modern Game Boy mods is to use a laminated screen. This basically seals the front lens to the screen to prevent any dust from entering between the screen and lens, and makes the image look hella nice. There aren't any off-the-shelf laminated screen kits that would work with this build, but one could potentially do a custom lamination by hand.
- Restoring the IR functionality of the GBC could also be done, as there is ample space for it on the circuit board and shell - I just do not trust myself with forming plastic to look nice, and it wasn't an important part of the build for me.
- Finding aftermarket equivalents for all the different required DMG parts would be ideal, instead of using a (hopefully broken) DMG for a donor console. For my personal build, I used original DMG components because I had a completely dead console lying around, but you can easily find DMG-style volume wheels and cartridge connectors online. The tricky parts are as follows:
  - A GBC EXT port can be used in place of the DMG one (but would look kind of weird in the DMG EXT hole in the shell).
  - There are a few power switches I've ordered to try out in place of the DMG one, but they haven't arrived yet. There's no one fully drop-in replacement that I've found, though, so it would require circuit modifications.
  - I haven't been able to locate a headphone jack exactly the same as the DMG one, but the circuit could easily be adapted to accept a different style.
  - The DC jack could be tricky. I haven't looked very hard for any kind of replacement for this.
- Any other of the various popular GBC mods could be incorporated if desired - line out audio, bluetooth, overclocking, etc. With the ATTINY on the IPS board, one could incorporate button combinations to interface with these mods without the need of any additional buttons or (*shudder*) touch controls.

## Potential Issues/Annoyances
-	When the button LEDs are on max brightness, using the NeoPixel LEDs specifically (especially on the white color setting), a ~1 kHz whine can be heard through the speakers or headphones. I attempted to remove this whine with different methods – adding filtering to the supplies, using separate supplies for the audio/LEDs, etc. – but I wasn’t able to remove it completely. And obviously adding a filter on the audio output is a no-go since 1 kHz is smack dab in the middle of the audible range. Changing to different colors can reduce the volume of the whine, red in particular seems to be quite low, and setting the LEDs at low brightness (or just completely off) removes it. (So just don’t play with the LEDs on if it bugs you!)

## Resources and Acknowledgements
-	The board outlines and many of the footprints for the DMG components are adapted from <a href="https://gbdev.gg8.se/files/schematics/">this DMG recreation project</a>, so very special thanks to Rolf, bit9, and nitro2k01 for saving me hours of work!
-	Thank you to gekkio for their <a href="https://gbhwdb.gekkio.fi/">Game Boy repository</a> and <a href="https://github.com/Gekkio/gb-schematics">github</a>: I referenced many of the DMG and GBC resources during this build, even just for looking at pictures of different PCBs.
-	Very special thanks to the users of the gbdev and r/Gameboy discord servers for technical resources, troubleshooting/feedback, and suggestions.
## License
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

This project is the culmination of over half a year of research, development, and testing. Please give me appropriate credit, provide a link to the license, and indicate if any changes were made to this project if you modify and share it. **You may not use this work for commercial purposes.** If you remix, transform, or build upon the material, you must distribute your contributions under the same license.
