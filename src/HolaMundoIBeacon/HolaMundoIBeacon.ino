// -*-c++-*-

// Autor: Juan Carlos Hernandez Ramirez
// 22/09/2021

// https://learn.sparkfun.com/tutorials/nrf52840-development-with-arduino-and-circuitpython

// https://stackoverflow.com/questions/29246805/can-an-ibeacon-have-a-data-payload

#include <bluefruit.h>

//Se elimina la deficion de las variables min y max ya que en bluefrit.h ya existen
#undef min
#undef max

#include "LED.h"
#include "PuertoSerie.h"

#include <Adafruit_TinyUSB.h>
namespace Globales {
  
  LED elLED ( /* NUMERO DEL PIN LED = */ 7 );

  PuertoSerie elPuerto ( /* velocidad = */ 115200 ); // 115200 o 9600 o ...

  // Serial1 en el ejemplo de Curro creo que es la conexión placa-sensor 
};

#include "EmisoraBLE.h"
#include "Publicador.h"
#include "Medidor.h"

/**
 * La funcion Global() es donde se declaran todas las variables globales.
 * Global{
 *  elLed:LED
 *  elPuerto:PuertoSerie
 *  elPublicador:Publicador
 *  elMedidor:Medidor
 * }:namespace
 */

namespace Globales {
	
  Publicador elPublicador;
  Medidor elMedidor(&Serial1);
  
};

/**
 * La funcion inicializarComunicacionSensor() de momento nada.
 * inicializarPlaquita()
 */

void inicializarComunicacionSensor () {

  Serial1.begin(9600);

}

/**
 * La funcion setup() esta funcion sólo se ejecutará una vez al inicio del sistema.
 * setup() ->
 */
void setup() {
  using namespace Globales;
  // 
  // Iniciamos el Serial1 para establecer la comunicación UART con el sensor
  // 
  inicializarComunicacionSensor();


  // 
  // Inicializamos la emisora BLE de Bluefruit...
  // 
  elPublicador.encenderEmisora();

  delay( 1000 ); 

  elMedidor.getInformacionSensor();

  elPuerto.escribir( "---- setup(): fin ---- \n " );

} // setup ()



// --------------------------------------------------------------
// loop ()
// --------------------------------------------------------------
namespace Loop {
  uint8_t cont = 0;
  bool leerEEPROM = true;
};

// ..............................................................
// ..............................................................
void loop () {

  using namespace Loop;
  using namespace Globales;

  if(leerEEPROM){
    
    leerEEPROM = false;
  }
  

  cont++;

  // 
  // Mido del sensor 
  // 
  elMedidor.iniciarMedicion('\r');

  elPuerto.escribir( "\n---- loop(): empieza " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );

  // 
  // Obtengo las mediciones y publico
  // 
  uint16_t valorConcentracion = elMedidor.getConcentracionGas();
  int intervaloEmision = 1000;
  uint8_t valorTemperatura = elMedidor.getTemperatura();
  uint8_t valorRH = elMedidor.getRH();
  String tipoMedicion = elMedidor.getTipoMedicion();

  elPublicador.publicarMedicion( valorConcentracion, /*valorTemperatura, valorRH, tipoMedicion, */
                  intervaloEmision // intervalo de emisión
                  );

  //A ver que saca en el puerto serie...
  elPuerto.escribir( "\n");
  elPuerto.escribir( valorConcentracion );
  /*elPuerto.escribir( "\n");
  elPuerto.escribir( valorTemperatura );
  elPuerto.escribir( "\n");
  elPuerto.escribir( valorRH );
  elPuerto.escribir( "\n");
  elPuerto.escribir( tipoMedicion );
  elPuerto.escribir( "\n");
  */

  /*elPuerto.escribir( "\n---- Envio C02: empieza \n" );
  elPuerto.escribir( valorConcentracion );
  elPublicador.publicarConcentracion( valorConcentracion,
              intervaloEmision // intervalo de emisión
              );

  elPuerto.escribir( "\n---- Envio C02: TERMINA \n" );

  // 
  // Obtengo la temperatura y publico
  // 
  

  elPuerto.escribir( "\n---- Envio Temperatura: empieza \n" );
  elPuerto.escribir( valorTemperatura );
  elPublicador.publicarTemperatura( valorTemperatura, 
                  intervaloEmision // intervalo de emisión
                  );
  elPuerto.escribir( "\n---- Envio Temperatura: TERMINA \n" );


  // 
  // Obtengo la humedad y publico
  // 
  

  elPuerto.escribir( "\n---- Envio Humedad Relativa: empieza \n" );
  elPuerto.escribir( valorRH );
  elPublicador.publicarRH( valorRH, 
                  intervaloEmision // intervalo de emisión
                  );
  elPuerto.escribir( "\n---- Envio Humedad Relativa: TERMINA \n" );

  elPuerto.escribir( "---- loop(): acaba **** " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );
  elPublicador.laEmisora.detenerAnuncio();*/
  delay( 1000 );
  // 
  // 
  // 
  
} // loop ()
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
