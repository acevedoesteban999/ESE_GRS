#pragma once
#include "LoaderObject.h"
class StackLoaderObject
{
public:
	//////////////////////////////////////////////////VARIABLES////////////////////////
	int contLoaderObject;
    int cantLoaderObject;
	GLfloat angules[6];
	double*CoordReales;
	bool Salir;
	/////////DINAMICOS///////////////
    LoaderObject**Stack;
	///////////////////////////////////////////////////METODOS///////////////////////////

	///////////////CONSTRUCTORES Y DESTUCTOR//////
	StackLoaderObject(void);
	~StackLoaderObject(){
		delete[]Stack;
	}
	////////////////PUSH/////////////////////////
	static void push(char*c,StackLoaderObject*slo,double R=1,double G=1,double B=1);
	static void pushByTxt(char*c,StackLoaderObject*s);
	///////////////DRAWS//////////////////////////
	static void draw(StackLoaderObject*slo,int i=-1);
	static void RotateAndMoveArtic(int i,StackLoaderObject*slo);
	//////////////SETS//////////////////////////////
	static void setAnguleArt1(GLfloat*angules,StackLoaderObject*slo);
	
};

