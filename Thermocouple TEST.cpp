#include <Arduino.h>
#include <max6675.h>
#include <Adafruit_ST7789.h>

int thermoDO = GPIO_NUM_37;
int thermoCS = GPIO_NUM_35;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

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

  Serial.println(F("screen is on"));



  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {

   screen.setCursor(0, 0);
  screen.setTextColor(ST77XX_BLACK);
  screen.setTextSize(2);
  screen.setTextWrap(true);
  // displays the temperature on the screen
  screen.print(F("C = "));
  screen.print(thermocouple.readCelsius());


  // basic readout test, just print the current temp
  
  Serial.print("C = "); 
  Serial.println(thermocouple.readCelsius());
  Serial.print("F = ");
  Serial.println(thermocouple.readFahrenheit());
 
  // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(1000);
}