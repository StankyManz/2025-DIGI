#include <Arduino.h>
#include <Adafruit_ST7789.h>



const int thermistorPin = A0;  // use any ADC pin like 32–39

Adafruit_ST7789 screen = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);

pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
// turn on the screen / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);  

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
  screen.print(adcValue);

  Serial.print("ADC Value: ");
  Serial.println(adcValue);
  delay(500);
}
