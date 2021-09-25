// -*-c++-*-

// Autor: Juan Carlos Hernandez Ramirez
// 22/09/2021


#ifndef LED_H_INCLUIDO
#define LED_H_INCLUIDO


void esperar (long tiempo) {
  delay (tiempo);
}

class LED {
private:
  int numeroLED;
  bool encendido;
public:

  LED (int numero)
	: numeroLED (numero), encendido(false)
  {
	pinMode(numeroLED, OUTPUT);
	apagar ();
  }

  void encender () {
	digitalWrite(numeroLED, HIGH); 
	encendido = true;
  }

  void apagar () {
	  digitalWrite(numeroLED, LOW);
	  encendido = false;
  }

  void alternar () {
	if (encendido) {
	  apagar();
	} else {
	  encender ();
	}
  }

  void brillar (long tiempo) {
	encender ();
	esperar(tiempo); 
	apagar ();
  }
};

#endif
