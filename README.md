# Smart IoT Home based on 3 microcontrollers
## Evaluatie Week 7: "Freestyle" oefening

### Gecombineerde kennis van elektronica, programmeren, sensoren en I/O interfacing.**

1. Maak gebruik van minstens 1 microcontroller (naar keuze)
   -  Ja, 3 microcontrollers
2. Lees minstens 1 parameter in met een sensor (temperatuur/licht/…) (digitaal of analoog)
   -	Ja, 6 sensors
3. Stuur minstens een externe device aan gebruik makende van een externe schakeltrap
   -	Ja, 2 fans op elk een 9V batterij
4. De gemeten parameter(s) alsook de status van de output(s) moeten zowel zichtbaar zijn op een lokaal display als op de afstandsbediening via de Blynk app op je telefoon. En je moet de output(s) kunnen schakelen vanaf je telefoon.
   -	Ja, zichtbaar op OLED scherm en in de Blynk app
   -	Ja, stepper motor, relay en 3 led’s kunnen geschakeld worden via de Blynk app
   
### Parts:

**- ESP32 as smart bedroom:**
- Temperature sensor (BMP280 I2C)
- Airco with a fan (12V computer fan)
- Smart blinds with motor (Stepper Motor 28BYJ-48)
- RGB Smart light (4 pin RGB Led)
- 3 Smart lights (5mm yellow LED)
- Smart relay (KY-038 & 5V Tongling relay)
- Display to show all the values (128x64 OLED SSD1306 IC2)

**- Mini D1 (ESP8266) as smart chicken house:**
- Temperature sensor (DS18B20)
- Light sensor (BH1750 I2C)
- Chicken gate control with motor (TowerPro SG90 Servo)
- Airco with a fan (12V computer fan)

**- Arduino Nano 33 IoT as smart weather station:**
- Inside temperature sensor (BMP180)
- Inside humidity sensor (DHT11)
- Outside temperature (WiFi)
- Outside humidity (WiFi)
- Light sensor (LDR)
- (Water sensor)
- Sunrise (WiFi)
- Sunset (WiFi)

###### Exercise for the "Sensors & Interfacing" course in the Internet of Things education. 
###### © Dries Debouver
