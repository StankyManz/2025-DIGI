#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Arduino_JSON.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>


const char* ssid = "T8-Arduino"; 
const char* password = "T8-Arduino";

AsyncWebServer server(80);
const byte LEDPIN = 2; // GPIO pin for the LED
String ledState;



// PRESSURE STUFF
// Create an Event Source on /events
AsyncEventSource events("/events");
// Json Variable to Hold Sensor Readings
JSONVar readings;
// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;
// Create a sensor object
Adafruit_BMP280 bmp; // BMP280 connect to ESP32 I2C (GPIO 21 = SDA, GPIO ...

/***************************
* BMP sensor stuff
***************************/
void initBMP()
{
if (!bmp.begin(0x76)) //what does 0x76 signal???
{
Serial.println("Couldnt find the BMP280 sensor, check wiring!");
while (1) //what does this while loop do? and why would we do it?
;
}
}

/***************************
* Get Sensor Readings and return JSON object
***************************/
String getSensorReadings()
{
//100.0F means take the pressure reading and divide it into a floating
//point so you don't have 25.5 become 25
readings["pressure"] = String(bmp.readPressure() / 100.0F);

String jsonString = JSON.stringify(readings);
return jsonString;
}


void initLittleFS()
{
  if (!LittleFS.begin(true)) 
  {
    Serial.println("LittleFS Mount Failed");
    return;
  }
  else 
  {

  Serial.println("LittleFS Mounted Successfully");
  }
}
void initWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Use this IP in your browser:");
  Serial.println(WiFi.localIP());
  Serial.println("Connected to WiFi");
}
  String processor(const String &VAR)
  {
    if (VAR == "STATE")
    {
      if (digitalRead(LEDPIN) == HIGH)
      {
        ledState = "ON";
      }
      else
      {
        ledState = "OFF";
      }
      return ledState;
    }
    return String();
  }
void setup()
{ 
  Serial.begin(115200);
  while(!Serial) 
  {
    delay(100);
  }
  initWiFi();
  initLittleFS();
  initBMP();
  pinMode(LEDPIN, OUTPUT);
}
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) 
{
  request->send(LittleFS, "/index.html", "text/html", false, processor);
});
false, processor); });

server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) 
{
  digitalWrite(LEDPIN, LOW);
  request->send(LittleFS, "/index.html", "text/html", false, processor);
;
false, processor); });

server.begin();
}
void loop()
{
  // Nothing to do here
}
  // The server will handle requests asynchronously