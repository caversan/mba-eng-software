import serial
import time

PORT = "COM7"
BAUD = 115200
CMD = "AT+CFG?\r\n"

print(f"Conectando na porta {PORT}...")

try:
    with serial.Serial(PORT, BAUD, timeout=1) as ser:
        time.sleep(2)
        print(f"Enviando comando: {CMD.strip()}")
        ser.write(CMD.encode())
        time.sleep(1)
        response = ser.read(64)
        print("Resposta:")
        print(response.decode(errors="replace"))
except Exception as e:
    print(f"Erro: {e}")
