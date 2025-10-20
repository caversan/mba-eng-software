# Database Backups - Política de Segurança

## 📊 Backups do Firestore

### 🛡️ Status de Proteção
Os backups de banco foram movidos para proteção no .gitignore por conterem:
- Dados de telemetria IoT em grande volume
- Possíveis padrões de uso residencial
- Informações de timestamps que podem revelar rotinas

### 📁 Arquivos Protegidos:
- `firestore-backup-30-05-2025.json` (89.810 linhas)
- `firestore-base-separada.json`
- `firestore-base-separada-sem-as-sextas.json`
- `firestore-base-separada-sem-as-sextas-e-qua.json`
- `firestore_ajustado.json`
- Arquivos CSV de análise comparativa

### 🔐 Diretrizes de Backup

#### ✅ Boas Práticas:
- Backups devem ficar em storage seguro (não no repositório)
- Use criptografia para dados sensíveis
- Implemente rotação automática de backups
- Mantenha logs de acesso aos backups

#### ⚠️ Dados de Telemetria IoT:
Embora sejam dados técnicos, podem revelar:
- Padrões de consumo energético
- Rotinas domésticas
- Horários de presença/ausência
- Dados de sensores de movimento

### 🗂️ Estrutura Recomendada:
```
backup-seguro/
├── daily/
│   ├── firestore-YYYY-MM-DD.json.enc
│   └── metadata-YYYY-MM-DD.json
├── weekly/
└── monthly/
```

### 📋 Comandos para Backup Seguro:

1. **Backup com criptografia:**
   ```bash
   # Fazer backup
   gcloud firestore export gs://seu-bucket/backup-$(date +%Y%m%d)
   
   # Criptografar localmente
   gpg --symmetric --cipher-algo AES256 firestore-backup.json
   ```

2. **Restaurar backup:**
   ```bash
   # Descriptografar
   gpg --decrypt firestore-backup.json.gpg > firestore-backup.json
   
   # Restaurar
   gcloud firestore import gs://seu-bucket/backup-20250530
   ```

### 🔄 Automação Recomendada:

```python
# Exemplo de script de backup automatizado
import os
from firebase_admin import credentials, firestore
from datetime import datetime

def backup_firestore():
    # Fazer backup
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    backup_file = f"backup_{timestamp}.json"
    
    # Criptografar
    os.system(f"gpg --symmetric --batch --yes --passphrase $BACKUP_PASSPHRASE {backup_file}")
    
    # Mover para storage seguro
    os.system(f"mv {backup_file}.gpg /secure/backups/")
    
    # Limpar arquivo temporário
    os.remove(backup_file)
```

---

**⚠️ IMPORTANTE:** Nunca commite backups de produção no controle de versão!