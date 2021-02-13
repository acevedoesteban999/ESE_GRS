#pragma once
#include "Forms.h"
class Button:public Forms
{
private:
	GLfloat R,G,B;
public:
	Button();
	Button(char*name,Type bt,CRD crd,GLfloat R,GLfloat G,GLfloat B,float wigth,float height,float TotalWigth,float TotalHeight):Forms(name,crd,wigth,height,TotalWigth,TotalHeight){
    this->R=R;
	this->G=G;
	this->B=B;
	this->t=bt;
	this->t=bt;
	}
	~Button();
	void Draw(){
	glPushMatrix();
				  glLoadIdentity();
				  glTranslatef((GLfloat)(-TotalWigth/2+coord->x),(GLfloat)(TotalHeight/2-coord->y),(GLfloat)TotalWigth/2); 
				  glColor3f(this->R,this->G,this->B);
				  glBegin(GL_POLYGON);
				  glVertex3f(0,0,-1);
				  glVertex3f((GLfloat)Wigth,0,-1);
				  glVertex3f((GLfloat)Wigth,(GLfloat)-Height,-1);
				  glVertex3f(0,(GLfloat)-Height,-1);
				  glEnd();
				  glPopMatrix();
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