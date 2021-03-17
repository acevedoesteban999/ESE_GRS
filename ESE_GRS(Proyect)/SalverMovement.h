#pragma once
#include <fstream>
using namespace std;
class SalverMovement
{
private:
	char*movimientos;
	unsigned cant,cont;
public:
	bool Enable,errorCarga;
	unsigned porciento;
	SalverMovement(void)
	{
	   cant=100;
	   cont=0;
	   movimientos=new char[cant];
	   movimientos[0]=0;
	   Enable=errorCarga=false;
	};
	~SalverMovement(void){};
	static void Add(char movemt,SalverMovement*sm){
		if(sm->cont+1>=sm->cant)
		{
		char*newData=new char[sm->cant+100];
		sm->cant+=100;
		for(unsigned i=0;i<sm->cont;i++)
		newData[i]=sm->movimientos[i];
		delete sm->movimientos;
		sm->movimientos=newData;
		}
		sm->movimientos[sm->cont++]=movemt;
		sm->movimientos[sm->cont]=0;
	};
	static void Clear(SalverMovement*sm){
		sm->cant=100;
		sm->cont=0;
		sm->movimientos=new char[sm->cant];
	    sm->movimientos[0]=0;
	   }
	static void Guardar(char*address,SalverMovement*sm){
	fstream f;
	char*Address;
	if(address[strlen(address)-1]!='v'||address[strlen(address)-2]!='t'||address[strlen(address)-3]!='m'||address[strlen(address)-4]!='.')
	{
		Address=new char[strlen(address)+5];
		unsigned ii=0;
		for(unsigned i=0;i<strlen(address);i++)
			Address[i]=address[i];
		Address[strlen(address)]='.';
		Address[strlen(address)+1]='m';
		Address[strlen(address)+2]='t';
		Address[strlen(address)+3]='v';
		Address[strlen(address)+4]=0;
	}
	else
	{
	Address=new char[strlen(address)+1];
	for(unsigned i=0;i<strlen(address);i++)
		Address[i]=address[i];
	Address[strlen(address)]=0;
	}
	f.open(Address,ios::out|ios::binary);
	if(f.is_open())
	{
		   f.write((char*)&sm->cont,sizeof(unsigned));
		   for(unsigned i=0;i<sm->cont;i++)
		   {
			   sm->porciento=(unsigned)((i/sm->cont)*100);
			   f.write(&sm->movimientos[i],sizeof(char));
		   }
		   
	}
	f.close();
	}
	static void Cargar(char*address,SalverMovement*sm){
	fstream f;
	if(address[strlen(address)-1]!='v'||address[strlen(address)-2]!='t'||address[strlen(address)-3]!='m'||address[strlen(address)-4]!='.')
	{
     sm->errorCarga=true;
		return;
	}
	sm->Clear(sm);
	f.open(address,ios::in|ios::binary);
	if(f.is_open())
	{
	   f.read((char*)&sm->cont,sizeof(unsigned));
	   sm->movimientos=new char[sm->cont+1];
	   sm->movimientos[sm->cont]=0;
	   sm->cant=sm->cont;
       for(unsigned i=0;i<sm->cont;i++)
	   {
		   sm->porciento=(unsigned)((i/sm->cont)*100);
		   f.read((char*)&sm->movimientos[i],sizeof(char));
	   }
	}
	else
		sm->errorCarga=true;
	f.close();
}
	static void MostrarMovent(SalverMovement*sm);
	static unsigned GETCont(SalverMovement*sm){return sm->cont;};
	static char*GETMovimientos(SalverMovement*sm){return sm->movimientos;};
	
	
	
	
	};


