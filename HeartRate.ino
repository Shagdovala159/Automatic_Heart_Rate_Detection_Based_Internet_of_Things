#include <ESP8266WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = "";   // your network SSID (name) 
char pass[] = "";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = ;
const char * myWriteAPIKey = "";

long int beatCount = 0; 
int lastbeat; 
const int sensor = 4; 
const int pinBuzzer = 2; 

unsigned long startMillis; 
unsigned long currentMillis; 
const unsigned long period = 60000; 

int number = 0;

void setup() {
  Serial.begin(9600);  // Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(sensor,INPUT); 
  pinMode(pinBuzzer, OUTPUT); 
  startMillis = millis(); 
  lastbeat = beatCount; 
  delay(10);
  Serial.println("Connected");
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
      digitalWrite(pinBuzzer, HIGH);
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println("!");
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  if(digitalRead(sensor)== HIGH)
  {
    lastbeat = beatCount;
    beatCount++;
    if(lastbeat != beatCount)
    {
    digitalWrite(pinBuzzer, LOW);
    delay(50);
    digitalWrite(pinBuzzer, HIGH);
    }
    Serial.println(beatCount);
    delay(50);
  }
  currentMillis = millis();
  if (currentMillis - startMillis >= period)
  {
  Serial.print("Jumlah 1 menit : ");
  Serial.println(beatCount);
    startMillis = currentMillis;
    int x = ThingSpeak.writeField(myChannelNumber, 1, beatCount, myWriteAPIKey);
    digitalWrite(pinBuzzer, LOW);
    delay(100);
    digitalWrite(pinBuzzer, HIGH);
    delay(100);
    digitalWrite(pinBuzzer, LOW);
    delay(100);
    digitalWrite(pinBuzzer, HIGH);
    delay(100);
    digitalWrite(pinBuzzer, LOW);
    delay(100);
    digitalWrite(pinBuzzer, HIGH);
      if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
    delay(10);
    beatCount = 0;
  }
}
