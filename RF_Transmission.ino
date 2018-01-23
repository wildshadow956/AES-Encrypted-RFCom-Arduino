#include <RCSwitch.h>
#include <AESLib.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySwitch.enableTransmit(12);

}

byte rx_byte = 0;
char rx_str[30];
int index = 0;
byte bte[30];
uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};

void resetMsg(){
   for(int i=0; i<sizeof(rx_str); i++){
          rx_str[i] = '\0';
          bte[i] = '\0';
        }
        index = 0;
}
void charsToBytes(){
    for(int i=0;i<sizeof(rx_str);i++){
          bte[i] = (byte)rx_str[i];               //Système de conversion des chars en bytes
         
       } 
}


void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
      rx_byte = Serial.read();
      if(rx_byte != '\n'){
        
          rx_str[index++] = rx_byte;        // Création de la chaîne de caractères créées par le client
      }else{

        Serial.print("Envoi du message : ");   
        Serial.println(rx_str);
        Serial.print("Cryptage du message");
        delay(1000);
        Serial.print(".");
        delay(1000);
        Serial.print(".");
        delay(1000);
        Serial.println(".\n");
                                               // Cryptage du message
        aes256_enc_single(key, rx_str);
        Serial.println(rx_str);

        charsToBytes();

        for(int i=0; i<sizeof(bte);i++){
          if(bte[i] != '\0'){
           mySwitch.send(bte[i], 24);     //Envoi du messages       
           Serial.println(bte[i]);
           delay(140);
          }
        }
       mySwitch.send('\n', 24);     // Permet au récepteur de savoirr de connaître la in du message
       Serial.println("DONE");
       
       
       resetMsg();
     }
    
  }
}
