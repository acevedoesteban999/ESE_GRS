#pragma once
#include <windows.h>
#include <iostream>

class PuertoSerie
{
public:
	PuertoSerie();
	PuertoSerie(const char* PuertoCom, unsigned long Velocidad);
	//PuertoSerie(System::String^PuertoCom, unsigned long Velocidad);
	~PuertoSerie();

	void inicializa(const char* PuertoCom, unsigned long Velocidad);
	char* Recibir();
	void Trasmitir( char *data);
	//void Trasmitir(System::String^data);
	bool Error(){return error;};
	bool EstaConectado();
	char* ErrorStr(){return errorstr;};

private:
	HANDLE handler;
	bool IsConectado;
	bool error;
	char*errorstr; 
};

