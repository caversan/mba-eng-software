const admin = require('firebase-admin');
const fs = require('fs');

// Caminho para o arquivo de credenciais do Firebase
const serviceAccount = require('../caversan-iot-db-firebase-adminsdk-fbsvc-4863fd7f3a.json');

// Inicialize o Firebase Admin SDK
admin.initializeApp({
  credential: admin.credential.cert(serviceAccount)
});

const db = admin.firestore();

// Leia o arquivo JSON ajustado
const data = JSON.parse(fs.readFileSync('../bkp-database/firestore_ajustado_bkp.json', 'utf8'));

// Itere sobre os dados e adicione-os à coleção 'iot_data_limpo'
const importData = async () => {
  for (const [docId, docData] of Object.entries(data)) {
    await db.collection('iot_data_limpo').doc(docId).set(docData);
    console.log(`Documento ${docId} importado com sucesso.`);
  }
};

importData().then(() => {
  console.log('Importação concluída.');
  process.exit(0);
}).catch(error => {
  console.error('Erro durante a importação:', error);
  process.exit(1);
});
