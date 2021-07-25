#include "Thread.h"
#include "ThreadController.h"

void piscaLed1(){
  
}

void piscaLed2(){
  
}

ThreadController cpu;

Thread t1;
Thread t2;

void setup() {
  t1.setInterval(500);
  t1.onRun(piscaLed1);
  
  t1.setInterval(300);
  t1.onRun(piscaLed2);

  cpu.add(&t1);
  cpu.add(&t2);
  
}

void loop() {
  
  cpu.run();
  
}
