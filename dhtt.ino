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
	tft.setCursor(0, 30); // x, y
	tft.setFreeFont(&FreeSansBold18pt7b);

	float t = dht.readTemperature();
	float h = dht.readHumidity();

	tft.println("Temp   Hum");
	tft.drawLine(0, 38, 250, 38, TFT_BLUE);
	tft.setCursor(0, 70);
	tft.setFreeFont(&FreeSans18pt7b);
	tft.printf("%.1f c   %.1f%%", t, h);

	Serial.print(F("% Temperature: "));
	Serial.print(t);
	Serial.print(F("°C\n\r"));
	delay(1000);
}
