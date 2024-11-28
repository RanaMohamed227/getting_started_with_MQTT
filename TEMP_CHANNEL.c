#include "ThingSpeak.h"  // Include the ThingSpeak library to send data to the ThingSpeak IoT platform.
#include <esp_now.h>      // Include ESP-NOW library for wireless communication (not used in this code).
#include <WiFi.h>         // Include WiFi library to enable WiFi functionality.
#include "DHT.h"          // Include DHT library for reading temperature and humidity from the DHT sensor.
#include "Adafruit_Sensor.h" // Include Adafruit sensor library (used by DHT library for advanced sensor features).

#define DHTPIN 27         // Define the GPIO pin (pin 27) connected to the DHT sensor data pin.
#define DHTTYPE DHT11     // Specify the type of DHT sensor (DHT11 in this case).

// WiFi credentials
const char* ssid = "Wokwi-GUEST"; // Default SSID provided by the Wokwi simulation environment.
const char* password = "";        // Default WiFi network in Wokwi does not require a password.

DHT dht(DHTPIN, DHTTYPE); // Create an instance of the DHT class to interact with the sensor.

WiFiClient client;        // Create a WiFi client object for ThingSpeak communication.
float Humidity;           // Variable to hold humidity value.
float Temperature;        // Variable to hold temperature value in Celsius.
float Heat_Index;         // Variable to hold the computed heat index value.

unsigned long myChannelNumber = 2768085; // ThingSpeak channel number for data storage.
const char* myWriteAPIKey = "HEDL0L9VCVZUA4RX"; // API key to authenticate with ThingSpeak.

// Pin configuration
int q1 = 25;              // Define pin 25 for additional functionality (unused in the code).

// Setup function (runs once when the device starts)
void setup() {
  Serial.begin(115200);   // Start serial communication for debugging at 115200 baud rate.
  pinMode(q1, OUTPUT);    // Configure pin `q1` as an output pin (not actively used in this code).

  WiFi.mode(WIFI_STA);    // Set the ESP32 to WiFi Station mode (client mode for connecting to a network).
  dht.begin();            // Initialize the DHT sensor for reading temperature and humidity.
  ThingSpeak.begin(client); // Initialize the ThingSpeak library for data transmission.
}

// Main loop function (runs repeatedly after setup completes)
void loop() {
  // Check if the device is connected to WiFi
  if (WiFi.status() != WL_CONNECTED) { // If WiFi is not connected:
    Serial.print("Attempting to connect"); // Print a message indicating connection attempts.
    while (WiFi.status() != WL_CONNECTED) { // Retry connection until successful.
      WiFi.begin(ssid, password);           // Attempt to connect to the specified WiFi network.
      delay(5000);                          // Wait for 5 seconds before retrying.
    }
    Serial.println("\nConnected.");         // Once connected, print a success message.
  }

  // Read humidity and temperature data from the DHT sensor
  float h = dht.readHumidity();            // Read the current humidity value.
  float t = dht.readTemperature();         // Read temperature in Celsius.
  float f = dht.readTemperature(true);     // Read temperature in Fahrenheit.

  // Check if the sensor reading is valid
  if (isnan(h) || isnan(t) || isnan(f)) {  // If any value is NaN (Not a Number), it indicates a failed read.
    Serial.println(F("Failed to read from DHT sensor!")); // Print an error message.
    return;                                // Exit the loop iteration and try again next time.
  }

  // Calculate the heat index
  float hif = dht.computeHeatIndex(f, h);         // Calculate heat index in Fahrenheit using temperature and humidity.
  float hic = dht.computeHeatIndex(t, h, false);  // Calculate heat index in Celsius (set `isFahrenheit` to false).

  // Print the sensor data and calculated values to the Serial Monitor
  Serial.print(F("Humidity: "));
  Serial.print(h);              // Print the humidity value.
  Serial.print(F("%  Temperature: "));
  Serial.print(t);              // Print temperature in Celsius.
  Serial.print(F("°C "));
  Serial.print(f);              // Print temperature in Fahrenheit.
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);            // Print heat index in Celsius.
  Serial.print(F("°C "));
  Serial.print(hif);            // Print heat index in Fahrenheit.
  Serial.println(F("°F"));

  // Send the collected data to ThingSpeak
  ThingSpeak.setField(1, h);   // Set ThingSpeak Field 1 to the humidity value.
  ThingSpeak.setField(2, t);   // Set ThingSpeak Field 2 to the temperature in Celsius.
  ThingSpeak.setField(3, f);   // Set ThingSpeak Field 3 to the temperature in Fahrenheit.

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); // Send data to ThingSpeak and store the response.

  // Check if the data update was successful
  if (x == 200) {              // HTTP 200 response code indicates a successful update.
    Serial.println("Channel update successful."); // Print a success message.
    Serial.print("Humidity = ");
    Serial.println(h);         // Print the updated humidity value.
    Serial.print("Temperature = ");
    Serial.println(t);         // Print the updated temperature in Celsius.
    Serial.print("Heat Index = ");
    Serial.println(f);         // Print the updated temperature in Fahrenheit.
  } else {
    // Uncomment the following line for debugging in case of failure.
    // Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(2000); // Wait for 2 seconds before starting the next iteration.
}
