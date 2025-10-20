#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"

// Usando configurações do arquivo config.h (protegido pelo .gitignore)
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* mqtt_server = MQTT_SERVER;
const int mqtt_port = MQTT_PORT;
const char* mqtt_user = MQTT_USER;
const char* mqtt_password = MQTT_PASSWORD;
const char* mqtt_topic = MQTT_TOPIC;

WiFiClient espClient;
PubSubClient client(espClient);
String inputBuffer = "";

void setup_wifi() {
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < WIFI_TIMEOUT) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFalha ao conectar no WiFi.");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect(MQTT_CLIENT_ID, mqtt_user, mqtt_password)) {
      Serial.println(" conectado!");
    } else {
      Serial.print(" falhou, rc=");
      Serial.print(client.state());
      Serial.println(" — tentando novamente em 5 segundos...");
      delay(MQTT_RECONNECT_DELAY);
    }
  }
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Iniciando ESP8266...");
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      inputBuffer.trim();
      if (inputBuffer.startsWith("{") && inputBuffer.endsWith("}")) {
        Serial.println("Enviando JSON para MQTT: " + inputBuffer);
        client.publish(mqtt_topic, inputBuffer.c_str());
      } else {
        Serial.println("JSON inválido: " + inputBuffer);
      }
      inputBuffer = "";
    } else {
      inputBuffer += c;
    }
  }
}
