#include <SPI.h> // kütüphaneler eklendi
#include <RF24.h>
 
#define LED 2 // 5. pine led bağlanmıştır
 
#define RF_CS 7 // RF24 üzerindeki CS pininin (bazı modellerde CE diye yazılmaktadır) arduino ya takıldığı pin numarası verilmiştir
#define RF_CSN 8 // RF24 üzerindeki CSN pininin arduino ya takıldığı pin numarası verilmiştir
 
RF24 radio(RF_CS, RF_CSN); // RF24 türünde radio isimli değişken tanımlandı
const uint64_t pipes[2] = { 0xe7e7e7e7e7LL, 0xc2c2c2c2c2LL }; // paralel veri yolu adresleri
 
boolean durum =false;
 
void setup() {
  Serial.begin(9600); // seri haberleşme hızı
  pinMode(LED, OUTPUT);
  radio.begin(); // rf24 haberleşmesi başlatıldı
  radio.openWritingPipe(pipes[0]); //  modülün verici olarak kullanılması için gerekli olan data yolu adresini haberleşmeye açar. Yani 0xe7e7e7e7e7LL adresi veriyi gönderen kısım.
  //Bunu karşı taraf 0xc2c2c2c2c2LL adresi ile alır
  radio.openReadingPipe(1, pipes[1]); //  modülün alıcı olarak kullanılması için gerekli olan data yolu adresini haberleşmeye açar. Yani 0xc2c2c2c2c2LL adresi veriyi alan kısım.
  //Yani veri karşıdaki 0xe7e7e7e7e7LL adresinden alınır
  radio.startListening(); // radio modüllerinden veri gelinip gelinmediğini kontrol eetmektedir.
  radio.printDetails();
}
 
void loop() {
 
  unsigned long time = millis();  // programın çalışma süresinin tutulduğu değişken
  // belli bir sürede modüllerin birbiri ile haberleşmediği durumlarda uyarı vermesi için kullanılacaktır
 
  uint8_t on[1],off[1];
  on[0]=1;
  off[0]=0;
  radio.stopListening();
 
  if(!durum)
  {
    digitalWrite(LED,HIGH); // led yandığında karşı tarafın ledi  sonecek
    
    radio.write( &on,sizeof(on));
    durum= true;
     Serial.println("1 deneeme ");
     Serial.println(radio.available());//baglanti var mı
  }
  else
  {
    digitalWrite(LED,LOW);
    radio.write( &off,sizeof(off));
    durum=false;
     Serial.println("2 deneme");
  }
  radio.startListening();
 
  delay(1000);
}
