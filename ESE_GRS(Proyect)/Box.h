#include "Forms.h"
class Box:public Forms{

private:
	Forms**forms;
	unsigned cant,cont;
	unsigned PulsadO;
public:
	Box():Forms("DefaultNameBox",*new CRD(0,0,0),0,0,0,0)
	{ 
	   cont=0;
	   cant=10;
	   forms=new Forms*[cant];
	   this->t=Type::BOX;
	   PulsadO=0;
	}
	Box(char*name,CRD coord,float TotalWigth,float TotalHeight):Forms(name,coord,0,0,TotalWigth,TotalHeight)
	{
	   cont=0;
	   cant=10;
	   forms=new Forms*[cant];
	   this->t=Type::BOX;
	   PulsadO=0;
	}
	~Box(){delete[]forms;};
	void ChecketCont(Box*b){
		if(b->cont>=b->cant)
		{
			Forms**newForms=new Forms*[b->cant+10];
			b->cant+=10;
			for(unsigned i=0;i<b->cont;i++)
				newForms[i]=b->forms[i];
			delete[]b->forms;
			b->forms=newForms;
		}
	}
	static void AddForm(Forms*f,Box*b,float x=0,float y=0,float z=0)
	{
		b->ChecketCont(b);

		f->SetCoord((float)(b->coord->x+x),(float)(b->coord->y+b->Height+y),(float)(b->coord->z+z));
		b->Height+=f->Height+y+5;
		if(f->Wigth+x>b->Wigth)
			b->Wigth=f->Wigth+x;

		b->forms[b->cont++]=f;
		
    }
	bool Pulsado(float x,float y)
	{
		
		if(Forms::Pulsado(x,y))
		   {
		   for(unsigned i=0;i<cont;i++)
		      {
				  if(forms[i]->Pulsado(x,y))
				  {
					  PulsadO=i;
				      return true;
				  }
		      }
		  
		}
	   return false;
	}
	void Draw(){
		if(!this->NoDraw)
		{
			glPushMatrix();
	        glLoadIdentity();
	        glTranslatef((GLfloat)(-TotalWigth/2+coord->x),(GLfloat)(TotalHeight/2-coord->y),(GLfloat)2*this->TotalWigth-1); 
	        glColor3f(1,1,1);
	        glBegin(GL_POLYGON);
	        glVertex3f(-5,5,(GLfloat)-1.2);
	        glVertex3f(Wigth,5,(GLfloat)-1.2);
	        glVertex3f(Wigth,-Height-5,(GLfloat)-1.2);
	        glVertex3f(-5,-Height-5,(GLfloat)-1.2);
	        glEnd();
			

			
			float ContHeigth=0;
			for(unsigned i=0;i<cont;i++)
			{
				
				glColor3f(0,0,0);
			    glBegin(GL_LINE_LOOP);
				glVertex3f(-2,(GLfloat)(-ContHeigth+2.5),(GLfloat)-1.1);
				glVertex3f(Wigth-5,(GLfloat)(-ContHeigth+2.5),(GLfloat)-1.1);
				ContHeigth+=forms[i]->Height+5;
				glVertex3f(Wigth-5,(GLfloat)(-ContHeigth+2.5),(GLfloat)-1.1);
				glVertex3f(-2,(GLfloat)(-ContHeigth+2.5),(GLfloat)-1.1);
	            glEnd();
			}

			glPopMatrix();
			for(unsigned i=0;i<cont;i++)
				forms[i]->Draw();
			
		
		}
		
	
	}
	unsigned Click(){
		for(unsigned i=0;i<cont;i++)
			if(i!=PulsadO)
			   forms[i]->NoClick();
		forms[PulsadO]->Click();
		return (unsigned)t;
	}
	void NoClick(){
	
	};
	unsigned GetCont(){return cont;};
	unsigned GetChecket(){
		return PulsadO;};
	unsigned BoxGetRBG_RBChecket(char*RBGname,char*RBname){
		for(unsigned i=0;i<cont;i++)
			if(!strcmp(forms[i]->name,RBGname))
				return forms[i]->RBGGetChecket();
		return 0;
	};
	bool BoxGetRBChecket(char*RBname)
	{
		for(unsigned i=0;i<cont;i++)
			if(!strcmp(forms[i]->name,RBname))
				return forms[i]->RBGetCheket();
		return false;
	}
	unsigned BoxGetRBGChecket(char*RBGname)
	 {
		 for(unsigned i=0;i<cont;i++)
			if(!strcmp(forms[i]->name,RBGname))
				return forms[i]->RBGGetChecket();
		 return 0;
	 
	 
	 }
    unsigned BoxGetElemChecket(){
		 return PulsadO;
	 }
	bool Escribiendo()
	{
		for(unsigned i=0;i<cont;i++)
			if(forms[i]->t==Type::TEXTBOX&&forms[i]->Escribiendo())
				return true;
		return false;
	}
	void AddText(char c){
		for(unsigned i=0;i<cont;i++)
			if(forms[i]->active&&forms[i]->Escribiendo())
				forms[i]->AddText(c);
	}
	void SubText(){
		for(unsigned i=0;i<cont;i++)
			if(forms[i]->active&&forms[i]->Escribiendo())
				forms[i]->SubText();

}
	void ActivateDesactivate(bool ActDesact){
		this->active=ActDesact;
		for(unsigned i=0;i<cont;i++)
			forms[i]->ActivateDesactivate(ActDesact);
	}
	bool BoxGetActiveDesact(char*ElementName){
	     for(unsigned i=0;i<cont;i++)
			 if(!strcmp(forms[i]->name,ElementName))
				 return forms[i]->GetActiveDesavt();
		 return false;
	};
	bool BoxGetRBGActiveDesact(char*RBGName,char*RBName){
	 for(unsigned i=0;i<cont;i++)
		 if(!strcmp(forms[i]->name,RBGName))
			 return forms[i]->RBGGetRBActiveDesavt(RBName);
	 return false;
	};
	void BoxCambiarChecketRB(char*RBname){
	   for(unsigned i=0;i<cont;i++)
		 if(!strcmp(forms[i]->name,RBname))
			 forms[i]->CambiarChecket();

	};
	void BoxSetActivateDesactivate(char*ElementName,bool actvDesact){
	for(unsigned i=0;i<cont;i++)
		if(!strcmp(forms[i]->name,ElementName))
			forms[i]->ActivateDesactivate(actvDesact);
	};
};