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
#include "PuertoSerie.h"
#include <string>
#include "CRD.h"
#include "DataProcessor.h"
#include "TimeDuration.h"
#include "IGSClass.h"
#include "MeSSenger.h"
#include "StackForms.h"
#include "SalverMovement.h"
#define PI 3.14159265
using namespace std;

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
	static void DrawingObjectIGS();
	static void ShowAngules();
	///////////DEFAULTGLUTS
	static void movRaton(GLsizei x,GLsizei y);
	static void teclaRaton(int boton,int state,int x,int y);
	static void reshape(int x,int y);
	static void initProyecc();
	static void wheelAndRotate(bool a=false);
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
	static void defaul_menu(int opcion);
	//////////////DATOS
	static void cargarDatosFromTXT();
    static void SaveObj(char*address,LoaderObject*l);
	static void cargarInitDatos();
	static void slavarInitDatos();
	static void recivirDatosCOM();
    static void CalcularCoordenadas();
	static char* Verificacion(char*c,unsigned*strleN);
	//HILOS
	static void ThreadCOM();
	static void ThreadCargObject();
	static void ThreadCargMovent();
	static void ThreadGuardarMovent();
	static void ThreadSimular();
 };

