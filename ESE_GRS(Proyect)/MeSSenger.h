#pragma once
#include <ctime>
#include "TimeDuration.h"
#include "ESE_GRS.h"
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
	MeSSenger(){Drawing=false;};
	MeSSenger(char*meSSenger,position Position,GLfloat wigth,GLfloat hight,float Time=3,GLfloat R=1,GLfloat G=1,GLfloat B=1,unsigned BigLV=0,GLfloat x=0,GLfloat y=0,GLfloat z=0);
	~MeSSenger(void);
	static void Drawing_and_Decremt(MeSSenger*m);
	static void NewMessenger(char*newMessenger,MeSSenger*m){
		m->meSSenger=new char[strlen(newMessenger)+1];
		m->meSSenger[strlen(newMessenger)]=0;
		for(unsigned i=0;i<strlen(newMessenger);i++)
			m->meSSenger[i]=newMessenger[i];
	
	};
};

