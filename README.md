# a simple MIDI-Controller for the Line 6 POD 2.0

Pressing one of the buttons selects program 1A, 1B, 1C or 1D. Pressing the same button twice switches between banks 1 and 2.

*Example:* Power up the pedal and the pod. press button 3, this will change to program 1c. press button 1, this will change to 1A. If you press button 1 again, program 2A will be selected. Now press button 4, 2D will be selected. Press button 4 again, 1D will be selected.

If you are compiling the sketch on the commandline, be sure to edit the Makefile (especially the line starting
with ARDUINO_PORT, this is probably different on your computer)

Here is the wiring diagram:

![wiring diagram](breadboard-wiring.png)
