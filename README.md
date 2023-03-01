# NodeMCU-PK2v2-mqtt1
Writting first code lines using NodeMCU and MQTT (Message Queue Telemetry Transport).

Comunicação assincrona, com payload menor do que o que fizemos com servidor. This is a follow up from the content of [server-html1](https://github.com/Rafaelatff/NodeMCU-PK2v2-server-html1) studies using ESP8266.

In MQTT we have:

* Broker.
* Clients (can publish and subscribe to topics).
* QoS0, QoS1 and QoS2.

## MQTT Adafruit server

We will be using the MQTT from [Adafruit](https://accounts.adafruit.com/users/sign_in), that is free at the moment of our project creation.

It looks that we will have problems, but lets go on.

![image](https://user-images.githubusercontent.com/58916022/221728280-bfc0129a-76b8-4172-8b77-75a649fbe672.png)

In 'Feed' we will be creating a feed for the green LED of PK2v2.

![image](https://user-images.githubusercontent.com/58916022/221729277-c1e28b28-71c1-44fd-96b1-5db0340fb96f.png)

The in 'Dashboard' we will be creating our visualization dashboard, with the name of PK2v2.

![image](https://user-images.githubusercontent.com/58916022/221729516-8b1bb3ca-d447-4d5c-a9a0-ffc7538cb330.png)

Then lets create the green LED image on dashboard:

![image](https://user-images.githubusercontent.com/58916022/221731249-465f11c4-d0fe-4f23-9c54-45c5a143d660.png)

We will be using the indicator:

![image](https://user-images.githubusercontent.com/58916022/221731461-221491aa-6d6d-47d2-a87b-84b16d4d4155.png)

Connect it to the LED:

![image](https://user-images.githubusercontent.com/58916022/221731555-d04d6328-43a2-48f9-8584-4b5fbc476f9a.png)

And we will add the condition for ON and OFF, and the color for both conditions:

![image](https://user-images.githubusercontent.com/58916022/221731801-758943ca-9f33-4ca0-80d0-cee321c79811.png)

## Code

To get the credencials, just click on the key simbol and copy the Arduino lines:

![image](https://user-images.githubusercontent.com/58916022/221730721-5d9f7d82-ca9b-4ace-ab3c-e60a94d6d6ac.png)

```c
#define IO_USERNAME  "rafaelatff"
#define IO_KEY       "aio_ldNH891Nwiwcw2IaiJPyYfhdvaEo"
```
Then install de adafruit lib for arduino:

![image](https://user-images.githubusercontent.com/58916022/222023860-c0e8c6ec-54d5-4490-b8f6-c9f3585c92da.png)

The Adafruit MQTT lib will also be installed together:

![image](https://user-images.githubusercontent.com/58916022/222024069-fe9ac340-9b0a-4145-82d5-dec581e73792.png)

Then, we add the lib and some macros:

```c
#include "AdafruitIO_WiFi.h"

#define WIFI_SSID "CYBERDYNE"
#define WIFI_PASS "password here"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#define greenLED D4

// Topic configuration "rafaelatff/feeds/greenLED"
AdafruitIO_Feed *feed_greenLED = io.feed("greenLED");
```

In 'setup ()' we configure serial, WiFi coonection, things (greenLED) and we call:

```c
brokerConnection();
```

This function brokerConnection() may need connection later, that is why we kept as a function.

```c
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
```

Then, in 'loop()'we just:

```c
void loop() {
  // put your main code here, to run repeatedly:
  // check message
  byte state = io.run();

  // check connection
  if(state == AIO_NET_DISCONNECTED | state == AIO_DISCONNECTED){
    brokerConnection(); // if disconnected, connect again
  }
}
```

All this code will call a handler function, so here it is:

```c
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
```

## First results

The serial monitor showed the following information:

![image](https://user-images.githubusercontent.com/58916022/222031663-4836b9dd-e4af-4fb3-9570-92b94b48f2b8.png)

And then <3 :

![WhatsApp Video 2023-02-28 at 23 53 38](https://user-images.githubusercontent.com/58916022/222033546-28acb1f9-c7d9-428a-b5d2-b49191ae1f20.gif)

