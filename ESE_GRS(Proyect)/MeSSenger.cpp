#include "MeSSenger.h"
#include <iostream>


MeSSenger::MeSSenger(char*meSSenger,position Position,GLfloat wigth,GLfloat height,float Time,GLfloat R,GLfloat G,GLfloat B,unsigned BigLV,GLfloat x,GLfloat y,GLfloat z)
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
}
void MeSSenger::Drawing_and_Decremt(MeSSenger*m)
{
	if(m->Drawing)
	   {
	   if(!m->t->Decrementa(m->t))
	      {
			  ESE_GRS::text(m->meSSenger,m->x,m->y,m->z,m->R,m->G,m->B,m->BigLV==1?1:0,m->BigLV>1?1:0);
	      }
	   else
		   m->Drawing=false;
	   
	   }
}

