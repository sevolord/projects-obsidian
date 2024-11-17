#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Прототипы функций
void IRAM_ATTR triggerColdWater();
void IRAM_ATTR triggerHotWater();

#define OLED_RESET -1
Adafruit_SSD1306 OLED(128, 64, &Wire, OLED_RESET);

volatile int cold_water_counter = 0; 
volatile int hot_water_counter = 0;

#define COLD_WATER_PULSE_PIN 12 //D6
#define HOT_WATER_PULSE_PIN  13 //D7

void setup() {
  Serial.begin(9600);
  
  pinMode(COLD_WATER_PULSE_PIN, INPUT_PULLUP);
  pinMode(HOT_WATER_PULSE_PIN, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(COLD_WATER_PULSE_PIN), triggerColdWater, RISING);
  attachInterrupt(digitalPinToInterrupt(HOT_WATER_PULSE_PIN), triggerHotWater, RISING);

  if (!OLED.begin(SSD1306_PAGEADDR, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  
  OLED.clearDisplay();
  OLED.setTextWrap(false);
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
  OLED.setCursor(0, 0);
  OLED.println("Start");
  OLED.display();
}

void loop() {
  // Обработка счетчиков в основном цикле
  static int last_cold_water = 0;
  static int last_hot_water = 0;

  if (cold_water_counter != last_cold_water) {
    last_cold_water = cold_water_counter;
    displayWater("Cold", last_cold_water);
  }

  if (hot_water_counter != last_hot_water) {
    last_hot_water = hot_water_counter;
    displayWater("Hot", last_hot_water);
  }
}

void displayWater(const char* type, int count) {
  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.printf("%s water: %d l", type, count * 10);
  OLED.display();
}

void IRAM_ATTR triggerColdWater() {
  cold_water_counter++;
}

void IRAM_ATTR triggerHotWater() {
  hot_water_counter++;
}
