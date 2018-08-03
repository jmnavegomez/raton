/*raton
Copyright (C) 2018  Jose Manuel Naveiro

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Mouse.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Arduino.h>
int botonI=4;
int botonD=5;

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(981152);
float X;
float Y;
float Z;
float ayud1;
float ayud2;
float ayud3=9.8;

void setup() {
  Mouse.begin();
  Serial.begin(9600);
  pinMode(botonI,INPUT_PULLUP);
  pinMode(botonD,INPUT_PULLUP);
  /* Initialise the sensor */
  if (!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1);
  }

  /* Set the range to whatever is appropriate for your project */
  //accel.setRange(ADXL345_RANGE_16_G);
  // displaySetRange(ADXL345_RANGE_8_G);
  // displaySetRange(ADXL345_RANGE_4_G);
  accel.setRange(ADXL345_RANGE_2_G);
  accel.setDataRate(ADXL345_DATARATE_400_HZ);
}

void loop(void) {
  int estadoBotonI=digitalRead(botonI);
  int estadoBotonD=digitalRead(botonD);
  Serial.println(estadoBotonI);
  if(estadoBotonI==0)
  {
    Serial.println("Apretando boton izq");
    Mouse.press(MOUSE_LEFT);  
  }
  else{
    Serial.println("Suelto boton izq");
    Mouse.release(MOUSE_LEFT);
  }
  if(estadoBotonD==0){
    Serial.println("Apretando boton DCho");
    Mouse.press(MOUSE_RIGHT);
  }
  else{
    Serial.println("Suelto boton DCho");
    Mouse.release(MOUSE_RIGHT);
  }
  /* Get a new sensor event */
  sensors_event_t event;
  accel.getEvent(&event);

  X = event.acceleration.x; /*Datos eje X*/
  Y = event.acceleration.y; /*Datos eje Y*/
  Z = event.acceleration.z; /*Datos eje Z*/

  /*Operaciones/tratamiento de datos */
  ayud1 = X/11;//(X / abs(X)) * sqrt(1 - pow(X / 11, 2));
  ayud2 = Y/11;//(Y / abs(Y)) * sqrt(1 - pow(Y / 11, 2));
  ayud3 = Z;
  Serial.print(ayud1);
  Serial.println(ayud2);
  
  Mouse.move((int)(ayud1*10), (int)(ayud2*10)); /*Movimiento*/

  

  delay(4);
}
