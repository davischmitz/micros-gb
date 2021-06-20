#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example of data captured by IRrecvDumpV2.ino
uint16_t rawData[99] = {8960, 4576,  530, 1714,  530, 1716,  528, 590,  
412, 686,  528, 634,  528, 632,  528, 636,  530, 1720,  524, 634,  528, 
1712,  530, 1716,  528, 632,  528, 634,  524, 634,  528, 632,  528, 632,  
528, 634,  528, 636,  528, 1716,  526, 630,  530, 636,  528, 636,  528, 
630,  530, 636,  524, 638,  522, 1712,  528, 634,  526, 632,  532, 628,  
528, 1718,  472, 1662,  528, 632,  528, 632,  530, 632,  530, 630,  528, 
632,  528, 632,  526, 636,  526, 640,  520, 632,  526, 632,  528, 636,  
528, 594,  528, 632,  530, 630,  530, 634,  528, 634,  526, 596,  528};

void setup() {
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1);
}

void loop() {
  Serial.println("a rawData capture from IRrecvDumpV2");
  irsend.sendRaw(rawData, 99, 38);  // Send a raw data capture at 38kHz.
  delay(200000);
}
