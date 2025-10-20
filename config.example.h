/*
 * Arquivo de exemplo para configurações sensíveis
 * 
 * IMPORTANTE: Este é um arquivo de EXEMPLO
 * Copie este arquivo para 'config.h' e preencha com suas credenciais reais
 * O arquivo 'config.h' está no .gitignore e não será commitado
 * 
 * Uso: #include "config.h" no seu código principal
 */

#ifndef CONFIG_EXAMPLE_H
#define CONFIG_EXAMPLE_H

// =================== CONFIGURAÇÕES WiFi ===================
// Substitua pelos dados da sua rede WiFi
#define WIFI_SSID "SUA_REDE_WIFI"
#define WIFI_PASSWORD "SUA_SENHA_WIFI"

// =================== CONFIGURAÇÕES MQTT ===================
// Substitua pelos dados do seu broker MQTT
#define MQTT_SERVER "seu.broker.mqtt.com"
#define MQTT_PORT 1883
#define MQTT_USER "seu_usuario_mqtt"
#define MQTT_PASSWORD "sua_senha_mqtt"
#define MQTT_CLIENT_ID "seu_client_id_unico"

// Tópicos MQTT (ajuste conforme necessário)
#define MQTT_TOPIC_TELEMETRY "casa/energia/telemetria"
#define MQTT_TOPIC_CONFIG "casa/energia/config"
#define MQTT_TOPIC_STATUS "casa/energia/status"

// =================== CONFIGURAÇÕES API ===================
// Se usar APIs externas
#define API_KEY "sua_chave_da_api"
#define API_ENDPOINT "https://api.exemplo.com"

// =================== CONFIGURAÇÕES DE SEGURANÇA ===================
// Chaves de criptografia (se implementada)
#define ENCRYPTION_KEY "sua_chave_de_32_caracteres_aqui"

// =================== CONFIGURAÇÕES OTA ===================
// Para atualizações remotas (Over The Air)
#define OTA_PASSWORD "senha_para_ota_updates"

// =================== CONFIGURAÇÕES THINGSPEAK ===================
// Se usar ThingSpeak para IoT
#define THINGSPEAK_API_KEY "sua_api_key_thingspeak"
#define THINGSPEAK_CHANNEL_ID 123456

// =================== CONFIGURAÇÕES BLYNK ===================
// Se usar plataforma Blynk
#define BLYNK_AUTH_TOKEN "seu_token_blynk"

#endif // CONFIG_EXAMPLE_H