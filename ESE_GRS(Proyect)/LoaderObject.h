#pragma once
#include "GL\freeglut.h"
#include <iostream>
#include <fstream>
#include "VERTs.cpp"
using namespace std;

class LoaderObject
{
public:
	//////////////////////////////////////////////VARIABLES//////////////////////////////////
	GLdouble R,G,B;
	//int contHastak,contvf,contvn;
	int contv,contf,cantv,cantf;
	unsigned contVERTs;
	string nameStr;
	bool empty;
	/////DINAMICOS/////
	GLfloat *vertvCargX,*vertvCargY,*vertvCargZ;
	VERTs*veRts;
    //GLfloat *vertvnCargX,*vertvnCargY,*vertvnCargZ;
    //GLfloat *vertvfCargX,*vertvfCargY,*vertvfCargZ;
	////////////////////////////////////////////////METODOS//////////////////////

	///////////////CONSTRUCTORES Y DESTUCTOR//////
	LoaderObject();
	LoaderObject(char*name,double R=0.1,double G=0.1,double B=0.1);
	LoaderObject::~LoaderObject(void)
{
	delete[]vertvCargX,vertvCargY,vertvCargZ/*,vertvnCargX,vertvnCargY,vertvnCargZ,vertvfCargX,vertvfCargY,vertvfCargZ*/;
	delete[]veRts;
}
	//////////////////CARGAR//////////////////////
	static void cargarObject(char*name,LoaderObject*l);
	static string findd(string s,int caso=0);
	static void LoaderObject::recorrerArchiv(char*c,LoaderObject*l);
	//////////////////GUARDAR///////////////////////////
	static void Add(GLfloat*Vertices,LoaderObject*l);
	//////////////////DRAW//////////////////////////////
	static void pintarse(LoaderObject*l); 
	static void pintarNewBoj(LoaderObject*l);
	
	
};

