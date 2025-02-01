#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>


char ssid[] = "WiFi";
char pass[] = "Password";

int status = WL_IDLE_STATUS;

IPAddress ip;
IPAddress subnet;
IPAddress gateway;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, pass);

  Wire.begin(21, 22);
  
  lcd.init();
  lcd.backlight();
}

void loop() {
  while (WiFi.status() != WL_CONNECTED) {
    lcd.setCursor(0,0);
    lcd.print("Connecting...");
  }
  
  delay(2000);

  
  //Show error message if failure to connect  
  if (WiFi.status() != WL_CONNECTED){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Failed to connect to network!");
  } else {
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
  }

  delay (2000);

  lcd.clear();
  
  ip = WiFi.localIP();
  
  //Get ESP's IP Address
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("IP Address:");
  lcd.setCursor(0,1);
  lcd.print(ip);

  delay(2000);

  lcd.clear();

  subnet = WiFi.subnetMask();

  lcd.setCursor(0,0);
  lcd.print("Subnet:");
  lcd.setCursor(0,1);
  lcd.print(subnet);

  delay(2000);

  lcd.clear();

  gateway = WiFi.gatewayIP();

  lcd.setCursor(0,0);
  lcd.print("Gateway:");
  lcd.setCursor(0,1);
  lcd.print(gateway);

  delay(2000);
}
