#include "ESE_GRS.h"
#include <iostream>

int main(int argv,char*argc[]){
	glutInit(&argv,argc);//inicio el GLUT
	ESE_GRS Proyect;
	glutMainLoop();//le digo q se quede esperando eventos 
	return 0;
}

