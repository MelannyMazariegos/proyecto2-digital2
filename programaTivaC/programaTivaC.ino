#include <bitmaps.h>
#include <font.h>
#include <lcd_registers.h>

#define RXp2 PD6 //Pines para la comunicacion entre esp32 y Tiva C
#define TXp2 PD7
const int guardar = PUSH2;
const int medir = PUSH1;
int latido;
int mandar;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  pinMode(guardar, INPUT_PULLUP);
  pinMode(medir, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  mandar = digitalRead(medir);
  if(mandar == LOW){
   if (Serial2.available()>0){
     latido = Serial2.parseInt();
     String incomingData = Serial2.readStringUntil('\n');
     Serial.println(latido);
  }
 }
}
