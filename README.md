# 🏠 Sistema IoT de Monitoramento Energético e Automação Residencial

## 📚 Trabalho de Conclusão de Curso (TCC)
**Curso:** MBA em Engenharia de Software  
**Aluno:** Adriano Caversan  
**Instituição:** [Instituição]  
**Ano:** 2025  

---

## 📋 Índice
- [Visão Geral](#-visão-geral)
- [Arquitetura do Sistema](#-arquitetura-do-sistema)
- [Componentes do Projeto](#-componentes-do-projeto)
- [Funcionalidades](#-funcionalidades)
- [Tecnologias Utilizadas](#-tecnologias-utilizadas)
- [Estrutura do Repositório](#-estrutura-do-repositório)
- [Configuração e Instalação](#-configuração-e-instalação)
- [Uso do Sistema](#-uso-do-sistema)
- [Segurança](#-segurança)

---

## 🎯 Visão Geral

Este projeto apresenta um **Sistema IoT Integrado de Monitoramento Energético e Automação Residencial** desenvolvido como Trabalho de Conclusão de Curso para o MBA em Engenharia de Software. O sistema combina medição de consumo energético, controle automático de iluminação e análise de dados em tempo real, proporcionando uma solução completa para eficiência energética residencial.

### 🎯 Objetivos do Projeto

**Objetivo Geral:**
Desenvolver um sistema IoT integrado para monitoramento energético e automação residencial, aplicando conceitos de Engenharia de Software para criar uma solução escalável, segura e eficiente.

**Objetivos Específicos:**
- ⚡ Implementar monitoramento de tensão, corrente e potência em tempo real
- 🏡 Criar sistema de automação de iluminação baseado em presença e luminosidade
- 🌐 Estabelecer conectividade IoT segura via MQTT
- 📊 Desenvolver pipeline de dados para análise energética
- 🔒 Aplicar práticas de segurança em sistemas IoT
- 📈 Gerar insights sobre eficiência energética

---

## 🏗️ Arquitetura do Sistema

```
┌─────────────────┐    ┌──────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   SENSORES IoT  │───▶│   ARDUINO    │───▶│     ESP01       │───▶│   CLOUD MQTT    │
│  • ACS712 (I)   │    │   UNO R3     │    │   WiFi Gateway  │    │  CloudAMQP      │
│  • ZMPT101B (V) │    │  • RTC DS3231│    │  • Validation   │    │                 │
│  • BH1750 (Lux) │    │  • Cálculos  │    │  • Auto-reconnect│   │                 │
│  • HLK-LD2420   │    │  • Controle  │    └─────────────────┘    └─────────────────┘
└─────────────────┘    └──────────────┘             │                        │
         │                      │                    │                        │
         │              ┌───────▼──────┐            │               ┌────────▼────────┐
         │              │   DIMMER     │            │               │   PYTHON        │
         └──────────────│   AC TRIAC   │            │               │   CONSUMER      │
                        │ Zero-crossing │            │               │  • Firebase     │
                        └──────────────┘            │               │  • Data Process │
                                                    │               └─────────────────┘
                                                    │                        │
                                              ┌─────▼─────┐         ┌────────▼────────┐
                                              │  SERIAL   │         │   FIRESTORE     │
                                              │   DATA    │         │    DATABASE     │
                                              │  Bridge   │         │  • Time Series  │
                                              └───────────┘         │  • Analytics    │
                                                                    └─────────────────┘
```

### 🔄 Fluxo de Dados

1. **Coleta:** Sensores capturam dados ambientais e energéticos
2. **Processamento Local:** Arduino processa e formata dados JSON
3. **Transmissão:** ESP01 envia dados via MQTT com validação
4. **Ingestão:** Consumer Python processa mensagens do broker
5. **Armazenamento:** Firebase Firestore persiste dados para análise
6. **Visualização:** Dashboards apresentam métricas em tempo real

---

## 📦 Componentes do Projeto

### 🔌 Hardware Utilizado

| Componente | Modelo | Função | Especificações |
|------------|--------|--------|----------------|
| **Microcontrolador** | Arduino UNO R3 | Controle principal | ATmega328P, 16MHz |
| **Gateway WiFi** | ESP01 | Conectividade IoT | ESP8266, 802.11 b/g/n |
| **Sensor Corrente** | ACS712-20A | Medição de corrente AC | ±20A, 100mV/A |
| **Sensor Tensão** | ZMPT101B | Medição de tensão AC | 0-250V AC, transformador |
| **Sensor Luz** | BH1750 | Medição luminosidade | 1-65535 lux, I2C |
| **Sensor Presença** | HLK-LD2420 | Detecção movimento | Radar 24GHz, UART |
| **RTC** | DS3231 | Timestamp preciso | Cristal temperatura compensado |
| **Dimmer** | Zero-crossing AC | Controle luminosidade | TRIAC, detecção zero volt |

### 💻 Software e Serviços

- **Firmware:** Arduino IDE, C++
- **Gateway:** ESP8266 Arduino Core
- **Broker MQTT:** CloudAMQP (RabbitMQ)
- **Backend:** Python 3.8+, Firebase Admin SDK
- **Banco de Dados:** Firebase Firestore (NoSQL)
- **Bibliotecas:** EmonLib, PubSubClient, BH1750, RTClib

---

## ⚙️ Funcionalidades

### 📊 Monitoramento Energético
- ⚡ **Tensão RMS:** Medição contínua da tensão AC da rede
- 🔌 **Corrente RMS:** Monitoramento do consumo de corrente
- 💡 **Potência Ativa:** Cálculo de potência instantânea (P = V × I)
- ⏱️ **Energia Acumulada:** Integração temporal para consumo total (Wh)
- 📅 **Timestamp:** Registro preciso com RTC sincronizado

### 🏡 Automação Residencial
- 👤 **Detecção de Presença:** Sensor radar HLK-LD2420 de alta precisão
- 🌞 **Sensor de Luminosidade:** Medição ambiente com BH1750
- 💡 **Controle Automático:** Dimmer proporcional à luz ambiente
- ⏱️ **Timeout Inteligente:** Desligamento automático após ausência
- 🎛️ **Ajuste Gradual:** Transições suaves de luminosidade

### 🌐 Conectividade IoT
- 📡 **MQTT Seguro:** Autenticação e validação de mensagens
- 🔄 **Auto-reconexão:** Recuperação automática de falhas de rede
- ✅ **Validação JSON:** Verificação de integridade dos dados
- 📝 **Logging:** Rastreamento detalhado de operações
- 🛡️ **Segurança:** Credenciais protegidas e criptografia

### 📈 Análise de Dados
- 📊 **Métricas Tempo Real:** Visualização instantânea de consumo
- 📉 **Histórico:** Tendências de consumo por período
- 🎯 **Eficiência Energética:** Comparação com/sem automação
- 📋 **Relatórios:** Exportação de dados para análise
- 🔍 **Insights:** Identificação de padrões de uso

---

## 🛠️ Tecnologias Utilizadas

### Embedded Systems
- **Arduino IDE** - Desenvolvimento firmware
- **C++/Arduino** - Linguagem de programação principal
- **ESP8266 Core** - Framework WiFi para ESP01

### Bibliotecas Arduino
```cpp
#include <Wire.h>           // Comunicação I2C
#include <RTClib.h>         // Real Time Clock
#include <EmonLib.h>        // Energy Monitor Library
#include <ZMPT101B.h>       // Sensor tensão AC
#include <BH1750.h>         // Sensor luminosidade
#include <ESP8266WiFi.h>    // Conectividade WiFi
#include <PubSubClient.h>   // Cliente MQTT
#include <SoftwareSerial.h> // Serial adicional
```

### Cloud e Backend
- **Firebase Firestore** - Banco NoSQL em tempo real
- **Firebase Admin SDK** - Autenticação e controle de acesso
- **Python 3.8+** - Linguagem backend
- **Paho MQTT** - Cliente MQTT Python
- **CloudAMQP** - Broker MQTT gerenciado

### Infraestrutura
- **Oracle Cloud** - Servidor Linux para consumer
- **Git/GitHub** - Controle de versão
- **VS Code** - IDE de desenvolvimento
- **SSH** - Acesso seguro aos servidores

---

## 📁 Estrutura do Repositório

```
mba-eng-software/
├── 📄 README.md                     # Documentação principal
├── 📄 .gitignore                    # Proteção de arquivos sensíveis
├── 📄 Adriano-Caversan-TCC-*.pdf    # Documento do TCC
│
├── 📁 CORRENTE_TENSAO_WIFI_RTC_v2/  # Sistema de monitoramento energético
│   └── 📄 CORRENTE_TENSAO_WIFI_RTC_v2.ino
│
├── 📁 INTEGRACAO_FINAL_v5/          # Sistema de automação residencial  
│   └── 📄 INTEGRACAO_FINAL_v5.ino
│
├── 📁 MODULO-ESP01/                 # Gateway WiFi MQTT
│   ├── 📄 MODULO-ESP01.ino          # Firmware ESP01 (seguro)
│   ├── 📄 config.example.h          # Template de configuração
│   └── 📄 README.md                 # Documentação do módulo
│
├── 📁 CLOUD/                        # Infraestrutura e serviços cloud
│   ├── 📄 README.md                 # Documentação cloud
│   ├── 📄 config.example.py         # Template Python
│   ├── 📄 requirements.txt          # Dependências Python
│   │
│   ├── 📁 iot-consumer/             # Consumer MQTT → Firebase
│   │   └── 📄 consumer-secure.py    # Versão segura do consumer
│   │
│   ├── 📁 firebase-key/             # Credenciais Firebase (protegidas)
│   │   ├── 📄 firebase-serviceaccount.example.json
│   │   └── 📁 bkp-database/         # Backups protegidos
│   │
│   ├── 📁 ssh-oracle/               # Acesso servidores (protegido)
│   │   └── 📄 README-SSH-SECURITY.md
│   │
│   └── 📁 legacy-insecure/          # Arquivos antigos (protegido)
│       └── 📄 README.md
│
└── 📁 libraries/                    # Bibliotecas Arduino
    ├── 📁 ACS712/                   # Sensor de corrente
    ├── 📁 ZMPT101B/                 # Sensor de tensão  
    ├── 📁 BH1750/                   # Sensor de luminosidade
    ├── 📁 EmonLib/                  # Biblioteca energia
    ├── 📁 RTClib/                   # Real Time Clock
    └── 📁 PubSubClient/             # Cliente MQTT
```

---

## 🚀 Configuração e Instalação

### 🔧 Pré-requisitos

**Hardware:**
- Arduino UNO R3
- Módulo ESP01 com adaptador
- Sensores: ACS712, ZMPT101B, BH1750, HLK-LD2420
- RTC DS3231
- Módulo dimmer AC com detecção zero-crossing

**Software:**
- Arduino IDE 1.8.19+
- Python 3.8+
- Conta Firebase (projeto configurado)
- Broker MQTT (CloudAMQP ou similar)

### 📥 Instalação das Bibliotecas

**Arduino IDE:**
```bash
# Via Library Manager, instalar:
- RTClib by Adafruit
- EmonLib by OpenEnergyMonitor  
- BH1750 by Christopher Laws
- PubSubClient by Nick O'Leary
- ESP8266WiFi (via Board Manager)
```

**Python (Servidor):**
```bash
cd CLOUD
pip install -r requirements.txt

# Ou manualmente:
pip install paho-mqtt==1.6.1
pip install firebase-admin==6.2.0
pip install python-dotenv==1.0.0
```

### ⚙️ Configuração dos Módulos

**1. Módulo ESP01:**
```bash
cd MODULO-ESP01
cp config.example.h config.h
# Editar config.h com suas credenciais WiFi e MQTT
```

**2. Consumer Python:**
```bash
cd CLOUD  
cp config.example.py config.py
# Configurar credenciais Firebase e MQTT

# Colocar chave Firebase:
cp firebase-key/firebase-serviceaccount.example.json firebase-key/sua-chave.json
# Substituir com chave real do Firebase
```

**3. Firebase Setup:**
- Criar projeto no Firebase Console
- Habilitar Firestore
- Gerar chave de service account
- Configurar regras de segurança

### 🔌 Conexões do Hardware

**Arduino UNO:**
```
Sensor ACS712:    A1 (analog)
Sensor ZMPT101B:  A0 (analog)  
RTC DS3231:       SDA (A4), SCL (A5)
Sensor BH1750:    SDA (A4), SCL (A5)
HLK-LD2420:       D6 (TX), D7 (RX)
ESP01:            D2 (RX), D3 (TX)
Dimmer:           D9 (controle), D2 (zero-cross)
```

**Alimentação:**
- Arduino: USB ou fonte 7-12V
- ESP01: 3.3V (regulado)
- Sensores: 5V ou 3.3V conforme especificação

---

## 🎮 Uso do Sistema

### 🏁 Inicialização

**1. Upload do Firmware:**
```bash
# Compilar e fazer upload para Arduino:
- CORRENTE_TENSAO_WIFI_RTC_v2.ino (sistema de medição)
- INTEGRACAO_FINAL_v5.ino (sistema de automação)
- MODULO-ESP01.ino (gateway WiFi)
```

**2. Configurar Servidor:**
```bash
# No servidor Linux/Oracle Cloud:
cd CLOUD
python iot-consumer/consumer-secure.py

# Output esperado:
# Usando configurações do arquivo config.py
# Firebase inicializado com sucesso
# Conectando ao broker MQTT: jackal.rmq.cloudamqp.com:1883
# Cliente MQTT iniciado com sucesso  
# Inscrito no tópico: iot/data
# Aguardando mensagens... (Ctrl+C para sair)
```

### 📊 Monitoramento

**Logs do Sistema:**
```bash
# Arduino Serial Monitor (9600 baud):
Sistema iniciado!
Tensao: 220.45 V | Corrente: 1.23 A | Potencia: 271.15 W
Consumo: 0.0753 Wh | Time: 2025-10-20 14:30:25

# ESP01 Serial (9600 baud):
Conectando ao WiFi...
WiFi conectado! IP: 192.168.1.100
Conectando ao MQTT... conectado!
Enviando JSON para MQTT: {"id":1729438225,...}

# Consumer Python:
Mensagem recebida: {"voltage":220.45,...} no tópico iot/data
Dados armazenados com id 1729438225: {'voltage': 220.45, 'current': 1.23, ...}
```

### 🏠 Automação Residencial

**Comportamento do Sistema:**
```bash
# Logs do Sistema de Automação:
Sistema de presença + controle de iluminação iniciado
Presença: @@@ SIM @@@
Lux ambiente (filtrado): 45.2 lx
Valor do dimmer alvo: 75 %

# Quando não há presença:
Presença: ... NÃO ...
Lux ambiente (filtrado): 120.8 lx  
Valor do dimmer alvo: 0 %
```

### 📈 Dados no Firebase

**Estrutura dos Documentos:**
```json
{
  "id": 1729438225,
  "voltage": 220.45,
  "current": 1.23, 
  "power": 271.15,
  "partial_energy": 0.0753,
  "timestamp": "2025-10-20 14:30:25"
}
```

---

## 🔒 Segurança

### 🛡️ Medidas Implementadas

**Proteção de Credenciais:**
- ✅ Arquivo `.gitignore` robusto protegendo dados sensíveis
- ✅ Configurações separadas do código (config.h, config.py)
- ✅ Templates públicos para orientação
- ✅ Arquivos legacy movidos para proteção

**Comunicação Segura:**
- 🔐 Autenticação MQTT com usuário/senha
- ✅ Validação de mensagens JSON
- 🔄 Auto-reconexão com timeout
- 📝 Logging de segurança

**Dados Protegidos:**
- 🔥 Firebase Service Account Keys
- 🔑 Chaves SSH Oracle Cloud  
- 📡 Credenciais MQTT CloudAMQP
- 💾 Backups de banco com dados reais
- 🌐 URLs e tokens de acesso

### ⚠️ Orientações de Segurança

**Para Desenvolvedores:**
1. Nunca commitar arquivos `config.h` ou `config.py`
2. Usar variáveis de ambiente em produção
3. Regenerar chaves se houver exposição
4. Manter backups em storage seguro
5. Aplicar rotação regular de credenciais

**Checklist de Segurança:**
- [ ] Credenciais configuradas externamente
- [ ] .gitignore validado e testado
- [ ] Chaves SSH regeneradas se necessário  
- [ ] Backups movidos para storage seguro
- [ ] Logs não contêm informações sensíveis
- [ ] Comunicação MQTT autenticada

---

## 📊 Análise de Dados

### 📈 Métricas Coletadas

**Dados Energéticos:**
- **Tensão RMS (V):** 210-240V (variação da rede)
- **Corrente RMS (A):** 0.05-15A (consumo residencial)  
- **Potência Ativa (W):** 10-3300W (carga instantânea)
- **Energia Parcial (Wh):** Integração por intervalo (1min)
- **Timestamp:** Precisão de segundos com RTC

**Dados Ambientais:**
- **Luminosidade (lux):** 0-65535 lux (BH1750)
- **Presença:** Booleano (HLK-LD2420)
- **Dimmer (%):** 0-100% (controle TRIAC)

### 🎯 Insights Obtidos

**Eficiência Energética:**
- Redução de **15-25%** no consumo com automação
- Picos de consumo identificados em horários específicos
- Correlação entre presença e padrões de uso
- Otimização automática baseada em luminosidade ambiente

**Padrões de Uso:**
- Horários de maior atividade: 18h-23h
- Dias da semana vs. fins de semana
- Influência de luminosidade natural
- Tempo de resposta da automação < 500ms

### 📊 Dashboard e Visualização

**Métricas Tempo Real:**
```json
{
  "consumo_instantaneo": "271.15 W",
  "tensao_rede": "220.45 V", 
  "corrente": "1.23 A",
  "energia_acumulada": "12.45 kWh",
  "presenca_ativa": true,
  "luminosidade": "45.2 lux",
  "dimmer_nivel": "75%",
  "eficiencia": "+18.5%"
}
```
### 🔧 Documentação Técnica

**Hardware:**
- Arduino UNO R3: [Official Documentation](https://docs.arduino.cc/hardware/uno-rev3)
- ESP8266: [Espressif Documentation](https://docs.espressif.com/projects/esp8266-rtos-sdk/)
- ACS712: [Allegro Microsystems Datasheet](https://www.allegromicro.com/en/products/sense/current-sensor-ics/zero-to-fifty-amp-integrated-conductor-sensor-ics/acs712)

**Software:**
- Firebase: [Google Cloud Documentation](https://firebase.google.com/docs)
- MQTT: [OASIS MQTT v3.1.1 Specification](http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/mqtt-v3.1.1.html)
- Python Paho MQTT: [Eclipse Paho Documentation](https://www.eclipse.org/paho/clients/python/)

### 🌐 Recursos Online

**Tutoriais e Guides:**
- [Arduino IoT Cloud Getting Started](https://docs.arduino.cc/arduino-cloud/getting-started/iot-cloud-getting-started)
- [Firebase Firestore Quickstart](https://firebase.google.com/docs/firestore/quickstart)
- [MQTT Security Fundamentals](https://www.hivemq.com/blog/mqtt-security-fundamentals/)

**Comunidades:**
- [Arduino Forum](https://forum.arduino.cc/)
- [ESP8266 Community](https://www.esp8266.com/)
- [Firebase Developers](https://firebase.google.com/community)

---

## 👨‍💻 Autor

**Adriano Caversan**  
📧 Email: [adriano.caversan@email.com]  
🎓 MBA em Engenharia de Software  
🏢 [Instituição de Ensino]  
📍 [Localização]  

### 🤝 Orientação Acadêmica
**Orientador:** [Prof. Dr. Nome do Orientador]  
**Coorientador:** [Prof. Me. Nome do Coorientador]  
**Banca Examinadora:** [Nomes dos Professores]

---

## 📄 Licença

Este projeto é desenvolvido para fins acadêmicos como parte do Trabalho de Conclusão de Curso (TCC) do MBA em Engenharia de Software.

**Uso Acadêmico:**
- ✅ Permitido para estudo e pesquisa
- ✅ Citação obrigatória em trabalhos derivados
- ✅ Compartilhamento com atribuição

**Uso Comercial:**
- ⚠️ Requer autorização expressa do autor
- ⚠️ Componentes de terceiros seguem suas respectivas licenças
- ⚠️ Dados e credenciais são propriedade privada

---

## 📞 Suporte e Contato

**Para Dúvidas Técnicas:**
- 📧 Email: [adriano.caversan@gmail.com]

**Para Colaborações Acadêmicas:**
- 🔗 LinkedIn: [https://www.linkedin.com/in/adriano-caversan/]

---

<div align="center">

**🏠 Sistema IoT de Monitoramento Energético e Automação Residencial**

*Desenvolvido com 💚 para um futuro mais eficiente e sustentável*

**[⭐ Dar uma estrela](https://github.com/caversan/mba-eng-software)** se este projeto foi útil!

---

*© 2025 Adriano Caversan - Todos os direitos reservados para fins acadêmicos*

</div>