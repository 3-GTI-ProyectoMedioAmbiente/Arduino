// -*- mode: c++ -*-
#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#elif defined(SPARK)
#include "application.h"
#else
//#include "WProgram.h"
#endif
// ------------------------------------------------------
class Medidor { //classe Medidor
private:
    Stream *_mySerial;
    long dataArray[11]; //Multipurpose array
    String informacionSensor[5]; //Stores the character based EEPROM data
      
    //unsigned long sleepTime;
    //bool isSleeping;

public:
//-------------------------------------------
    // mySerial: Stream -> Constructor() ->
    // 
    // Constructor de la clase Medidor.
    //
    //@params mySerial Puerto serie para la comunicación entre sensor y placa
    //
    //-------------------------------------------
    Medidor(Stream *mySerial) : _mySerial(mySerial) {
      //isSleeping = false;
    }
    
    Medidor(Stream &mySerial) : _mySerial(&mySerial) {
      //isSleeping = false;
    }
  /**
 * La funcion Medidor() es un contructor vacio.
 * Medidor()
 */
  /*Medidor(  ) {
  } // ()
  */
  
  // .....................................................

  /**
 * La funcion iniciarMedidor() para las cosas que no se puedan hacer en el constructor, if any.
 * iniciarMedidor()
 */
  int iniciarMedidor(char c) {
    delay(500);
      String dataString;
      _mySerial->write(c);
      while (!_mySerial->available()) {
      }
      dataString = _mySerial->readStringUntil('\n');
      for (int i = 0; i < 11; i++) {
        String subS = dataString.substring(0, dataString.indexOf(','));
        if (subS.length() == 0) return 0;
        dataArray[i] = subS.toInt();
        dataString = dataString.substring(dataString.indexOf(',') + 2);
      }
      return 1;
  } // ()
  // .....................................................

  /**
 * La funcion medirCO2() devuelve el valor de C02.
 * medirCO2() -> Z
 */
  int medirCO2() {
    dataArray[1] = dataArray[1] - 2250;
    if(dataArray[1] < 0){
      dataArray[1] = 0;
    }
      return dataArray[1];
  } // ()
  // .....................................................

  /**
 * La funcion medirTemperatura() devuelve el valor de Tempertura.
 * medirTemperatura() -> Z
 */
  /*int medirTemperatura() {
  return 37; // qué frío !
  } // ()
  */
  // ------------------------------------------------------

}; // class

// ------------------------------------------------------
#endif
