# 🌩️ CLOUD - Infraestrutura e Serviços IoT

## 🚨 **ATENÇÃO CRÍTICA DE SEGURANÇA** 🚨

**Esta pasta continha informações extremamente sensíveis que foram PROTEGIDAS:**

### 🔐 **Dados Críticos Protegidos:**

1. **🔥 Firebase Service Account** - Chave privada do Admin SDK
2. **🔑 Chaves SSH** - Acesso aos servidores Oracle Cloud  
3. **📡 Credenciais MQTT** - Broker CloudAMQP
4. **💾 Backups de Banco** - 89k+ registros de telemetria IoT

**✅ TODOS OS DADOS SENSÍVEIS FORAM MOVIDOS PARA ARQUIVOS PROTEGIDOS PELO .GITIGNORE**

---

## 📁 Estrutura da Pasta CLOUD

### 🔧 **iot-consumer/**
Consumer Python para bridge MQTT → Firebase
- **`consumer-secure.py`** ✅ Versão segura (usa config.py)
- **`consumer.py`** ❌ Versão original (com credenciais expostas)

### 🔑 **firebase-key/**
Credenciais e backups do Firebase
- **`firebase-serviceaccount.example.json`** ✅ Template público
- **`caversan-iot-db-firebase-adminsdk-*.json`** 🛡️ PROTEGIDO
- **`bkp-database/`** 🛡️ PROTEGIDO

### 🖥️ **ssh-oracle/**
Chaves SSH para servidores Oracle Cloud
- **`README-SSH-SECURITY.md`** ✅ Orientações de segurança
- **`ssh-key-2025-04-22.key.pub`** 🛡️ PROTEGIDO

### 🧪 **teste-vsmqtt/** & **presence-sensor-debug/**
Scripts de teste e depuração

---

## 🛠️ **Configuração Segura**

### 1. **Setup do Consumer Python:**

```bash
# 1. Instalar dependências
cd CLOUD
pip install -r requirements.txt

# 2. Configurar credenciais
cp config.example.py config.py
# Edite config.py com suas credenciais

# 3. Configurar Firebase
cp firebase-key/firebase-serviceaccount.example.json firebase-key/sua-chave.json
# Substitua com sua chave real do Firebase

# 4. Executar consumer seguro
python iot-consumer/consumer-secure.py
```

### 2. **Variáveis de Ambiente (Produção):**

```bash
# Definir variáveis de ambiente
export FIREBASE_CRED_PATH="/path/to/firebase-key.json"
export MQTT_BROKER="seu.broker.mqtt.com"
export MQTT_USERNAME="seu_usuario"
export MQTT_PASSWORD="sua_senha"
export MQTT_TOPIC="iot/data"

# Executar consumer
python iot-consumer/consumer-secure.py
```

---

## 🔒 **Políticas de Segurança Implementadas**

### ✅ **Proteções Ativas:**
- 🛡️ Credenciais Firebase protegidas pelo .gitignore
- 🛡️ Chaves SSH removidas do repositório
- 🛡️ Backups de banco protegidos
- 🛡️ Scripts refatorados para usar configuração externa
- 🛡️ Templates públicos para orientação

### 📋 **Checklist de Segurança:**
- [ ] Arquivo `config.py` configurado e não commitado
- [ ] Chave Firebase real colocada e protegida
- [ ] Variáveis de ambiente configuradas (produção)
- [ ] Chaves SSH regeneradas se necessário
- [ ] Backups movidos para storage seguro
- [ ] Credenciais antigas revogadas se expostas

---

## 🏗️ **Arquitetura do Sistema**

```
Arduino/ESP01 → MQTT Broker → Python Consumer → Firebase Firestore
     ↓              ↓              ↓              ↓
 Sensores IoT   CloudAMQP    Servidor Linux   Cloud Database
```

### 📊 **Fluxo de Dados:**
1. **Sensores** coletam dados (tensão, corrente, presença, luz)
2. **ESP01** envia JSON via MQTT para CloudAMQP
3. **Consumer Python** processa e valida dados
4. **Firebase Firestore** armazena dados para análise
5. **Dashboards** visualizam dados em tempo real

---

## 🚨 **Incidentes de Segurança**

### ✅ **Corrigidos:**
- **2025-10-20:** Credenciais MQTT expostas no ESP01 → **CORRIGIDO**
- **2025-10-20:** Chave Firebase Admin SDK exposta → **CORRIGIDO**  
- **2025-10-20:** Chave SSH pública no repositório → **CORRIGIDO**
- **2025-10-20:** Backups de banco commitados → **CORRIGIDO**

### 🔄 **Ações Tomadas:**
1. Todas as credenciais movidas para arquivos protegidos
2. .gitignore atualizado para proteger dados sensíveis
3. Scripts refatorados para usar configuração externa
4. Documentação de segurança criada
5. Templates públicos fornecidos para orientação

---

## 📞 **Suporte e Troubleshooting**

### 🔧 **Problemas Comuns:**

**Consumer não conecta ao MQTT:**
- Verifique credenciais no `config.py`
- Teste conectividade com o broker
- Confirme que o tópico está correto

**Firebase não inicializa:**
- Verifique se o arquivo de credenciais existe
- Confirme que o path está correto no config
- Teste permissões do service account

**Dados não aparecem no Firestore:**
- Verifique logs do consumer
- Confirme formato JSON dos dados
- Teste permissões de escrita no Firestore

---

**⚠️ LEMBRETE CRÍTICO:** Nunca commite credenciais, chaves ou backups de produção no controle de versão!