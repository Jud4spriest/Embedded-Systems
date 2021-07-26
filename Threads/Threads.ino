#include "Thread.h"
#include "ThreadController.h"

#define led1 2
#define led2 4

ThreadController cpu;

Thread t1;
void piscaLed1(){
  digitalWrite(led1, !digitalRead(led1));
  Serial.println("Led1");
}

Thread t2;
void piscaLed2(){
  digitalWrite(led2, !digitalRead(led2));
  Serial.println("Led2");
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);

  t1.setInterval(500);
  t1.onRun(piscaLed1);
   t2.setInterval(300);
  t2.onRun(piscaLed2);


  
}

void loop(){
  if(t1.shouldRun())
    t1.run();
  if(t2.shouldRun())
    t2.run();

  
}

//void loop() {
//  void (*ptrblink)();
//  void (*ptrblink2)();
//  
//  ptrblink = blinkLedsVerd;
//  ptrblink2 = blinkLedsVerm;
//
//  
//  if(millis()%2==0) threadLed(ptrblink,1000);
//  else threadLed(ptrblink2,500);
//  
//}
//
//void threadLed(void (*pointblink)(void),long interval){
//    t1.setInterval(interval);
//    t1.onRun(pointblink);
//    t1.run();
//}
//
//void blinkLedsVerd(){
//  digitalWrite(led1, !digitalRead(led1));
//  Serial.println("led1");
//  }
//void blinkLedsVerm(){
//  digitalWrite(led2, !digitalRead(led2));
//  Serial.println("led2");
//  }


//00000000000000000000000000000000000


//
//  #include "Thread.h"
//#include "ThreadController.h"
//
//#define led1 2
//#define led2 4
//
//ThreadController cpu;
//
//Thread t1;
//void piscaLed1(){
//  digitalWrite(led1, !digitalRead(led1));
//  Serial.println("Led1");
//}
//
//Thread t2;
//void piscaLed2(){
//  digitalWrite(led2, !digitalRead(led2));
//  Serial.println("Led2");
//}
//
//int led = 0;
//
//void setup() {
//  pinMode(led1, OUTPUT);
//  pinMode(led2, OUTPUT);
//  Serial.begin(9600);
//  
//  
//}
//
//void loop() {
//
//  threadLed(1000);
//  if(millis()<10000) led = led1;
//  else led = led2;
//  
//}
//
//void threadLed(long interval){
//    t1.setInterval(interval);
//    t1.onRun(blinkLeds);
//    t1.run();
//}
//
//void blinkLeds(){
//  digitalWrite(led, !digitalRead(led));
//  Serial.println("led1");
//  }
