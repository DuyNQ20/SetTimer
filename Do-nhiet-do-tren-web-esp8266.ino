// Them thu vien

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>
#include "index.h"

// Pin
// Su dung cam bien DHT11
#define DHTTYPE DHT22
#define DHTPIN D1
#define output_pin D2
int temp=0, tempOld=0;
int humi=0, humiOld=0, tus=0;
String trangthai = "OFF";
// Thiet lap DHT
DHT dht(DHTPIN, DHTTYPE);

// Thong so WiFi nha ban
const char* ssid = "DESKTOP-BDE4ACL 0105";
const char* password = "12345678";

// Tao server
ESP8266WebServer server(80);

void setup() {

// Khai bao GPIO5
  pinMode(output_pin, OUTPUT);
  digitalWrite(output_pin, 0);
  // Mo Serial
  Serial.begin(115200);
  delay(10);

  // Khoi tao DHT
  dht.begin();

  // Ket noi toi mang WiFi
  //Serial.println();
  //Serial.println();
  Serial.print("Ket noi toi mang ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Da ket noi WiFi");
  
  server.on("/", handleRoot);
  server.on("/temp", temperature);
  server.on("/humi", humidity);
  server.on("/led", ledControl);
  // Khoi dong server
  server.begin();
  Serial.println("Khoi dong Server");

  // In ra dia chi IP
  Serial.println(WiFi.localIP());
  
 
}
void loop(void){
  server.handleClient();          //Handle client requests
}

void handleRoot()
{
  String s = MAIN_page; //Doc trang HTML
  server.send(200, "text/html", s); // Gui HTML den client
}

void temperature()
{
temp = dht.readTemperature();
//  if(temp == tempOld){}
//  else
//  {tempOld = temp;
   server.send(200, "text/plane", String(temp));
    
//  }
}

void humidity()
{
  humi = dht.readHumidity();
//  if(humi == humiOld){}
//  else{
//    humiOld = humi;
    server.send(200, "text/plane", String(humi));
//    }
}
void ledControl()
{
    tus = digitalRead(output_pin);
    if(tus== LOW)
    {
      trangthai = "OFF";
      digitalWrite(output_pin, 1);
    }
    else
    {
      trangthai = "ON";
      digitalWrite(output_pin, 0);
    }
    server.send(200, "text/plane", trangthai);
}
