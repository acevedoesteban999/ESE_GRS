#include "Forms.h"
class Label:public Forms
{
private:
	char*escritura;
	GLfloat R,G,B;
	unsigned LetterSize;
public:
	Label(){};
	Label(char*name,char*escritura,CRD coord,unsigned LetterSize,GLfloat R,GLfloat G,GLfloat B,float TotalWigth,float TotalHeight):Forms(name,coord, 0, 20, TotalWigth, TotalHeight)
	{
		this->t=Type::LABEL;
		this->R=R;
		this->G=G;
		this->B=B;
		this->LetterSize=LetterSize;
		this->escritura=new char[strlen(escritura)+1];
		this->escritura[strlen(escritura)]=0;
		for(unsigned i=0;i<strlen(escritura);i++)
			this->escritura[i]=escritura[i];
	}
	~Label(){delete escritura;};
	void CambiarEscritura(char*NewEscritutra){
		NewText(NewEscritutra);
	}
	void NewText(char*newTexts){
		escritura=new char[strlen(newTexts)+1];
		escritura[strlen(newTexts)]=0;
		for(unsigned i=0;i<strlen(newTexts);i++)
			escritura[i]=newTexts[i];
		}
	void NewCRD(CRD*crd){
		coord=new CRD(*crd);
	}
	void Draw()
	{
		Forms::teXt(escritura,(GLfloat)coord->x,(GLfloat)coord->y,(GLfloat)R,(GLfloat)G,(GLfloat)B,LetterSize,this);
	}
	void SetColor(GLfloat R,GLfloat G,GLfloat B){
	this->R=R;
	this->B=B;
	this->G=G;};
	unsigned Click(){return 0;};


};