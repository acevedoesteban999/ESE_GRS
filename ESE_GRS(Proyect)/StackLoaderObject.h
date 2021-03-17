#pragma once
#include "LoaderObject.h"
#include "ESE_GRS.h"
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
	StackLoaderObject(void)
{
	contLoaderObject=0;
    cantLoaderObject=10;
    Stack=new LoaderObject*[cantLoaderObject];//inicializo el arreglo
	CoordReales=new double[3];
	Salir=false;
};
	~StackLoaderObject(){}
	////////////////PUSH/////////////////////////
	static void push(char*c,StackLoaderObject*slo,double R,double G,double B){
  //agrego un nuevo LoaderObject(.obj con direccion *c) en el Stack 
  LoaderObject*newLoaderObject=new LoaderObject(c,R,G,B);
  if(newLoaderObject->empty==false)
      {
	   if(slo->contLoaderObject>=slo->cantLoaderObject)//aumento el tamaño del arreglo en caso de ser necesario
	      {
		   LoaderObject**newdata=new LoaderObject*[slo->cantLoaderObject+10];
		   slo->cantLoaderObject+=10;
		   for(int i=0;i<slo->cantLoaderObject;i++)
			   newdata[i]=slo->Stack[i];
		   slo->Stack=newdata;
 	       }
  } 
	  slo->Stack[slo->contLoaderObject++]=newLoaderObject;

     
};
	static void pushByTxt(char*name,StackLoaderObject*slo){
   //agrego todos los .obj del txt "Entrada_de_Modelos" 
	fstream f;
    f.open(name,ios::in);
    char c[100];
     if(f.is_open())
        {
			while(!f.eof()&&!slo->Salir)
		    {
	           f.getline(c,100);
			   if(c[0]=='&'){
			   string name_obj(c);
			   name_obj=name_obj.substr(1,name_obj.find_first_of(" "));
			   string s(c);
			   s=s.substr(name_obj.length()+1,s.length()-name_obj.length());
			   string r=s.substr(0,s.find_first_of(" "));
			   s=s.substr(s.find_first_of(" ")+1,s.length()-s.find_first_of(" "));
			   string g=s.substr(0,s.find_first_of(" "));
			   s=s.substr(s.find_first_of(" ")+1,s.length()-s.find_first_of(" "));
			   string b=s.substr(0,s.find_first_of(" "));
			   slo->push((char*)name_obj.c_str(),slo,(double)atof(r.c_str()),(double)atof(g.c_str()),(double)atof(b.c_str()));
	         }
		 }
  
   }
  else
	  cout<<"Error: ARCHIVO TXT:'"<<name<<"'-DIRECCION O NOMBRE DE ARCHIVO INCORECTO "<<endl;//si no existe el archivo en esa direccion
	 f.close();
};
	///////////////DRAWS//////////////////////////
	static void smallEjeCoordSLO(GLfloat size){
	//pinto un eje de coordenada x,y,z

	
		glColor3f(1.0,0.0,0.0);

	glBegin(GL_LINES);
	glVertex3f(size,0.0,0.0);
	glVertex3f(0.0,0.0,0.0);
	glEnd();

	
		glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0,size,0.0);
	glVertex3f(0.0,0.0,0.0);
	glEnd();

	
		glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0,0.0,size);
	glVertex3f(0.0,0.0,0.0);
	glEnd();
	

}
	static void draw(StackLoaderObject*slo,int i){
	//posiciono,pinto y trasaldo(para q el proximo se pueda posicionar)ademas pinto los ejes de coordenadas de guia
	glPushMatrix();
	if(i==-1)
    {
		for(int ii=0;ii<slo->contLoaderObject;ii++)
		{   
		   slo->RotateAndMoveArtic(ii,slo);
   		   slo->Stack[ii]->pintarse(slo->Stack[ii]);
		}
		slo->RotateAndMoveArtic(slo->contLoaderObject,slo);			
	}
		
	else if(i<=slo->contLoaderObject&&i>=0) 
	{
		slo->Stack[i]->pintarse(slo->Stack[i]);
		StackLoaderObject::smallEjeCoordSLO(20);
    }
	else if(i==-2)
	{
	
	}
	glPopMatrix();
	//glPushMatrix();
	/////////////////////////////////////////////////////////////////////
	//glLoadIdentity();
	////Explicacion:la coordenada q me devuelve la matrx de modelview tiene q ser sacada ahora
	////porq la matriz ya viene de antes;del dispaly con una rotacion y un whell distintas de la del 00
	////por eso se carga la identidad,no se puede cargar antes,debido a q los objetos se pintarian esaticos en la palntalla
	////por lo tanto se sacan las coordenadas ahora;
	//for(int ii=0;ii<=slo->contLoaderObject;ii++)
	//		   {   
	//			    slo->RotateAndMoveArtic(ii,slo);
	//           }
	//GLdouble mModel[16];
	//glGetDoublev(GL_MODELVIEW_MATRIX,mModel);
	//slo->CoordReales[0]=(double)mModel[12];
	//slo->CoordReales[1]=(double)mModel[13];
	//slo->CoordReales[2]=(double)mModel[14];
	//glPopMatrix();
	//37.481040954589844 361.38070678710937 472.38644409179687
};
	static void RotateAndMoveArtic(int caso,StackLoaderObject*slo){
	//procedimientos(rotaciones segun angArtc's) q se hacen con aterioridad para q quede pintado en la posicion q se desee
	
	//cada caso corresponde con la posicion del LoaderObject en el Stack
	switch (caso)
	{
	case 0:
		break;

	case 1:
		   glTranslatef(0.0,0.0,(GLfloat)-0.25);
		break;

     case 2:
		 glRotatef(slo->angules[0],0.0,0.0,1.0);
		 glTranslatef(0.0,0.0,(GLfloat)7.45);	
		break;

	case 3:
		glTranslatef(0.0,(GLfloat)-18.2,(GLfloat)36.5);
	    glRotatef(-slo->angules[1],0,1,0);
		break;

	case 4:
		glTranslatef(0.0,(GLfloat)0.5,0.0);
		break;

	case 5:
		glTranslatef((GLfloat)-150,0,0);
		glRotatef(-slo->angules[2],0,1,0);
		break;
		
		case 6:
		   glTranslatef(0.0,(GLfloat)12.3,0.0);	
		break;

		case 7:
			glTranslatef(0.0,0.0,(GLfloat)200);
		break;

		case 8:
			glTranslatef(0,(GLfloat)7.716,(GLfloat)25.5);
			glRotatef(slo->angules[3],1,0,0);
		break;

		case 9:
			glTranslatef(0,0.0,(GLfloat)53);
			glRotatef(slo->angules[4],0,1,0);
		break;

		case 10:	
			glTranslatef(0.0,(GLfloat)-8.915,(GLfloat)35);
			glRotatef(slo->angules[5],0,0,1);
		break;

		case 11:
			glTranslatef(0,0,(GLfloat)6);
			break;

		case 12:
			glTranslatef((GLfloat)142.696,(GLfloat)0,(GLfloat)10.645);
			break;

		case 13:
			glTranslatef((GLfloat)34,0,0);
			break;

	}

	           //    GLdouble mModel[16];
	            //    glGetDoublev(GL_MODELVIEW_MATRIX,mModel);
				//	cout<<"x:"<<mModel[12]<<" y:"<<mModel[13]<<" z:"<<mModel[14]<<endl;
	
	
		
	 
	

} ;
	//////////////SETS//////////////////////////////
	static void setAnguleArt1(GLfloat*angules,StackLoaderObject*slo){
	//no hace falta explicar VERDAD?
	slo->angules[0]=angules[0];
	slo->angules[1]=angules[1];
	slo->angules[2]=angules[2];
	slo->angules[3]=angules[3];
	slo->angules[4]=angules[4];
	slo->angules[5]=angules[5];
};
	
};

