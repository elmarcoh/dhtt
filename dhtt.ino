#include "DHT.h"
#include <TFT_eSPI.h>
#include <SPI.h>

#define DHTPIN 17
#define DHTTYPE DHT11
#define BUTTON1PIN 35
#define BUTTON2PIN 0

DHT dht(DHTPIN, DHTTYPE);
TFT_eSPI tft = TFT_eSPI();

bool useFahrenheit = false;
bool showTemp = true;
long lastButton1Press = 0;
long lastButton2Press = 0;
long coolDownMs = 400;

bool cooldownPassed(long* lastPress) {
	long now = millis();
	if ((now  - *lastPress) > coolDownMs) {
		*lastPress = now;
		return true;
	}
	return false;
}

void IRAM_ATTR toggleTempUnit() {
	if (!cooldownPassed(&lastButton1Press)) {
		return;
	}
	Serial.println(F("Button 1 pressed!"));
	useFahrenheit = !useFahrenheit;
}

void IRAM_ATTR switchScreen() {
	if (!cooldownPassed(&lastButton2Press)) {
		return;
	}
	Serial.println(F("Button 2 pressed!"));
	showTemp = !showTemp;
}

void setup() {
	Serial.begin(115200);

	// set button interrupts
	pinMode(BUTTON1PIN, INPUT);
	pinMode(BUTTON2PIN, INPUT);
	attachInterrupt(BUTTON1PIN, toggleTempUnit, FALLING);
	attachInterrupt(BUTTON2PIN, switchScreen, FALLING);

	// Serial.println(F("DHTxx test!"));
	dht.begin();
	tft.begin();

	// set screen to be horizontal
	tft.setRotation(1);
}

void tempScreen() {
	tft.fillScreen(TFT_BLACK);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.setCursor(0, 30); // x, y
	tft.setFreeFont(&FreeSansBold18pt7b);

	float t = dht.readTemperature(useFahrenheit);
	float h = dht.readHumidity();

	tft.println("Temp   Hum");
	tft.drawLine(0, 38, 250, 38, TFT_BLUE);
	tft.setCursor(0, 70);
	tft.setFreeFont(&FreeSans18pt7b);

	char tempSuffix = 'c';
	if (useFahrenheit) {
		tempSuffix = 'f';
	}
	char* format = "%.1f %c   %.1f%%";
	tft.printf(format, t, tempSuffix, h);

	Serial.printf(format, t, tempSuffix, h);
	Serial.print("\n\r");
}

void otherScreen() {
	tft.fillScreen(TFT_BLUE);
}

void loop() {
	if (showTemp) {
		tempScreen();
	} else {
		otherScreen();
	}
	delay(1000);
}
