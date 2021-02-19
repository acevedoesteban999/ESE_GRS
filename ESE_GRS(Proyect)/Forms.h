#pragma once
#include "CRD.h"
#include "ESE_GRS.h"
enum Type
{
	FORMS,BUTTON,BUTTONINITCOM,BUTTONINITSETANGULES,BUTTONCANCELSETANGULES,BUTTONCANCELCOM,BUTTONINTICARGAMOVENTS,BUTTONCANCELCARGAMOVENTS,BUTTONINITSTOPCOM,BUTTONCANCELSTOPCOM,BUTTOMGUARDARMOVENT,TEXTBOX,LABEL,RADIOBUTTONGROUP,RADIOBUTTON
};
class Forms
{
public:
	
	Type t;
	char*name;
	CRD*coord;
	float Wigth,Height,TotalWigth,TotalHeight;
	bool active;


public:
	Forms(){
		t=Type::FORMS;
		coord=new CRD();
		name=new char;
		active=false;
	};
	Forms(char*name,CRD coord,float wigth,float height,float TotalWigth,float TotalHeight){
		this->name=new char[strlen(name)+1];
		this->name[strlen(name)]=0;
		for(unsigned i=0;i<strlen(name);i++)
			this->name[i]=name[i];
		this->TotalHeight=TotalHeight;
		this->TotalWigth=TotalWigth;
		this->Wigth=wigth;
		this->Height=height;
		this->coord=new CRD(coord);
		this->active=true;
	};
	~Forms(){delete name,coord;};
	static void Activate(Forms*f){
		f->active=true;
	};
	static void Desactivate(Forms*f){
		f->active=false;
	};
	static void teXt(char*c,GLfloat x,GLfloat y,GLfloat R,GLfloat G,GLfloat B,unsigned LetterSize,Forms*f){
	//dibujo el char c en la posicion x,y,z con color RGB
	
	glColor3f(R,G,B);
	glRasterPos3f((GLfloat)-f->TotalWigth/2+x,(GLfloat)((f->TotalHeight/2)-y-f->Height*4/5),(GLfloat)2*f->TotalWigth-1);
	for(unsigned int i=0;i<strlen(c);i++){
		if(LetterSize==2)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		else if(LetterSize==1)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);
		else if(LetterSize==0)
	 	    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c[i]);
		
		
	}
}
	static bool IsPulsdo(float x,float y,Forms*f){
		if(f->t==Type::RADIOBUTTONGROUP)
		{
			if(x>=f->coord->x&&x<=f->coord->x+15&&y>=f->coord->y&&y<=f->coord->y+f->Height)
			   return true;
			return false;
		   
		}
		else if(x>=f->coord->x&&x<=f->coord->x+f->Wigth&&y>=f->coord->y&&y<=f->coord->y+f->Height)			
			return true;
		return false;
	}
	virtual void NewTotalProp(float wigth,float height){
		this->TotalWigth=wigth;
		this->TotalHeight=height;
	}
	virtual  bool Pulsado(float x,float y){
		if(x>=this->coord->x&&x<=this->coord->x+this->Wigth&&y>=this->coord->y&&y<=this->coord->y+this->Height)
			return true;
		return false;
	
	};
	virtual bool Escribiendo(){
		return false;};
	virtual char*GetEscritura(){
		return "NULL";};
	virtual bool GetEstoyEscribindo(){return false;}
	virtual unsigned GetChecket(){return 0;};
	virtual void NewText(char*newText){};
	virtual void NewCRD(CRD*crd){};
	virtual void AddRB(char*name,char*escritura,bool Checket=false){};
	virtual void SubRB(char*nameRB){};
	virtual void AddText(char letra){};
	virtual void AddNewText(char*newTexts){};
	virtual void SubText(){};
	virtual void NoClick(){};
	virtual void SetColor(GLfloat R,GLfloat G,GLfloat B){};
	virtual void SetNewProp(float Wigth=0,float Height=0){
		if(Wigth)
		this->Wigth=Wigth;
		if(Height)
		this->Height=Height;
	} 
	virtual void CambiarEscritura(char*newText){};
	virtual void CambiarChecket(){}
	virtual double* GetChecketPositton(){
		double*a=new double[2];
		a[0]=this->coord->x;
		a[1]=this->coord->y;
		return a;};
	//PURAS
	virtual void Draw()=0; 
	virtual unsigned Click()=0;
};
