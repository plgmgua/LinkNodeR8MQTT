#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <functional>
#include "switch.h"


 
// Connect to the WiFi
const char* ssid = "EL_MUNDO_DE_SOFIA";
const char* password = "XXXXXXX";
const char* mqttServer = "192.168.8.2";
const int mqttPort = 1883;

 
WiFiClient espClient;
PubSubClient client(espClient);

// Set Relay Pins
int relayOne = 4;
int relayTwo = 5;
int relayThree = 12;
int relayFour = 13;
int relayFive = 14;
int relaySix = 15;
int relaySeven = 16;
 
void setup() {
   Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
   while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
     if (client.connect("ESP8266Client" )) {
       Serial.println("connected");  
    } else {
       Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
     }
    //Set relay pins to outputs
       pinMode(4,OUTPUT);
       pinMode(5,OUTPUT);
       pinMode(12,OUTPUT); 
       pinMode(13,OUTPUT);
       pinMode(14,OUTPUT);
       pinMode(15,OUTPUT);
       pinMode(16,OUTPUT); 
       client.publish("secondfloor/status", "pinMode=Set");
  }
        client.subscribe("secondfloor/cmd");
        client.publish("secondfloor/status", "Rx8_ON");
}
 
void callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic,"secondfloor/cmd")==0) {
    payload[length] = '\0'; // Null terminator used to terminate the char array
    String message = (char*)payload;
    if (message == "r1on") {
        digitalWrite(relayOne, HIGH);   // sets relayOne on 
        client.publish("secondfloor/status", "R1 is On"); 
    }
    if (message == "r1off") {
        digitalWrite(relayOne, LOW);   // sets relayOne off 
        client.publish("secondfloor/status", "R1 is Off"); 
    }
    if (message == "r2on") {
        digitalWrite(relayTwo, HIGH);   // sets relayTwo on 
        client.publish("secondfloor/status", "R2 is On"); 
    }
    if (message == "r2off") {
        digitalWrite(relayTwo, LOW);   // sets relayTwoe off 
        client.publish("secondfloor/status", "R2 is Off"); 
    }
    if (message == "r3on") {
        digitalWrite(relayThree, HIGH);   // sets relayThree on 
        client.publish("secondfloor/status", "R3 is On"); 
    }
    if (message == "r3off") {
        digitalWrite(relayThree, LOW);   // sets relayOne on 
        client.publish("secondfloor/status", "R3 is Off"); 
    }
    if (message == "r4on") {
        digitalWrite(relayFour, HIGH);   // sets relayFour on 
        client.publish("secondfloor/status", "R4 is On"); 
    }
    if (message == "r4off") {
        digitalWrite(relayFour, LOW);   // sets relayFour on 
        client.publish("secondfloor/status", "R4 is Off"); 
    }
    if (message == "r5on") {
        digitalWrite(relayFive, HIGH);   // sets relayFive on 
        client.publish("secondfloor/status", "R5 is On"); 
    }
    if (message == "r5off") {
        digitalWrite(relayFive, LOW);   // sets relayFive off 
        client.publish("secondfloor/status", "R5 is Off"); 
    }
    if (message == "r6on") {
        digitalWrite(relaySix, HIGH);   // sets relaySix on 
        client.publish("secondfloor/status", "R6 is On"); 
    }
    if (message == "r6off") {
        digitalWrite(relaySix, LOW);   // sets relaySix off 
        client.publish("secondfloor/status", "R6 is Off"); 
    }
    if (message == "r7on") {
        digitalWrite(relaySeven, HIGH);   // sets relaySeven on 
        client.publish("secondfloor/status", "R7 is On"); 
    }
    if (message == "r7off") {
        digitalWrite(relaySeven, LOW);   // sets relaySeven on 
        client.publish("secondfloor/status", "R7 is Off"); 
    }
 
  }
   
 }
 
void loop() {
  client.loop();
 }
