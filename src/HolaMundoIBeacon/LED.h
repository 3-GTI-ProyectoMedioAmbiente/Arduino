// -*-c++-*-

// Autor: Juan Carlos Hernandez Ramirez
// 22/09/2021


#ifndef LED_H_INCLUIDO
#define LED_H_INCLUIDO

// ----------------------------------------------------------
/**
 * La funcion esperar() recibe un parametro tiempo que se utiliza para realizar una espera de ese valor dado.
 * Z -> esperar()
 * @param tiempo parametro tiempo dado de valor entero.
 * @return nada.
 */
void esperar (long tiempo) {
  delay (tiempo); //realizar una espera de ese valor dado
}
// ----------------------------------------------------------

// ----------------------------------------------------------
class LED { //classe Led 
private:
  int numeroLED; //parametro privado numeroLED de valor entero.
  bool encendido; //parametro privado encendido dado en formato booleano
public:

  // .........................................................
 /**
 * La funcion Led() es un contructor y recibe un parametro numero de valor entero.
 * Z -> Constructor() ->
 * @param numero parametro numero de valor entero.
 * @return nada.
 */
  LED (int numero)
	: numeroLED (numero), encendido(false)
  {
	pinMode(numeroLED, OUTPUT);
	apagar ();
  }
  // .........................................................

  // .........................................................
  /**
 * La funcion encender() se utiliza para encender el led.
 * encender() ->
 */
  void encender () {
	digitalWrite(numeroLED, HIGH); 
	encendido = true; //pone el booleano en true.
  }
  // .........................................................

  // .........................................................
  /**
 * La funcion apagar() se utiliza para apagar el led.
 * apagar() ->
 */
  void apagar () {
	  digitalWrite(numeroLED, LOW);
	  encendido = false; //pone el booleano en false.
  }
  // .........................................................

  // .........................................................
  /**
 * La funcion alternar() se utiliza para alternar el led.
 * alternar()
 */
  void alternar () {
	if (encendido) { //si encendido es true
	  apagar();
	} else { //si encendido es false
	  encender ();
	}
  } // ()
  // .........................................................
  
  // .........................................................
  /**
 * La funcion brillar() recibe un parametro tiempo de valor entero y hace que el les brille por un tiempo dado.
 * Z -> brillar() ->
 * @param numero parametro tiempo de valor entero.
 * @return nada.
 */
  void brillar (long tiempo) {
	encender ();
	esperar(tiempo); 
	apagar ();
  }
  // ----------------------------------------------------------
}; // class
// ----------------------------------------------------------
#endif
