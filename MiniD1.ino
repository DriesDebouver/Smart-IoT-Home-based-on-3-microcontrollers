/*
 * Smart IoT Chicken House
 * Made by Dries Debouver in March 2020
 */

#include <Wire.h>
#include <BH1750.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//BH1750:
BH1750 lightMeter;
float lux;

//Dallas:
OneWire oneWire(D5); //Pin
DallasTemperature sensor(&oneWire);
float temp;

//Servo:
Servo servo;
const int servoPin = D7;
int angle = 0;
int gate;
int gateServo;

//Fan:
const int fanPin = D6;
int fan;

//Blynk:
char auth[] = "gl64vI0XgjkCGETeHbG5Ir0ylgfs-I03";
char ssid[] = "WiFi-Debouver-2.4";
char pass[] = "UzpSk6g9D3E3";

void setup() {
  Serial.begin(9600);
  pinMode(fanPin, OUTPUT);
  //BH1750:
  Wire.begin(D4, D3); // SDA, SLC
  lightMeter.begin();
  //Dallas:
  sensor.begin();
  //Servo:
  servo.attach(servoPin);
  servo.write(angle);
  //Blynk:
  Blynk.begin(auth, ssid, pass, "server.wyns.it", 8081);
}

void loop() {
  //BH1750:
  lux = lightMeter.readLightLevel();

  //Dallas:
  sensor.requestTemperatures();
  temp = sensor.getTempCByIndex(0);

  //Servo:
  //If dark outside & gate is open: close chicken gate:
  if (lux < 100 && gate == 1) {
    servo.write(180);
    gate = 0;
  }
  //If bright outside & gate is closed: open chicken gate:
  if (lux > 100 && gate == 0) {
    servo.write(0);
    gate = 1;
  }

  //Fan:
  if (temp > 23) {
    digitalWrite(fanPin, HIGH);
    fan = 1;
  } else {
    digitalWrite(fanPin, LOW);
    fan = 0;
  }

  //Serial monitor print:
  Serial.println("---------------------------");
  Serial.print("Light (LUX): ");
  Serial.println(lux);
  Serial.print("Temperature (°C): ");
  Serial.println(temp);
  if (gate == 0) {
    Serial.println("Chicken gate: CLOSED");
  }
  if (gate == 1) {
    Serial.println("Chicken gate: OPEN");
  }
  if (fan == 0) {
    Serial.println("Fan: OFF");
  }
  if (fan == 1) {
    Serial.println("Fan: ON");
  }

  //Blynk:
  Blynk.run();
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, lux);
  Blynk.virtualWrite(V2, gate);
  Blynk.virtualWrite(V3, fan);
}
