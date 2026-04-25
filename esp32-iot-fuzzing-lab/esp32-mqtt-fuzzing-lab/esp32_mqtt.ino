#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* mqtt_server = "your_MQTT_BROKER_IP";

WiFiClient espClient;
PubSubClient client(espClient);


// WiFi connection
void setup_wifi() {

  delay(10);
  Serial.println("Connecting to WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");

  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
}


// MQTT message handler
void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message received (length=");
  Serial.print(length);
  Serial.print("): ");

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();

  // Detect abnormal payload size
  if(length > 120){
    Serial.println("WARNING: Large malformed payload detected!");
  }

  // Detect possible overflow attempt
  if(length > 200){
    Serial.println("ALERT: Potential overflow attempt detected!");
  }

}


// MQTT reconnect logic
void reconnect() {

  while (!client.connected()) {

    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP32Client")) {

      Serial.println("MQTT Connected");

      client.subscribe("test/topic");

    } else {

      Serial.print("MQTT Failed, state=");
      Serial.println(client.state());

      delay(2000);

    }
  }
}


// Initial setup
void setup() {

  Serial.begin(115200);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}


// Main loop
void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

}