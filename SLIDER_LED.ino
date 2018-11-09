#define BLYNK_PRINT Serial
#include <Adafruit_Sensor.h>
#include <BH1750FVI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <SPI.h>
#include <FastLED.h>

#define DATA_PIN 4
CRGB leds[64];
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char ssid[] = "MGBot";
char pass[] = "Terminator812";
char auth[] = "42611c53888c42bd813761ca7c5af125";
IPAddress blynk_ip(139, 59, 206, 133);

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1
BLYNK_WRITE(V1)
{
  FastLED.clear();
 int r = param[0].asInt(); // assigning incoming value from pin V1 to a variable
 int g = param[1].asInt();
 int b = param[2].asInt();
fill_solid( leds, 8, CRGB(r,g,b)); 
FastLED.show();
delay(500);
  FastLED.clear();
  FastLED.show();
 Serial.print("V1 Slider value is: ");
  Serial.println("r - " + String(r) +", g - " + String(g)+", b - " + String(b));

}


void setup()
{
  // Debug console
  Serial.begin(115200);
 delay(512);
 Blynk.begin(auth, ssid, pass, blynk_ip, 8442);
   FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, 64);
}

void loop()
{
  Blynk.run();
}
