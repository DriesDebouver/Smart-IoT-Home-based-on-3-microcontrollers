/*
 * Smart IoT Bedroom
 * Made by Dries Debouver in March 2020
 */

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_SSD1306.h>
#include <Stepper.h>

//OLED:
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Blynk:
char auth[] = "...";
char ssid[] = "...";
char pass[] = "...";
BlynkTimer timer;

//BMP280:
Adafruit_BMP280 bmp;
float bmpTemp;
int bmpTime = 0;

//Fan:
const int fanPin = 4;
int fan;

//Relay
const int relayPin = 2;
int relay = 0;
int relayStatus = 0;

//Stepper:
const int stepsPerRevolution = 2048; //number of steps per rotation: 2048 = 360°
const int in1 = 5;
const int in2 = 18;
const int in3 = 19;
const int in4 = 23;
Stepper stepper = Stepper(stepsPerRevolution, in1, in3, in2, in4);
int blindsStepper;
float blinds;

//RGB LED:
int red;
int green;
int blue;
const int redPin = 25;
const int greenPin = 33;
const int bluePin = 32;
const int freq = 5000;
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
const int resolution = 8;

//LED'S:
const int ledPin1 = 13;
const int ledPin2 = 12;
const int ledPin3 = 14;
const int ledPin4 = 27;
WidgetLED led1(V7);
WidgetLED led2(V8);
WidgetLED led3(V9);

//Blynk: this functions will be called every time there is something controlled in the Blynk app:
//Blinds:
BLYNK_WRITE(V4) {
  blindsStepper = param.asInt(); //Assigning incoming value from the slider (Pin V3) to a variable called 'blindsStepper'
  //Blinds down:
  if (blindsStepper == 0) {
    Serial.println("Blinds going down...");
    stepper.step(stepsPerRevolution);
    stepper.step(stepsPerRevolution);
    blinds = 0;
  }
  //Blinds half:
  if (blindsStepper == 50) {
    //If they are down:
    if (blinds == 0) {
      Serial.println("Blinds going half...");
      stepper.step(-stepsPerRevolution);
      blinds = 50;
    }
    //If they are up:
    if (blinds == 100) {
      Serial.println("Blinds going half");
      stepper.step(stepsPerRevolution);
      blinds = 50;
    }
  }
  //Blinds up:
  if (blindsStepper == 100) {
    Serial.println("Blinds going up...");
    stepper.step(-stepsPerRevolution);
    stepper.step(-stepsPerRevolution);
    blinds = 100;
  }
}

//RGB Led:
BLYNK_WRITE(V5) {
  red = param[0].asInt();
  green = param[1].asInt();
  blue = param[2].asInt();
  ledcWrite(redChannel, red);
  ledcWrite(greenChannel, green);
  ledcWrite(blueChannel, blue);
}

//Relay:
BLYNK_WRITE(V6) {
  relay = param.asInt();
  if (relay == 0) {
    digitalWrite(relayPin, LOW);
    relayStatus = 0;
  }
  if (relay == 1) {
    digitalWrite(relayPin, HIGH);
    relayStatus = 1;
  }
}

void myTimerEvent() {
  Blynk.virtualWrite(V10, millis() / 1000);
}

void setup() {
  Serial.begin(9600);
  pinMode(fanPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  //RGB LED:
  ledcSetup(redChannel, freq, resolution);
  ledcSetup(greenChannel, freq, resolution);
  ledcSetup(blueChannel, freq, resolution);
  ledcAttachPin(redPin, redChannel);
  ledcAttachPin(greenPin, greenChannel);
  ledcAttachPin(bluePin, blueChannel);

  //BMP280 Sensor:
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1) delay(10);
  }

  //SSD1306 OLED:
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  //Stepper:
  stepper.setSpeed(10); //RPM

  //Blynk:
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  //Measure temperature from BMP280 sensor every 10 seconds:
  if (millis() > bmpTime) {
    bmpTemp = bmp.readTemperature();
    //Fan:
    if (bmpTemp > 25) {
      digitalWrite(fanPin, HIGH);
      fan = 1;
    } else {
      digitalWrite(fanPin, LOW);
      fan = 0;
    }
    Serial.print("Temperature: ");
    Serial.print(bmpTemp);
    Serial.println(" °C");
    bmpTime = millis() + 10000;
  }

  //Serial monitor print:
  Serial.println("---------------------------");
  Serial.print("Blinds: ");
  Serial.print(blindsStepper);
  Serial.println("%");
  if (blinds == 0) {
    Serial.println("Blinds: CLOSED");
  }
  if (blinds == 50) {
    Serial.println("Blinds: HALF");
  }
  if (blinds == 100) {
    Serial.println("Blinds: OPEN");
  }
  if (fan == 0) {
    Serial.println("Fan: OFF");
  }
  if (fan == 1) {
    Serial.println("Fan: ON");
  }
  if (relayStatus == 0) {
    Serial.println("Relay: OFF");
  }
  if (relayStatus == 1) {
    Serial.println("Relay: ON");
  }

  //OLED print:
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.print("Temperature: ");
  display.print(bmpTemp, 1);
  display.print((char)247); // ' ° ' degrees symbool
  display.print("C");
  display.setCursor(0, 15);
  display.setTextColor(BLACK, WHITE);
  if (blinds == 0) {
    display.println("Blinds: CLOSED");
  }
  if (blinds == 50) {
    display.println("Blinds: HALF");
  }
  if (blinds == 100) {
    display.println("Blinds: OPEN");
  }
  display.setCursor(0, 30);
  display.setTextColor(WHITE);
  if (fan == 0) {
    display.println("Fan: OFF");
  }
  if (fan == 1) {
    display.println("Fan: ON");
  }
  display.setCursor(0, 45);
  display.setTextColor(BLACK, WHITE);
  if (relayStatus == 0) {
    display.println("Relay: OFF");
  }
  if (relayStatus == 1) {
    display.println("Relay: ON");
  }
  display.display();

  //Blynk:
  Blynk.run();
  timer.run();
  Blynk.virtualWrite(V0, bmpTemp);
  Blynk.virtualWrite(V1, blindsStepper);
  Blynk.virtualWrite(V2, fan);
  Blynk.virtualWrite(V3, relayStatus);
  int led1value = digitalRead(ledPin1);
  int led2value = digitalRead(ledPin2);
  int led3value = digitalRead(ledPin3);
  if (led1value == LOW) {
    led1.off();
  }
  if (led1value == HIGH) {
    led1.on();
  }
  if (led2value == LOW) {
    led2.off();
  }
  if (led2value == HIGH) {
    led2.on();
  }
  if (led3value == LOW) {
    led3.off();
  }
  if (led3value == HIGH) {
    led3.on();
  }
}
