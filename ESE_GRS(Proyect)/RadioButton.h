#pragma once
#include "Forms.h"
class RadioButton:public Forms
{
private:
	bool Checket;
public:
	Label*l;
	RadioButton(){};
	RadioButton(char*RadioButtonName,CRD coord,char*escritura,float TotalWigth,float TotalHeight,bool Checket=false):Forms(RadioButtonName,coord,15,15,TotalWigth,TotalHeight){
		this->Checket=Checket;
		l=new Label(RadioButtonName,escritura,*new CRD(coord.x+20,coord.y-2,coord.z),1,(GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7,TotalWigth,TotalHeight);
		t=Type::RADIOBUTTON;
		
	};
	~RadioButton(){};
	void Draw(){
	glPushMatrix();
	glLoadIdentity();
	glTranslatef((GLfloat)(-TotalWigth/2+coord->x),(GLfloat)(TotalHeight/2-coord->y),(GLfloat)TotalWigth/2); 
	glColor3f((GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);
	if(!Checket)
	{
	glBegin(GL_LINE_STRIP);
	glVertex3f(0,0,-1);
	glVertex3f(15,0,-1);
	glVertex3f(15,-15,-1);
	glVertex3f(0,-15,-1);
	glVertex3f(0,0,-1); 
	glEnd();
	}
	else
	{
	glColor3f(0,1,0);
	glBegin(GL_POLYGON);
	glVertex3f(0,0,-1);
	glVertex3f(15,0,-1);
	glVertex3f(15,-15,-1);
	glVertex3f(0,-15,-1);
	glEnd();
	}
	glPopMatrix();
	l->Draw();
	};
	void NotChecket(){Checket=false;}
	void NewTotalProp(float wigth,float height){
		Forms::NewTotalProp(wigth,height);
		l->NewTotalProp(wigth,height);
	}
	void CambiarEscritura(char*newText){l->NewText(newText);};
	void CambiarChecket(){Checket?Checket=false:Checket=true;};
	void NewCRD(CRD*crd){
		coord=new CRD(*crd);
		l->NewCRD(new CRD(crd[0].x+20,crd[0].y,crd[0].z));
	}
	static bool IsChecket(RadioButton*rb){return rb->Checket;};
	unsigned Click(){
		if(!Checket)
		   Checket=true;
		else
		   Checket=false;
	return (unsigned)t;};
};