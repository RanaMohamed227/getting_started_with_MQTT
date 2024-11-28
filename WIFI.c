#include <WiFi.h>
#include <PubSubClient.h>

// WiFi Credentials
const char* ssid = "Wokwi-GUEST"; // iam using the default wifi in thw wokwi website 
const char* password = ""; // the default wifi network in the website does not have a password 

const char* mqttServer = "test.mosquitto.org"; //using the broker mosquito to publish messages and subscribe into it 
const int mqttPort = 1883;  //unsecured port of mqtt 
const char* mqttUser = ""; // leaving it empty so i can use all on the ip address
const char* mqttPassword = ""; // no initialized password 

int ValueToSend;
#define ADCpin 36   //pin for PIR potentiometer sensor 
#define LED 26    //built-in LED is pin 2

WiFiClient espClient; //establishing client on esp32
PubSubClient client(espClient); //publish through this client

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud rate (ESP: Sets up UART0 for debugging or serial communication with the computer).
  WiFi.begin(ssid, password); // start the wifi using the credentials given above 

  while (WiFi.status() != WL_CONNECTED) // check if the wifi is connected 
  {
    delay(1000);
    Serial.println("Connecting to WiFi..."); // print these messages in the console telling that the wifi is still connecting and delay 
  }
  Serial.println("Connected to WiFi"); // if i escaped the above loop then this means i am now connected so print in the console that its connected

  client.setServer(mqttServer, mqttPort); //set the mqtt broker or server by the info given above 
  client.setCallback(callback); // send to the broker or publish it the callback or msg or data

  while (!client.connected()) {
    Serial.println("Connecting to MQTT..."); // this is the stage where i want to publish the info so i am waiting to make sure that i am connected 
    
    if (client.connect("userid")) {  
   // connect  using the userid 
   //user id must be unique in case of many users under one topic to avoid conflict/crosstalk information
   
      Serial.println("Connected to MQTT"); // finally connected 
      client.subscribe("LED");            //SUBSCRIBE TOPIC--> LED on or off 

    } else {
// if its not connected print the message failed state
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }
  
  pinMode(LED, OUTPUT);// Set GPIO 26 as an output pin (ESP: Configures pin 26 to send digital signals to control external components like an LED).
}
}

void loop() 
{
  int ADC = analogRead(ADCpin); //initialize an integer value with the potentiometer pin of the sensor 
  ValueToSend = map(ADC,0,4095,0,100); // map these value so the most it can reach is 100 not 4095 , unit is volt
  Serial.println(ValueToSend); // publish the reading of the pir 
  char payload[10]; // buffer array size is proportional to message that wanted to be sent
  snprintf(payload, sizeof(payload), "%d", ValueToSend); //print the value in the console
  client.publish("pubtopic", payload);    //PUBLISH TOPIC 
  
  // Printing message value on Serial Monitor and waiting
  client.loop();
  Serial.println();
  delay(1000);   //adjust interval
}

// this function manages the data sent to the broker 

void callback(String topic, byte* payload, unsigned int length) {
  Serial.println();
  Serial.print("Message received on topic: "); // print the message sent to the console
  Serial.println(topic); // print topic 
  Serial.println("Message: "); // print message 
  String msg; 

  if (topic == "LED"){ // if the topic is LED then subscribe to the message
// loop on the message to be printed in an array called payload 

    for (int i = 0; i < length; i++) {
      //Serial.print((char)payload[i]);
      msg += (char)payload[i];
    }
    Serial.println(msg);
    Serial.print("LED status: ");
// if the message is ON then make the led high in the schematic this info is from the switch in the node red
    if (msg == "ON"){ 
      digitalWrite(LED, HIGH);
      Serial.println("ON"); 
    }

// if the message is OFF then make the led LOW in the schematic this info is from the switch in the node red
    else if (msg == "OFF"){ 

      digitalWrite(LED, LOW);
      Serial.println("OFF");
    }
  }
  Serial.println();
  delay(1000);   //adjust interval
}
