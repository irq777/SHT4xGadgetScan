/*
 SHT4xGadgetScan
   
  This code was build on the "Scan Callback" example from the ArduinoBLE library.
  It scans and decodes temperature and humidity advertised by Sensirion Smart Gadget of type SHT4x
  Sensirion Smart Gadget of type SHT31 is not compatible, because the advertising does not contain any sensor-data. You need to connect to obtain the values.

  Hardware: 
  Arduino Uno Wifi Rev4
  Sensirion Smart Gadget (SHT4x)

  Documentation:
  https://github.com/Sensirion/arduino-ble-gadget/blob/master/documents/Sensirion_BLE_communication_protocol.pdf
  Datasheet of Sensirion Smart Gadget (SHT4x)

*/

#include <ArduinoBLE.h> // https://github.com/arduino-libraries/ArduinoBLE/

void setup() {
  Serial.begin(9600);
  while (!Serial);

  delay(1000);
  Serial.println("Booting...");

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  Serial.println("Bluetooth® Low Energy Central continous scan for SHT4x started (enable Bluetooth® on your SHT4x Smart Gadget!)");

  // set the discovered event handle
  BLE.setEventHandler(BLEDiscovered, bleCentralDiscoverHandler);

  // start scanning for peripherals with duplicates
  BLE.scan(true);
}

void loop() {
  // poll the central for events
  BLE.poll();
}

void bleCentralDiscoverHandler(BLEDevice peripheral) {
  
  String sht40 = "SHT40 Gadget"; // Sensirion SHT40: "SHT40 Gadget"
  String localname;

  //Skip all adversing without name
  if(!peripheral.hasLocalName())
    return;
  
  localname = peripheral.localName();

  //Skip all beside SHT40 Sensirion Smart Gadget
  if(strcmp(localname.c_str(),sht40.c_str())!=0)
    return;
  
  // discovered a peripheral
  Serial.println("Discovered Smart Gadget");
  Serial.println("-----------------------");

  // print address
  Serial.print("Address: ");
  Serial.println(peripheral.address());

  // print the local name, if present
  if (peripheral.hasLocalName()) {
    Serial.print("Local Name: ");
    Serial.println(peripheral.localName());
  }

  // print the RSSI
  Serial.print("RSSI: ");
  Serial.println(peripheral.rssi());

  if (peripheral.hasAdvertisementData()) {
    uint8_t adv_data[peripheral.advertisementDataLength()];
    char s [1];

    Serial.print("Advertising Data Length: ");
    Serial.println(peripheral.advertisementDataLength());
    if(peripheral.advertisementData(adv_data,peripheral.advertisementDataLength())){
      Serial.print("Advertising Data: ");    
      for(int i = 0; i < peripheral.advertisementDataLength(); i++){
        sprintf (s, "%02x",adv_data[i]);
        Serial.print(s);  
      }   
      Serial.println();
    }
      decode_sht40(adv_data);
  }
  Serial.println();
}

void decode_sht40(uint8_t *adv_data){
  unsigned short humid,temp,id = 0;
  Serial.print("Device ID: ");
  id = extract_sht40_id_bigend16(adv_data);
  Serial.println(id,HEX);

  Serial.print("Temperature: ");
  temp = extract_sht40_temp_littleend16(adv_data);
  Serial.println(temp * (175.0 / 65535) - 45, 1); // Formula from page 3 of the SHT4x datasheet

  Serial.print("Humidity: ");
  humid = extract_sht40_humid_littleend16(adv_data);
  Serial.println(humid * (125.0 / 65535) -6, 1); // Formula from page 3 of the SHT4x datasheet
}

short extract_sht40_id_bigend16(const unsigned char *buf){
  return (((short)buf[9]) << 8) |
          (((short)buf[10]) << 0);
}

short extract_sht40_temp_littleend16(const unsigned char *buf){
  return (((short)buf[11]) << 0) |
          (((short)buf[12]) << 8);
}

short extract_sht40_humid_littleend16(const unsigned char *buf){
  return (((short)buf[13]) << 0) |
          (((short)buf[14]) << 8);
}
