# DMGC-HDP-01
**TO-DO:**

- Upload pictures
- Upload BOM
- Upload files
- In-text links

[blank board pictures]

This little board is quite simple. You can transplant all of the parts from the original DMG headphone board to this one. This board also uses an original DMG headphone jack. Modifications to the circuit would be required to use an off-the-shelf jack.
# Board Characteristics
-	Layers: 2
-	Thickness: 1.2 mm
-	Surface Finish: HASL
# Circuit Overview
![image](https://user-images.githubusercontent.com/97127539/175819188-d64cca93-572c-4d30-a57a-c0b97963eb7a.png)

On the top of the board: pin 1 is the left output, pin 2 is the right output, pin 3 is the GND reference, and pin 4 is the headphone detect pin which is normally connected to GND through the headphone jack (when headphones are placed in the jack, pin 4 will be disconnected from GND).

R1 and R2 are included to pull down the negative sides of the DC blocking capacitors C1 and C2 when headphones are not connected – without them, the outputs would be floating. This will prevent inrush current during headphone insertion, which I have seen cause issues with the LM4853 in the past.
# Bill of Materials
Lots of parts.
# Resources
-	Rolf, bit9, and nitro2k01’s DMG schematics and layouts
# License
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/80x15.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.


