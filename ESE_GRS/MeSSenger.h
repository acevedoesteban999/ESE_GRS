#pragma once
#include <ctime>
#include "TimeDuration.h"
#include "ESE_GRS.h"
#include <iostream>
enum position{
	CENTER_TOP,CENTER_BUTTOM
	};
class MeSSenger
{
	
private:
	char*meSSenger;
	unsigned BigLV;
	GLfloat R,G,B,x,y,z;
	TimeDuration*t;
public:
	bool Drawing;
	MeSSenger()
	{
		meSSenger=new char[1];
		t=new TimeDuration();
		Drawing=false;
	};
	MeSSenger(char*meSSenger,position Position,GLfloat wigth,GLfloat height,float Time=3,GLfloat R=1,GLfloat G=1,GLfloat B=1,unsigned BigLV=0,GLfloat x=0,GLfloat y=0,GLfloat z=0)
{
	this->meSSenger=new char[strlen(meSSenger)+1];
	this->meSSenger[strlen(meSSenger)]=0;
		for(unsigned i=0;i<strlen(meSSenger);i++)
			this->meSSenger[i]=meSSenger[i];
		if(Position==position::CENTER_TOP)
	{
		this->x=(GLfloat)-int(strlen(meSSenger)*4.5);
		this->y=(GLfloat)height/2-20;
		this->z=(GLfloat)2*wigth-1;
	}
	
		else if(Position==position::CENTER_BUTTOM)
	{
		this->x=(GLfloat)-int(strlen(meSSenger)*4.5);
		this->y=-(GLfloat)height/2-20;
		this->z=(GLfloat)2*wigth-1;
	}
	else
	{
	this->x=x;
	this->y=y;
	this->z=z;
	}
	this->t=new TimeDuration(Time);
		this->R=R;
		this->G=G;
		this->B=B;
		this->BigLV=BigLV;
		Drawing=true;
};
	~MeSSenger(void)
	{
		delete[]meSSenger;
		delete t;
	};
	static void textMSS(char*c,GLfloat x,GLfloat y,GLfloat z,GLfloat R,GLfloat G,GLfloat B,bool big,bool moreBig){
	//dibujo el char c en la posicion x,y,z con color RGB
	
	glColor3f(R,G,B);
	glRasterPos3f(x,y,z);					  
	for(unsigned int i=0;i<strlen(c);i++){
        if(moreBig)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		else if(big)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);
	    else 
	 	    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c[i]);
		
		
	}
}
	static void Drawing_and_Decremt(MeSSenger*m)
{
	if(m->Drawing)
	   {
	   if(!m->t->Decrementa(m->t))
	      {
			  MeSSenger::textMSS(m->meSSenger,m->x,m->y,m->z,m->R,m->G,m->B,m->BigLV==1?1:0,m->BigLV>1?1:0);
	      }
	   else
		   m->Drawing=false;
	   
	   }
};
	static void NewMessenger(char*newMessenger,MeSSenger*m){
		m->meSSenger=new char[strlen(newMessenger)+1];
		m->meSSenger[strlen(newMessenger)]=0;
		for(unsigned i=0;i<strlen(newMessenger);i++)
			m->meSSenger[i]=newMessenger[i];
	
	};
};

