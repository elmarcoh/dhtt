#include "DHT.h"
#include <TFT_eSPI.h>
#include <SPI.h>

#define DHTPIN 17
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
TFT_eSPI tft = TFT_eSPI();

void setup() {
	Serial.begin(115200);
	Serial.println(F("DHTxx test!"));
	dht.begin();
	tft.begin();
	tft.setRotation(1);
}

void loop() {
	tft.fillScreen(TFT_BLACK);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.setCursor(0, 60); // x, y
	tft.setFreeFont(&FreeSansBold18pt7b);
	tft.print("Hello World");

	float t = dht.readTemperature();
	float h = dht.readHumidity()

	Serial.print(F("% Temperature: "));
	Serial.print(t);
	Serial.print(F("°C\n\r"));
	delay(2000);
}
