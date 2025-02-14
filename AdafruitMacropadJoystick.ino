#include <Joystick.h>
#include <RotaryEncoder.h>
//A macro for the number of keys on the macropad
#define KEYS 12

// Create the rotary encoder
RotaryEncoder encoder(PIN_ROTA, PIN_ROTB, RotaryEncoder::LatchMode::FOUR3);
void checkPosition() {  encoder.tick(); } // just call tick() to check the state.
// our encoder position state
int encoder_pos = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }     // wait till serial port is opened
  Serial.println("Adafruit Macropad with RP2040");
  // set all mechanical keys to inputs
  for (uint8_t i=0; i<=12; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  Joystick.begin();
}

void loop() {
  UpdateKeys();
  UpdateEncoder();

}

void UpdateEncoder(){
  encoder.tick();          // check the encoder
  int newPos = encoder.getPosition();
  if (encoder_pos != newPos) {
    Joystick.Z(newPose);
    encoder_pos = newPos;
  }
}

void UpdateKeys(){
  for(int i = 1; i <= KEYS; i++){
      Joystick.button(i, !digitalRead(i));
      delay(10);
    }
}

