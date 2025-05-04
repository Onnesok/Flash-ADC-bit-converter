#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// 3-bit input pins
const int bit2Pin = 2;  // MSB
const int bit1Pin = 3;
const int bit0Pin = 4;  // LSB

// Output pins
const int ledPin = 11;
const int fanPin = 8;
const int buzzerPin = 9;

// Initialize LCD: address 0x27, 20 columns x 4 rows (update address if needed)
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // Input pins
  pinMode(bit2Pin, INPUT);
  pinMode(bit1Pin, INPUT);
  pinMode(bit0Pin, INPUT);

  // Output pins
  pinMode(ledPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Serial Monitor
  Serial.begin(9600);

  // LCD init
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("3-bit Decoder Demo");
}

void loop() {
  // Read inputs
  int b2 = digitalRead(bit2Pin);
  int b1 = digitalRead(bit1Pin);
  int b0 = digitalRead(bit0Pin);

  // Combine bits to decimal
  int adcValue = (b2 << 2) | (b1 << 1) | b0;

  // Print to Serial Monitor
  Serial.print("Bits: ");
  Serial.print(b2);
  Serial.print(b1);
  Serial.print(b0);
  Serial.print(" (Decimal: ");
  Serial.print(adcValue);
  Serial.println(")");

  // Clear the LCD before updating
  lcd.clear();

  // Print to LCD (clear previous values)
  lcd.setCursor(0, 1);
  lcd.print("Bits: ");
  lcd.print(b2);
  lcd.print(b1);
  lcd.print(b0);
  lcd.print("   ");  // Extra spaces to clear previous longer text

  lcd.setCursor(0, 2);
  lcd.print("Decimal: ");
  lcd.print(adcValue);
  lcd.print("    ");  // Extra spaces to clear previous longer text

  // Control devices
  digitalWrite(ledPin, adcValue == 2 ? HIGH : LOW);
  digitalWrite(fanPin, adcValue == 4 ? HIGH : LOW);
  digitalWrite(buzzerPin, adcValue == 6 ? HIGH : LOW);

  delay(500);
}
