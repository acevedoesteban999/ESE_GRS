#pragma once
#include "Forms.h"
class RadioButton:public Forms
{
private:
	
	unsigned forma;
	GLfloat R,G,B;
public:
	bool Checket,SoloLabel;
	Label*l;
	bool noContCheck;
	RadioButton(){};
	RadioButton(char*RadioButtonName,CRD coord,char*escritura,float TotalWigth,float TotalHeight,bool Checket=false):Forms(RadioButtonName,coord,15,15,TotalWigth,TotalHeight){
		SoloLabel=false;
		this->Checket=Checket;
		l=new Label(RadioButtonName,escritura,*new CRD(coord.x+20,coord.y-2,coord.z),1,(GLfloat)0,(GLfloat)0,(GLfloat)0,TotalWigth,TotalHeight);
		t=Type::RADIOBUTTON;
		forma=0;
		R=B=0;
		G=1;
		noContCheck=false;
	};
	~RadioButton(){};
	void Draw(){


	     glPushMatrix();
	     glLoadIdentity();
	     glTranslatef((GLfloat)(-TotalWigth/2+coord->x),(GLfloat)(TotalHeight/2-coord->y),(GLfloat)2*this->TotalWigth-1); 
       	 glColor3f((GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);
		 if(!SoloLabel)
		    {
			if(!this->active)
	           {
	           glBegin(GL_LINE_LOOP);
	            glVertex3f(0,0,-1);
	            glVertex3f(15,0,-1);
	            glVertex3f(15,-15,-1);
	            glVertex3f(0,-15,-1);
	           glEnd();
	           glBegin(GL_LINES);
	            glVertex3f(0,0,-1);
	            glVertex3f(15,-15,-1);
	            glVertex3f(0,-7.5,-1);
	            glVertex3f(7.5,-15,-1);
	            glVertex3f(7.5,0,-1);
	            glVertex3f(15,-7.5,-1);
	           glEnd();
	           }
	       else
	           {
	           if(!Checket)
	              {
	               glBegin(GL_LINE_LOOP);
	               glVertex3f(0,0,-1);
	               glVertex3f(15,0,-1);
	               glVertex3f(15,-15,-1);
	               glVertex3f(0,-15,-1);
	               glEnd();
	              }
	           else
	              {
	              glColor3f(this->active?this->R:(GLfloat)0.2,this->active?this->G:(GLfloat)0.2,this->active?this->B:(GLfloat)0.2);
	              glBegin(GL_POLYGON);
	               glVertex3f(0,0,-1);
	               glVertex3f(15,0,-1);
	               glVertex3f(15,-15,-1);
	               glVertex3f(0,-15,-1);
	              glEnd();
	               }
	           }
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
	static void SetStyle(GLfloat R,GLfloat G,GLfloat B,unsigned forma,RadioButton*rb){
		rb->forma=forma;
		rb->R=R;
		rb->G=G;
		rb->B=B;
	};
	static bool IsChecket(RadioButton*rb){return rb->Checket;};	
	unsigned GetChecket(){
		return IsChecket(this);
	}
	unsigned Click(){
		if(!Checket)
		   Checket=true;
		else
		   Checket=false;
	return (unsigned)t;};
	static void Contar_NoCont_Check(bool contNoCont,RadioButton*rb){rb->noContCheck=contNoCont;};
	static void SetSoloLabel(bool SoloLabeL,RadioButton*rb){rb->SoloLabel=SoloLabeL;};
};