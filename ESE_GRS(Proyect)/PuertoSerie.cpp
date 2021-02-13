#include "PuertoSerie.h"
#include <iostream>
using namespace std;

PuertoSerie::PuertoSerie()
	:IsConectado(false)
{
}


 PuertoSerie::PuertoSerie(const char* PuertoCom, unsigned long Velocidad):IsConectado(false)
{

	inicializa(PuertoCom,Velocidad);
}
 /*PuertoSerie::PuertoSerie(System::String^PuertoCom, unsigned long Velocidad):IsConectado(false)
{
	msclr::interop::marshal_context context;
	const char*c=context.marshal_as<const char*>(PuertoCom);
	inicializa(c,Velocidad);
}*/

PuertoSerie::~PuertoSerie()
{
	if(IsConectado)
	{
		IsConectado=false;
		CloseHandle(handler);
	}
}

void PuertoSerie::inicializa(const char* PuertoCom, unsigned long Velocidad)
{
	handler=CreateFile(PuertoCom,GENERIC_READ | GENERIC_WRITE,NULL,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	if (handler==INVALID_HANDLE_VALUE)
	{
		error=true;
	    errorstr="ERROR: CreateFile";
		return;
	}
	DCB ParametrosTxSerie;
	if (!GetCommState(handler,&ParametrosTxSerie))
	{
		error=true;
		errorstr="ERROR: GetCommState";
		return;
	}
	ParametrosTxSerie.DCBlength=sizeof(DCB);
	ParametrosTxSerie.BaudRate=Velocidad;
	ParametrosTxSerie.ByteSize=8;
	ParametrosTxSerie.StopBits=TWOSTOPBITS;
	ParametrosTxSerie.Parity=(BYTE)PARITY_NONE;
	if(!SetCommState(handler,&ParametrosTxSerie))
	{
		error=true;
		errorstr="ERROR: SetCommStatus";
		return;
	}
	IsConectado=true;
	PurgeComm(handler,PURGE_RXCLEAR|PURGE_TXCLEAR);
	error=false;
}
char* PuertoSerie::Recibir()
{
	DWORD leidos;
	COMSTAT cs;
	char*cadena=NULL;
	ClearCommError(handler,&leidos,&cs);
	leidos=0;
	if(cs.cbInQue){
		cadena=new char[cs.cbInQue+3];
		cadena[cs.cbInQue]=0;
		ReadFile(handler,cadena,cs.cbInQue,&leidos,NULL);
		
		return cadena;
	}
	return cadena;
}
	
void PuertoSerie::Trasmitir(char *oBuffer)
{
	DWORD iBytesWritten;
	iBytesWritten=0;
	WriteFile(handler,oBuffer,strlen(oBuffer),&iBytesWritten,NULL);
}
/*void PuertoSerie::Trasmitir(System::String^data)
{
	msclr::interop::marshal_context context;
	const char*c=context.marshal_as<const char*>(data);
	Trasmitir((char*)c);
}*/

bool PuertoSerie::EstaConectado()
{
	return IsConectado;
}