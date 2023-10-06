# SHT4xGadgetScan
An Arduino Uno Wifi based Bluetooth scanner for Sensirion SHT4x Smart Gadgets measuring temperature and humidity.

This code was build on the "Scan Callback" example from the ArduinoBLE library.
It scans and decodes temperature and humidity advertised by Sensirion Smart Gadget of type SHT4x
Sensirion Smart Gadget of type SHT31 is not compatible, because the advertising does not contain any sensor-data. You need to connect to obtain the values.

## Hardware: 
- Arduino Uno Wifi Rev4
- Sensirion Smart Gadget (SHT4x)

## Installation
1. Install Arduino IDE
2. Go to Tools -> Board -> Boards Manager and install "Arduino Uno R4 Boards"
3. Go to Tools -> Board -> Arduino Uno R4 Boards and select "Arduino UNO R4 Wifi"
4. Go to Tools -> Manage Libraries and install "ArduinoBLE" library
5. Connect board via USB
6. Select the "Arduino UNO R4 Wifi" port via Tools -> Port
7. Verify & upload sketch
8. Put your Sensirion Smart Gadget (SHT4x) in range and enable Bluetooth via long button press (it shows the Bluetooth icon)
9. Watch the Tools -> Serial Monitor (you should see the temperature & humidity values that are advertised by the SHT4x in range)

## Documentation:
- https://github.com/Sensirion/arduino-ble-gadget/blob/master/documents/Sensirion_BLE_communication_protocol.pdf
- Datasheet of Sensirion Smart Gadget (SHT4x)
