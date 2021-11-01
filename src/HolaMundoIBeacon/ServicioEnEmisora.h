// -*-c++-*-

// Autor: Juan Carlos Hernandez Ramirez
// 22/09/2021

#ifndef SERVICIO_EMISORA_H_INCLUIDO
#define SERVICIO_EMISORA_H_INCLUIDO
// ----------------------------------------------------
#include <vector>

// ----------------------------------------------------
/**
 * La funcion alReves() recibe un parametro Texto y pone al revés el contenido de una array en el mismo array.
 * Texto,Z -> esperar()
 * @param p parametro de valor Texto.
 * @param n parametro de valor entero.
 * @return p.
 */
template< typename T >
T *  alReves( T * p, int n ) { 
  T aux;

  for( int i=0; i < n/2; i++ ) { // pone al revés el contenido de una array en el mismo array
	aux = p[i];
	p[i] = p[n-i-1];
	p[n-i-1] = aux;
  }
  return p;
} // ()
// ----------------------------------------------------

// ----------------------------------------------------
/**
 * La funcion stringAUint8AlReves() copio nombreServicio -> uuidServicio pero al revés.
 * Texto,Z,Z -> stringAUint8AlReves() -> Z
 * @param pString parametro de valor Texto.
 * @param pUint parametro de valor natural.
 * @param tamMax parametro de valor entero.
 * @return pUint.
 */
uint8_t * stringAUint8AlReves( const char * pString, uint8_t * pUint, int tamMax ) {

	int longitudString =  strlen( pString );
	int longitudCopiar = ( longitudString > tamMax ? tamMax : longitudString );
	for( int i=0; i<=longitudCopiar-1; i++ ) {
	  pUint[ tamMax-i-1 ] = pString[ i ];
	} // for

	return pUint;
} // ()
// ----------------------------------------------------------

// ----------------------------------------------------------
class ServicioEnEmisora { // classe ServicioEnEmisora
public:

  // --------------------------------------------------------
  /**
  * La funcion CallbackCaracteristicaEscrita() hace un callBack de las caracteristicas escritas.
  * CallBackCaracteristicaEscrita:N,BLECharasteristic,N,N
  */
  using CallbackCaracteristicaEscrita = void ( uint16_t conn_handle,
											   BLECharacteristic * chr,
											   uint8_t * data, uint16_t len); 
  // --------------------------------------------------------

  class Caracteristica { //classe Caracteristica
  private:

    // --------------------------------------------------------
    /**
	* La funcion uuidCaracteristica() el uuid se copia aquí (al revés) a partir de un string-c.
	* uuidCaracteristica:[N]
	*/
	uint8_t uuidCaracteristica[16] = { 
	  // least signficant byte, el primero
	  '0', '1', '2', '3', 
	  '4', '5', '6', '7', 
	  '8', '9', 'A', 'B', 
	  'C', 'D', 'E', 'F'
	};
	// --------------------------------------------------------

    // --------------------------------------------------------
	/**
	* La funcion laCaracteristica() declarar la laCaracteristica.
	* laCaracteristica:BLECharacteristic
	*/
	BLECharacteristic laCaracteristica;
    // --------------------------------------------------------

  public:

	// --------------------------------------------------------
	/**
	* La funcion Caracteristica() es un contructor que recibe un texto.
	* Texto -> Constructor() ->
	* @param nombreCaracteristica_ parametro de valor Texto.
	*/
	Caracteristica( const char * nombreCaracteristica_ )
	  :
	  laCaracteristica( stringAUint8AlReves( nombreCaracteristica_, &uuidCaracteristica[0], 16 ) )
	{
	  
	} // ()
	// --------------------------------------------------------

	// --------------------------------------------------------
	/**
	* La funcion Caracteristica() es un contructor.
	* Texto,N,SecureMode_t,N -> Constructor() ->
	* @param nombreCaracteristica_ parametro de valor Texto.
	* @param props parametro de valor natural.
	* @param permisoRead parametro de valor SecureMode_t.
	* @param permisoWrite parametro de valor SecureMode_t.
	* @param tam parametro de valor natural.
	*/
	Caracteristica( const char * nombreCaracteristica_ ,
					uint8_t props,
					SecureMode_t permisoRead,
					SecureMode_t permisoWrite, 
					uint8_t tam ) 
	  :
	  Caracteristica( nombreCaracteristica_ ) // llamada al otro constructor
	{
	  (*this).asignarPropiedadesPermisosYTamanyoDatos( props, permisoRead, permisoWrite, tam );
	} // ()
	// --------------------------------------------------------

  private:
	// .........................................................
	// CHR_PROPS_WRITE , CHR_PROPS_READ ,  CHR_PROPS_NOTIFY 
	// .........................................................
	/**
	* La funcion asignarPropiedades() no puedo escribir AUN si el constructor llama a esto: Serial.println( " laCaracteristica.setProperties( props ); ");.
	* N -> asignarPropiedades() ->
	* @param nombreCaracteristica_ parametro de valor natural.
	*/
	void asignarPropiedades ( uint8_t props ) {
	  (*this).laCaracteristica.setProperties( props );
	} // ()
	// .........................................................

	// .........................................................
	// SecureMode_t::SECMODE_OPEN  , SecureMode_t::SECMODE_NO_ACCESS
	// .........................................................
	/**
	* La funcion asignarPermisos() no puedo escribir AUN si el constructor llama a esto: Serial.println( "laCaracteristica.setPermission( permisoRead, permisoWrite ); " );.
	* SecureMode_t,SecureMode_t -> asignarPermisos() ->
	* @param permisoRead parametro de valor SecureMode_t.
	* @param permisoWrite parametro de valor SecureMode_t.
	*/
	void asignarPermisos( SecureMode_t permisoRead, SecureMode_t permisoWrite ) {
	  (*this).laCaracteristica.setPermission( permisoRead, permisoWrite );
	} // ()
	// .........................................................

	// .........................................................
	/**
	* La funcion asignarTamanyoDatos().
	* N -> asignarTamanyoDatos() ->
	@param tam parametro de valor natural.
	*/
	void asignarTamanyoDatos( uint8_t tam ) {
	  // no puedo escribir AUN si el constructor llama a esto: Serial.print( " (*this).laCaracteristica.setFixedLen( tam = " );
	  // no puedo escribir AUN si el constructor llama a esto: Serial.println( tam );
	  // (*this).laCaracteristica.setFixedLen( tam );
	  (*this).laCaracteristica.setMaxLen( tam );
	} // ()

  public:
	// .........................................................

	// .........................................................
	/**
	* La funcion asignarPropiedadesPermisosYTamanyoDatos() asigna propiedades y permisos y tamanyo a los datos.
	* N,SecureMode_t,SecureMode_t,N -> asignarPropiedadesYTamanyoDatos() ->
	* @param props parametro de valor natural.
	* @param permisoRead parametro de valor SecureMode_t.
	* @param permisoWrite parametro de valor SecureMode_t.
	* @param tam parametro de valor natural.
	*/
	void asignarPropiedadesPermisosYTamanyoDatos( uint8_t props,
												 SecureMode_t permisoRead,
												 SecureMode_t permisoWrite, 
												 uint8_t tam ) {
	  asignarPropiedades( props );
	  asignarPermisos( permisoRead, permisoWrite );
	  asignarTamanyoDatos( tam );
	} // ()												
	// .........................................................

	// .........................................................
	/**
	* La funcion escribirDatos() escribe los datos.
	* Texto -> escribirDatos()
	* @param str parametro de valor texto.
	* @return r.
	*/
	uint16_t escribirDatos( const char * str ) {
	  // Serial.print( " return (*this).laCaracteristica.write( str  = " );
	  // Serial.println( str );

	  uint16_t r = (*this).laCaracteristica.write( str );

	  // Serial.print( ">>>Escritos " ); Serial.print( r ); Serial.println( " bytes con write() " );

	  return r;
	} // ()
	// .........................................................

	// .........................................................
	/**
	* La funcion notificarDatos() notifica los datos.
	* Texto -> NotificasDatos()
	*	  N <-
	* @param str parametro de valor texto.
	* @return r.
	*/
	uint16_t notificarDatos( const char * str ) {
	  
	  uint16_t r = laCaracteristica.notify( &str[0] );

	  return r;
	} //  ()
	// .........................................................

	// .........................................................
	/**
	* La funcion instalarCallbackCaracteristicaEscrita() instala el Callback de caracteristicaEscrita.
	* CallBackCaracteristicaEscrita -> instalarCallBeckCaracteristicaEscrita()
	* @param cd parametro de valor CallbackCaracteristicaEscrita.
	*/
	void instalarCallbackCaracteristicaEscrita( CallbackCaracteristicaEscrita cb ) {
	  (*this).laCaracteristica.setWriteCallback( cb );
	} // ()
	// .........................................................

	// .........................................................
	/**
	* La funcion activar() inicializa laCaracteristica.
	* activar() ->
	*/
	void activar() {
	  err_t error = (*this).laCaracteristica.begin();
	  Globales::elPuerto.escribir(  " (*this).laCaracteristica.begin(); error = " );
	  Globales::elPuerto.escribir(  error );
	} // ()
	// --------------------------------------------------------

  }; // class Caracteristica
  
  // --------------------------------------------------------
private:
  
  // --------------------------------------------------------
  /**
  * La funcion uuidServicio() el uuid se copia aquí (al revés) a partir de un string-c.
  * uuidServicio:[N]
  */
  uint8_t uuidServicio[16] = {
	// least signficant byte, el primero
	'0', '1', '2', '3', 
	'4', '5', '6', '7', 
	'8', '9', 'A', 'B', 
	'C', 'D', 'E', 'F'
  };
  // --------------------------------------------------------

  // --------------------------------------------------------
  /**
  * La funcion elServicio() declarar la elServicio.
  * elServicio:BLEService
  */
  BLEService elServicio;
  // --------------------------------------------------------

  // --------------------------------------------------------
  /**
  * La funcion lasCaracteristicas() declarar el vector lasCaracteristicas.
  * lasCaracteristicas:[Caracteristica]
  */
  std::vector< Caracteristica * > lasCaracteristicas;

public:
  
  // .........................................................
  /**
  * La funcion ServicioEnEmisora() es un contstructor.
  * Texto -> Constructor() ->
  * @param nombreServicio_ parametro de valor Texto.
  */
  ServicioEnEmisora( const char * nombreServicio_ )
	:
	elServicio( stringAUint8AlReves( nombreServicio_, &uuidServicio[0], 16 ) )
  {
	
  } // ()
  // .........................................................

  // .........................................................
  /**
  * La funcion escribeUUID() escribe UUID.
  * escribeUUID()
  */
  void escribeUUID() {
	Serial.println ( "**********" );
	for (int i=0; i<= 15; i++) {
	  Serial.print( (char) uuidServicio[i] );
	}
	Serial.println ( "\n**********" );
  } // ()
  // .........................................................

  // .........................................................
  /**
  * La funcion anyadirCaracteristica() anyade una caracteristica a lasCaracteristicas.
  * Caracteristica -> anyadirCaracteristica() ->
  * @param car parametro de valor Caracteristica.
  */
  void anyadirCaracteristica( Caracteristica & car ) {
	(*this).lasCaracteristicas.push_back( & car );
  } // ()
  // .........................................................

  // .........................................................
  /**
  * La funcion activarServicio() activa elServicio.
  * activarServicio() <-
  */
  void activarServicio( ) {
	// entiendo que al llegar aquí ya ha sido configurado
	// todo: características y servicio
	err_t error = (*this).elServicio.begin();
	Serial.print( " (*this).elServicio.begin(); error = " );
	Serial.println( error );
	for( auto pCar : (*this).lasCaracteristicas ) {
	  (*pCar).activar();
	} // for

  } // ()
  // .........................................................

  // .........................................................
  /**
  * La funcion BLEService() "conversión de tipo": si pongo esta clase en un sitio donde necesitan un BLEService.
  * elServicio <- BLEService&()
  * @return elServicio
  */
  operator BLEService&() {
	return elServicio;
  } // ()
	
}; // class

#endif

// ----------------------------------------------------------
