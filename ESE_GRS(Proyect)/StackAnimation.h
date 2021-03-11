#include "Forms.h"
#include "CRD.h"
class StackAnimation:public Forms
{
public:
	Animacion**animations;
	unsigned cant,cont;
	StackAnimation(char*name):Forms(name,CRD(0,0,0),0,0,0,0){
		cont=0;
		cant=10;
		animations=new Animacion*[cant];
	};
	void Draw()
	{
		for(unsigned i=0;i<cont;i++)
			animations[i]->Draw();
	}
	void Sub(char*AnimationName)
	{
		for(unsigned i=0;i<cont;i++)
		{
			if(!strcmp(AnimationName,animations[i]->name))
			{

				for(unsigned ii=i;ii<cont-1;ii++)
					animations[ii]=animations[ii+1];
				cont--;
				break;
			}
		}

	}
	unsigned Click(){return 0;};
	void STANSetAnimation(char*name,CRD coord,float wigth,float height,float TotalWigth,float TotalHeight,float x,float R,float G,float B,float speed){
		if(cont>=cant)
		 {
			 Animacion**NewAnimations=new Animacion*[cant+10];
			 cant=+10;
			 for(unsigned i=0;i<cont;i++)
				 NewAnimations[i]=animations[i];
			 delete[]animations;
			 animations=NewAnimations;
		 }
		animations[cont++]=new Animacion(name,coord,wigth,height,TotalWigth,TotalHeight,x,R,G,B,speed);
	};
	void NewTotalProp(float wigth,float height)
	{
		for(unsigned i=0;i<cont;i++)
			animations[i]->NewTotalProp(wigth,height);
	}
	void MoveOnReshape(bool reshape){
		for(unsigned i=0;i<cont;i++)
			animations[i]->reshapeBool=reshape;
	}
	~StackAnimation(){delete[]animations;};

};