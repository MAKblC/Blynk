#define BLYNK_PRINT Serial
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 4 // DATA PIN
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 4, 4, PIN,
  NEO_TILE_TOP   + NEO_TILE_LEFT   + NEO_TILE_ROWS   + NEO_TILE_ZIGZAG +
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB + NEO_KHZ800);
// Go to the Project Settings (nut icon).
char ssid[] = "MGBot";
char pass[] = "Terminator812"; //pass
char auth[] = "eea222d055284eaba5a573b508db471e";
IPAddress blynk_ip(139, 59, 206, 133);
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };
// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1

BLYNK_WRITE(V1)
{
String text = param.asStr();
char charBufVar[20];
text.toCharArray(charBufVar, 20);

 matrix.fillScreen(0x1F);
 // delay(1);                     // one partial workaround
 // portDISABLE_INTERRUPTS();     // the other workaround
  matrix.show();
//  portENABLE_INTERRUPTS();
matrix.setCursor(0, 12);
matrix.print(utf8rus(charBufVar));
 // delay(1);                     // one partial workaround
  portDISABLE_INTERRUPTS();     // the other workaround
  matrix.show();
  portENABLE_INTERRUPTS();
 // delay (20);
  
   Serial.println(charBufVar);
}

void setup()
{
  // Debug console 
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
  matrix.setFont(0);
 
  Serial.begin(115200);
 delay(512);
 Blynk.begin(auth, ssid, pass, blynk_ip, 8442);
 
}

String utf8rus(String source)
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x2F; //sometimes can be 0x30 instead 0x2F
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x6F; //sometimes can be 0x70 instead 0x6F
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
return target;
}
void loop()
{
  Blynk.run();
  }
