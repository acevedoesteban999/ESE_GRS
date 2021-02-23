#pragma once
#include "Forms.h"
#include "RadioButton.h"
class RadioButtonGroup:public Forms
{
protected:
	unsigned cantRB,contRB,Checket;
	RadioButton**RB;
	Label*TopLabel;
	bool topLabelbool,lastChecket;
	
public:
	RadioButtonGroup(){};
	RadioButtonGroup(char*name,CRD coord,float TotalWigth,float TotalHeight):Forms(name,coord,0,0, TotalWigth, TotalHeight){
		t=Type::RADIOBUTTONGROUP;
		cantRB=10;
		contRB=0;
		RB=new RadioButton*[cantRB];
		TopLabel=new Label("","",*new CRD(0,0,0),0,0,0,0,0,0);
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
		if(this->active)
		{
		if(topLabelbool)
		{
		    glPushMatrix();
			 glTranslatef(0,25,0);
			 TopLabel->Draw();
			glPopMatrix();
		}
	glPushMatrix();
	glLoadIdentity();
	glTranslatef((GLfloat)(-TotalWigth/2+coord->x),(GLfloat)(TotalHeight/2-coord->y),(GLfloat)2*this->TotalWigth-1); 
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	glVertex3f(-5,5,(GLfloat)-1.1);
	glVertex3f(Wigth,5,(GLfloat)-1.1);
	glVertex3f(Wigth,-Height-5,(GLfloat)-1.1);
	glVertex3f(-5,-Height-5,(GLfloat)-1.1);
	glEnd();

	
	
	
	glPopMatrix();
    for(unsigned i=0;i<contRB;i++)
	   this->RB[i]->Draw();
		}
	}
    unsigned Click(){
	for(unsigned i=0;i<contRB;i++)
		if(!RB[i]->noContCheck)
			RB[i]->NotChecket();
	this->RB[Checket]->Click();

	if(lastChecket)
		return(unsigned)Type::RADIOBUTTON;

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
					   {
					      Checket=i;
						  lastChecket=false;
					   }
					   else
					   {
						   RB[i]->CambiarChecket();
						   lastChecket=true;
					   }
					   return true;
			       }
			
		
		      }
		  
		}
	   return false;
	}
	void AddRB(char*RadioButtonName,char*escritura,bool Cheket=false,bool SoloLabel=false,bool contNocontChecket=false,float DesplazarX=0,float DesplazarY=0,float DesplazarZ=0){
		
		if(Cheket)
		    {
				Checket=contRB;
			for(unsigned i=0;i<this->contRB;i++)
				RB[i]->NotChecket();
		     }
		if(this->Wigth<(float)(strlen(escritura)*9.5+25+DesplazarX))
			this->Wigth=(float)(strlen(escritura)*9.5+25+DesplazarX);
		RadioButton*rb=new RadioButton(RadioButtonName,*new CRD(this->coord->x,(double)(this->coord->y+(18*this->contRB)),this->coord->z),escritura,this->TotalWigth,this->TotalHeight,Cheket);
		if(this->contRB>=this->cantRB)
		{
			RadioButton**newRB=new RadioButton*[this->cantRB+10];
			this->cantRB+=10;
			for(unsigned i=0;i<this->contRB;i++)
				newRB[i]=this->RB[i];
		 this->RB=newRB;
		}

		if(SoloLabel)
		{
			rb->active=false;
			rb->SoloLabel=true;
		}
		rb->coord->x+=DesplazarX;
		rb->coord->y+=DesplazarY;
		rb->coord->z+=DesplazarZ;
		rb->l->coord->x+=DesplazarX;
		rb->l->coord->y+=DesplazarY;
		rb->l->coord->z+=DesplazarZ;
		rb->Contar_NoCont_Check(contNocontChecket,rb);
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
	bool GetRBChecket(char*name){
		for(unsigned i=0;i<contRB;i++)
			if(RB[i]->active&&!strcmp(name,RB[i]->name))
				return RB[i]->GetChecket()?1:0;
		return 0;
	};
	void SetChecket(char*name,bool checket){
		for(unsigned i=0;i<contRB;i++)
			if(!strcmp(name,RB[i]->name))
				RB[i]->Checket=checket;
	};
	static void SetTopEscritura(bool active,char*escritura,RadioButtonGroup*rdg)
	{
	rdg->topLabelbool=active;
	if(active)
	{
		rdg->TopLabel=new Label("LabelEscrituraRD",escritura,*rdg->coord,1,(GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7,rdg->TotalWigth,rdg->TotalHeight);
	}
	}
	
};