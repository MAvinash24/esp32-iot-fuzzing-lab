#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// UUIDs (custom)
#define SERVICE_UUID        "your-service-uuid-1234"
#define CHARACTERISTIC_UUID "your-characteristic-uuid-1234"

BLECharacteristic *pCharacteristic;

class MyCallbacks : public BLECharacteristicCallbacks {

  void onWrite(BLECharacteristic *pCharacteristic) {

    std::string value = pCharacteristic->getValue();

    Serial.print("Received BLE Data (len=");
    Serial.print(value.length());
    Serial.print("): ");

    for (int i = 0; i < value.length(); i++) {
      Serial.print(value[i]);
    }

    Serial.println();

    // Detection logic (like MQTT fuzz)
    if (value.length() > 50) {
      Serial.println("⚠️ WARNING: Large malformed payload detected!");
    }

    if (value.length() > 120) {
      Serial.println("🚨 Potential overflow attempt!");
    }
  }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("ESP32_BLE_FUZZ");

  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();

  Serial.println("BLE Server Started...");
}

void loop() {
  delay(1000);
}