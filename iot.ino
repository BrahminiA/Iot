#define BLYNK_PRINT Serial
#define echoPin D7 // Echo Pin
#define trigPin D6 // Trigger Pin
long duration, distance;
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "2d7c019024544189832a1aa885061f84";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "BRAHMANI";
char pass[] = "honey111";
BLYNK_WRITE(V1)
{
 // This command writes Arduino's uptime in seconds to Virtual Pin (1)
 Blynk.virtualWrite(V1,distance);
}
void setup()
{
 // Debug console
 Serial.begin(9600);
 pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
 Blynk.begin(auth, ssid, pass);
 // You can also specify server:
 //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
 //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}
void loop()
{
 digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
//Calculate the distance (in cm) based on the speed of sound.
distance = duration/58.2;
Serial.println(distance);
//Delay 50ms before next reading.
delay(50);
Blynk.virtualWrite(V1,distance);
if(distance<=10)
{
 Blynk.notify("TANK IS FULL");
 Blynk.virtualWrite(V1,distance);
}
else if(distance>=185)
{
 Blynk.notify("TANK IS EMPTY");
 Blynk.virtualWrite(V1,distance);
}
 Blynk.run();
}
