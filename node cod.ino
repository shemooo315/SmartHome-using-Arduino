#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h> 
#include <Servo.h>

#define BEDLED D0 
#define LIVLED D1
#define BATHLED D2
#define GLED D3
#define KITLED D4

#define gServoPin D6
#define dServoPin D7

Servo gServo;
Servo dServo;

const char *ssid = "T23MCU"; // Enter SSID here 
const char *password = "12345678"; // Enter Password here 

bool GLEDState = LOW; 
bool LIVLEDState = LOW; 
bool BATHLEDState = LOW; 
bool BEDLEDState = LOW; 
bool KITLEDState = LOW;
 
ESP8266WebServer server(80); 

void setup()  {
  Serial.begin(115200); 
  pinMode(GLED, OUTPUT);
  pinMode(LIVLED, OUTPUT);
  pinMode(BEDLED, OUTPUT);
  pinMode(BATHLED, OUTPUT);
  pinMode(KITLED, OUTPUT); 

  gServo.attach(gServoPin);
  gServo.write(0);
  dServo.attach(dServoPin);
  dServo.write(0);
  
  WiFi.softAP(ssid, password); 
  IPAddress IP = WiFi.softAPIP(); 
  Serial.print("AP IP address: "); 
  Serial.println(IP); 
  //server.on("/", handleGOn);   
  server.on("/GLEDON", handleGOn); 
  server.on("/GLEDOFF", handleGOff);
  server.on("/LIVLEDON", handleLIVOn); 
  server.on("/LIVLEDOFF", handleLIVOff);
  server.on("/BATHLEDON", handleBATHOn); 
  server.on("/BATHLEDOFF", handleBATHOff);
  server.on("/BEDLEDON", handleBEDOn); 
  server.on("/BEDLEDOFF", handleBEDOff);
  server.on("/KITLEDON", handleKITOn); 
  server.on("/KITLEDOFF", handleKITOff); 
  
  server.on("/GDOORON", handleGDOOROn); 
  server.on("/GDOOROFF", handleGDOOROff); 
  server.on("/MDOORON", handleMDOOROn); 
  server.on("/MDOOROFF", handleMDOOROff); 
  
  server.onNotFound(handleNotFound); 
  server.begin(); 
  Serial.println("HTTP server started"); 
}

void loop() {
  server.handleClient(); 
  digitalWrite(GLED, GLEDState); 
  digitalWrite(LIVLED, LIVLEDState); 
  digitalWrite(BEDLED, BEDLEDState); 
  digitalWrite(BATHLED, BATHLEDState); 
  digitalWrite(KITLED, KITLEDState); 
}
void handleGOn() {
  GLEDState = HIGH; 
  Serial.println ("GARAGE LED Status: ON"); 
  server.send(200, "text/plain", "GARAGE LED Status: ON"); 
}
void handleGOff() { 
  GLEDState = LOW; 
  Serial.println("GARAGE LED Status: OFF"); 
  server.send(200, "text/plain", "GARAGE LED Status: OFF"); 
} 

void handleLIVOn() {
  LIVLEDState = HIGH; 
  Serial.println ("LIVING LED Status: ON"); 
  server.send(200, "text/plain", "LIVING LED Status: ON"); 
}
void handleLIVOff() { 
  LIVLEDState = LOW; 
  Serial.println("LIVING LED Status: OFF"); 
  server.send(200, "text/plain", "LIVING LED Status: OFF"); 
} 

void handleBEDOn() {
  BEDLEDState = HIGH; 
  Serial.println ("BED LED Status: ON"); 
  server.send(200, "text/plain", "BED LED Status: ON"); 
}
void handleBEDOff() { 
  BEDLEDState = LOW; 
  Serial.println("BED LED Status: OFF"); 
  server.send(200, "text/plain", "BED LED Status: OFF"); 
} 

void handleBATHOn() {
  BATHLEDState = HIGH; 
  Serial.println ("BATH LED Status: ON"); 
  server.send(200, "text/plain", "BATH LED Status: ON"); 
}
void handleBATHOff() { 
  BATHLEDState = LOW; 
  Serial.println("BATH LED Status: OFF"); 
  server.send(200, "text/plain", "BATH LED Status: OFF"); 
} 

void handleKITOn() {
  KITLEDState = HIGH; 
  Serial.println ("KITCHEN LED Status: ON"); 
  server.send(200, "text/plain", "KITCHEN LED Status: ON"); 
}
void handleKITOff() { 
  KITLEDState = LOW; 
  Serial.println("KITCHEN LED Status: OFF"); 
  server.send(200, "text/plain", "KITCHEN LED Status: OFF"); 
} 

void handleGDOOROn() { 
  gServo.write(90);
   Serial.println("GARAGE DOOR Status: ON"); 
  server.send(200, "text/plain", "GARAGE DOOR Status: ON"); 

} 
void handleGDOOROff() { 
  gServo.write(0);
  Serial.println("GARAGE DOOR Status: OFF"); 
  server.send(200, "text/plain", "GARAGE DOOR Status: OFF"); 

} 
void handleMDOOROn() { 
  dServo.write(90);
  Serial.println("MAIN DOOR Status: ON"); 
  server.send(200, "text/plain", "MAIN DOOR Status: ON"); 

} 
void handleMDOOROff() { 
  //close main door servo
  dServo.write(0);
  Serial.println("MAIN DOOR Status: OFF"); 
  server.send(200, "text/plain", "MAIN DOOR Status: OFF"); 

} 

void handleNotFound() {
  server.send(404, "text/plain", "Not found"); 
}