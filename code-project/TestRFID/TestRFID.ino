#include "SPI.h"
#include "MFRC522.h"

// Определение пинов для RC522
#define RST_PIN PB3  // Сброс
#define SS_PIN  PB4  // SDA (SS)
// MOSI - PB5
// MISO - PB6 
// SCK  - PB7

MFRC522 mfrc522(SS_PIN, RST_PIN); // Создание объекта mfrc522

void setup() {
  Serial.begin(9600);

  // Инициализация SPI
  SPI.begin(); 
  
  // Настройка пинов
  pinMode(RST_PIN, OUTPUT);
  pinMode(SS_PIN, OUTPUT);

  // Инициализация RC522
  mfrc522.PCD_Init();
  delay(4);
  
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  // Сброс цикла, если на считывателе нет карты
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {  
    return;
  }

  // Вывод информации о карте на монитор порта
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}