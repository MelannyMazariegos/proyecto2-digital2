#include <Arduino.h>
#define RXp2 16
#define TXp2 17 
int sensorPin = 35; 
int recibir;
float factor = 0.75;		// coeficiente para filtro pasa bajos
float maximo = 0.0;		// para almacenar valor maximo 
int minimoEntreLatidos = 300;	// 300 mseg. de tiempo minimo entre latidos
float valorAnterior = 500;	// para almacenar valor previo
int latidos = 0;		// contador de cantidad de latidos
int BPM = 0;
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  static unsigned long tiempoLPM = millis();	// tiempo Latidos Por Minuto con
						// valor actual devuelto por millis()
  static unsigned long entreLatidos = millis(); // tiempo entre Latidos con
						// valor actual devuelto por millis()

  int valorLeido = analogRead(sensorPin);		// lectura de entrada analogica A0

  float valorFiltrado = factor * valorAnterior + (1 - factor) * valorLeido;	// filtro pasa bajos
  float cambio = valorFiltrado - valorAnterior;		// diferencia entre valor filtrado y
							// valor anterior
  valorAnterior = valorFiltrado;		// actualiza valor anterior con valor filtrado

  if ((cambio >= maximo) && (millis() > entreLatidos + minimoEntreLatidos)) {	// si cambio es
					// es mayor o igual a maximo y pasaron al menos 300 mseg.
    maximo = cambio;			// actualiza maximo con valor de cambo
    entreLatidos = millis();		// actualiza variable entreLatidos con millis()
    latidos++;				// incrementa latidos en uno
  }  
  maximo = maximo * 0.97;		// carga maximo como el 97 por ciento de su propio
					// valor para dejar decaer y no perder pulsos

  if (millis() >= tiempoLPM + 15000) {		// si transcurrieron al menos 15 segundos
    BPM = latidos*4;
    Serial2.println(BPM);
    latidos = 0;				// coloca contador de latidos en cero
    tiempoLPM = millis();			// actualiza variable con valor de millis()
  }
  if (Serial2.available()>0){
    String mensaje = Serial2.readStringUntil('\n');
    Serial.print("BPM: ");
    Serial.println(mensaje);
  }
  delay(50);
}