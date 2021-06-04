/* rawSend.ino Example sketch for IRLib2
 *  Illustrates how to send a code Using raw timings which were captured
 *  from the "rawRecv.ino" sample sketch.  Load that sketch and
 *  capture the values. They will print in the serial monitor. Then you
 *  cut and paste that output into the appropriate section below.
 */
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender
#include <dht.h>

#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;

IRsendRaw mySender;

bool sinalEnviado = false;

void setup() {
  Serial.begin(9600);
  delay(2000); 
  while (!Serial); //delay for Leonardo
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
}
/* Cut and paste the output from "rawRecv.ino" below here. It will 
 * consist of a #define RAW_DATA_LEN statement and an array definition
 * beginning with "uint16_t rawData[RAW_DATA_LEN]= {…" and concludes
 * with "…,1000};"
 */
#define RAW_DATA_LEN 42
uint16_t rawData[RAW_DATA_LEN]={
  2518, 1030, 326, 1010, 326, 574, 322, 574, 
  322, 1010, 746, 602, 294, 602, 294, 598, 
  298, 598, 298, 598, 298, 598, 298, 602, 
  294, 602, 294, 598, 298, 602, 298, 594, 
  298, 602, 742, 594, 298, 1034, 302, 598, 
  298, 1000};

/*
 * Cut-and-paste into the area above.
 */
   
void loop() {

  DHT.read11(dht_apin);
  int temp = DHT.temperature;
  Serial.print("temperature = ");
  Serial.print(temp); 
  Serial.println(" C");
  if (temp > 20 && !sinalEnviado) {
    mySender.send(rawData,RAW_DATA_LEN,36);//Pass the buffer,length, optionally frequency
    Serial.println(F("AC Switched On"));
    sinalEnviado = true;
  }
  delay(2000);
}
