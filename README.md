# Game Boy DMG Color
**TO-DO:**
- Include pictures
- Update power draw measurements
- Upload gerber files
- Record audio output
- Generate audio spectrum plots
- Add copyright
- Higher resolution schematic pictures

[Picture of DMGC]

This is my design for an original Game Boy (model name DMG) with native Game Boy Color support, and a handful of improved features! This is an original creation - newly designed PCBs, with only some necessary components harvested from an original Game Boy and Game Boy Color (no hardware emulation – this project uses the original CPU). Here are the project goals:
-	An original Game Boy aesthetic, using the original Game Boy shell and external parts (link port, volume wheel, power switch, etc.), but with the capability of playing Game Boy and Game Boy Color games.
-	A nice, large IPS screen – the GBC Q5 XL IPS Backlight with OSD kit – with brightness and color palette control via the "navigation switch" housed where the contrast wheel used to be. (I will refer to the PCB attached to the Q5 screen as the “Q5 board”)
-	A modernized, efficient switch mode power supply that can run off 4x AA batteries or input from the DC jack, just like the original DMG. Testing shows that playing with NiMH AA batteries can yield more than 17 hours of gameplay at normal settings (AKA, the way I normally play it - maximum brightness and headphones). 
-	Louder, warmer sound through a modern audio amplifier.
-	The option for backlit buttons, with multiple color modes and settings.
-	No externally viewable case modifications, outside of trimming the DMG power switch cover for Game Boy Color game compatibility.

The code name for this project is DMGC. This console uses four PCBs, just as the original DMG model did - a CPU board (DMGC-CPU), display board (DMGC-IPS), power board (DMGC-PWR), and headphone jack board (DMGC-HDP). All circuit board assemblies have their own separate folders in this repository which contain detailed descriptions of operation, source files for schematics and board layouts (designed using Eagle), exported Gerber files, and some other relevant files. 

Next to an original DMG… one can really see the improvements!

[picture of DMGC next to DMG]

## Disclaimer

**Before I go any further, please read this important disclaimer.**

I made this project first and foremost **for my own consumption**. All of the features I have included are things I **personally** wanted. I have tried my hardest to make the project modular, if others would like to improve or change things easily, and I have also tried very hard to make the design somewhat less prone to potential errors during assembly (such as spacing out power pins on the FFC connectors). But in the end, every decision I made was for what I wanted the final product to be, with my skill level in mind.

This project is fully open-sourced under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International license. Schematics, gerbers, and the BOM are provided in the various folders. If you choose to build this project yourself, be warned - this is a considerably advanced, and expensive build. **You are 100% liable for any damage done to your property or yourself. I am not responsible for any damage or loss of property incurred while attempting this project, or after completion of the project.** While I am confident in this design, I cannot claim full compatibility with every system configuration. And there may be latent issues that have yet to crop up. I will update this page if I encounter any, and if you see anything I may have missed, or some dubious design choice, feel free to ask questions or comment as such. Corrections are welcome. However, I **will not** obligate myself to providing tech support.

**Do not attempt this project if you are uncomfortable or inexperienced with detailed electronics troubleshooting, or are not proficient in soldering.**

[pictures of the four blank circuit boards]

## Bill of Materials

This is the high-level BOM for my specific build. Each folder for each board will contain detailed BOMs near the bottom of each README that contain all of the electronic components needed for each circuit board. Note that some parts may be out of stock at these links, but many (such as the IPS kit) can be found at alternate other retailers online. Parts that deviate from the ones listed here (like different shell designs) might necessitate different fitment modifications.

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
-	Custom designed 3D-printed IPS bracket (file located within the DMGC-IPS-01 folder)
-	<a href="https://retrogamerepairshop.com/collections/game-boy-dmg-shells/products/game-boy-dmg-original-new-shells-factory-a?variant=32530346967114">Game Boy DMG Shell – Factory A (Midnight Blue)</a>
-	<a href="https://store.kitsch-bent.com/products/silicone-buttons?variant=40627510771907">Kitsch-Bent clear silicone DMG buttons</a>

## Assembly Pictures
Here are some pictures of the assembly process. Detailed images of the circuit boards are shown in their respective folders.

First, I started with the back half of the DMG shell. I measured the wires going to the PWR and HDP boards from the CPU board after placing them in the back shell. The PWR board needs five (LENGTH)" wires, and the HDP board needs four (LENGTH)" wires. I removed all the boards, soldered the wires in, then placed it back in the shell and secured the assembly with the proper screws. (I put a game in the cartridge slot to keep the CPU board in place easier while assembling.)

[picture of back half of shell, with boards]

Then, I prepared the Q5 board solder pads. I cut six 30 gauge wire segments and soldered them on the brightness, palette, battery, and OSD input pads. These will be soldered to the bottom of the IPS board after installed.

[picture of wires]

For the top half of the shell, as per instructions on a similar DMG IPS kit that uses the Q5 screen, I very carefully cut ~1 mm of plastic around the border of the viewing port, and trimmed any extra plastic to make the surface underneath the lens smooth (there are "IPS ready" shells that should not require this cut). I used a black marker pen to color in the edges of the newly cut plastic, so they would not be as easily visible at an angle. And I trimmed two posts off of the shell so the screen would fit flush against it. 

[picture of front half of shell with lens and screen, from behind]

Then I installed the front lens, and placed the screen, backed with the 3D printed bracket, into the front half of the shell.

[picture of bracket]
[picture of front half]

Once the bracket was placed and flush with the shell, I put the buttons in and placed the IPS board over top, slid the Q5 screen FFC into the connector on the PCB (making sure it fit without any added stress on any connections), and secured it all in place.

[picture of two halves, ready to be assembled, with FFC on the CPU board]

After that, it was just a matter of connecting the FFC to both the CPU and IPS screens, tucking it under the boards ensuring no kinks or sharp bends, and screwing it together.

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
-	Push in: Toggle button LED color setting
-	Push in/Hold + D-pad Left: Decrease button LED brightness
-	Push in/Hold + D-Pad Right: Increase button LED brightness
-	Push in/Hold when turning on power switch: Disable LEDs until another power cycle

## Power Draw Measurements
For these estimates, battery life is calculated using four eneloop pro NiMH AA batteries (total of ~11800 mWh). Keep in mind that these are very rough estimates. I tried to be conservative in the power draw measurements, so hopefully these numbers represent a *mostly* worst case. Actual playtime *will* vary due to a variety of factors - changes in efficiency and performance as the battery voltage changes, differences in game audio, etc.

I measured the power draws using a MiniWare MDP-XP Mini Digital Power Supply, and used the largest average power draw shown on the display. Input voltage was set to 4.3 V, just above the point where the power LED dims. I tested with the Legend of Zelda: Link's Awakening, letting the game sit on the title screen after the intro cinematic, where sound is relatively loud and the screen is mostly white. The audio gain on the test console is set to ~0.38 (see CPU board for more detail on this gain value - a higher gain will greatly impact power draw at high volumes out of the speaker). 

| Test Criteria | Power Draw | Estimated Battery Life |
| ------------- | ------------- | ------------- |
| IPS max brightness, NeoPixel LEDs max brightness (white), speaker volume 100%, Everdrive X5	| 800 mW	| 14.8 hr |
| IPS max brightness, NeoPixel LEDs off, speaker volume 100%, Everdrive X5 | 770 mW	| 15.3 hr |
| IPS max brightness, NeoPixel LEDs off, headphones, Everdrive X5	| 680 mW	| 17.4 hr |
| IPS max brightness, NeoPixel LEDs off, headphones, original cartridge | 670 mW	| 17.6 hr |
| IPS min brightness, NeoPixel LEDs off, headphones, original cartridge	| 500 mW	| 23.6 hr |

*Note: If powering through the DC jack instead of batteries, an OEM adapter may not be able to supply enough power to the DMGC at maximum settings. Furthermore, <a href = "https://retrogamerepairshop.com/products/dmg-game-boy-original-dmg-usb-power-cord-adapter?variant=39454726455468">cables like these</a> will require at least ~200 mA output from the USB port for reliable operation at all settings. (USB 1.0 and 2.0 are likely not sufficient for higher loads, such as with the button LEDs on)*

## Audio Recordings and Spectrum
I mentioned the sound of the DMGC is "warmer" than an original GBC - it's bassier with less background noise (I suspect owing mostly to the modernized power supply). I connected the headphone jack to my computer's microphone input, and used Audacity to obtain line out recordings. Then I graphed the spectrum using Audacity's "plot spectrum" analysis tool. You can see the larger amplitudes of the lower frequencies in the spectrum plot of the DMGC. I'm not an audiophile, but I do think it sounds nicer. Listen for yourself. (GitHub only allows for video files to be uploaded, MP3 files are provided above)

### Original GBC Audio

https://user-images.githubusercontent.com/97127539/180215249-4b21aca1-a9fd-430a-a870-95bf4837e4da.mp4

### DMGC Audio

https://user-images.githubusercontent.com/97127539/180215280-5e533449-5116-4848-a94b-92f8979db334.mp4

### Original GBC Audio Spectrum

![image](https://user-images.githubusercontent.com/97127539/180213625-09bf0430-d7a2-47d9-acbe-a77910de87cb.png)

### DMGC Audio Spectrum

![image](https://user-images.githubusercontent.com/97127539/180213573-0bff4368-c301-432c-91fa-dc71b0badb11.png)

## Possible Additions/Changes
Want to improve this project? Maybe try one of these things (because I probably won’t):
- This console uses 4x AAs instead of a single rechargeable battery in order to maintain the feel and weight of the original DMG model, but an obvious change to the build is to utilize a LiPo battery with proper battery management. The DC jack could be repurposed to charge the battery instead. With the advent of affordable rechargeable AAs, the appeal of the AC adapter is diminished, so this would be a good repurposing. However, the maximum output current of most DMG AC adapters is rated for ~200mA at ~6V, so charging would be considerably slower than, say, USB-C charging. I have seen cables that convert the DC jack to a USB-A connector, however.
- A popular option for modern Game Boy mods is to use a laminated screen. This basically seals the front lens to the screen to prevent any dust from entering between the screen and lens, and makes the image look hella nice. There aren't any off-the-shelf laminated screen kits that would work with this build, but one could potentially do a custom lamination by hand.
- Restoring the IR functionality of the GBC could also be done, as there is ample space for it on the circuit board and shell - I just do not trust myself with forming plastic to look nice, and it wasn't an important part of the build for me.
- Finding aftermarket equivalents for all the different required DMG parts would be ideal, instead of using a (hopefully broken) DMG for a donor console. For my personal build, I used original DMG components because I had a completely dead console lying around, but you can easily find DMG-style volume wheels and cartridge connectors online. The tricky parts are as follows:
  - A GBC EXT port can be used in place of the DMG one (but would look kind of weird in the DMG EXT hole in the shell).
  - There are a few power switches I've ordered to try out in place of the DMG one, but they haven't arrived yet. There's no one fully drop-in replacement that I've found, though, so it would require circuit modifications.
  - I haven't been able to locate a headphone jack exactly the same as the DMG one, but the circuit could easily be adapted to accept a different style.
  - The DC jack could be tricky. I haven't looked very hard for any kind of replacement for this.
- Any other of the various popular GBC mods could be incorporated if desired - line out audio, bluetooth, overclocking, etc. With the ATTINY on the IPS board, one could incorporate button combinations to interface with these mods without the need of any additional buttons or (*shudder*) touch controls.

## Potential Issues/Annoyances
-	When the button LEDs are on max brightness, using the NeoPixel LEDs specifically (especially on the white color setting), a ~1 kHz whine can be heard through the speakers or headphones. I attempted to remove this whine with different methods – adding filtering to the supplies, using separate supplies for the audio/LEDs, etc. –  this lowered the noise amplitude, but I wasn’t able to remove it completely. And obviously adding a filter on the audio output is a no-go since 1 kHz is smack dab in the middle of the audible range. Changing to different color settings can reduce the volume of the whine, red in particular seems to be quite low, and setting the LEDs at low brightness (or just completely off) removes it. So just don’t play with the LEDs on if it bugs you! I kept the color sweep during power-on enabled on every color setting - if you want to disable the LEDs for the entire play session, hold the navigation dial in when you turn it on (but at that point... why did you bother adding the LEDs in the first place?)
-	The original DMG A/C adapter that plugs into the DC jack cannot support play with maximum settings (backlit buttons, maximum brightness, maximum speaker volume, flash cart). If you start up the Game Boy with less than maximum settings, then during gameplay increase the load on the power supply such as by increasing the screen brightness or maxing out the volume on the speakers, the console may shut off. If you're powering the console through the DC jack, I suggest using a USB adapter cable into a USB 3.0 port (or some style of USB wall charger)

## Resources and Acknowledgements
-	The board outlines and many of the footprints for the DMG components are adapted from <a href="https://gbdev.gg8.se/files/schematics/">this DMG recreation project</a>, so very special thanks to Rolf, bit9, and nitro2k01 for saving me hours of work!
-	Thank you to gekkio for their <a href="https://gbhwdb.gekkio.fi/">Game Boy repository</a> and <a href="https://github.com/Gekkio/gb-schematics">github</a>: I referenced many of the DMG and GBC resources during this build, even just for looking at pictures of different PCBs.
-	Immense thanks to the users of the gbdev and r/Gameboy discord servers for technical resources, troubleshooting/feedback, and suggestions. Shout out to lidnariq and kevtris especially!

## License

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

This project is the culmination of over half a year of research, development, and testing. Please give me appropriate credit, provide a link to the license, and indicate if any changes were made to this project if you modify and share it. You may not use this work for commercial purposes. If you remix, transform, or build upon the material, you must distribute your contributions under the same license.
