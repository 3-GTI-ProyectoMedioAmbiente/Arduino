// -*-c++-*-

// Autor: Juan Carlos Hernandez Ramirez
// 22/09/2021

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

// --------------------------------------------------------------
class Publicador { // classe Publicador

  // ............................................................
private:
  /**
 * La funcion beaconUUID().
 * beaconUUID:[Texto]
 */
  uint8_t beaconUUID[16] = { 
	'E', 'P', 'S', 'G', '-', 'G', 'T', 'I', 
	'-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
	};
  // ............................................................

public:

  /**
 * La funcion laEmisora().
 * laEmisora:EmisoraBLE
 */
  EmisoraBLE laEmisora {
	"EA:86:B7:6C:64:9B_Angle_corp", //  nombre emisora
	  0x004b, // fabricanteID (Apple)
	  4 // txPower
	  };
  // ............................................................

  /**
 * La funcion RSSI().
 * RSSI():Z
 */
  const int RSSI = -53; // por poner algo, de momento no lo uso
  // ............................................................

public:

  // ............................................................
  /**
 * La funcion MedicionesID() almacena todas las mediciones.
 * MedicionesID -> N,N,N
 */
  enum MedicionesID  {
	CO2 = 11,
	TEMPERATURA = 12,
	RUIDO = 13
  };
  // ............................................................

  // ............................................................
  /**
  * La funcion Publicador() es un constructor vacio.
  * Publicador()
  */
  Publicador( ) {
	// ATENCION: no hacerlo aquí. (*this).laEmisora.encenderEmisora();
	// Pondremos un método para llamarlo desde el setup() más tarde
  } // ()
  // ............................................................

  // ............................................................
  /**
  * La funcion encenderEmisora() llama a la funcion laEmisora y la enciende.
  * encenderEmisora() ->
  */
  void encenderEmisora() {
	(*this).laEmisora.encenderEmisora();
  } // ()
  // ............................................................
  
  // ............................................................
  /**
  * La funcion publicarCO2() publica los valores de CO2 en laEmisora.
  * Z,N,Z -> publicarCO2() <-
  * @param valorCO2 parametro de valor entero.
  * @param contador parametro de valor natural.
  * @param tiempoEspera parametro de valor entero.
  */
  void publicarMedicion( int16_t valorConcentracion, long tiempoEspera ) {

	//
	// 1. empezamos anuncio
	//
	uint16_t major = (MedicionesID::CO2 << 8) ;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID 
											//major,
											//valorConcentracion, // minor
											//(*this).RSSI // rssi
									);

	/*
	Globales::elPuerto.escribir( "   publicarCO2(): valor=" );
	Globales::elPuerto.escribir( valorCO2 );
	Globales::elPuerto.escribir( "   contador=" );
	Globales::elPuerto.escribir( contador );
	Globales::elPuerto.escribir( "   todo="  );
	Globales::elPuerto.escribir( major );
	Globales::elPuerto.escribir( "\n" );
	*/

	//
	// 2. esperamos el tiempo que nos digan
	//
	esperar( tiempoEspera );

	//
	// 3. paramos anuncio
	//
	(*this).laEmisora.detenerAnuncio();
  } // ()
  // ............................................................

  // ............................................................
  /**
  * La funcion publicarCO2() publica la temperatura en laEmisora.
  * Z,N,Z -> publicarTemperatura() <-
  * @param valorTemperatura parametro de valor entero.
  * @param contador parametro de valor natural.
  * @param tiempoEspera parametro de valor entero.
  */
  
   // ()
  // --------------------------------------------------------------

}; // class

// --------------------------------------------------------------
#endif
