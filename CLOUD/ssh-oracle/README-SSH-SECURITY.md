# SSH Keys - Orientações de Segurança

## ⚠️ IMPORTANTE - CHAVES SSH

### 🚨 Chave Removida por Segurança
A chave SSH pública `ssh-key-2025-04-22.key.pub` foi movida para proteção no .gitignore.

### 🔐 Como Gerar Novas Chaves SSH

1. **Gerar um novo par de chaves:**
   ```bash
   ssh-keygen -t rsa -b 4096 -C "seu-email@exemplo.com" -f ~/.ssh/seu_projeto_key
   ```

2. **Configurar permissões corretas:**
   ```bash
   chmod 600 ~/.ssh/seu_projeto_key      # Chave privada
   chmod 644 ~/.ssh/seu_projeto_key.pub  # Chave pública
   ```

3. **Adicionar ao ssh-agent:**
   ```bash
   ssh-add ~/.ssh/seu_projeto_key
   ```

### 📋 Boas Práticas

✅ **FAÇA:**
- Use chaves diferentes para cada projeto/servidor
- Proteja chaves privadas com passphrase
- Mantenha chaves fora do controle de versão
- Faça backup seguro das chaves

❌ **NÃO FAÇA:**
- Nunca commite chaves privadas (.key, .pem)
- Evite chaves públicas no repo (podem revelar infraestrutura)
- Não compartilhe chaves entre usuários
- Não use chaves sem passphrase em produção

### 🖥️ Configuração no Servidor

Para usar a chave SSH no Oracle Cloud ou outros servidores:

1. **Copie a chave pública para o servidor:**
   ```bash
   ssh-copy-id -i ~/.ssh/seu_projeto_key.pub usuario@servidor
   ```

2. **Ou manualmente adicione em ~/.ssh/authorized_keys**

3. **Teste a conexão:**
   ```bash
   ssh -i ~/.ssh/seu_projeto_key usuario@servidor
   ```

### 🔄 Rotação de Chaves

- Gere novas chaves regularmente (a cada 6-12 meses)
- Remova chaves antigas dos servidores
- Atualize deployments e scripts automatizados

---

**⚠️ LEMBRETE:** Se uma chave foi comprometida, gere novas imediatamente e revogue as antigas!