#pragma once
#include "Forms.h"
class Button:public Forms
{
private:
	GLfloat R,G,B;
public:
	Button(){};
	Button(char*name,Type bt,CRD crd,GLfloat R,GLfloat G,GLfloat B,float wigth,float height,float TotalWigth,float TotalHeight):Forms(name,crd,wigth,height,TotalWigth,TotalHeight){
    this->R=R;
	this->G=G;
	this->B=B;
	this->t=bt;
	this->t=bt;
	}
	~Button(){};
	void Draw(){
		if(!this->NoDraw)
		{
	glPushMatrix();
				  glLoadIdentity();
				  glTranslatef((GLfloat)(-TotalWigth/2+coord->x),(GLfloat)(TotalHeight/2-coord->y),(GLfloat)2*this->TotalWigth-1+TotalProfundidad); 
				  glColor3f(this->active?this->R:(GLfloat)this->R/2,this->active?this->G:(GLfloat)this->G/2,this->active?this->B:(GLfloat)this->B/2);
				  glBegin(GL_POLYGON);
				  glVertex3f(0,0,-1);
				  glVertex3f((GLfloat)Wigth,0,-1);
				  glVertex3f((GLfloat)Wigth,(GLfloat)-Height,-1);
				  glVertex3f(0,(GLfloat)-Height,-1);
				  glEnd();
				  glPopMatrix();
		}
	};
	void SetColor(GLfloat R,GLfloat G,GLfloat B){
	this->R=R;
	this->B=B;
	this->G=G;};
	unsigned Click(){
		return t;
		return 0;
	};


};