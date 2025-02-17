# AdafruitMacropadJoystick
Repo for FRC team-3691 [Adafruit MacroPad](https://www.adafruit.com/product/5128) implementation using Arduino.

# Setup MacroPad
1. Follow the [Adafruit MacroPad Arduino setup instructions.](https://learn.adafruit.com/adafruit-macropad-rp2040/arduino-ide-setup) (Stop once you have tested your setup by running the example code)
2. Download and open the source (.ino) file into the Arduino IDE.
3. Compile the source (.ino) and load it onto your Adafruit MacroPad.

# Testing (Windows Instructions)
1. Use Win + R to open the run prompt.
2. Type in joy.cpl and hit enter.
3. Select the MacroPad on the list > Properties > Test tab.
4. Make sure all the inputs on the MacroPad are showing up when you press them.

# VSCode Setup/Usage
1. To use the template classes in the AdafruitMacropad.cpp/.h and CommandAdafruitMacropad.cpp/.h files.
   - These can be copied and pasted into the include and cpp directories of your WPILIB robot project.
   - The classes are constructed in a very similar way to XboxController and CommandXboxController.
   - Current Documentation for template classes is lacking this will hopefully be improved in the future. However, usage is relatively straightforward.
2. To use without the template class you can treat the MacroPad as a Joystick or GenericHID device. Interfacing with it through WPILIB.
   


