#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
float v2;
int readVal;
const int analogPin = A0;
const int ledPinGreen  = 9;
const int ledPinYellow = 10;
const int ledPinRed    = 11;

int lastRisk = -1;

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(ledPinGreen,  OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(ledPinRed,    OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Medidor Voltaje");
  lcd.setCursor(0, 1);
  lcd.print("Cargando...");
  delay(2000);
  lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print("Voltaje:        ");
}

void loop() {
  readVal = analogRead(analogPin);
  v2 = (5.0 * readVal) / 1023.0;

  lcd.setCursor(9, 0);
  lcd.print(v2, 2);   
  lcd.print("V  ");   

  int risk;
  if (v2 <= 3.00) {
    risk = 0;
    digitalWrite(ledPinGreen,  HIGH);
    digitalWrite(ledPinYellow, LOW);
    digitalWrite(ledPinRed,    LOW);
  } else if (v2 <= 4.10) {
    risk = 1;
    digitalWrite(ledPinGreen,  HIGH);
    digitalWrite(ledPinYellow, HIGH);
    digitalWrite(ledPinRed,    LOW);
  } else {
    risk = 2;
    digitalWrite(ledPinGreen,  HIGH);
    digitalWrite(ledPinYellow, HIGH);
    digitalWrite(ledPinRed,    HIGH);
  }

  if (risk != lastRisk) {
    lcd.setCursor(0, 1);
    if      (risk == 0) lcd.print("Riesgo: Bajo    ");
    else if (risk == 1) lcd.print("Riesgo: Medio   ");
    else                lcd.print("Riesgo: Alto    ");
    lastRisk = risk;
  }

  Serial.println(v2);
  delay(500);
}
