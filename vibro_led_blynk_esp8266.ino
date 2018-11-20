#define BLYNK_PRINT Serial
int MoPin = 14;  // pin for vibro motor

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "57b1a109d4b14807b1d0641bd3b8726f"; // Token

char ssid[] = "MGBot";                            // Wifi client name
char pass[] = "Terminator812";                    // Wifi password
IPAddress blynk_ip(139, 59, 206, 133);            // Blynk server IP and port

BLYNK_WRITE(V1) {                                 // Reading button V1 from Blynk
  int buttonstate = param.asInt ();
   if (buttonstate==1) {
    digitalWrite(MoPin, HIGH);
    }
   else    {
    digitalWrite(MoPin, LOW);
    }
  }


void setup()
{
  // Debug console
  Serial.begin(115200);
 pinMode( MoPin, OUTPUT );
 Blynk.begin(auth, ssid, pass, blynk_ip, 8442);   
    digitalWrite(MoPin, HIGH);
    delay(1000);
    digitalWrite(MoPin, LOW);
}

void loop()
{
  Blynk.run();
}
