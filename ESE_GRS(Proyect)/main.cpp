#include "ESE_GRS.h"
#include <iostream>

int main(int argv,char*argc[]){
	glutInit(&argv,argc);//inicio el GLUT
	ESE_GRS*ESE_GRS_Proyect=new ESE_GRS;
	glutMainLoop();//le digo q se quede esperando eventos 
	return 0;
}

