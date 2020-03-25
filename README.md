# Smart IoT Home based on 3 microcontrollers
## Evaluation Week 7: "Freestyle" exercise

### Combined knowledge from electronics, programming, sensors and I/O interfacing.

In this project I made a Smart Bedroom, Smart Chicken House and Smart Weather Station with almost all of the parts that I have.
It works on 3 seperate microcontrollers: ESP32, Wemos Mini D1 and Arduino Nano 33 IoT.

### Instructions:
1. Use at least 1 microcontroller (of your choice)
   - Yes, 3 microcontrollers
2. Read in at least 1 parameter with a sensor (temperature / light / ...) (digital or analog)
   - Yes, 6 sensors
3. Control at least one external device using an external switching stage
   - Yes, 2 fans each with a 9V battery and transistor
4. The measured parameter(s) as well as the status of the output(s) must be visible on a local display as well as on the Blynk app on your phone. You should be able to switch the output(s) from your phone.
   - Yes, visible on OLED screen and in the Blynk app
   - Yes, stepper motor, relay, 3 LED's and RGB LED can be controlled via the Blynk app
   
### Parts:

**- ESP32 as Smart Bedroom:**
- Temperature sensor (BMP280 I2C)
- Airco with a fan (12V computer fan)
- Smart blinds with motor (Stepper Motor 28BYJ-48)
- RGB Smart light (4 pin RGB Led)
- 3 Smart lights (5mm yellow LED)
- Smart relay (KY-038 & 5V Tongling relay)
- Display to show all the values (128x64 OLED SSD1306 IC2)

**- Mini D1 (ESP8266) as Smart Chicken House:**
- Temperature sensor (DS18B20)
- Light sensor (BH1750 I2C)
- Chicken gate control with motor (TowerPro SG90 Servo)
- Airco with a fan (12V computer fan)

**- Arduino Nano 33 IoT as smart weather station:**

I made this in another project: https://github.com/DriesDebouver/Smart-IoT-Weather-Station/blob/master/README.md
- Inside temperature sensor (BMP180)
- Inside humidity sensor (DHT11)
- Outside temperature (WiFi)
- Outside humidity (WiFi)
- Light sensor (LDR)
- (Water sensor)
- Sunrise (WiFi)
- Sunset (WiFi)

### Video link:
[![Video](http://img.youtube.com/vi/toF9ledohuA/0.jpg)](http://www.youtube.com/watch?v=toF9ledohuA)

###### Exercise for the "Sensors & Interfacing" course in the Internet of Things education. 
###### © Dries Debouver
