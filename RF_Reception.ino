#include <RCSwitch.h>
#include <AESLib.h>


RCSwitch mySwitch = RCSwitch();

int ledPin = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  mySwitch.enableReceive(0);
}
byte rx_byte = 0;
char rx_str[50];
int index = 0;
uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
bool decBool = false;

void resetMsg(){
   for(int i=0; i<sizeof(rx_str); i++){
          rx_str[i] = '\0';
          
        }
        index = 0;
        rx_byte = '\0';
}
void ledSignal(){
  digitalWrite(ledPin,HIGH);
  delay(100);
  digitalWrite(ledPin,LOW);
  delay(100);
  digitalWrite(ledPin,HIGH);
  delay(100);
  digitalWrite(ledPin,LOW);
  delay(100);
  digitalWrite(ledPin,HIGH);
  delay(100);
  digitalWrite(ledPin,LOW);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mySwitch.available()){

     rx_byte = mySwitch.getReceivedValue();
     if(rx_byte != '\n' && rx_byte != '\0'){        
      
        rx_str[index++] = rx_byte;  //Réception des caractères encodés
        decBool = false;
        delay(630);
        
     }else{
      
       if(rx_byte != '\0' && decBool == false){ // decBool empêche que cette condition soit tout le temps exécuté
        
        Serial.print("Nouveau message crypté : ");
        ledSignal();
        Serial.println(rx_str);
        aes256_dec_single(key,rx_str);
        Serial.print("Décryptage du message");
        
        delay(1000);
        Serial.print(".");
        delay(1000);
        Serial.print(".");
        delay(1000);
        Serial.println(".\n");
        
        Serial.println(rx_str);
        decBool= true;
       }
        resetMsg();
     }
     
  }

}
