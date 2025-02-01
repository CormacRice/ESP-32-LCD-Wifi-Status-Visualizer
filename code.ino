#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>

#define LED1 5
#define LED2 6

char ssid[] = "VMA1968F5";
char pass[] = "72GrsYvuhtb";

int status = WL_IDLE_STATUS;

IPAddress hostPC (192, 168, 0, 222);


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, pass);

  Wire.begin(21, 22);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Connecting...");
  
  if (WiFi.status() != WL_CONNECTED){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Failed to connect to network!");
  digitalWrite(LED1, HIGH);
  delay(1000);
  }
  delay(2000);

  if (WiFi.status() == WL_CONNECTED) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connected!");
  lcd.setCursor(0,1);
  lcd.print("SSID: ");
  lcd.print(ssid);
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("Key: ");
  lcd.print(pass);

  digitalWrite(LED2, HIGH);
  delay(1000);
  } else {
  lcd.clear();
  }
}
