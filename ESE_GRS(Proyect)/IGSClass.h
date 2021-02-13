#pragma once
#include <fstream>
#include"CRD.h"
using namespace std;
class IGSClass
{
private:
	unsigned S,G,D,P,ContDs,ContPs,LastD,LastP;
	unsigned cant,cont,cantNL,contNL;
	CRD*puntoRestriccion;
public:
	CRD*Vertex;
	unsigned*NewLine;
	IGSClass(void);
	~IGSClass(){delete NewLine,Vertex;};
	static void add(CRD vertex,IGSClass*igs);
	static void NewLINE(IGSClass*igs);
	static void End(char*name,IGSClass*igs);
	static void Clear(IGSClass*igs){igs=new IGSClass;}
	static void SetRestriccion(CRD*crd,IGSClass*igs){
		igs->puntoRestriccion=new CRD(*crd);
	}
	static double getCoordRestricion(unsigned opcion,IGSClass*igs){
		switch (opcion)
		{
		case 0:
			return igs->puntoRestriccion->x;
			break;
		case 1:
			return igs->puntoRestriccion->y;
			break;
		case 2:
			return igs->puntoRestriccion->z;
			break;
	   }
	}
	static unsigned GETCont(IGSClass*igs){return igs->cont;};
	static unsigned GETContNL(IGSClass*igs){return igs->contNL;};
	static void CancelLastPoint(IGSClass*igs){if(igs->cont>0)igs->cont--;};
};

