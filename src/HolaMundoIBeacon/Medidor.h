// -*- mode: c++ -*-

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

class Medidor {
private:

public:


  Medidor(  ) {
  }


  void iniciarMedidor() {
	// las cosas que no se puedan hacer en el constructor, if any
  } 

  int medirCO2() {
	return 235;
  }

  int medirTemperatura() {
	return -12;
  } 
	
}; // class

#endif
