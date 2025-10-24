#include <Arduino.h>
#include <Adafruit_ST7789.h>

const int thermistorPin = A0;  

void setup() {
  Serial.begin(115200);

  // initialize screen
  screen.init(135, 240); // Init ST7789 240x135
  screen.setRotation(3);
  screen.fillScreen(ST77XX_YELLOW);
}

void loop() {
  int adcValue = analogRead(thermistorPin);

    screen.setCursor(0, 0);
  screen.setTextColor(ST77XX_BLACK);
  screen.setTextSize(2);
  screen.setTextWrap(true);
  // displays the temperature on the screen
  screen.print(F("TEMP "));
  screen.print(adcValue());

  Serial.print("ADC Value: ");
  Serial.println(adcValue);
  delay(500);
}
