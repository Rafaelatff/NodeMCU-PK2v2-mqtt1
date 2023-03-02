#include <ESP8266WiFi.h>
#include "AdafruitIO_WiFi.h"

// Wifi configuration
//const char ssid[] = "CYBERDYNE";
//const char senha[] = "put your pass here";
#define WIFI_SSID "CYBERDYNE"
#define WIFI_PASS "put your pass here"

// Server configuration
WiFiServer server_name(80); // IP:door -> IP:80

// MQTT configuration
#define IO_USERNAME  "rafaelatff"
#define IO_KEY       "aio_UAkf55Pa0KIsF7esrlMiX46tJaWa" // changed from yesterday

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#define greenLED D4

// Topic configuration "rafaelatff/feeds/greenLED"
AdafruitIO_Feed *feed_greenLED = io.feed("greenLED");

// const byte LED_Green = D4;
// const byte greenLED = 2;  // the three can be used, 2 (gpio), D4 (board) and #define
const byte yellowLED = D7;
const byte redLED = D3;
const byte tecla = D0;
#define LDR A0

boolean statusGreenLED = LOW;
boolean statusYellowLED = LOW;
boolean statusRedLED = LOW;

void thingsConfig();
void networkConfig();
void brokerConnection();

void setup() {
  // put your setup code here, to run once:

  // PK2v2 and other things function configuration
  thingsConfig();

  // Configura serial para monitorar conexão via terminal
  Serial.begin(74880);
  delay(100);

  // Network configuration
  networkConfig();

  // Server configuration
  brokerConnection();
}

void loop() {
  // put your main code here, to run repeatedly:
  // check message
  byte state = io.run();

  // check connection
  if(state == AIO_NET_DISCONNECTED | state == AIO_DISCONNECTED){
    brokerConnection(); // if disconnected, connect again
  }
}
// Handler for the greenLED
void handle_greenLED(AdafruitIO_Data *data) {

  // Message
  Serial.print("Data  <- ");
  Serial.print(data->feedName());
  Serial.print(" : ");
  Serial.println(data->value());

  // Write greenLED output
  if(data->isTrue()) digitalWrite(greenLED, HIGH);
  else digitalWrite(greenLED, LOW);
}

void networkConfig(){
  Serial.print("\r\n"); // new line and carriage return
  Serial.print("Connecting to the network ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" ");
  Serial.println("WiFi Connected");
  Serial.println("IP Address:");
  Serial.println(WiFi.localIP());
}

void thingsConfig(){
  // Digital output configuration
  pinMode(greenLED,OUTPUT);
  pinMode(yellowLED,OUTPUT);
  pinMode(redLED,OUTPUT);

  // Digital input configuration
  pinMode(tecla,INPUT); // 10k pull-up
}

void brokerConnection(){
  Serial.print("Connecting to Adafruit IO");

  // Call the connection to io.adafruit.com
  io.connect();

  // call a handler to receibe the message of the greenLED
  feed_greenLED->onMessage(handle_greenLED);

  // Wait for connection to be completed
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // Connected
  Serial.println('\r');
  Serial.println(io.statusText());

  // Update feed status
  feed_greenLED->get();
}
