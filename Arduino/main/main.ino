// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPININSIDE 2
#define DHTPINOUTSIDE 3
#define DHTTYPE DHT11     // DHT 11
#define LIGHTPIN A0 

DHT_Unified dhtInside(DHTPININSIDE, DHTTYPE);
DHT_Unified dhtOutside(DHTPINOUTSIDE, DHTTYPE);

uint32_t delayMS;

int temperatureInside, temperatureOutside;
int humidityInside, humidityOutside;
int light;

void setup() {
  pinMode(LIGHTPIN,INPUT);
  pinMode(A1,INPUT);
  Serial.begin(115200); 
  // Initialize device.
  dhtInside.begin();
  dhtOutside.begin();
  Serial.println("Initialized");
}

void loop() {
      sensors_event_t eventInside;
      sensors_event_t eventOutside;
        
      dhtInside.temperature().getEvent(&eventInside);
      dhtOutside.temperature().getEvent(&eventOutside);
      if (isnan(eventInside.temperature) || isnan(eventOutside.temperature)) {
            Serial.println("Error reading temperature(s)!");
      }else{
            temperatureInside = eventInside.temperature;
            temperatureOutside = eventOutside.temperature;
            Serial.print("T In: ");
            Serial.print(eventInside.temperature);
            Serial.print("   T Out: ");
            Serial.println(eventOutside.temperature);
      }

      dhtInside.humidity().getEvent(&eventInside);
      dhtOutside.humidity().getEvent(&eventOutside);
      if (isnan(eventInside.relative_humidity) || isnan(eventOutside.relative_humidity)) {
            Serial.println("Error reading humidity(s)!");
      }else{
            humidityInside = eventInside.relative_humidity;
            humidityOutside = eventOutside.relative_humidity;
            Serial.print("H In: ");
            Serial.print(eventInside.relative_humidity);
            Serial.print("   H Out: ");
            Serial.println(eventOutside.relative_humidity);
      }

      light = map(analogRead(LIGHTPIN),0,1023,0,100);
      Serial.print("Light: ");
      Serial.println(light);

      
      delay(2000);
}
