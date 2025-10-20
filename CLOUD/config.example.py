# config.example.py - Template de configuração Python
# 
# INSTRUÇÕES:
# 1. Copie este arquivo para 'config.py'
# 2. Preencha com suas credenciais reais
# 3. O arquivo 'config.py' não será commitado (protegido pelo .gitignore)

import os

# =================== CONFIGURAÇÕES FIREBASE ===================
FIREBASE_CRED_PATH = 'firebase-key/sua-chave-firebase.json'

# =================== CONFIGURAÇÕES MQTT ===================
MQTT_BROKER = "seu.broker.mqtt.com"
MQTT_PORT = 1883
MQTT_USERNAME = "seu_usuario_mqtt"
MQTT_PASSWORD = "sua_senha_mqtt"
MQTT_TOPIC = "iot/data"

# =================== CONFIGURAÇÕES DE AMBIENTE ===================
# Alternativamente, use variáveis de ambiente:
# FIREBASE_CRED_PATH = os.getenv('FIREBASE_CRED_PATH', 'firebase-key/default.json')
# MQTT_BROKER = os.getenv('MQTT_BROKER', 'localhost')
# MQTT_PORT = int(os.getenv('MQTT_PORT', 1883))
# MQTT_USERNAME = os.getenv('MQTT_USERNAME')
# MQTT_PASSWORD = os.getenv('MQTT_PASSWORD')
# MQTT_TOPIC = os.getenv('MQTT_TOPIC', 'iot/data')

# =================== CONFIGURAÇÕES DE LOG ===================
LOG_LEVEL = "INFO"
LOG_FILE = "logs/consumer.log"

# =================== CONFIGURAÇÕES DE BANCO ===================
FIRESTORE_COLLECTION = "sensor_data"