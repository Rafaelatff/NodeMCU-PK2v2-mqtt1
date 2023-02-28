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

To get the credencials, just click on the key simbol and copy the Arduino lines:

![image](https://user-images.githubusercontent.com/58916022/221730721-5d9f7d82-ca9b-4ace-ab3c-e60a94d6d6ac.png)

```c
#define IO_USERNAME  "rafaelatff"
#define IO_KEY       "aio_ldNH891Nwiwcw2IaiJPyYfhdvaEo"
```
