#pragma once
#include "CRD.h"
#include "ESE_GRS.h"
enum ItemsType{
 ITEMS,POINTSS,LINE_STRIP,CURVE
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
	~Items(){};
	virtual void Draw()=0;
	void Add(CRD*point)
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
	void Draw(){
		glPointSize(2);
		glColor3f(1,1,1);
		glBegin(GL_POINTS);
		for(unsigned i=0;i<cont;i++)
			glVertex3f((GLfloat)PoIntS[i].x,(GLfloat)PoIntS[i].y,(GLfloat)PoIntS[i].z);
		glEnd();
		glPointSize(1);
	};
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
};
class Curve:public Items
{
	Curve():Items(){
		t=ItemsType::CURVE;
	}
	~Curve(){};
	void Draw(){

	}
};