#include <Arduino.h>
#define RXp2 16 //Pines para la comunicacion entre Esp32 y Tiva c
#define TXp2 17 
int sensorPin = 35; //Pin del sensor
float factor = 0.75;		// coeficiente para filtro pasa bajas
float maximo = 0.0;		// valor maximo
int minimoEntreLatidos = 300;	// tiempo minimo entre latidos
float valorAnterior = 500;	// almacenar valor anterior
int latidos = 0;		// contador de cantidad de latidos
int BPM = 0;
void setup() {
  //Se inicializan los monitores seriales
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  static unsigned long tiempoLPM = millis();	// tiempo para latidos por minuto
  static unsigned long entreLatidos = millis(); // tiempo entre latidos

  int valorLeido = analogRead(sensorPin);		// lectura del sensor

  float valorFiltrado = factor * valorAnterior + (1 - factor) * valorLeido;	// filtro pasa bajas
  float cambio = valorFiltrado - valorAnterior;		// diferencia entre valor filtrado y valor anterior
  valorAnterior = valorFiltrado;		// actualiza valor anterior con valor filtrado

  if ((cambio >= maximo) && (millis() > entreLatidos + minimoEntreLatidos)) {	
    maximo = cambio;			// actualiza el valor maximo
    entreLatidos = millis();		// actualiza el tiempo entre latidos
    latidos++;				// incrementa en uno los latidos
  }  
  maximo = maximo * 0.97;		// carga maximo como el 97 por ciento de su propio valor para dejar decaer y no perder pulsos

  if (millis() >= tiempoLPM + 15000) {		// tiempo que transcurre para medir el pulso
    BPM = latidos*4; //Calculo para la frecuencia cardiaca
    Serial2.println(BPM); //Se manda este dato a tiva c
    latidos = 0;				// resetea el contador de latidos
    tiempoLPM = millis();			// actualiza el tiempo de latidos por minutos
  }
  delay(50);
  //Para recibir datos del tiva C
  while (Serial2.available()){
    String mensaje = Serial2.readStringUntil('\n');
    Serial.println(mensaje); //Se imprime el dato en el monitor serial
  }
}