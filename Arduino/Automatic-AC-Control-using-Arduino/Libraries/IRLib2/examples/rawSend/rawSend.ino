/* rawSend.ino Example sketch for IRLib2
 *  Illustrates how to send a code Using raw timings which were captured
 *  from the "rawRecv.ino" sample sketch.  Load that sketch and
 *  capture the values. They will print in the serial monitor. Then you
 *  cut and paste that output into the appropriate section below.
 */
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender

IRsendRaw mySender;

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  Serial.println(F("Every time you press a key is a serial monitor we will send."));
}
/* Cut and paste the output from "rawRecv.ino" below here. It will 
 * consist of a #define RAW_DATA_LEN statement and an array definition
 * beginning with "uint16_t rawData[RAW_DATA_LEN]= {…" and concludes
 * with "…,1000};"
 */
#define RAW_DATA_LEN 350
uint16_t rawData[RAW_DATA_LEN]={
  554, 17778, 2930, 8970, 438, 558, 434, 1542, 
  438, 554, 434, 554, 438, 554, 434, 554, 
  438, 554, 434, 554, 434, 558, 434, 1542, 
  438, 554, 434, 558, 430, 1570, 514, 478, 
  490, 498, 490, 1490, 434, 1546, 434, 1542, 
  438, 1542, 438, 1542, 438, 554, 434, 554, 
  434, 558, 434, 554, 434, 558, 434, 558, 
  430, 582, 406, 582, 510, 482, 510, 478, 
  490, 502, 430, 558, 434, 554, 438, 554, 
  434, 554, 434, 554, 438, 554, 434, 554, 
  438, 554, 434, 554, 438, 554, 434, 554, 
  434, 558, 434, 554, 434, 582, 410, 578, 
  494, 498, 510, 478, 490, 498, 434, 558, 
  434, 554, 438, 554, 434, 1542, 438, 1542, 
  438, 1542, 434, 1546, 518, 2954, 2902, 8970, 
  442, 1546, 434, 578, 410, 582, 490, 498, 
  494, 498, 466, 522, 434, 558, 434, 554, 
  434, 554, 438, 1542, 438, 550, 438, 554, 
  434, 1542, 438, 554, 438, 1542, 434, 1542, 
  438, 1570, 490, 1490, 490, 1486, 438, 1542, 
  438, 554, 434, 554, 438, 554, 434, 554, 
  434, 554, 438, 554, 434, 554, 438, 554, 
  434, 554, 438, 554, 434, 554, 434, 582, 
  410, 578, 494, 498, 510, 478, 490, 502, 
  434, 554, 434, 554, 438, 554, 434, 554, 
  438, 554, 434, 554, 438, 554, 434, 554, 
  434, 554, 438, 554, 434, 554, 438, 554, 
  434, 558, 430, 582, 410, 582, 490, 498, 
  490, 502, 490, 498, 434, 554, 434, 558, 
  434, 3014, 2922, 8974, 442, 1542, 438, 554, 
  434, 554, 434, 554, 438, 554, 434, 554, 
  438, 554, 434, 558, 430, 562, 430, 1566, 
  494, 498, 510, 482, 466, 1510, 434, 558, 
  434, 1542, 438, 1542, 438, 554, 434, 1542, 
  438, 1542, 438, 1542, 438, 1534, 442, 1570, 
  410, 1570, 494, 1486, 434, 1542, 438, 554, 
  438, 554, 434, 554, 434, 1542, 438, 1542, 
  442, 1538, 438, 554, 434, 558, 434, 554, 
  434, 582, 406, 582, 410, 1566, 510, 482, 
  490, 502, 434, 1542, 438, 1542, 438, 554, 
  434, 554, 434, 554, 438, 1542, 438, 554, 
  434, 554, 434, 558, 434, 554, 434, 558, 
  434, 578, 410, 582, 502, 1474, 494, 1486, 
  434, 1546, 438, 1538, 438, 1000};


/*
 * Cut-and-paste into the area above.
 */
   
void loop() {
  if (Serial.read() != -1) {
    //send a code every time a character is received from the 
    // serial port. You could modify this sketch to send when you
    // push a button connected to an digital input pin.
    mySender.send(rawData,RAW_DATA_LEN,36);//Pass the buffer,length, optionally frequency
    Serial.println(F("Sent signal."));
  }
}

