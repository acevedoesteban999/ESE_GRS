#pragma once
#include "TextBox.h"
#include "Button.h"
#include "Label.h"
#include "RadioButtonGroup.h"
class StackForms
{
private:
	Forms**forms;
	unsigned cant;
	unsigned cont;
public:
	StackForms(){cont=0;cant=10;forms=new Forms*[cant];};
	~StackForms(){delete[]forms;};
	static void Add(Forms*form,StackForms*sf){
		
		for(unsigned i=0;i<sf->cont;i++)
			if(sf->ExistForm(form->name,sf->forms[i]))
		         sf->Sub(form->name,sf);
	
	if(sf->cont>=sf->cant)
	{
		Forms**NewForms=new Forms*[sf->cant+10];
		sf->cant+=10;
		for(unsigned i=0;i<sf->cont;i++)
			NewForms[i]=sf->forms[i];
		delete sf->forms;
		sf->forms=NewForms;
	}
	sf->forms[sf->cont++]=form;	
	
}
	static void Sub(char*name,StackForms*sf)
	{
		for(int i=(int)sf->cont-1;i>=0;i--)
		{
			if(sf->ExistForm(name,sf->forms[i]))
			{
				for(unsigned ii=i;ii<sf->cont-1;ii++)
					sf->forms[ii]=sf->forms[ii+1];
				sf->cont--;
				break;
			}
		}
	}
	static void DrawForms(StackForms*sf){
		for(unsigned i=0;i<sf->cont;i++)
			if(sf->forms[i]->active)
			    sf->forms[i]->Draw();
	}
	static void ActivateForm(char*name,StackForms*sf){
		for(unsigned i=0;i<sf->cont;i++)
			if(sf->ExistForm(name,sf->forms[i]))
				sf->forms[i]->Activate(sf->forms[i]);
	}
	static void DesactivateForm(char*name,StackForms*sf){
		for(unsigned i=0;i<sf->cont;i++)
			if(sf->ExistForm(name,sf->forms[i]))
				sf->forms[i]->Desactivate(sf->forms[i]);
	}
    static void AddText(char c,StackForms*sf){
		for(unsigned i=0;i<sf->cont;i++)
			if(sf->forms[i]->active&&sf->forms[i]->t==Type::TEXTBOX&&sf->forms[i]->Escribiendo())
				sf->forms[i]->AddText(c);
	}
	static void AddNewText(char*FormsName,char*newText,StackForms*sf)
	{
		for(unsigned i=0;i<sf->cont;i++)
		{
			if(sf->ExistForm(FormsName,sf->forms[i]))
			{
				sf->forms[i]->NewText(newText);
				break;
			}
		}
	}
	static void AddNewCRD(char*name,CRD*crd,StackForms*sf){
	for(unsigned i=0;i<sf->cont;i++)
	   {
		if(sf->ExistForm(name,sf->forms[i]))
		   {
			sf->forms[i]->NewCRD(crd);
			break;
		   }
       }
	
	}
    static void SubText(StackForms*sf){
		for(unsigned i=0;i<sf->cont;i++)
			if(sf->forms[i]->active&&sf->forms[i]->t==Type::TEXTBOX&&sf->forms[i]->Escribiendo())
				sf->forms[i]->SubText();

}
	static void SetColor(char*name,GLfloat R,GLfloat G,GLfloat B,StackForms*sf){
		sf->GetForm(name,sf)->SetColor(R,G,B);
	
	}
	static unsigned PresionarForm(float x,float y,StackForms*sf){
		unsigned a=0;
		for(unsigned i=0;i<sf->cont;i++)
		{
			if(sf->forms[i]->active)
			{
			 if(sf->forms[i]->Pulsado(x,y))	 
				a=sf->forms[i]->Click();
			 else
				sf->forms[i]->NoClick();
			}
		}
		return a;
	}
	static void NewTotalsProp(float wigth,float height,StackForms*sf){
		for(unsigned i=0;i<sf->cont;i++)
			sf->forms[i]->NewTotalProp(wigth,height);
	
	}
	static Forms* GetForm(char*name,StackForms*sf){
		for(int i=(int)sf->cont-1;i>=0;i--)
		{
			if(sf->ExistForm(name,sf->forms[i]))
				return sf->forms[i];
		}
		    Forms*f=new Button("ErrorGetForms",Type::FORMS,*new CRD(0,0,0),0,0,0,0,0,0,0);
			return f;
	
	}; 
	static Forms* GetForm(unsigned numero,StackForms*sf){if(numero<sf->cont)return sf->forms[numero];};
	static bool ExistForm(char*name,Forms*f)
	{
			if(!strcmp(f->name,name))
				return true;
	     return false;
	}
};