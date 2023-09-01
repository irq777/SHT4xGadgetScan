# SHT4xGadgetScan
An Arduino Uno Wifi based Bluetooth scanner for Sensirion SHT4x Smart Gadgets measuring temperature and humidity.

This code was build on the "Scan Callback" example from the ArduinoBLE library.
It scans and decodes temperature and humidity advertised by Sensirion Smart Gadget of type SHT4x
Sensirion Smart Gadget of type SHT31 is not compatible, because the advertising does not contain any sensor-data. You need to connect to obtain the values.

## Hardware: 
- Arduino Uno Wifi Rev4
- Sensirion Smart Gadget (SHT4x)

## Documentation:
- https://github.com/Sensirion/arduino-ble-gadget/blob/master/documents/Sensirion_BLE_communication_protocol.pdf
- Datasheet of Sensirion Smart Gadget (SHT4x)
