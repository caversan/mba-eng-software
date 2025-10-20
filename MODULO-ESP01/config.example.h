/*
 * Template de configuração para o módulo ESP01
 * 
 * INSTRUÇÕES:
 * 1. Copie este arquivo para 'config.h'
 * 2. Preencha com suas credenciais reais
 * 3. O arquivo 'config.h' não será commitado (protegido pelo .gitignore)
 */

#ifndef CONFIG_H
#define CONFIG_H

// =================== CONFIGURAÇÕES WiFi ===================
#define WIFI_SSID "SUA_REDE_WIFI"
#define WIFI_PASSWORD "SUA_SENHA_WIFI"

// =================== CONFIGURAÇÕES MQTT ===================
#define MQTT_SERVER "seu.broker.mqtt.com"
#define MQTT_PORT 1883
#define MQTT_USER "seu_usuario_mqtt"
#define MQTT_PASSWORD "sua_senha_mqtt"
#define MQTT_TOPIC "iot/data"
#define MQTT_CLIENT_ID "ESP8266Client"

// =================== CONFIGURAÇÕES DE CONEXÃO ===================
#define WIFI_TIMEOUT 15000  // 15 segundos timeout WiFi
#define MQTT_RECONNECT_DELAY 5000  // 5 segundos entre tentativas MQTT

#endif // CONFIG_H