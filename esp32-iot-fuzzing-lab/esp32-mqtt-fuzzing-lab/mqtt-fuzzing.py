import paho.mqtt.client as mqtt
import random
import string
import time

BROKER = "your_KALI_IP"   # CHANGE to your Kali IP
PORT = 1883
TOPIC = "esp32/test"

client = mqtt.Client()

def random_payload():
    payload_types = [
        lambda: ''.join(random.choices(string.ascii_letters, k=10)),
        lambda: ''.join(random.choices(string.printable, k=50)),
        lambda: bytes(random.getrandbits(8) for _ in range(20)),
        lambda: "A" * 1000,  # Overflow attempt
        lambda: "\x00\xff\xfe\xfd",  # Binary garbage
    ]
    return random.choice(payload_types)()

def fuzz():
    client.connect(BROKER, PORT, 60)

    while True:
        payload = random_payload()

        try:
            client.publish(TOPIC, payload)
            print(f"[+] Sent: {payload}")
        except Exception as e:
            print(f"[!] Error: {e}")

        time.sleep(0.8)  # Adjust the delay as needed

if __name__ == "__main__":
    fuzz()