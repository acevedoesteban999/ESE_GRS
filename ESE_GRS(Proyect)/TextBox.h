#pragma once
#include "Forms.h"
#include "TimeDuration.h"

class TextBox:public Forms
{
public:
	bool escribiendo;
	char*escritura;
	TimeDuration tim;
	bool dosClicks;
	TextBox();
	TextBox(char*name,CRD crd,float wigth,float height,float TotalWigth,float TotalHeight):Forms(name,crd,wigth,height,TotalWigth,TotalHeight){
		dosClicks=escribiendo=false;
		escritura=new char;
		t=Type::TEXTBOX;
		escritura=new char(0);
	};
	TextBox(char*name,char*Escritura,CRD crd,float wigth,float height,float TotalWigth,float TotalHeight):Forms(name,crd,wigth,height,TotalWigth,TotalHeight){
		dosClicks=escribiendo=false;
		escritura=new char;
		t=Type::TEXTBOX;
		escritura=new char[strlen(Escritura)+1];
		escritura[strlen(Escritura)]=0;
		for(unsigned i=0;i<strlen(Escritura);i++)
			escritura[i]=Escritura[i];
	};
	~TextBox(){delete escritura;};
	bool Escribiendo(){
		return escribiendo;};
	char*GetEscritura(){
		return escritura;
	};
	void AddNewText(char*N){NewText(N);};
	void AddText(char letra){
		
		char*NewEscritura=new char[strlen(escritura)+1];
		for(unsigned i=0;i<strlen(escritura);i++)
			NewEscritura[i]=escritura[i];
		NewEscritura[strlen(escritura)]=letra;
		NewEscritura[strlen(escritura)+1]=0;
		escritura=NewEscritura;
		if(strlen(escritura)*10>Wigth)
			 Wigth+=(float)(strlen(escritura)*10)/5;
	}
	void SubText()
	{
		if(strlen(escritura)>0)
		{
	    char*NewEscritura=new char[strlen(escritura)];
		for(unsigned i=0;i<strlen(escritura)-1;i++)
			NewEscritura[i]=escritura[i];
		NewEscritura[strlen(escritura)-1]=0;
		escritura=NewEscritura;
		}
	}
	void CambiarEscritura(char*Newescritura){NewText(Newescritura);};
	void NewText(char*newText)
	{
		
		escritura=new char[strlen(newText)+1];
		escritura[strlen(newText)]=0;
		for(unsigned i=0;i<strlen(newText);i++)
			escritura[i]=newText[i];
		if((float)strlen(escritura)*10>Wigth)
		   Wigth+=(float)(strlen(escritura)*10)/2;
		
		
	}
	//PURAS///
	void Draw(){
	glPushMatrix();
				  glLoadIdentity();
				  glTranslatef((GLfloat)(-TotalWigth/2+coord->x),(GLfloat)(TotalHeight/2-coord->y),(GLfloat)2*this->TotalWigth-1); 
				  glColor3f(1,1,1);
				  glBegin(GL_POLYGON);
				  glVertex3f(0,0,-1);
				  glVertex3f((GLfloat)Wigth,0,-1);
				  glVertex3f((GLfloat)Wigth,(GLfloat)-Height,-1);
				  glVertex3f(0,(GLfloat)-Height,-1);
				  glEnd();
				  glLoadIdentity();
				  Forms::teXt(escritura,(GLfloat)coord->x,(GLfloat)coord->y,(GLfloat)0,(GLfloat)0,(GLfloat)0,1,this);
				  glPopMatrix();
	
	
	
	};
	unsigned Click(){
		if(!escribiendo)
			escribiendo=true;

		if(!dosClicks)
		{
			dosClicks=true;
			tim.ResettIncrementa(&tim);
			tim.Incrementa(&tim);
		}
		else if(dosClicks)
		{
		dosClicks=false;
		tim.Incrementa(&tim);
		if(tim.TimE<=1.5)
			NewText("");

		}

		return t;
	}
	void NoClick(){
		if(escribiendo)
			escribiendo=false;
	}
	


};