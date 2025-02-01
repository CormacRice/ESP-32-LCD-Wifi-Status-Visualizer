#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>

#define LEDPin1 8
#define LEDPin2 10 

char ssid[] = "wifi";
char pass[] = "password";

int status = WL_IDLE_STATUS;

unsigned long checkTime = 10000;
unsigned long startTime = 0;

IPAddress ip;
IPAddress subnet;
IPAddress gateway;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, pass);

  Wire.begin(21, 22);

  pinMode (LEDPin1, OUTPUT);
  pinMode (LEDPin2, OUTPUT);
  
  lcd.init();
  lcd.backlight();

  startTime = millis();
}

void loop() {

  unsigned long currentMillis = millis();
  
  if (WiFi.status() != WL_CONNECTED && currentMillis - startTime < checkTime) {
    lcd.setCursor(0,0);
    lcd.print("Connecting...");
  }

  
  //Show error message if failure to connect  
  if (currentMillis - startTime >= checkTime && WiFi.status() != WL_CONNECTED){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Failed to");
  lcd.setCursor(0,1);
  lcd.print("connect!");

  digitalWrite(LEDPin2, HIGH);
  delay(500);
  digitalWrite(LEDPin2, LOW);
  delay(500);
  
  } 

  if (WiFi.status() == WL_CONNECTED) {

  digitalWrite(LEDPin1, HIGH);
    
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
} 
