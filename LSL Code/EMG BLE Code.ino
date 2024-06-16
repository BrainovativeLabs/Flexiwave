#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

const int emgPin = A0; // Analog pin for EMG sensor
const int sampleRate = 500; // Sampling rate in Hz
const float lowCutoff = 20.0; // Low cutoff frequency of bandpass filter
const float highCutoff = 500.0; // High cutoff frequency of bandpass filter

float filterCoeffs1[5]; // Array to hold coefficients for the first filter stage
float filterCoeffs2[5]; // Array to hold coefficients for the second filter stage
float x1[3] = {0}; // Input signal history for the first stage
float y1_hist[3] = {0}; // Output signal history for the first stage
float x2[3] = {0}; // Input signal history for the second stage
float y2_hist[3] = {0}; // Output signal history for the second stage

#define BAUD_RATE 115200
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {
  Serial.begin(BAUD_RATE);
  calculateCoeffs(filterCoeffs1, lowCutoff, highCutoff, sampleRate);
  calculateCoeffs(filterCoeffs2, lowCutoff, highCutoff, sampleRate);

  // Create the BLE Device
  BLEDevice::init("ESP32");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting for a client connection to notify...");
}

void loop() {
  static unsigned long lastTime = 0;
  if (millis() - lastTime >= 1000 / sampleRate) {
    lastTime = millis();
    int rawEMG = analogRead(emgPin);
    float filteredEMG = applyBandpassFilter(rawEMG);
    
    if (deviceConnected) {
      pCharacteristic->setValue(filteredEMG);
      pCharacteristic->notify();
      delay(3); // bluetooth stack will go into congestion if too many packets are sent
    }
    
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
      delay(500); // give the bluetooth stack the chance to get things ready
      pServer->startAdvertising(); // restart advertising
      Serial.println("start advertising");
      oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
      oldDeviceConnected = deviceConnected;
    }
  }
}

// Calculate the coefficients for a 2nd order bandpass filter
void calculateCoeffs(float *coeffs, float lowCutoff, float highCutoff, int fs) {
  float f0 = (highCutoff + lowCutoff) / 2.0;
  float BW = highCutoff - lowCutoff;
  float Q = f0 / BW;
  float w0 = 2.0 * PI * f0 / fs;
  float alpha = sin(w0) / (2.0 * Q);

  float b0 = alpha;
  float b1 = 0;
  float b2 = -alpha;
  float a0 = 1 + alpha;
  float a1 = -2 * cos(w0);
  float a2 = 1 - alpha;

  coeffs[0] = b0 / a0;
  coeffs[1] = b1 / a0;
  coeffs[2] = b2 / a0;
  coeffs[3] = a1 / a0;
  coeffs[4] = a2 / a0;
}

// Apply the 4th order bandpass filter
float applyBandpassFilter(int input) {
  // Shift the history for the first stage
  for (int i = 2; i > 0; i--) {
    x1[i] = x1[i-1];
    y1_hist[i] = y1_hist[i-1];
  }
  x1[0] = input;

  // Apply the first stage filter
  y1_hist[0] = filterCoeffs1[0] * x1[0] + filterCoeffs1[1] * x1[1] + filterCoeffs1[2] * x1[2] - filterCoeffs1[3] * y1_hist[1] - filterCoeffs1[4] * y1_hist[2];

  // Shift the history for the second stage
  for (int i = 2; i > 0; i--) {
    x2[i] = x2[i-1];
    y2_hist[i] = y2_hist[i-1];
  }
  x2[0] = y1_hist[0];

  // Apply the second stage filter
  y2_hist[0] = filterCoeffs2[0] * x2[0] + filterCoeffs2[1] * x2[1] + filterCoeffs2[2] * x2[2] - filterCoeffs2[3] * y2_hist[1] - filterCoeffs2[4] * y2_hist[2];

  return y2_hist[0];
}
