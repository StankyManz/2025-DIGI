#include <WiFi.h>
//HAN Notes - you can remove this library #include <LittleFS.h>
#include <ESPAsyncWebServer.h>

//HAN Notes - what is this chunk of code used for?
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

#define THERMISTOR_PIN A0  // Use actual analog pin when known
float tempThreshold = 30.0; // Default temperature threshold

//HAN Notes - what is this object for?
AsyncWebServer server(80);

// ====== INIT FUNCTIONS ======

/*
  * HAN Notes - give an overview of what this method does
  */
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi. IP:");
  Serial.println(WiFi.localIP());
}

/*
  * HAN Notes - give an overview of what this method does
  */
String processor(const String& var) {
  if (var == "THRESHOLD") {
    return String(tempThreshold);
  }
  return String();
}

// Getting Temp
float readThermistorC() {
  int raw = analogRead(THERMISTOR_PIN);
  float voltage = raw * (3.3 / 4095.0);
  float temperature = (voltage - 0.5) * 100;
  return temperature;
}

/*
  * HAN Notes - give an overview of what this method does
  */
void setup() {
  Serial.begin(115200);
  initWiFi();
  initLittleFS();
  pinMode(THERMISTOR_PIN, INPUT);

  //HAN Notes - I would use the code for my simple server rather than keeping on with the LittleFS code
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", "text/html", false, processor);
  });

  // Setting threshold
  server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("value")) {
      tempThreshold = request->getParam("value")->value().toFloat();
      Serial.print("Threshold set to: ");
      Serial.println(tempThreshold);
    }
    request->send(200, "text/plain", "Threshold updated");
  });

  server.on("/temp", HTTP_GET, [](AsyncWebServerRequest *request) {
    float currentTemp = readThermistorC();
    request->send(200, "text/plain", String(currentTemp));
  });

  server.begin();
}

/*
  * HAN Notes - give an overview of what this method does
  */
void loop() {
  float currentTemp = readThermistorC();

  if (currentTemp > tempThreshold) {
    Serial.println("Temperature above threshold");
    // Add alarm function here
  } else {
    Serial.println("Temperature normal");
  }

  delay(2000); // Read every 2 seconds
}
