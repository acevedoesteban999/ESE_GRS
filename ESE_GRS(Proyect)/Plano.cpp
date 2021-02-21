#include "Plano.h"
#include <math.h>

Plano::Plano(void)
{
}

Plano::Plano(CRD*punts){
	CRD Punt1=punts[0],Punt2=punts[1],Punt3=punts[2];
	Punto1=new CRD(Punt1);
	CRD v1,v2;
	double d1,d2,d3,d4,d5,d6;
	v1.x=Punt1.x-Punt2.x;
	v1.y=Punt1.y-Punt2.y;
	v1.z=Punt1.z-Punt2.z;
	v2.x=Punt1.x-Punt3.x;
	v2.y=Punt1.y-Punt3.y;
	v2.z=Punt1.z-Punt3.z;
	d1=v1.y*v2.z;
	d2=v1.z*v2.y;
	d3=v1.x*v2.z;
	d4=v1.z*v2.x;
	d5=v1.x*v2.y;
	d6=v1.y*v2.x;
	this->A=d1-d2;
	this->B=-(d3-d4);
	this->C=-(d5-d6);
	this->D=-(A+B+C);
};
Plano::Plano(CRD Punt1,CRD Punt2,CRD Punt3){
	Punto1=new CRD(Punt1);
	CRD v1,v2;
	double d1,d2,d3,d4,d5,d6;
	v1.x=Punt1.x-Punt2.x;
	v1.y=Punt1.y-Punt2.y;
	v1.z=Punt1.z-Punt2.z;
	v2.x=Punt1.x-Punt3.x;
	v2.y=Punt1.y-Punt3.y;
	v2.z=Punt1.z-Punt3.z;
	d1=v1.y*v2.z;
	d2=v1.z*v2.y;
	d3=v1.x*v2.z;
	d4=v1.z*v2.x;
	d5=v1.x*v2.y;
	d6=v1.y*v2.x;
	this->A=d1-d2;
	this->B=-(d3-d4);
	this->C=d5-d6;
	this->D=-(A*Punto1->x+B*Punto1->y+C*Punto1->z);
	if(A<0)
	{
	A*=-1;
	B*=-1;
	C*=-1;
	D*=-1;
	}
}

Plano::~Plano(void)
{
}
double Plano::DistnciaReal(CRD punt,Plano*p){
    double denomin=sqrt((p->A*p->A)+(p->B*p->B)+(p->C*p->C));
	double real=(p->A*punt.x+p->B*punt.y+p->C*punt.z+p->D)/denomin;
	return real;
}
CRD Plano::Distncia(CRD punt,Plano*p){
	CRD puntPlano,V;
	double denomin,A=p->A,B=p->B,C=p->C,D=p->D;
	double t=(-D-A*punt.x-B*punt.y-C*punt.z)/(A*A+B*B+C*C);//calculo el parametro t como la inteseccion de la recta creada por le punot y la normal del plano y el plano
	puntPlano.x=punt.x+A*t;//calculo la coordenada x el punto de interseccion entre la recta y el plano
	puntPlano.y=punt.y+B*t;//calculo la coordenada y el punto de interseccion entre la recta y el plano
	puntPlano.z=punt.z+C*t;//calculo la coordenada z el punto de interseccion entre la recta y el plano
	//hallo el vector 
	V.x=puntPlano.x-punt.x;
	V.y=puntPlano.y-punt.y;
	V.z=puntPlano.z-punt.z;
	//calculo la norma	
	//double norma=sqrt(V.x*V.x+V.y*V.y+V.z*V.z);
	return V;

}
