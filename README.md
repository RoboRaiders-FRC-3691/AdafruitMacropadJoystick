# AdafruitMacropadJoystick
Repo for FRC team-3691 [Adafruit MacroPad](https://www.adafruit.com/product/5128) implementation using Arduino.

#Setp MacroPad
1. Follow the [Adafruit MacroPad Arduino setup instructions.](https://learn.adafruit.com/adafruit-macropad-rp2040/arduino-ide-setup) (Stop once you have tested your setup by running the example code)
2. Download and open the source (.ino) file into the Arduino IDE.
3. Compile the source (.ino) and load it onto your Adafruit MacroPad.

#Testing (Windows Instructions)
1. Use Win + R to open the run prompt.
2. Type in joy.cpl and hit enter.
3. Select the MacroPad on the list > Properties > Test tab.
4. Make sure all the inputs on the MacroPad are showing up when you press them.

#VSCode Setup
Simply treat the MacroPad as a generic joystick in WPILIB VSCode. (Todo: Implement custom MacroPad class derived from Joystick)


