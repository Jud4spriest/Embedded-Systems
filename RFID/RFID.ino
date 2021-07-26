//#include <EEPROM.h>     // We are going to read and write PICC's UIDs from/to EEPROM
#include "Thread.h"
#include "ThreadController.h"
#include <SPI.h>        // RC522 Module uses SPI protocol
#include <MFRC522.h>  // Library for Mifare RC522 Devices

#define ledVerd 2
#define ledAmar 6
#define ledVerm 4
#define botao 5
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int leds[] = {ledVerd,ledAmar,ledVerm};
int led;
int ledAnt;
int sizearr = sizeof(leds)/sizeof(int);
int c = 0;
long previousMillis = 0;
String data[10];

ThreadController cpu;
Thread piscaLeds;
Thread executeRFID;

void setup() {
  
  pinMode(botao, INPUT_PULLUP);
  for(int i=0; i<sizearr; i++){
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW); 
  }
  // # Inicialize Threads
   
  // # Protocol Configuration
  Serial.begin(9600);  // Initialize serial communications with PC
  SPI.begin();           // MFRC522 Hardware uses SPI protocol
  rfid.PCD_Init();    // Initialize MFRC522 Hardware

  // # Final setup
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
}

void loop() {
  
	threadLed(ledVerd,500);
  Serial.println(threadLed.tid());
  //Serial.print("estado botao: ");
  //Serial.println(digitalRead(botao)==true ? "true" : "false");
  
  if(verificaBotao()){
    threadLed(ledAmar,300);
    //Serial.println("entrei");
    while(true){
      
      //Serial.println("loop");
      for(int i=0 ; i<sizeof(data);i++){
        if(data[i] == leitura()) break;
        else{
          data[c] = leitura();
          c++;
        }
      }
      if(verificaBotao()) {
        //Serial.println(verificaBotao());
        break;
      }
    }
  }
}

void threadRfid(){


  
}

boolean verificaBotao(){ 
  
  int interval = 200;
  if(!digitalRead(botao) && (millis() - previousMillis > interval) ){
    previousMillis = millis(); 
    //Serial.println("verificando botao... TRUE!");
    return true;
  }
  else{
    //Serial.println("verificando botao... FALSE!");
    return false;
  }
}

void threadLed(int led_desire,long interval){
	  ledAnt = led;
	  led = led_desire;
    if(led != ledAnt){
      digitalWrite(ledAnt, LOW);
      piscaLeds.setInterval(interval);
      piscaLeds.onRun(blinkLed);
    }
    //Serial.print("LedAtual: ");
    //Serial.println(led);
    //Serial.print("LedAnterior: ");
    //Serial.println(ledAnt);
   
    if(piscaLeds.shouldRun()) piscaLeds.run();
}

void blinkLed(){
  //if(led != ledAnt) digitalWrite(ledAnt, LOW);
	digitalWrite(led, !digitalRead(led));
}


String leitura() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()){ //VERIFICA SE O CARTÃO PRESENTE NO LEITOR É DIFERENTE DO ÚLTIMO CARTÃO LIDO. CASO NÃO SEJA, FAZ
    return "\0"; //RETORNA PARA LER NOVAMENTE
  }
  /***INICIO BLOCO DE CÓDIGO RESPONSÁVEL POR GERAR A TAG RFID LIDA***/
  String strID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i<(rfid.uid.size-1) ? ":" : "");
  }
  strID.toUpperCase();
  /***FIM DO BLOCO DE CÓDIGO RESPONSÁVEL POR GERAR A TAG RFID LIDA***/

  Serial.print("Identificador (UID) da tag: "); //IMPRIME O TEXTO NA SERIAL
  Serial.println(strID); //IMPRIME NA SERIAL O UID DA TAG RFID
  
  rfid.PICC_HaltA(); //PARADA DA LEITURA DO CARTÃO
  rfid.PCD_StopCrypto1(); //PARADA DA CRIPTOGRAFIA NO PCD

  return strID;
}


































  
/*
  for(int i=0; i<sizearr; i++){
    if(!digitalRead(leds[i])) digitalWrite(leds[i], HIGH);
    else digitalWrite(leds[i], LOW); 
    delay(500);                      
  }
*/

//##################################################
//
//  // Look for new cards
//  if ( ! rfid.PICC_IsNewCardPresent()) 
//  {
//    return;
//  }
//  // Select one of the cards
//  if ( ! rfid.PICC_ReadCardSerial()) 
//  {
//    return;
//  }
//  //Mostra UID na serial
//  Serial.print("UID da tag :");
//  String conteudo= "";
//  byte letra;
//  for (byte i = 0; i < rfid.uid.size; i++) 
//  {
//     Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(rfid.uid.uidByte[i], HEX);
//     conteudo.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
//     conteudo.concat(String(rfid.uid.uidByte[i], HEX));
//  }
//  Serial.println();
//  Serial.print("Mensagem : ");
//  conteudo.toUpperCase();
//
//if (conteudo.substring(1) == "BD 9B 06 7D") //UID 2 - Cartao
//  {
//    Serial.println("Tag cadastrado!");
//    delay(3000);
//  }
//  
//}
