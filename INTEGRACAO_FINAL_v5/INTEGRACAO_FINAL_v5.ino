#include <Wire.h>
#include <BH1750.h>
#include <SoftwareSerial.h>

// Pinos
#define PINO_ZC 2
#define PINO_DIM 9
#define HLK_TX 6
#define HLK_RX 7

// Configurações
#define LUX_MIN 0
#define LUX_MAX 100
#define DIMMER_MAX 60
#define DIMMER_MIN 10
#define INTERVALO_LEITURA_LUX 1000
#define INTERVALO_PRESENCA 1000
#define TIMEOUT_SEM_PRESENCA 30000
#define PASSO_DIMMER 1
#define INTERVALO_DIMMER 10

// Instâncias
BH1750 luximetro;
SoftwareSerial hlkSerial(HLK_TX, HLK_RX);

volatile int valorDimmerAtual = 0;
int valorDimmerAlvo = 0;

bool presencaDetectada = false;
unsigned long ultimoMovimento = 0;
unsigned long ultimaLeituraLux = 0;
unsigned long ultimaAtualizacaoPresenca = 0;
unsigned long ultimaAtualizacaoDimmer = 0;

String buffer = "";

// Variável para armazenar a média móvel exponencial do lux
float luxFiltrado = 0.0;
const float alpha = 0.1; // Fator de suavização para EMA

void zeroCross() {
  if (valorDimmerAtual > 0) {
    int valorLimite = constrain(valorDimmerAtual, 0, DIMMER_MAX);
    long atraso = 8200L * (100L - valorLimite) / 100L;
    delayMicroseconds(atraso);
    digitalWrite(PINO_DIM, HIGH);
    delayMicroseconds(6);
    digitalWrite(PINO_DIM, LOW);
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  luximetro.begin();
  hlkSerial.begin(115200);

  pinMode(PINO_DIM, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PINO_ZC), zeroCross, RISING);

  Serial.println(F("Sistema de presença + controle de iluminação iniciado"));
}

void loop() {
  // --- Leitura da UART do HLK-LD2420 ---
  while (hlkSerial.available()) {
    char c = hlkSerial.read();

    if (c == '\r' || c == '\n') {
      if (buffer.length() > 0) {
        if (buffer.indexOf("ON") != -1) {
          presencaDetectada = true;
          ultimoMovimento = millis();
        } else if (buffer.indexOf("OFF") != -1) {
          presencaDetectada = false;
        }
        buffer = "";
      }
    } else {
      buffer += c;
    }
  }

  // --- Atualização do estado de presença ---
  if (millis() - ultimaAtualizacaoPresenca >= INTERVALO_PRESENCA) {
    ultimaAtualizacaoPresenca = millis();
    Serial.print("Presença                           : ");
    Serial.println(presencaDetectada ? "@@@ SIM @@@" : "                             ... NÃO ...");
  }

  // --- Leitura do sensor de luz ---
  if (millis() - ultimaLeituraLux >= INTERVALO_LEITURA_LUX) {
    ultimaLeituraLux = millis();

    float lux = luximetro.readLightLevel();
    // Aplicar média móvel exponencial
    luxFiltrado = alpha * lux + (1 - alpha) * luxFiltrado;

    Serial.print("Lux ambiente (filtrado): ");
    Serial.print(luxFiltrado);
    Serial.println(" lx");

    bool semPresencaPorMuitoTempo = (millis() - ultimoMovimento > TIMEOUT_SEM_PRESENCA);

    if (presencaDetectada && !semPresencaPorMuitoTempo) {
      int novoValor = map(constrain(luxFiltrado, LUX_MIN, LUX_MAX), LUX_MIN, LUX_MAX, DIMMER_MAX, DIMMER_MIN);
      valorDimmerAlvo = novoValor;
    } else {
      valorDimmerAlvo = 0;
    }

    Serial.print("Valor do dimmer alvo: ");
    Serial.print(valorDimmerAlvo);
    Serial.println(" %");
  }

  // --- Ajuste gradual do valor do dimmer ---
  if (millis() - ultimaAtualizacaoDimmer >= INTERVALO_DIMMER) {
    ultimaAtualizacaoDimmer = millis();

    if (valorDimmerAtual < valorDimmerAlvo) {
      valorDimmerAtual += PASSO_DIMMER;
      if (valorDimmerAtual > valorDimmerAlvo) {
        valorDimmerAtual = valorDimmerAlvo;
      }
    } else if (valorDimmerAtual > valorDimmerAlvo) {
      valorDimmerAtual -= PASSO_DIMMER;
      if (valorDimmerAtual < valorDimmerAlvo) {
        valorDimmerAtual = valorDimmerAlvo;
      }
    }
  }
}
