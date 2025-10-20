#include <Wire.h>
#include <RTClib.h>
#include <EmonLib.h>
#include <ZMPT101B.h>
#include <SoftwareSerial.h>

// Pinos dos sensores
#define PINO_CORRENTE A1
#define PINO_TENSAO A0

// Calibração
#define CURRENT_CAL 0.61              // Corrente calibrada conforme testes reais
#define VOLTAGE_SENSITIVITY 430       // Mantido pois a tensão está coerente

// Comunicação com ESP
SoftwareSerial espSerial(2, 3); // D2 (RX) <- ESP TX | D3 (TX) -> ESP RX

// Instâncias
EnergyMonitor emon1;
ZMPT101B voltSensor(PINO_TENSAO);
RTC_DS3231 rtc;

// Controle de tempo
unsigned long ultimaLeituraMillis = 0;
unsigned long intervaloLeitura = 60000; // 60 segundos
float energiaWh = 0;

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);

  emon1.current(PINO_CORRENTE, CURRENT_CAL);
  voltSensor.setSensitivity(VOLTAGE_SENSITIVITY);

  if (!rtc.begin()) {
    Serial.println("Erro ao iniciar o RTC!");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC sem dados válidos, configurando hora...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  ultimaLeituraMillis = millis();
  Serial.println("Sistema iniciado!");
}

void loop() {
  unsigned long agoraMillis = millis();
  if (agoraMillis - ultimaLeituraMillis >= intervaloLeitura) {
    ultimaLeituraMillis = agoraMillis;

    float tensao = voltSensor.getRmsVoltage();

    emon1.calcVI(17, 100);
    float corrente = emon1.Irms;  // Inclui o consumo do Arduino e periféricos

    float potencia = tensao * corrente;
    float tempoHoras = intervaloLeitura / 3600000.0;
    float consumoParcial = potencia * tempoHoras;
    energiaWh += consumoParcial;

    DateTime now = rtc.now();
    char timestamp[25];
    snprintf(timestamp, sizeof(timestamp), "%04d-%02d-%02d %02d:%02d:%02d",
             now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
    uint32_t epoch = now.unixtime();

    Serial.print("Tensao: "); Serial.print(tensao);
    Serial.print(" V | Corrente: "); Serial.print(corrente);
    Serial.print(" A | Potencia: "); Serial.print(potencia);
    Serial.print(" W | Consumo: "); Serial.print(consumoParcial);
    Serial.print(" Wh | Time: "); Serial.println(timestamp);

    espSerial.print(F("{\"id\":"));
    espSerial.print(epoch);
    espSerial.print(F(",\"voltage\":"));
    espSerial.print(tensao, 2);
    espSerial.print(F(",\"current\":"));
    espSerial.print(corrente, 2);
    espSerial.print(F(",\"power\":"));
    espSerial.print(potencia, 2);
    espSerial.print(F(",\"partial_energy\":"));
    espSerial.print(consumoParcial, 4);
    espSerial.print(F(",\"timestamp\":\""));
    espSerial.print(timestamp);
    espSerial.println(F("\"}"));
  }
}
