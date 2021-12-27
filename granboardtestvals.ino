#include <Keypad.h>
#include <BLEDevice.h>
#include <BLE2902.h>
BLEServer* pServer = NULL;

BLECharacteristic* pCharacteristic = NULL;
//BLECharacteristic* pCharacteristic2 = NULL;

bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;
int txValue = 0;
//int customKey = 0;
char customKey = 0;

#define SERVICE_UUID        "442f1570-8a00-9a28-cbe1-e1d4212d53eb"
#define CHARACTERISTIC_UUID "442f1571-8a00-9a28-cbe1-e1d4212d53eb"
//#define CHARACTERISTIC_UUID2 "442f1572-8a00-9a28-cbe1-e1d4212d53eb"


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      BLEDevice::startAdvertising();
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

const byte ROWS = 8;
const byte COLS = 11;
const int debounceTime = 20;//20 works better than great !
char hexaKeys[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
  'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'X', 'T', 'U', 'V',
  'W', 'S', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7',
  '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
  'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
  'u', 'v', 'w', 'x', 'y', 'z', '!', '@', '#', '$', '%',
  '^', '&', '*', '(', ')', '-', '?', ';', ':', '"', '[',
  '{', ']', '}', '_', '=', '+', ',', '<', '.', '>', '/',
};
byte colPins[COLS] = {12, 13, 14, 15, 18, 23, 25, 26, 27, 32, 33,};
byte rowPins[ROWS] =  {0, 2, 3, 4, 5, 19, 21, 22,};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

String inputString;
long inputInt;
//BluetoothSerial SerialBT;

void setup()
{
  Serial.begin(115200);
  inputString.reserve(10); // maximum number of digit for a number is 10, change if needed

  // Create the BLE Device
  BLEDevice::init("GRANBOARD");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);
  // BLEService *pService = pServer->createService(SERVICE_UUID2);
  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x00);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();

  Serial.println("Waiting a client connection to notify...");
}
void loop() {

  while (deviceConnected) {
    customKey = customKeypad.getKey();
    delay(debounceTime);
    if (customKey == 't') {
      pCharacteristic->setValue("3.3@");
      break;
    }
    else if (customKey == '%') {
      pCharacteristic->setValue("3.4@");
      break;
    }
    else if (customKey == '[') {
      pCharacteristic->setValue("3.5@");
      break;
    }
    else if (customKey == '/') {
      pCharacteristic->setValue("3.6@");
      break;
    }
    else if (customKey == 'K') {
      pCharacteristic->setValue("2.3@");
      break;
    }
    else if (customKey == 'V') {
      pCharacteristic->setValue("2.4@");
      break;
    }
    else if (customKey == '7') {
      pCharacteristic->setValue("2.5@");
      break;
    }
    else if (customKey == 'i') {
      pCharacteristic->setValue("2.6@");
      break;
    }
    else if (customKey == 'I') {
      pCharacteristic->setValue("1.2@");
      break;
    }
    else if (customKey == 'T') {
      pCharacteristic->setValue("1.4@");
      break;
    }
    else if (customKey == '5') {
      pCharacteristic->setValue("1.5@");
      break;
    }
    else if (customKey == 'g') {
      pCharacteristic->setValue("1.6@");
      break;
    }
    else if (customKey == 'H') {
      pCharacteristic->setValue("0.1@");
      break;
    }
    else if (customKey == 'X') {
      pCharacteristic->setValue("0.3@");
      break;
    }
    else if (customKey == '4') {
      pCharacteristic->setValue("0.5@");
      break;
    }
    else if (customKey == 'f') {
      pCharacteristic->setValue("0.6@");
      break;
    }
    else if (customKey == 'G') {
      pCharacteristic->setValue("0.0@");
      break;
    }
    else if (customKey == 'R') {
      pCharacteristic->setValue("0.2@");
      break;
    }
    else if (customKey == '3') {
      pCharacteristic->setValue("0.4@");
      break;
    }
    else if (customKey == 'e') {
      pCharacteristic->setValue("4.5@");
      break;
    }
    else if (customKey == 'J') {
      pCharacteristic->setValue("1.0@");
      break;
    }
    else if (customKey == 'U') {
      pCharacteristic->setValue("1.1@");
      break;
    }
    else if (customKey == '6') {
      pCharacteristic->setValue("1.3@");
      break;
    }
    else if (customKey == 'h') {
      pCharacteristic->setValue("4.4@");
      break;
    }
    else if (customKey == 'A') {
      pCharacteristic->setValue("2.0@");
      break;
    }
    else if (customKey == 'L') {
      pCharacteristic->setValue("2.1@");
      break;
    }
    else if (customKey == 'W') {
      pCharacteristic->setValue("2.2@");
      break;
    }
    else if (customKey == '8') {
      pCharacteristic->setValue("4.3@");
      break;
    }
    else if (customKey == 'B') {
      pCharacteristic->setValue("3.0@");
      break;
    }
    else if (customKey == 'M') {
      pCharacteristic->setValue("3.1@");
      break;
    }
    else if (customKey == 'S') {
      pCharacteristic->setValue("3.2@");
      break;
    }
    else if (customKey == '9') {
      pCharacteristic->setValue("4.2@");
      break;
    }
    else if (customKey == 'C') {
      pCharacteristic->setValue("9.1@");
      break;
    }
    else if (customKey == 'N') {
      pCharacteristic->setValue("9.0@");
      break;
    }
    else if (customKey == 'Y') {
      pCharacteristic->setValue("9.2@");
      break;
    }
    else if (customKey == 'a') {
      pCharacteristic->setValue("8.2@");
      break;
    }
    else if (customKey == 'D') {
      pCharacteristic->setValue("10.1@");
      break;
    }
    else if (customKey == 'O') {
      pCharacteristic->setValue("10.0@");
      break;
    }
    else if (customKey == 'Z') {
      pCharacteristic->setValue("10.2@");
      break;
    }
    else if (customKey == 'b') {
      pCharacteristic->setValue("8.3@");
      break;
    }
    else if (customKey == 'E') {
      pCharacteristic->setValue("7.1@");
      break;
    }
    else if (customKey == 'P') {
      pCharacteristic->setValue("7.0@");
      break;
    }
    else if (customKey == '1') {
      pCharacteristic->setValue("7.2@");
      break;
    }
    else if (customKey == 'c') {
      pCharacteristic->setValue("8.4@");
      break;
    }
    else if (customKey == 'n') {
      pCharacteristic->setValue("6.1@");
      break;
    }
    else if (customKey == 'y') {
      pCharacteristic->setValue("6.0@");
      break;
    }
    else if (customKey == ')') {
      pCharacteristic->setValue("6.3@");
      break;
    }
    else if (customKey == '=') {
      pCharacteristic->setValue("8.5@");
      break;
    }
    else if (customKey == 'm') {
      pCharacteristic->setValue("11.1@");
      break;
    }
    else if (customKey == 'x') {
      pCharacteristic->setValue("11.2@");
      break;
    }
    else if (customKey == '(') {
      pCharacteristic->setValue("11.4@");
      break;
    }
    else if (customKey == '_') {
      pCharacteristic->setValue("8.6@");
      break;
    }
    else if (customKey == 'l') {
      pCharacteristic->setValue("11.0@");
      break;
    }
    else if (customKey == 'w') {
      pCharacteristic->setValue("11.3@");
      break;
    }
    else if (customKey == '*') {
      pCharacteristic->setValue("11.5@");
      break;
    }
    else if (customKey == '}') {
      pCharacteristic->setValue("11.6@");
      break;
    }
    else if (customKey == 'k') {
      pCharacteristic->setValue("6.2@");
      break;
    }
    else if (customKey == 'v') {
      pCharacteristic->setValue("6.4@");
      break;
    }
    else if (customKey == '&') {
      pCharacteristic->setValue("6.5@");
      break;
    }
    else if (customKey == ']') {
      pCharacteristic->setValue("6.6@");
      break;
    }
    else if (customKey == 'j') {
      pCharacteristic->setValue("7.3@");
      break;
    }
    else if (customKey == 'u') {
      pCharacteristic->setValue("7.4@");
      break;
    }
    else if (customKey == '^') {
      pCharacteristic->setValue("7.5@");
      break;
    }
    else if (customKey == '{') {
      pCharacteristic->setValue("7.6@");
      break;
    }

    else if (customKey == 'p') {
      pCharacteristic->setValue("0.0@");
      break;
    }
    else if (customKey == '!') {
      pCharacteristic->setValue("0.2@");
      break;
    }
    else if (customKey == '?') {
      pCharacteristic->setValue("0.4@");
      break;
    }
    else if (customKey == ',') {
      pCharacteristic->setValue("4.5@");
      break;
    }
    else if (customKey == 'q') {
      pCharacteristic->setValue("9.3@");
      break;
    }
    else if (customKey == '@') {
      pCharacteristic->setValue("9.4@");
      break;
    }
    else if (customKey == ';') {
      pCharacteristic->setValue("9.5@");
      break;
    }
    else if (customKey == '<') {
      pCharacteristic->setValue("9.6@");
      break;
    }
    else if (customKey == 'r') {
      pCharacteristic->setValue("5.0@");
      break;
    }
    else if (customKey == '#') {
      pCharacteristic->setValue("5.3@");
      break;
    }
    else if (customKey == ':') {
      pCharacteristic->setValue("5.5@");
      break;
    }
    else if (customKey == '.') {
      pCharacteristic->setValue("5.6@");
      break;
    }
    else if (customKey == 's') {
      pCharacteristic->setValue("5.1@");
      break;
    }
    else if (customKey == '$') {
      pCharacteristic->setValue("5.2@");
      break;
    }
    else if (customKey == '"') {
      pCharacteristic->setValue("5.4@");
      break;
    }
    else if (customKey == '>') {
      pCharacteristic->setValue("4.6@");
      break;
    }
    else if (customKey == 'o') {
      pCharacteristic->setValue("4.0@");
      break;
    }
    else if (customKey == 'z') {
      pCharacteristic->setValue("8.0@");
      break;
    }
    else if (customKey == 'F') {
      pCharacteristic->setValue("BTN@");
      break;
    }
    else {
      customKey = NULL;
      pCharacteristic->notify();
      value++;
      //delay(300);
    }
    pCharacteristic->setValue("");
    value++;
    customKey = NULL;
   // delay(6);
  }
}
