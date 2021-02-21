#pragma once
#include "CRD.h"
class Plano
{
public:
	CRD*Punto1;
	double A,B,C,D;//Secuencia Ax+By+Cz+D=0
	Plano();
	Plano(CRD Punt1,CRD Punt2,CRD Punt3);
	Plano(CRD*punts);
	~Plano(void);
	static CRD Distncia(CRD punto,Plano*p);
	double DistnciaReal(CRD punt,Plano*p);
};

