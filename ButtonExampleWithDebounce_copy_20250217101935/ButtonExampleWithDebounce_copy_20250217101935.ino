#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// colors from the library we can use
#define ST77XX_BLACK 0x0000
#define ST77XX_WHITE 0xFFFF
#define ST77XX_RED 0xF800
#define ST77XX_GREEN 0x07E0
#define ST77XX_BLUE 0x001F
#define ST77XX_YELLOW 0xFFE0

//create the tft object
Adafruit_ST7735 tftScreen = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);

  //turn on backlight by setting it to HIGH
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);

  //initialize TFT
  tftScreen.initR(INITR_BLACKTAB);
  tftScreen.setRotation(1);  // what do the 1, 2, 3, 4 options do?
  tftScreen.fillScreen(ST77XX_BLACK);
  Serial.println("tft screen height is :");
  Serial.println(tftScreen.height());
  Serial.println("tft screen width is :");
  Serial.println(tftScreen.width());
  Serial.println("screen should be ready to go");
}

void loop() {
  //blank the screen - good as this is the loop method
  tftScreen.fillScreen(ST77XX_BLACK);

  //call the method with an array of text and a color
  testDrawText(
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur "
    "adipiscing est sed tincidunt feugiat. Maecenas eu massa, "
    "aliquet id malesuada vel, tincidunt sit amet turpis. Sed porttitor "
    "neque sit amet pretium tristique. Sed blandit, nulla aliquet "
    "lobortis hendrerit, est nisl lobortis lorem. In vestibulum purus a "
    "tortor imperdiet posuere.",
    ST77XX_WHITE);
  Serial.println("lots of text should be on the screen");

  //pause for 2 seconds
  delay(2000);

  //call the method
  tftScreenPrintTest();
  Serial.println("hello world x3 in different sizes");
  delay(2000);

  //what does inverting the display do to the colors?
  tftScreen.invertDisplay(true);
  Serial.println("inverted colors");
  delay(1000);
  tftScreen.invertDisplay(false);
  Serial.println("normal colors");
  delay(1000);

  Serial.println("repeating the loop code");
}

//takes an array of text and a color then does ...
void testDrawText(char *text, uint16_t color) {
  //missing line of code here that becomes apparent after the first cycle through the loop
  tftScreen.setCursor(0, 0);
  tftScreen.setTextColor(color);
  tftScreen.setTextWrap(true);
  tftScreen.print(text);
}

//stops text wrapping, blanks the screen to black
//then what?
void tftScreenPrintTest() {
  tftScreen.setTextWrap(false);
  tftScreen.fillScreen(ST77XX_BLACK);

  tftScreen.setCursor(0, 30);
  tftScreen.setTextColor(ST77XX_RED);
  tftScreen.setTextSize(1);
  tftScreen.println("Hello World!");

  tftScreen.setTextColor(ST77XX_YELLOW);
  tftScreen.setTextSize(2);
  tftScreen.println("Hello World!");

  tftScreen.setTextColor(ST77XX_GREEN);
  tftScreen.setTextSize(3);
  tftScreen.println("Hello World!");
}



// NEXT SECTION OF CODE FOR PRACTICE:




#include <ESP32Servo.h>

const byte SERVOPIN = 18;
int servoPos = 0;

Servo exampleServo; // Naming servo

String name = "Troy Yaboy";



void setup() {  // Setting up and attatching servo and setting its period. Creating serial monitor and printing a question for the user.

exampleServo.setPeriodHertz(50); // standard 50hz servo
exampleServo.attach(SERVOPIN, 500, 2400); 

  Serial.begin(115200);
  Serial.println("serial monitor and servo example");
 
  Serial.print("What is your name?");
  while (Serial.available() == 0) {
  
  }
name = Serial.readStringuntil('\n');
Serial.print("hi");
Serial.println(name);
}

  void loop() {
    Serial.println("Where should the servo move? pick 0 -180");
if (Serial.avaliable() > 0 {
      servoPos = Serial.pareInt();
}
exampleServo.write(servoPos);
Serial.pritn("servo moving to ")
Serial.println(servoPos);
 delay(500);
  }


  // NEXT SECTION FOR PRACTICE



#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <WiFi.h>

//Wifi Info
const char SSID[] = "yourNetworkName";
const char PASSWORD[] = "yourPassword";

//the WiFi status
int status = WL_IDLE_STATUS;

//Hexadecimal mac adress
byte mac[6];

Adafruit_ST7789 tftScreen = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup()
{
  pinMode(TFT_BACKLITE, OUTPUT);
  pinMode(TFT_I2C_POWER, OUTPUT);

  //turn on backlight 
  digitalWrite(TFT_BACKLITE, HIGH);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  //Initiate TFT
  tftScreen.init(135,240);
  tftScreen.setRotation(3);
  tftScreen.fillScreen(ST77XX_BLACK);

  Serial.begin(115200);
  while (!Serial)
  {
    delay(100); //stall while waiting
  }

  //Display MAC Address 
  status = WiFi.begin(SSID);

  if(status != WL_CONNECTED)
  {
    Serial.println("Couldnt get a wifi connection");
    while (true);
  }
  else
  {
    WiFi.macAddress(mac);
    Serial.println("Default Mac Adress");
    //Add .HEX to format
    //print to serial
    Serial.print(mac[5], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.print(mac[0], HEX);
    
    //Print to screen
    tftScreen.setCursor(0,0);
    tftScreen.setTextColor(ST77XX_YELLOW);
    tftScreen.setTextSize(1);
    tftScreen.setTextWrap(true);
    tftScreen.print(mac[5], HEX);
    tftScreen.print(":");
    tftScreen.print(mac[4], HEX);
    tftScreen.print(":");
    tftScreen.print(mac[3], HEX);
    tftScreen.print(":");
    tftScreen.print(mac[2], HEX);
    tftScreen.print(":");
    tftScreen.print(mac[1], HEX);
    tftScreen.print(":");
    tftScreen.print(mac[0], HEX);

  }
  

  
}

void loop()
{
    //Blank
}
