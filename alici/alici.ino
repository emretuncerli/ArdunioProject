#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"           //Modül ile ilgili kütüphaneleri ekliyoruz
#define RF_CS 7
#define RF_CSN 8
RF24 radio(RF_CS, RF_CSN);
const uint64_t pipes[2] = { 0xe7e7e7e7e7LL, 0xc2c2c2c2c2LL }; // paralel veri yolu adresleri
int led = 2;

void setup(void){
 Serial.begin(9600);
 radio.begin();
 radio.openWritingPipe(pipes[1]);
 radio.openReadingPipe(1,pipes[0]);
 radio.startListening();
 radio.printDetails();
 pinMode(led, OUTPUT);
 }
 
void loop() {

  if (radio.available()) {
    char rx_data[1];   // gelen verinin dizi sayısı 1. Çünkü ya 0 gelecek yada 1 gelecek
    radio.read( &rx_data, 1 );
 
    if(rx_data[0]==1)
    {
      
      Serial.println(rx_data[0]);
      digitalWrite(led,HIGH);
      Serial.print("Sonsun ");
    }
    if(rx_data[0]==0)
    {
      digitalWrite(led,LOW);
      Serial.print("Yansin: ");
    }
  }
}

