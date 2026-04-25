import asyncio
import random
import string
from bleak import BleakClient

ADDRESS = "XX:XX:XX:XX:XX:XX"  # replace with your ESP32 MAC
CHAR_UUID = "your-characteristic-uuid"  # replace with your characteristic UUID

def random_payload():
    length = random.randint(10, 200)
    return ''.join(random.choice(string.printable) for _ in range(length))

async def fuzz():
    async with BleakClient(ADDRESS) as client:
        print("Connected to ESP32")

        for i in range(100):
            payload = random_payload()
            await client.write_gatt_char(CHAR_UUID, payload.encode())

            print(f"[{i}] Sent:", payload)

            await asyncio.sleep(0.5)

asyncio.run(fuzz())