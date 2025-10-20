# Projeto MBA Engenharia de Software - Sistema IoT

## 🔒 Segurança e Configurações Sensíveis

### Status Atual ✅
O projeto atualmente **NÃO contém dados sensíveis** no código. Todas as configurações são parâmetros técnicos seguros para compartilhamento público.

### Orientações de Segurança

#### 1. Configurações Futuras
Se você planeja adicionar conectividade (WiFi, MQTT, APIs):

1. **Copie o arquivo de exemplo:**
   ```bash
   cp config.example.h config.h
   ```

2. **Edite o `config.h` com suas credenciais reais**
   - Senhas WiFi
   - Credenciais MQTT
   - Chaves de API
   - Tokens de autenticação

3. **NUNCA commite o arquivo `config.h`** (já está no .gitignore)

#### 2. Boas Práticas Implementadas

✅ **Arquivo .gitignore criado** - Protege arquivos sensíveis  
✅ **Template de configuração** - Orienta configurações seguras  
✅ **Separação de código e credenciais** - Previne vazamentos  

#### 3. Uso do Template de Configuração

```cpp
// No seu arquivo .ino, inclua as configurações:
#include "config.h"

// Use as constantes definidas:
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
client.setServer(MQTT_SERVER, MQTT_PORT);
```

#### 4. Verificações de Segurança

Antes de fazer commit, verifique:
- [ ] Não há senhas hardcoded no código
- [ ] Arquivos de configuração estão no .gitignore
- [ ] Logs não contêm informações sensíveis
- [ ] Credenciais estão em arquivos separados

### 📁 Estrutura de Arquivos de Configuração

```
projeto/
├── .gitignore              # Ignora arquivos sensíveis
├── config.example.h        # Template público (commitado)
├── config.h               # Suas credenciais (NÃO commitado)
└── src/
    └── main.ino           # Código principal
```

### 🚨 Em Caso de Vazamento Acidental

Se credenciais foram commitadas acidentalmente:
1. Mude imediatamente todas as senhas/chaves
2. Use `git filter-branch` ou `git-secrets` para limpar o histórico
3. Force push para reescrever o histórico remoto

### 📋 Checklist de Segurança

- [ ] .gitignore configurado
- [ ] Credenciais em arquivo separado
- [ ] Template de exemplo criado
- [ ] Documentação de segurança escrita
- [ ] Código revisado por pares
- [ ] Testes sem credenciais reais

## 🔧 Arquivos do Projeto

### CORRENTE_TENSAO_WIFI_RTC_v2/
Sistema de monitoramento de energia com:
- Sensor de corrente ACS712
- Sensor de tensão ZMPT101B  
- RTC DS3231 para timestamp
- Comunicação serial com ESP

### INTEGRACAO_FINAL_v5/
Sistema de automação residencial com:
- Sensor de presença HLK-LD2420
- Sensor de luminosidade BH1750
- Controle de dimmer por zero-crossing
- Lógica de presença e ajuste automático de luz

### MODULO-ESP01/ 🆕
Gateway IoT para conectividade MQTT:
- **⚠️ CONTÉM CREDENCIAIS SENSÍVEIS** (agora protegidas)
- Bridge Serial-MQTT para dados de sensores
- Auto-reconnect WiFi e MQTT
- Validação JSON integrada
- **Configuração obrigatória necessária**

### CLOUD/ 🌩️ **CRÍTICO**
Infraestrutura e serviços cloud:
- **🚨 CONTINHA DADOS EXTREMAMENTE SENSÍVEIS** (agora protegidos)
- Consumer Python MQTT → Firebase
- Chaves Firebase Admin SDK (protegidas)
- Chaves SSH Oracle Cloud (protegidas)
- Backups de banco com 89k+ registros (protegidos)
- **Scripts refatorados para segurança**

### Libraries/
Bibliotecas necessárias para o funcionamento dos projetos.

---

**⚠️ IMPORTANTE:** Mantenha sempre suas credenciais seguras e nunca as compartilhe publicamente!