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
  Medidor elMedidor;
  
};

/**
 * La funcion inicializarPlaquita() de momento nada.
 * inicializarPlaquita()
 */

void inicializarPlaquita () {

  // de momento nada

}

/**
 * La funcion setup() esta funcion sólo se ejecutará una vez al inicio del sistema.
 * setup() ->
 */

void setup() {

  Globales::elPuerto.esperarDisponible();
  inicializarPlaquita();

  // Suspend Loop() to save power
  // suspendLoop();
  Globales::elPublicador.encenderEmisora();

  // Globales::elPublicador.laEmisora.pruebaEmision();

  Globales::elMedidor.iniciarMedidor();

  esperar( 1000 );
  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " );

}

/**
 * La funcion lucecitas() enciende y apaga el led.
 * lucecitas()
 */

inline void lucecitas() {
  using namespace Globales;

  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  elLED.brillar( 100 );
  esperar ( 400 ); 
  Globales::elLED.brillar( 100 );
  esperar ( 400 ); 
  Globales::elLED.brillar( 1000 );
  esperar ( 1000 ); 
} 

/**
 * La funcion Loop declara cont a 0.
 * Loop{
 *  cont:N = 0
 *  }:namespace
 */

namespace Loop {
  uint8_t cont = 0;
};

/**
 * La funcion loop() esta funcion se ejecutará en bucle mientras el sistema este en funcionamiento.
 * loop()
 */

void loop () {

  using namespace Loop;
  using namespace Globales;

  cont++;

  elPuerto.escribir( "\n---- loop(): empieza " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );
  lucecitas();

  int valorCO2 = elMedidor.medirCO2();
  
  elPublicador.publicarCO2( valorCO2+cont,
							cont,
							1000 // intervalo de emisión
							);
							
  // mido y publico
  int valorTemperatura = elMedidor.medirTemperatura();
  
  elPublicador.publicarTemperatura( valorTemperatura+cont, 
									cont,
									1000 // intervalo de emisión
									);

  // prueba para emitir un iBeacon y poner
  // en la carga (21 bytes = uuid 16 major 2 minor 2 txPower 1 )
  // lo que queramos (sin seguir dicho formato)

  // Al terminar la prueba hay que hacer Publicador::laEmisora privado

  char datos[21] = {
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H'
  };

  // elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( &datos[0], 21 );
 // elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( "MolaMolaMolaMolaMolaM", 21 );

  esperar( 2000 );

  elPublicador.laEmisora.detenerAnuncio();
  
  elPuerto.escribir( "---- loop(): acaba **** " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );
  
}
