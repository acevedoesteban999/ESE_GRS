#pragma once
#include <fstream>
#include "GL\freeglut.h"
#include"CRD.h"
using namespace std;
class IGSClass
{
private:
	unsigned S,G,D,P,ContDs,ContPs,LastD,LastP;
	CRD*puntoRestriccion;
public:
	CRD*Vertex;
	unsigned*NewLine,*NewPoint;
	unsigned cant,cont,cantNL,contNL,cantNP,contNP;
	IGSClass(void);
	~IGSClass(){delete NewLine,Vertex;};
	static void Draw(bool PintLinSusp,unsigned RadioButtonCant,CRD*cooRd,IGSClass*igs);
	static void add(CRD vertex,IGSClass*igs);
	static void NewLINE(IGSClass*igs);
	static void NewPOINT(IGSClass*igs);
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
	static void CancelLastPoint(IGSClass*igs);
	static double* Media(IGSClass*igs);
	
};

