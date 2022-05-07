#pragma once
#include "GL\freeglut.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <thread>
#include <mutex>
#include <string.h>
#include "LoaderObject.h"
#include "StackLoaderObject.h"
#include <string>
#include "CRD.h"
#include "DataProcessor.h"
#include "TimeDuration.h"
#include "MeSSenger.h"
#include "StackForms.h"
#define PI 3.14159265
#include "Plano.h"
#include "StackBoceto.h"
#include "Box.h"
#include "Animacion.h"
#include "StackAnimation.h"
#include "Connection.h"
#include "XLSClass.h"
#include <mmsystem.h>
using namespace std;
enum Language
{
	ENGLISH	,SPANISH
};
 class ESE_GRS

{
public:
	ESE_GRS();
	~ESE_GRS();
	////////////DIBUJAR
	static void display();
	static void Entorno();
	static void text(char*c,GLfloat x,GLfloat y,GLfloat z,GLfloat R=1.0,GLfloat G=1.0,GLfloat B=1.0,bool big=false,bool moreBig=false);
	static void smallEjeCoord(GLfloat size=10);
	static void ShowAngules();
	static Box* Interfaz(unsigned interfz=0,INTERFZType Buttom=INTERFZType::SPECIFIC);
	///////////DEFAULTGLUTS
	static void movRaton(GLsizei x,GLsizei y);
	static void movPasiveRaton(GLsizei x,GLsizei y);
	static void teclaRaton(int boton,int state,int x,int y);
	static void reshape(int x,int y);
	static void initProyecc();
	static void wheelAndRotate();
	static void Idle();
	static void Inicializar();
	static bool IniciarCargObjetos();
	static void wheel(int boton,int direcc,int x,int y);
	static void keyboard(unsigned char tecla,int x,int y );
	static void SpecialKeys(int tecla,int x,int y );
	///////////MENUS
	static void InitMenu();
	static void MenuPuertoSeie(int caso);
	static void MenuVista(int opcion);
	static void MenuToDraw(int caso);
	static void default_menu(int opcion);
	static void MenuIdioma(int opcion);
	static void MenuAcceso(int opcion);
	//////////////DATOS
   	static void cargarInitDatos();
	static void salvarInitDatos();
	static void recivirDatosCOM();
    static void CalcularCoordenadas();
	static char* VerificacionDatos(char*cc,unsigned&strleN);
	static void Acceso(bool acceso);
	static bool ChekEntada(char*c,unsigned&i);
	static bool VerificacionSeguridad(char*c,unsigned i);
	static bool CodigoCliente(char*c,unsigned i);
	static bool CodigoServer(char*c,unsigned&i);
	static bool SetAnglesREdirecc();
	//HILOS
	static void ThreadCOM();
	static void ThreadCargObject();
 };

