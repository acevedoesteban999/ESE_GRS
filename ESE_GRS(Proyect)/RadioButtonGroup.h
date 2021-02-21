#pragma once
#include "Forms.h"
#include "RadioButton.h"
class RadioButtonGroup:public Forms
{
protected:
	unsigned cantRB,contRB,Checket;
	RadioButton**RB;
	
public:
	RadioButtonGroup(){};
	RadioButtonGroup(char*name,CRD coord,float TotalWigth,float TotalHeight):Forms(name,coord,0,0, TotalWigth, TotalHeight){
		t=Type::RADIOBUTTONGROUP;
		cantRB=10;
		contRB=0;
		RB=new RadioButton*[cantRB];
};
	~RadioButtonGroup(){};
	void NewTotalProp(float wigth,float height){
		Forms::NewTotalProp(wigth,height);
		for(unsigned i=0;i<contRB;i++)
		{
			RB[i]->TotalWigth=wigth;
			RB[i]->TotalHeight=height;
			RB[i]->l->TotalWigth=wigth;
			RB[i]->l->TotalHeight=height;
		}
	}	
	void Draw(){
	glPushMatrix();
	glLoadIdentity();
	glTranslatef((GLfloat)(-TotalWigth/2+coord->x),(GLfloat)(TotalHeight/2-coord->y),(GLfloat)TotalWigth/2); 
	glColor3f(1,1,1);

	glBegin(GL_LINE_LOOP);
	glVertex3f(-5,5,0);
	glVertex3f(Wigth,5,0);
	glVertex3f(Wigth,-Height-5,0);
	glVertex3f(-5,-Height-5,0);
	glEnd();

	
	
	
	glPopMatrix();
    for(unsigned i=0;i<contRB;i++)
	   this->RB[i]->Draw();
	
	}
    unsigned Click(){
	for(unsigned i=0;i<contRB;i++)
		if(!RB[i]->noContCheck)
			RB[i]->NotChecket();
	this->RB[Checket]->Click();
	return(unsigned)t;
	}
	bool Pulsado(float x,float y)
	{
		
		if(Forms::Pulsado(x,y))
		   {
		   for(unsigned i=0;i<contRB;i++)
		      {
				  if(y>=RB[i]->coord->y&&y<=RB[i]->coord->y+15&&x>=RB[i]->coord->x&&x<=RB[i]->coord->x+15)
				   {
					   if(!RB[i]->noContCheck)
					      Checket=i;
					   else
						   RB[i]->CambiarChecket();
					   return true;
			       }
			
		
		      }
		  
		}
	   return false;
	}
	void AddRB(char*RadioButtonName,char*escritura,bool Cheket=false){
		if(Cheket)
		    {
				Checket=contRB;
			for(unsigned i=0;i<this->contRB;i++)
				RB[i]->NotChecket();
		     }
		if(this->Wigth<strlen(escritura)*9+25)
			this->Wigth=(float)strlen(escritura)*9+25;
		RadioButton*rb=new RadioButton(RadioButtonName,*new CRD(this->coord->x,(double)(this->coord->y+(18*this->contRB)),this->coord->z),escritura,this->TotalWigth,this->TotalHeight,Cheket);
		if(this->contRB>=this->cantRB)
		{
			RadioButton**newRB=new RadioButton*[this->cantRB+10];
			this->cantRB+=10;
			for(unsigned i=0;i<this->contRB;i++)
				newRB[i]=this->RB[i];
		 this->RB=newRB;
		}
		this->RB[this->contRB++]=rb;
		this->Height+=18;
	}
    void SubRB(char*nameRB){
		
			for(unsigned i=0;i<this->contRB;i++)
			{
				if(!strcmp(this->RB[i]->name,nameRB))
				{
					for(unsigned ii=i;ii<this->contRB-1;i++)
						this->RB[i]=this->RB[i+1];
					break;
				}
			}
			this->contRB--;
			this->Height-=18;
}
	static RadioButton* GetRD(char*name,RadioButtonGroup*rbg){
		for(unsigned i=0;i<rbg->contRB;i++)
			if(!strcmp(rbg->RB[i]->name,name))
				return rbg->RB[i];
		return new RadioButton("GETRDError",*(new CRD(0,0,0)),"Error",0,0);
	
	}
	void SetNewProp(float wigth,float height){
		if(wigth)
			this->Wigth=wigth+25;
		if(height)
			this->Height=height;
	
	}
	unsigned GetChecket(){
		return Checket;};
	void CambiarChecket(){
		RB[Checket]->NoClick();
		do{
		Checket==contRB-1?Checket=0:Checket++;
		}while((RB[Checket]->noContCheck));
		RB[Checket]->Click();

	}
	double* GetChecketPositton(){
	   double*a=new double[2];
	   a[0]=RB[Checket]->coord->x;
	   a[1]=RB[Checket]->coord->y;
	   return a;
	}
	unsigned GetMaxChecket(){return this->contRB;};
	unsigned GetCONTRB(){return contRB;};
	void ActivDesactRB(char*name,bool activate){
		for(unsigned i=0;i<contRB;i++)
		{
			if(!strcmp(RB[i]->name,name))
			{
				RB[i]->active=activate;
				return;
			}
		}
	}
	bool IsChecket(char*name){
		for(unsigned i=0;i<contRB;i++)
			if(!strcmp(name,RB[i]->name))
				return RB[i]->GetChecket()?1:0;
		return 0;
	};
	void SetChecket(char*name,bool checket){
		for(unsigned i=0;i<contRB;i++)
			if(!strcmp(name,RB[i]->name))
				RB[i]->Checket=checket;
	};
	
};