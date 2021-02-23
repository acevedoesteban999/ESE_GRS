#pragma once
#include "CRD.h"
#include <iostream>
#include "GL\freeglut.h"
using namespace std;
class Sistema_Cartesiano
{

public:
	CRD*Vertex;
	unsigned*NewLine,*NewPoint;
	unsigned cant,cont,cantNL,contNL,cantNP,contNP;
	bool PintLinSusp;
	Sistema_Cartesiano(void){
	cont=contNL=contNP=0;
	cant=100;
	cantNL=cantNP=100;
	Vertex=new CRD[cant]; 
	NewLine=new unsigned[cantNL];
	NewPoint=new unsigned[cantNP];
	PintLinSusp=false;
	};
	~Sistema_Cartesiano(){delete NewLine,NewPoint,Vertex;};
	static void Pintar_NoPintar_LineaSuspensiva(bool PintLinSusP,Sistema_Cartesiano*sc){
	    sc->PintLinSusp=PintLinSusP;
	};
	static void NoPintarLineaSuspensiva(Sistema_Cartesiano*sc){sc->PintLinSusp=false;}; 
	static void Draw(CRD*cooRd,Sistema_Cartesiano*sc)
	{
	if(sc->cont)
	   {

        glColor3f(1,1,1);
	   
	    //Puntos//////////////////////////
			  glPointSize(5);
	          glBegin(GL_POINTS);
			  for(unsigned i=0;i<sc->cont;i++)//PUNTOS//Siempre pinto todos los puntos
	             {
			     glVertex3f((GLfloat)sc->Vertex[i].x,(GLfloat)sc->Vertex[i].y,(GLfloat)sc->Vertex[i].z);
	             }
	          glEnd();
	      //Lineas///////////////////////////
			  glPointSize(3);
		     glBegin(GL_LINE_STRIP);
	         for(unsigned i=0;i<sc->cont;i++)//LINEAS
	           {
				   bool contin=false;
				   for(unsigned ii=0;ii<sc->contNP;ii++)//si ese vetice es solo un punto
				   {
					   if(sc->NewPoint[ii]==i)
			           {
						   contin=true;
						   break;
				       }
				   
				   }
				   if(contin)//si era un punto subo al siguinete elemento del for
					   continue;
		        for(unsigned ii=0;ii<sc->contNL;ii++)//si este vertice es una nueva linea
		           {
			         if(sc->NewLine[ii]==i)
			           {
				        glEnd();//cambio a line strip de nuevo para q no cuente el ultimo elemento por donde va el for del arreglo de vertices
				        glBegin(GL_LINE_STRIP);
			          }
		           }
		        glVertex3f((GLfloat)sc->Vertex[i].x,(GLfloat)sc->Vertex[i].y,(GLfloat)sc->Vertex[i].z);//pinto el vertice para recta strip
	          }
		     glEnd();
	         if(sc->PintLinSusp)//LINEAS SUSPENSIVAS
	           {
	            glBegin(GL_LINES);
	            double a,b,c,d,e,f;
	            a=sc->Vertex[sc->cont-1].x;
	            b=sc->Vertex[sc->cont-1].y;
	            c=sc->Vertex[sc->cont-1].z;
	            d=cooRd->x-sc->Vertex[sc->cont-1].x;
	            e=cooRd->y-sc->Vertex[sc->cont-1].y;
	            f=cooRd->z-sc->Vertex[sc->cont-1].z;
	            for(unsigned i=0;i<=9;i++)
	               glVertex3f((GLfloat)(a+i*(d/9)),(GLfloat)(b+i*(e/9)),(GLfloat)(c+i*(f/9)));
	            glEnd();
	           }
	    } 
	
	};
	static void add(CRD vertex,Sistema_Cartesiano*sc){
	if(sc->cont>=sc->cant)
	{
		
		CRD*newdata=new CRD[sc->cant+100];
		sc->cant+=100;
		for(unsigned i=0;i<sc->cont;i++)
		{
			newdata[i]=sc->Vertex[i];
			newdata[i]=sc->Vertex[i];
			newdata[i]=sc->Vertex[i];
		}
		sc->Vertex=newdata;
	}
	sc->Vertex[sc->cont++]=vertex;

	
	};
	static void NewLINE(Sistema_Cartesiano*sc)
	{
	 if(sc->contNL>=sc->cantNL)
	     {
		  unsigned*NewData=new unsigned[sc->cantNL+10];
		  sc->cantNL+=10;
		  for(unsigned i=0;i<sc->contNL;i++)
			 NewData[i]=sc->NewLine[i];
		  sc->NewLine=NewData;
	      }
	sc->NewLine[sc->contNL++]=sc->cont;
	
	};
	static void NewPOINT(Sistema_Cartesiano*sc){
	if(sc->contNP>=sc->cantNP)
	     {
		  unsigned*NewData=new unsigned[sc->cantNP+10];
		  sc->cantNP+=10;
		  for(unsigned i=0;i<sc->contNP;i++)
			 NewData[i]=sc->NewPoint[i];
		  sc->NewPoint=NewData;
	      }
	sc->NewPoint[sc->contNP++]=sc->cont;
	};
	static void Clear(Sistema_Cartesiano*sc){sc=new Sistema_Cartesiano;}
	static void CancelLastPoint(Sistema_Cartesiano*sc){
	if(sc->cont>0)
		{
		for(unsigned i=0;i<sc->contNP;i++)
		{
			if(sc->NewPoint[i]==sc->cont-1)
			{
				for(unsigned ii=i;ii<sc->contNP-1;i++)
					sc->NewPoint[i]=sc->NewPoint[i+1];
				sc->contNP--;
			}
		}
		for(unsigned i=0;i<sc->contNL;i++)
		{
			if(sc->NewLine[i]==sc->cont-1)
			{
				for(unsigned ii=i;ii<sc->contNL-1;ii++)
					sc->NewLine[ii]=sc->NewLine[ii+1];
				sc->contNL--;
			}
		}

		
			sc->cont--;
		}
	};
	static double* Media(Sistema_Cartesiano*sc){
	   double*d=new double[3];
	d[0]=0;
	d[1]=0;
	d[2]=0;
	
	for(unsigned i=0;i<sc->cont;i++)
	{
		d[0]+=sc->Vertex[i].x;
		d[1]+=sc->Vertex[i].y;
		d[2]+=sc->Vertex[i].z;
	}
	d[0]/=sc->cont;
	d[1]/=sc->cont;
	d[2]/=sc->cont;
	return d;
	};





};