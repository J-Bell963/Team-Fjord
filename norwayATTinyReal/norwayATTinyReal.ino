#include <TM1637TinyDisplay.h>
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(1, 0, NEO_RGB + NEO_KHZ800);

int potPin = A1;
int butPin = 1;
int CLK = 3;
int DIO = 4;

TM1637TinyDisplay display(CLK, DIO);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.clear();
  strip.setBrightness(100);
  pinMode(butPin, INPUT);

  display.setBrightness(0);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
 int buttonState = digitalRead(butPin);
  int sensorVal = analogRead(potPin);
  strip.setPixelColor(0, 0, 0, 0);
  strip.show();

  uint16_t mappedVal;
  mappedVal = map(sensorVal, 0, 1023, 0, 200);
  int displayMap = map(sensorVal, 0, 1023, 450, 700);
  if (buttonState == 0) {

    strip.setPixelColor(0, Wheel((mappedVal) & 255));
    display.showNumber(displayMap);
    strip.show();
    delay(3000);

  } else {

    strip.setPixelColor(0, 0, 0, 0);
    strip.show();

  }

}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
