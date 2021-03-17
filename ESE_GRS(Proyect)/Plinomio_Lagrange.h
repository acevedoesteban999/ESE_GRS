#pragma once
#include "CRD.h"
class Plinomio_Lagrange
{
	class Compt{
private:
	float*elemts;
	CRD*point;
	unsigned cont,cant;
public:
	Compt(){};
	Compt(CRD*point){
	cont=0;
	cant=100;
	elemts=new float[cant];
	this->point=point;
	};
	~Compt(){};
	void Add(CRD*point)
	{
		if(cont>=cant)
		{
		cant+=100;
		float*newElem=new float[cant];
		for(unsigned i=0;i<cont;i++)
			newElem[i]=elemts[i];
		elemts=newElem;
		}
		this->elemts[cont++]=(float)-point->x;
	};
	float Response(float x){
		float nom=1,denom=1;
		for(unsigned i=0;i<cont;i++)
		{
			nom*=(float)(x+elemts[i]);
			denom*=(float)(this->point->x+elemts[i]);
		}
		return (float)(this->point->y*(nom/denom));	
	}


};
public:
    CRD*points;
	Compt**Components;
	unsigned cant,cont;
public:
	Plinomio_Lagrange()
	{
		this->cont=0;
		this->cant=100;
		this->points=new CRD[this->cant];
		this->Components=new Compt*[this->cant];
	};
	~Plinomio_Lagrange()
	{
		delete points;
	};
	void AddPoint(CRD*point)
	{
	 if(cont>=cant)
		{
		cant+=100;
		CRD*newPoints=new CRD[cant];
		Compt**NewComp=new Compt*[cant];
		for(unsigned i=0;i<cont;i++)
		{
			newPoints[i]=points[i];
			NewComp[i]=Components[i];
		}
		points=newPoints;
		Components=NewComp;
		}


	 for(unsigned i=0;i<cont;i++)
		 Components[i]->Add(point);
	 Components[cont]=new Compt(point);
	 for(unsigned i=0;i<cont;i++)
		 Components[cont]->Add(&points[i]);

	 this->points[cont++]=*point;
	}
	float Response(float x)
	{
		float response=0;
		for(unsigned i=0;i<cont;i++)
			response+=Components[i]->Response(x);
		return response;
	}

};
