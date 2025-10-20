# Módulo ESP01 - Gateway IoT

## ⚠️ CONFIGURAÇÃO DE SEGURANÇA OBRIGATÓRIA

**IMPORTANTE:** Este módulo contém credenciais sensíveis que foram removidas do código principal por segurança.

### 🔧 Configuração Inicial

1. **Copie o arquivo de configuração:**
   ```bash
   cp config.example.h config.h
   ```

2. **Edite o `config.h` com suas credenciais reais:**
   - WiFi SSID e senha
   - Servidor MQTT e credenciais
   - Tópicos MQTT personalizados

3. **NUNCA commite o arquivo `config.h`** (já está protegido pelo .gitignore)

### 📋 Funcionalidades

- **Gateway Serial-MQTT**: Recebe dados JSON pela serial e envia para MQTT
- **Auto-reconnect**: Reconecta automaticamente WiFi e MQTT em caso de falha
- **Validação JSON**: Valida formato antes de enviar
- **Timeout configurável**: Evita travamentos na conexão

### 🔌 Conexão com Arduino

```
Arduino UNO  →  ESP01
D2 (TX)      →  RX
D3 (RX)      →  TX  
GND          →  GND
3.3V         →  VCC
```

### 📤 Formato de Dados

O módulo espera dados JSON via serial:
```json
{"id":1698765432,"voltage":220.50,"current":1.25,"power":275.63,"partial_energy":0.0766,"timestamp":"2023-10-31 14:30:32"}
```

### 🔒 Credenciais Removidas

Por segurança, as seguintes credenciais foram removidas do código:
- ❌ WiFi SSID e senha
- ❌ Servidor MQTT
- ❌ Usuário e senha MQTT

**Todas estão agora no arquivo `config.h` (não commitado)**

### 🚨 Verificação de Segurança

Antes de cada commit, verifique:
- [ ] Arquivo `config.h` não está sendo commitado
- [ ] Não há credenciais hardcoded no código
- [ ] Arquivo `config.example.h` está atualizado

### 📝 Logs de Depuração

O módulo imprime logs úteis:
```
Iniciando ESP8266...
Conectando ao WiFi...
WiFi conectado!
IP: 192.168.1.100
Conectando ao MQTT... conectado!
Enviando JSON para MQTT: {"voltage":220.5,...}
```

### 🛠️ Troubleshooting

**WiFi não conecta:**
- Verifique SSID e senha no `config.h`
- Confirme que o ESP01 está no range do WiFi

**MQTT falha:**
- Verifique credenciais do broker
- Confirme que o servidor está acessível
- Teste conectividade de rede

**JSON inválido:**
- Verifique formato dos dados do Arduino
- Confirme que inicia com `{` e termina com `}`

---

**⚠️ LEMBRETE:** Mantenha sempre suas credenciais em `config.h` e nunca as compartilhe publicamente!