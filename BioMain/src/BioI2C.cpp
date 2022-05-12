#include <Arduino.h>
#include <Params.h>
#include <ChNil.h>

#if defined(I2C)

#include <Wire.h>
/*
 FLUX
 - B1011 XXX R/W  (XXX is the user defined address and R/W the read/write byte)
 --> TBD PH METER
 - B????????
 */

#define WIRE_MAX_DEVICES 5
uint8_t numberI2CDevices = 0;
uint8_t wireDeviceID[WIRE_MAX_DEVICES];

/********************
 * Utilities functions
 **********************/

void wireWrite(uint8_t address, uint8_t _data) {
  Wire.beginTransmission(address);
  Wire.write(_data);
  Wire.endTransmission();
}

void wireWrite(uint8_t address, uint8_t reg, uint8_t _data)  // used by 4-relay
{
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(_data);
  Wire.endTransmission();
}

uint8_t wireRead(uint8_t address) {
  uint8_t _data = 0;
  Wire.requestFrom(address, (uint8_t)1);
  if (Wire.available()) {
    _data = Wire.read();
  }
  return _data;
}

void wireInfo(Print* output) {
  // wireUpdateList();
  output->println("I2C");

  for (uint8_t i = 0; i < numberI2CDevices; i++) {
    output->print(i);
    output->print(": ");
    output->print(wireDeviceID[i]);
    output->print(" - ");
    output->println(wireDeviceID[i], BIN);
  }
}

void wireInsertDevice(uint8_t id, uint8_t newDevice) {
  // Serial.println(id);

  if (numberI2CDevices < WIRE_MAX_DEVICES) {
    for (uint8_t i = id + 1; i < numberI2CDevices - 1; i++) {
      wireDeviceID[i] = wireDeviceID[i + 1];
    }
    wireDeviceID[id] = newDevice;
    numberI2CDevices++;
  }
}

void wireRemoveDevice(uint8_t id) {
  for (uint8_t i = id; i < numberI2CDevices - 1; i++) {
    wireDeviceID[i] = wireDeviceID[i + 1];
  }
  numberI2CDevices--;
}

void wireUpdateList() {
  // 16ms
  uint8_t _data;
  uint8_t currentPosition = 0;
  // I2C Module Scan, from_id ... to_id
  for (uint8_t i = 0; i <= 127; i++) {
    Wire.beginTransmission(i);
    Wire.write(&_data, 0);
    // I2C Module found out!
    if (Wire.endTransmission() == 0) {
      // there is a device, we need to check if we should add or remove a
      // previous device
      if (currentPosition < numberI2CDevices &&
          wireDeviceID[currentPosition] ==
              i) {  // it is still the same device that is at the same position,
                    // nothing to do
        currentPosition++;
      } else if (currentPosition < numberI2CDevices &&
                 wireDeviceID[currentPosition] <
                     i) {  // some device(s) disappear, we need to delete them
        wireRemoveDevice(currentPosition);
        i--;
      } else if (currentPosition >= numberI2CDevices ||
                 wireDeviceID[currentPosition] >
                     i) {  // we need to add a device
        // Serial.print("add: ");        DEBUG POUR CONNAITRE L'ADRESSE DE L'I2C
        // !!!!!!!! Serial.println(i);
        wireInsertDevice(currentPosition, i);
        currentPosition++;
      }
      chThdSleep(1);
    }
  }
  while (currentPosition < numberI2CDevices) {
    wireRemoveDevice(currentPosition);
  }
}

bool wireDeviceExists(uint8_t id) {
  for (uint8_t i = 0; i < numberI2CDevices; i++) {
    if (wireDeviceID[i] == id)
      return true;
  }
  return false;
}

// We will combine flags in a byte. Using pointer does not seems to improve
// memory size so we don't use pointer
void setWireFlag(uint8_t* aByte, uint8_t address) {
  *aByte |= (1 << (address & 0b00000111));
}

void clearWireFlag(uint8_t* aByte, uint8_t address) {
  *aByte &= ~(1 << (address & 0b00000111));
}

bool wireFlagStatus(uint8_t* aByte, uint8_t address) {
  return *aByte & (1 << (address & 0b00000111));
}

#endif