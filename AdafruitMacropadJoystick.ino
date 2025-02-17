#include <Joystick.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_NeoPixel.h>
#include <RotaryEncoder.h>
//A macro for the number of keys on the macropad
#define KEYS 12

// Create the neopixel strip with the built in definitions NUM_NEOPIXEL and PIN_NEOPIXEL
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Create the OLED display
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &SPI1, OLED_DC, OLED_RST, OLED_CS);

// Create the rotary encoder
RotaryEncoder encoder(PIN_ROTA, PIN_ROTB, RotaryEncoder::LatchMode::FOUR3);
void checkPosition() {  encoder.tick(); } // just call tick() to check the state.
// our encoder position state
int encoder_pos = 0;

void UpdateEncoder();
void UpdateKeys();
uint32_t Wheel(byte WheelPos);

void setup() {
  //Create a serial connection for testing
  /*Serial.begin(115200);
  //while (!Serial) { delay(10); }     // wait till serial port is opened
  delay(100);  // RP2040 delay is not a bad idea

  Serial.println("Adafruit Macropad with RP2040"); */

  // start pixels!
  pixels.begin();
  pixels.setBrightness(255);
  pixels.show(); // Initialize all pixels to 'off'

  // Start OLED
  display.begin(0, true); // we dont use the i2c address but we will reset!
  display.display();
  
  // set all mechanical keys to inputs
  for (uint8_t i = 1; i <= KEYS; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  // set rotary encoder inputs and interrupts
  pinMode(PIN_ROTA, INPUT_PULLUP);
  pinMode(PIN_ROTB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_ROTA), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ROTB), checkPosition, CHANGE);  

  // text display tests
  display.setTextSize(1);
  display.setTextWrap(false);
  display.setTextColor(SH110X_WHITE, SH110X_BLACK); // white text, black background

  // Enable speaker
  pinMode(PIN_SPEAKER_ENABLE, OUTPUT);
  digitalWrite(PIN_SPEAKER_ENABLE, HIGH);
  // Play some tones
  pinMode(PIN_SPEAKER, OUTPUT);
  digitalWrite(PIN_SPEAKER, LOW);
  tone(PIN_SPEAKER, 988, 100);  // tone1 - B5
  delay(100);
  tone(PIN_SPEAKER, 1319, 200); // tone2 - E6
  delay(200);

  Joystick.use8bit();
  Joystick.useManualSend(true);
  Joystick.begin();
}

uint8_t j = 0;

void loop() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("* Adafruit Macropad *");

  UpdateEncoder();
  Joystick.send_now();

  for(int i=0; i< pixels.numPixels(); i++) {
    pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
  }

  UpdateKeys();
  Joystick.send_now();
  
  // show neopixels, incredment swirl
  pixels.show();
  j++;

  display.display();
}

void UpdateEncoder(){
  encoder.tick();          // check the encoder
  int newPos = -encoder.getPosition();
  if (encoder_pos != newPos) {
    if(newPos > 127){
      newPos = 127;
      encoder.setPosition(-127);
    }
    else if(newPos < -127){
      newPos = -127;
      encoder.setPosition(127);
    }
    
    Joystick.Zrotate(newPos);
    encoder_pos = newPos;
  }
  display.setCursor(0, 8);
  display.print("Rotary encoder: ");
  display.print(encoder_pos);

  //Push encoder button state
  Joystick.button(13, !digitalRead(PIN_SWITCH));

  //Update encoder button status to display
  display.setCursor(0, 24);
  if (!digitalRead(PIN_SWITCH)) {
    Serial.println("Encoder button");
    display.print("Encoder pressed ");
    pixels.setBrightness(255);     // bright!
  } else {
    pixels.setBrightness(80);
  }
}

void UpdateKeys(){
  for (int i = 1; i <= KEYS; i++){
      Joystick.button(i, !digitalRead(i));

      if (!digitalRead(i)) { // switch pressed!
        Serial.print("Switch "); Serial.println(i);
        pixels.setPixelColor(i-1, 0xFFFFFF);  // make white
        // move the text into a 3x4 grid
        display.setCursor(((i-1) % 3)*48, 32 + ((i-1)/3)*8);
        display.print("KEY");
        display.print(i);
      }
    }
}

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}