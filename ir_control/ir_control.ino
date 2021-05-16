/* rawSend.ino Example sketch for IRLib2
 *  Illustrates how to send a code Using raw timings which were captured
 *  from the "rawRecv.ino" sample sketch.  Load that sketch and
 *  capture the values. They will print in the serial monitor. Then you
 *  cut and paste that output into the appropriate section below.
 */
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender
#include <dht.h>

//#define dht_apin A0 // Analog Pin sensor is connected to
 
//dht DHT;

IRsendRaw mySender;

void setup() {
  Serial.begin(9600);
  delay(2000); 
  while (!Serial); //delay for Leonardo
//  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
}
/* Cut and paste the output from "rawRecv.ino" below here. It will 
 * consist of a #define RAW_DATA_LEN statement and an array definition
 * beginning with "uint16_t rawData[RAW_DATA_LEN]= {…" and concludes
 * with "…,1000};"
 */
#define RAW_DATA_LEN 68
uint16_t rawData[RAW_DATA_LEN]={
  4466, 4450, 578, 1650, 574, 1638, 574, 1654, 
  574, 534, 574, 542, 570, 534, 574, 542, 
  570, 526, 574, 1654, 570, 1642, 574, 1658, 
  570, 534, 574, 542, 574, 530, 574, 542, 
  574, 530, 574, 534, 574, 1646, 574, 542, 
  570, 534, 574, 542, 570, 534, 574, 542, 
  570, 526, 574, 1658, 574, 526, 570, 1650, 
  570, 1646, 566, 1658, 566, 1650, 566, 1658, 
  570, 1642, 570, 1000};
   
void loop() {

//  DHT.read11(dht_apin);
//  int temp = DHT.temperature;
//  Serial.print("temperature = ");
//  Serial.print(temp); 
//  Serial.println(" C");
//  if (temp > 29) {
//    mySender.send(rawDataOn,RAW_DATA_LEN,36);//Pass the buffer,length, optionally frequency
//    Serial.println(F("AC Switched On"));
//  }
//  else if (temp < 26) {
//    mySender.send(rawDataOff,RAW_DATA_LEN,36);//Pass the buffer,length, optionally frequency
//    Serial.println(F("AC Switched Off"));
//  }

    mySender.send(rawData, RAW_DATA_LEN, 36);
    Serial.println(F("Sent IR signal"));
    delay(5000);
}
