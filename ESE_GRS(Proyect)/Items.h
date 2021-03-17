#pragma once
#include "CRD.h"
#include "ESE_GRS.h"
#include "Matriz.h"
enum ItemsType{
 ITEMS,POINTSS,LINE_STRIP,SPLINECUBICO
};
class Items
{
public:
	CRD*PoIntS;
	ItemsType t;
	unsigned cont,cant;
	Items(){
	cont=0;
	cant=10;
	PoIntS=new CRD[cant];
	t=ItemsType::ITEMS;
	};
	virtual ~Items(){};
	virtual void Draw(){
		glPointSize(5);
		glColor3f(0,1,0);
		glBegin(GL_POINTS);
		for(unsigned i=0;i<cont;i++)
			glVertex3f((GLfloat)PoIntS[i].x,(GLfloat)PoIntS[i].y,(GLfloat)PoIntS[i].z);
		glEnd();
		glPointSize(1);
	};
	virtual void Add(CRD*point)
	{
	if(cont>=cant)
	   {
	      CRD*newPoints=new CRD[cant+10];
	      cant+=10;
	      for(unsigned i=0;i<cont;i++)
		     newPoints[i]=PoIntS[i];
	      delete PoIntS;
	      PoIntS=newPoints;
	   }
	   PoIntS[cont++]=*point;
	};
	virtual void Pure()=0;

};
class Points:public Items
{

public:
	Points():Items(){
		t=ItemsType::POINTSS;
	}
	~Points(){
		delete[] PoIntS;
	};
	void Pure(){};
};
class Strip_Line:public Items
{
public:
	Strip_Line():Items()
	{
		t=ItemsType::LINE_STRIP;
	};
	~Strip_Line(){
	};
	void Draw()
	{
		Items::Draw();
		if(cont==1)
		{
			glPointSize(2);
			glBegin(GL_POINTS);
		    glVertex3f((GLfloat)PoIntS[0].x,(GLfloat)PoIntS[0].y,(GLfloat)PoIntS[0].z);
			glEnd();
			glPointSize(1);
		}
		else
		{
		   glLineWidth(2);
		   glColor3f(1,1,1);
		   glBegin(GL_LINE_STRIP);
		   for(unsigned i=0;i<cont;i++)
		      glVertex3f((GLfloat)PoIntS[i].x,(GLfloat)PoIntS[i].y,(GLfloat)PoIntS[i].z);
		   glEnd();
		   glLineWidth(1);
		 }

	};
	void Pure(){};
};
class SplineCubico:public Items
{
private:
	float*h,*yi,*A,*B,*C,*D,*PUNTOSY;
	unsigned cantPuntY,contPuntY;
	Matriz*m;
public:
	SplineCubico():Items(){
		t=ItemsType::SPLINECUBICO;
		h=new float[cont];
		yi=new float[cant];
		A=new float(0);
		B=new float(0);
		C=new float(0);
		D=new float(0);
		PUNTOSY=new float(0);
		contPuntY=0;
		cantPuntY=1;
	}
	~SplineCubico(){
		delete h,yi,A,B,C,m;
	};
	void Add(CRD*point)
	{
		Items::Add(point);
		if(cant-cont==9&&cont!=1)
		{
			float*newh=new float[cant];
			float*newyi=new float[cant];
			for(unsigned i=0;i<cont;i++)
			{
				newh[i]=h[i];
			    newyi[i]=yi[i];
			}
			h=newh;
			yi=newyi;
		} 
		if(cont>1)
		{
			h[cont-2]=(float)(PoIntS[cont-1].x-PoIntS[cont-2].x);
			yi[cont-2]=(float)((PoIntS[cont-1].y-PoIntS[cont-2].y)/h[cont-2]);
			if(cont>2)
			{
			   float*Elements=new float[(unsigned)((cont-1)*(cont-1))];
			   float*Result=new float[cont-1];
			   unsigned contElements=0;
			   for(unsigned i=0;i<cont-2;i++)
			   {
			      for(unsigned j=0;j<cont-2;j++)
			      {
			      	if(i==j)
			   		Elements[contElements++]=2*(h[i]+h[i+1]);
			   	else
			   		Elements[contElements++]=h[1];
			      }
			      Result[i]=6*(yi[i+1]-yi[i]);
		 	   }
			   m=new Matriz(cont-2,Elements,Result);
			   float*M1=m->Solucion_ReduccionFilas();
			   float*M=new float[cont-1];
			   M[0]=0;
			   M[cont-1]=0;
			   for(unsigned i=0;i<cont-2;i++)
			      M[i+1]=M1[i];
			   A=new float[cont-1];
			   B=new float[cont-1];
			   C=new float[cont-1];
			   D=new float[cont-1];
			   for(unsigned i=0;i<cont-1;i++)
			   {
				  A[i]=(M[i+1]-M[i])/(6*h[i]);
				  B[i]=M[i]/2;
				  C[i]=yi[i]-((M[i+1]+2*M[i])/6)*h[i];
				  D[i]=(float)PoIntS[i].y;
			   }
			   cantPuntY=(unsigned)(PoIntS[cont-1].x - PoIntS[0].x);
			   contPuntY=0;
			   PUNTOSY=new float[cantPuntY];
			   for(unsigned i=0;i<cont-1;i++)
			      for(float j=(float)PoIntS[i].x;(i==cont-2?j<=(float)PoIntS[i+1].x:j<(float)PoIntS[i+1].x);j++)
					  PUNTOSY[contPuntY++]=(float)(A[i]*pow(j-PoIntS[i].x,3)   +  B[i]*pow(j-PoIntS[i].x,2)   +   C[i]*(j-PoIntS[i].x)   +   D[i]);
			}
		}
	}
	void Draw()
	{
		Items::Draw();
		if(cont>1)
		{
			glLineWidth(2);
			glColor3f(1,1,1);
			glBegin(GL_LINE_STRIP);
			for(unsigned i=0;i<contPuntY;i++)
			{
				glVertex3f((GLfloat)i,(GLfloat)PUNTOSY[i],0);
			}
			glEnd();
			glLineWidth(1);
			
		}
		
		/* if(cont>1)
		 {
			 for(unsigned i=0;i<cont-1;i++)
			 {
				 std::cout<<"S"<<i<<":"<<A[i]<<"(x"<<(PoIntS[i].x>=0?"+":"")<<PoIntS[i].x<<")^3"<<(B[i]>=0?"+":"");
			     std::cout<<B[i]<<"(x"<<(PoIntS[i].x>=0?"+":"")<<PoIntS[i].x<<")^2"<<(C[i]>=0?"+":"");
				 std::cout<<C[i]<<"(x"<<(PoIntS[i].x>=0?"+":"")<<PoIntS[i].x<<")"<<(D[i]>=0?"+":"");
				 std::cout<<D[i]<<std::endl;
			 }
		 }*/
	}
	void Pure(){};
};