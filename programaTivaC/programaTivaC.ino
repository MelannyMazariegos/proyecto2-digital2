#include <bitmaps.h>
#include <font.h>
#include <lcd_registers.h>
#define RXp2 PD6 //Pines para la comunicacion entre esp32 y Tiva C
#define TXp2 PD7
int melodia[] = {262, 196, 196, 220, 196, 0, 247, 262};
int duracionNotas[] = {4, 8, 8, 4, 4, 4, 4, 4};
int gan_melody[] = {330, 392, 330, 392, 0, 392, 440, 440};
int duraciones[] = {8, 8, 4, 4, 4, 4, 4, 4};
//const int BUZZER = 5;
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
   //for(int i = 0; i < 8; i++){
  //  int duracionNota = 1000/duracionNotas[i];
    //tone(BUZZER, melodia[i],duracionNotas);
//    int pausaEntreNotas = duracionNota * 1.30;
  //  delay(pausaEntreNotas);
    //noTone(BUZZER);
 //  }
  }
}
