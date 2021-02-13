#include "ESE_GRS.h"


///////////////////////////////////////////////////////////VARIABLES GLOBALES////////////////////////////////////////////////////
bool recibir_serie=false;
bool CargObjct=false,cargMenu=false;
bool boolNeXt=false,EsperandoReedireccionar=true;
bool threaDCOM=false,MostrarAngules=false,SeguirPuntoFinal=false;
bool corrdCambi=false,SetAngules=false;
char neXt;
unsigned toSaveCOM=2,toSaveSpeed=9600;
unsigned STRLEN,RadioButtonEstilo=0,RadioButtonRestriccion=0,RadioButtonSpeed=0,LastRBEstilo=0,LastRBRestriccion=0;
int contMenuToDraw=-1;
int movRatXinit=25,movRatYinit=0,movRatX=10,movRatY=0;
double trasladarX=0,trasladarY=0,trasladarZ=0;
double *cooRd=new double[3];

bool Pint=false;

int Initheight,Initwigth,velGiro=3;
int &movESE_GRSX=movRatX,&movESE_GRSY=movRatY,movESE_GRSZ=25;
float TimE=0,height,wigth;
GLfloat angules[6]={0,0,55,0,0,0};
GLfloat heightOrtho,wigthOrtho;
GLdouble movWheel=1;
char*msg,*recib="Esperando datos...";
///////////////////PUNTEROS////////////////////////
char*escrituraCOM="COM2",*escrituraVelocidad="9600";
///////////////////OBJECTS///////////////////////
StackLoaderObject*ManejadorObject=new StackLoaderObject();
//LoaderObject*NewObj;
PuertoSerie*p;
TimeDuration tCOM,TCentralTop,TSimular;
IGSClass*igs=new IGSClass;
thread*t1;
mutex m,m1,m2;
MeSSenger*messeng=new MeSSenger;
StackForms*ManejadorForms=new StackForms();
//SalverMovement*SalvMov=new SalverMovement();

//////////////////OTOS///////


///////////////////////////////////////////////////////////METODOS//////////////////////////////////////////////////////////////

////////////////CONTRUCTOR Y DESTRUCTOR//////////////////////////////////////////////
ESE_GRS::ESE_GRS(){
	//Constructor

	//funciones d inicialiacion del GLUT(OPENGL)
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);//inicio con cloes del rgb,doble buffer y buffer de profundidad
	Initheight=GetSystemMetrics (SM_CYSCREEN);//obtener tamaño y de pantalla
	Initwigth=GetSystemMetrics (SM_CXSCREEN);//obtener tamaño x de pantalla
	glutInitWindowPosition(0,0);//inicio de ventana de glut en 0,0 
	glutInitWindowSize(Initwigth-100,Initheight-100);//tamaño de la ventana
	height=(float)Initheight-100;
	wigth=(float)Initheight-100;
	glutCreateWindow("Mi Proyecto");//creo e inicio la ventana
	glEnable(GL_DEPTH_TEST);//acivo el buffer de profundidad

	/////////////////////////FUNCIONES POR DEFECTO/////////////////
	
	//funciones pedfinidad por el usuario para q GLUT las llame al realiarse un evento  
	glutDisplayFunc(display);//refescar pantalla
	glutMotionFunc(movRaton);//movimiento del raton
	glutMouseFunc(teclaRaton);//clics del raton
	glutReshapeFunc(reshape);//cambiar tamaño de pantalla
	glutMouseWheelFunc(wheel);//ruedita del mouse
	glutKeyboardFunc(keyboard);//teclado con teclas ASCLL
	glutSpecialFunc(SpecialKeys);//teclado con teclas speciales(Contl,Space,flechitas entre otras)
	glutIdleFunc(Idle);//al no recivir eventos
	glutCloseFunc(slavarInitDatos);//al cerrarse
	//////////////////////////INICIO MATRISES///////////////////////////////
	initProyecc();//inicializo el tipo de proyeccion y sus dimenciones
	cargarInitDatos();//cargar datos q se guardaron en un archivo .onrn q se guarda al cerrarse y hace q inicie donde lo dejastes(inicie el rotado lo demas tengo q programarlo)
	//InitMenu();
	t1=new thread(ThreadCargObject);
	ManejadorForms->Add(new Label("labelESE_GRS","ESE_GRS",*(new CRD(0,0,0)),1,(GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7,wigth,height),ManejadorForms);
	ManejadorForms->Add(new RadioButton("radioButtonMostrarAngules",*new CRD(0,0,0),"Angules",wigth,height,true),ManejadorForms);			
	MostrarAngules=true;
	ManejadorForms->Add(new Label("labelAngule0",(char*)to_string(angules[0]).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelAngule1",(char*)to_string(angules[1]).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelAngule2",(char*)to_string(angules[2]).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelAngule3",(char*)to_string(angules[3]).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelAngule4",(char*)to_string(angules[4]).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelAngule5",(char*)to_string(angules[5]).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelAnguleMatlab","MatLab",*new CRD(0,400,0),1,(GLfloat)1,(GLfloat)1,(GLfloat)1,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelAnguleCoordReales","OpenGL",*new CRD(0,420,0),1,(GLfloat)1,(GLfloat)1,(GLfloat)1,wigth,height),ManejadorForms);
	    
	/*igs->add(*new CRD(0,0,0),igs);
	igs->add(*new CRD(100,0,0),igs);
	//igs->NewLINE(igs);
	igs->add(*new CRD(200,110,0),igs);
	igs->add(*new CRD(300,300,0),igs);
	*/
}
ESE_GRS::~ESE_GRS(){
	//no hace falta explicar VERDAD?
	if(threaDCOM)
		{
		threaDCOM=false;
		recibir_serie=false;
	    t1->join();
	    }
	delete[]ManejadorObject;
	if(p->EstaConectado())
		delete p;
}
////////////////INICIALIZADORES//////////////////////////////////////////////////////
void ESE_GRS::initProyecc(){
	//inicio el tipo y dimenciones de la proyeccion
	glClearColor((GLclampf)0.3,(GLclampf)0.3,(GLclampf)0.3,1);//color de fondo
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-wigth/2,wigth/2,-height/2,height/2,-2*wigth,2*wigth);
	glMatrixMode(GL_MODELVIEW);

}
void ESE_GRS::Inicializar(){
	 glLoadIdentity();//cargo identidad

	 //inicio la proyeccion
	 initProyecc();
	
	
	 ManejadorObject->setAnguleArt1(angules,ManejadorObject);////agrego los angulos de rotacion a mi ManejadorObject
	 
	 wheelAndRotate();//me giro y acerco o alejo 
}
bool ESE_GRS::IniciarCargObjetos(){
	
	if(!CargObjct)
	{
		string g=string("Cargando Objetos ")+to_string(ManejadorObject->contLoaderObject)+string("/13 (")+to_string(ManejadorObject->contLoaderObject*100/13)+string("%)");
		text((char*)g.c_str(),-70,0,0,1,1,1,true,true);
		   glutPostRedisplay();
		   return false;
	}   
	else
	    {
		   InitMenu();
		   glutPostRedisplay();
		   cargMenu=true;
		   return true;
	    }


	       
	
	
	    


}
void ESE_GRS::InitMenu(){
	//inicializo y configuro los munu y subenu
	int SubMenuVista=glutCreateMenu(MenuVista);//Inicio de Submenus
	glutAddMenuEntry("Panoramica",-1);
	glutAddMenuEntry("Frontal(XY)",0);
	glutAddMenuEntry("Trasera(-XY)",1);
	glutAddMenuEntry("Derecha(ZY)",2);
	glutAddMenuEntry("Isquierda(-ZY)",3);
	glutAddMenuEntry("Superiror(X-Z)",4);
	glutAddMenuEntry("Inferior(XZ)",5);


	int subMenuToDraw=glutCreateMenu(MenuToDraw);
	glutAddMenuEntry("Ensamblar", - 1);
	for (int ii=0;ii<ManejadorObject->contLoaderObject;ii++)
	glutAddMenuEntry(ManejadorObject->Stack[ii]->nameStr.c_str(),ii);

	glutCreateMenu(defaul_menu);//aqui creo el menu general donde van todos los submenus

	//glutAddSubMenu("Iluminacion",SubMenuLight);//no lo estoy usando
	if(!recibir_serie)
	{
			glutAddMenuEntry("INICIAR PUERTO SERIE",0);
			glutAddSubMenu("Vista",SubMenuVista);//agrego el submenu
			glutAddSubMenu("Modelo a pintar",subMenuToDraw);//agrego el submenu
			//glutAddMenuEntry("CargarMovets",3);
			glutAddMenuEntry("Set_Angules",4);
	
	}
	else
	{
	   glutAddSubMenu("Vista",SubMenuVista);//agrego el submenu
	   glutAddMenuEntry("DETENER PUERTO SERIE",1);
	}
	
	

	glutAttachMenu(GLUT_RIGHT_BUTTON);//espaecifico con q tecla se activa el evento
}
void ESE_GRS::wheelAndRotate(bool a){
	//procedimientos de rotacion y acercamiento y alejamiento de la camara con el mouse
	if(a)
	{
	glScaled(-movWheel,-movWheel,-movWheel);
	glRotatef((GLfloat)-movRatX/velGiro,1.0,0.0,0.0);
	glRotatef((GLfloat)-movRatY/velGiro,0.0,0.0,1.0);
	glRotatef((GLfloat)-movESE_GRSZ/velGiro,0.0,0.0,1.0);
		return;
	}
	
	glScaled(movWheel,movWheel,movWheel);
	glRotatef((GLfloat)movRatX/velGiro,1.0,0.0,0.0);
	glRotatef((GLfloat)movRatY/velGiro,0.0,0.0,1.0);
	glRotatef((GLfloat)movESE_GRSZ/velGiro,0.0,0.0,1.0);
	
}
///////////////////DIBUJAR////////////////////////////////////////////////////////////
void ESE_GRS::display(){
	glMatrixMode(GL_MODELVIEW);//cargo martiz de vista
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//borro todo 
	if(!CargObjct||!cargMenu)
		IniciarCargObjetos();
	else
	{
	   // recivirDatosCOM();//recivo y proceso la entrada del puerto serie
		Inicializar();//iniciaizo proyeccin luces y pongo los angulos del brazo 
		Entorno();
		ManejadorObject->draw(ManejadorObject,contMenuToDraw);
		DrawingObjectIGS();
		//primero trasladar segun corrdenadas de la matriz de traslacion y rotacion del brazo 
		//glTranslatef((GLfloat)cooRd[0],(GLfloat)cooRd[1],(GLfloat)cooRd[2]);
		if(contMenuToDraw==-1){
			//es neceario el PuchMatrix para q la coordenada del OpenGL quede donde va,y no desplazada segun la coordenad del matlab
			//No inicamos el LoadIdentity porq ya la matriz llega a aki vacia,pero rotalda y escladada por whellAndRotate();
			glPushMatrix();
			//glTranslated(cooRd[0],cooRd[1],cooRd[2]);
		    glColor3d(0,0,0);
			glBegin(GL_POINTS);
			glVertex3f((GLfloat)cooRd[0],(GLfloat)cooRd[1],(GLfloat)cooRd[2]);
			glEnd();
			glPopMatrix();
		
			//las coordenadas no lleban una identidad,ya q cuando se sacan en el loaderObject,
		//se sacan con una identidad ya y en este punto del codigo todavia esta la coordenada de la modelview_matrix esta en 000,
		//pero si tiene un wheel y una rotacion,
		//por lo tanto se cargan sin mas para q se ejecute correctamante el WheelandRotate();
		
			//glTranslated(ManejadorObject->CoordReales[0],ManejadorObject->CoordReales[1],ManejadorObject->CoordReales[2]);
		glColor3d(1,1,1);
		glBegin(GL_POINTS);
		glVertex3f((GLfloat)ManejadorObject->CoordReales[0],(GLfloat)ManejadorObject->CoordReales[1],(GLfloat)ManejadorObject->CoordReales[2]);
		glEnd();
		}
		
		////Inicio los .obj y pongo el caartel de Cargando///////////////////////////////////////////
		
		

	}//end of carga de objetos
	glFlush();//siempre lleva esto no de q es bien 
	glutSwapBuffers();
}
void ESE_GRS::Entorno(){
	glPushMatrix();
	glLoadIdentity();

	

	 if(corrdCambi)//calculo las nuevas coordenadas del punto final
	   {
		cooRd=coordenadas();
	    if(SeguirPuntoFinal)
	      {
		  trasladarX=-cooRd[0];
		  trasladarY=-cooRd[1];
		  trasladarZ=-cooRd[2];
	      }
		corrdCambi=false;
	   }

	 string sd;
		string sdd;
		sdd+="MatLab :x:"+to_string(cooRd[0])+" y:"+to_string(cooRd[1])+" z:"+to_string(cooRd[2]);
		sd+="OpenGL:x:"+to_string(ManejadorObject->CoordReales[0])+" y:"+to_string(ManejadorObject->CoordReales[1])+" z:"+to_string(ManejadorObject->CoordReales[2]);
		ManejadorForms->AddNewText("labelAnguleCoordReales",(char*)(sd.c_str()),ManejadorForms);
		ManejadorForms->AddNewText("labelAnguleMatlab",(char*)(sdd.c_str()),ManejadorForms);
		if(!Pint)
			{
				Pint=true;
				glutPostRedisplay();
		    }
	 messeng->Drawing_and_Decremt(messeng);
	 text("o",-2.0,-1.5,2*wigth-1,(GLfloat)0.8,(GLfloat)0.8,(GLfloat)0.8);
	 ManejadorForms->DrawForms(ManejadorForms);
	//mostrar en pantalla el inicio de la conexion puerto serie 
	/*if(recibir_serie)
	    {
		   text(recib,(GLfloat)-int(strlen(recib)*4.5),-(GLfloat)((height/2)-20),(GLfloat)2*wigth-1,(GLfloat)0.5,(GLfloat)0.5,(GLfloat)0.5,true,true);
		}
	*/
	
	  glPopMatrix();
	  //pinto el eje de coordenadas del systema
	  glPushMatrix();
	  glLoadIdentity();
	  glTranslatef((GLfloat)-wigth*2/5,(GLfloat)-height*2/5,0.0);
	  wheelAndRotate();
	  text("x",(GLfloat)(50/movWheel),0,0);
	  text("y",0,(GLfloat)(50/movWheel),0);
	  text("z",0,0,(GLfloat)(50/movWheel));
	  smallEjeCoord((GLfloat)(50/movWheel));
	glPopMatrix();
	
	glTranslatef((GLfloat)trasladarX,(GLfloat)trasladarY,(GLfloat)trasladarZ);//desplazamiento manual de  ejes x , y , z
}
void ESE_GRS::DrawingObjectIGS(){
	if(igs->GETCont(igs)==1)
	{
		glColor3f(0,1,0);
		glBegin(GL_POINTS);
	    glVertex3f((GLfloat)igs->Vertex[0].x,(GLfloat)igs->Vertex[0].y,(GLfloat)igs->Vertex[0].z);
		glEnd();
	}
	else
	{
       for(unsigned i=1;i<igs->GETCont(igs);i++)
		{
			unsigned lastNL=igs->GETContNL(igs),actualNL=0;
			bool NEWLINE=false;
			for(unsigned ii=0;ii<lastNL;ii++)
			 {
				if(igs->NewLine[ii]==i)
				{
					if(i+1==igs->GETCont(igs))
						break;
					NEWLINE=true;
					i++;
					break;   				
				}
			 }
		if(lastNL)
		   glColor3f(1,1,1);
		glBegin(GL_LINE_STRIP);
		if(NEWLINE)
		   {  
			   if(++actualNL==lastNL)
				   glColor3f(0,1,0);				 
		   glEnd();
		   glBegin(GL_LINE_STRIP);
		   }
		glVertex3f((GLfloat)igs->Vertex[i-1].x,(GLfloat)igs->Vertex[i-1].y,(GLfloat)igs->Vertex[i-1].z);
		glVertex3f((GLfloat)igs->Vertex[i].x,(GLfloat)igs->Vertex[i].y,(GLfloat)igs->Vertex[i].z);
		glEnd();
		}
	}

}
void ESE_GRS::text(char*c,GLfloat x,GLfloat y,GLfloat z,GLfloat R,GLfloat G,GLfloat B,bool big,bool moreBig){
	//dibujo el char c en la posicion x,y,z con color RGB
	
	glColor3f(R,G,B);
	glRasterPos3f(x,y,z);
	for(unsigned int i=0;i<strlen(c);i++){
		if(moreBig)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		else if(big)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);
	    else 
	 	    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c[i]);
		
		
	}
}
void ESE_GRS::smallEjeCoord(GLfloat size){
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
/////////////////////FUNCIONES DE GLUT A LLAMAR POR DEFECTO////////////////////////////
void ESE_GRS::reshape(int x,int y){
	wigth=(float)x;height=(float)y;
	ManejadorForms->NewTotalsProp((float)x,(float)y,ManejadorForms);
	ManejadorForms->GetForm("radioButtonMostrarAngules",ManejadorForms)->NewCRD(new CRD(wigth-100,8,0));
	ManejadorForms->GetForm("labelAngule0",ManejadorForms)->NewCRD(new CRD(wigth-100,25,0));
	ManejadorForms->GetForm("labelAngule1",ManejadorForms)->NewCRD(new CRD(wigth-100,40,0));
	ManejadorForms->GetForm("labelAngule2",ManejadorForms)->NewCRD(new CRD(wigth-100,55,0));
	ManejadorForms->GetForm("labelAngule3",ManejadorForms)->NewCRD(new CRD(wigth-100,70,0));
	ManejadorForms->GetForm("labelAngule4",ManejadorForms)->NewCRD(new CRD(wigth-100,85,0));
	ManejadorForms->GetForm("labelAngule5",ManejadorForms)->NewCRD(new CRD(wigth-100,100,0));

	glViewport(0,0,x,y);//creo una zona de la ventana con el contenido  
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
void ESE_GRS::movRaton(GLsizei x,GLsizei y){
		movRatY+=x-movRatXinit;
		movRatX+=y-movRatYinit;
		movRatXinit=x;
		movRatYinit=y;

	glutPostRedisplay();//refresco y ejecuto el displayFunc()
}
void ESE_GRS::Idle(){
if(recibir_serie)
	glutPostRedisplay();
}
void ESE_GRS::teclaRaton(int boton,int state,int x,int y){
	if(boton==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
	   bool eRror=false;
	   string s;
	   switch (ManejadorForms->PresionarForm((float)x,(float)y,ManejadorForms))
	   {
	   case 0:
		  
		   break;

		                                                case Type::RADIOBUTTON:
				/////////////////////////////////////////////////////////RADIOBUTTON//////////////////////////////////////////////////////////

		    if(recibir_serie)/////////////////////////if recivir_serie///////////////////////////////////////////////////////////////////////////////////
		   {
			   if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("radioButtonGroupProp",ManejadorForms)))
			        RadioButtonEstilo=ManejadorForms->GetForm("radioButtonGroupProp",ManejadorForms)->GetChecket();
			   if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("radioButtonGroupRestriccion",ManejadorForms)))
		            RadioButtonRestriccion=ManejadorForms->GetForm("radioButtonGroupRestriccion",ManejadorForms)->GetChecket();   
			  /* if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("radioButtonSeguirMovim",ManejadorForms)))
			   {
				   if(SalvMov->Enable)
				   {
					   SalvMov->Enable=false;
					   ManejadorForms->GetForm("radioButtonSeguirMovim",ManejadorForms)->CambiarEscritura("Movent");
					   ManejadorForms->Sub("radioButtonGuardarArchivo",ManejadorForms);
					   ManejadorForms->Sub("buttonGurdarMovents",ManejadorForms);
					   ManejadorForms->Sub("textBoxurdarMovent",ManejadorForms);
				   }
				   else 
				   {
				   SalvMov->Enable=true;
				   ManejadorForms->GetForm("radioButtonSeguirMovim",ManejadorForms)->CambiarEscritura("Detener");
				   ManejadorForms->Add(new RadioButton("radioButtonGuardarArchivo",*new CRD(10,170+(18*11),0),"Guardar",wigth,height),ManejadorForms);
				   }
				
		       }
			   if(SalvMov->Enable&&Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("radioButtonGuardarArchivo",ManejadorForms)))
			  {
				  if(!SalvMov->GETCont(SalvMov))
				     {
				       SalvMov->Enable=false;
					   ManejadorForms->GetForm("radioButtonSeguirMovim",ManejadorForms)->CambiarEscritura("Movent");
					   ManejadorForms->GetForm("radioButtonSeguirMovim",ManejadorForms)->CambiarChecket();
					   ManejadorForms->Sub("radioButtonGuardarArchivo",ManejadorForms);
					   messeng=new MeSSenger("No hay datos para guardar",position::CENTER_TOP,wigth,height,3,1,1,0,2);
				     }
				  else
				  {
					  ManejadorForms->Add(new TextBox("textBoxurdarMovent",*new CRD(10,170+(18*11),0),100,20,wigth,height),ManejadorForms);
					  ManejadorForms->GetForm("textBoxurdarMovent",ManejadorForms)->CambiarEscritura("mtv.mtv");
					  ManejadorForms->Sub("radioButtonGuardarArchivo",ManejadorForms);
					  ManejadorForms->Add(new Button("buttonGurdarMovents",Type::BUTTOMGUARDARMOVENT,*new CRD(10,170+(18*11)+20,0),0,1,0,100,10,wigth,height),ManejadorForms);

				  }
			  
			  
			  }*/
			}
			else//////////////no recivir_Serie///////////////////////////////////////////////////////////////////////////////////
			{
			/*if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("radioButtonGroupSpeed",ManejadorForms)))
				   RadioButtonSpeed=ManejadorForms->GetForm("radioButtonGroupSpeed",ManejadorForms)->GetChecket();   
  
			  if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("buttoninitStopsimulacion",ManejadorForms)))
			  {
				  if(!InitStopSimul)
				  {
					messeng=new MeSSenger("Simulando...",position::CENTER_TOP,wigth,height,100,1,1,0,3);
				    ManejadorForms->GetForm("buttoninitStopsimulacion",ManejadorForms)->CambiarEscritura("Detener Simulacion");
					salirSimulacion=false;
					t2=new threaDCOM(ThreadSimular);
					InitStopSimul=true;
				  }
				  else
				  {
				   ManejadorForms->GetForm("buttoninitStopsimulacion",ManejadorForms)->CambiarEscritura("Iniciar Simulacion");
				   ManejadorForms->GetForm("buttoninitStopsimulacion",ManejadorForms)->CambiarChecket();
				   InitStopSimul=false;
				   salirSimulacion=true;
				  }
			  }
			  */
		    }
			//////////////////SIEMPRE///////////////////////////////////////////////////////////////////////////////////

			if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("radioButtonMostrarAngules",ManejadorForms)))
				{
					if(!MostrarAngules)
					{
						MostrarAngules=true;
						ManejadorForms->Add(new Label("labelAngule0",(char*)to_string(angules[0]).c_str(),*new CRD(wigth-100,25,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	                    ManejadorForms->Add(new Label("labelAngule1",(char*)to_string(angules[1]).c_str(),*new CRD(wigth-100,40,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	                    ManejadorForms->Add(new Label("labelAngule2",(char*)to_string(angules[2]).c_str(),*new CRD(wigth-100,55,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	                    ManejadorForms->Add(new Label("labelAngule3",(char*)to_string(angules[3]).c_str(),*new CRD(wigth-100,70,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	                    ManejadorForms->Add(new Label("labelAngule4",(char*)to_string(angules[4]).c_str(),*new CRD(wigth-100,85,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	                    ManejadorForms->Add(new Label("labelAngule5",(char*)to_string(angules[5]).c_str(),*new CRD(wigth-100,100,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	
					}
					else
					{
						ManejadorForms->Sub("labelAngule0",ManejadorForms);
						ManejadorForms->Sub("labelAngule1",ManejadorForms);
						ManejadorForms->Sub("labelAngule2",ManejadorForms);
						ManejadorForms->Sub("labelAngule3",ManejadorForms);
						ManejadorForms->Sub("labelAngule4",ManejadorForms);
						ManejadorForms->Sub("labelAngule5",ManejadorForms);
						MostrarAngules=false;
					
					}
				
				}


		   break;
	                                                 case Type::BUTTONCANCELSETANGULES:
		    ManejadorForms->Sub("textBoxsSetAngules0",ManejadorForms);
			ManejadorForms->Sub("textBoxsSetAngules1",ManejadorForms);
			ManejadorForms->Sub("textBoxsSetAngules2",ManejadorForms);
			ManejadorForms->Sub("textBoxsSetAngules3",ManejadorForms);
			ManejadorForms->Sub("textBoxsSetAngules4",ManejadorForms);
			ManejadorForms->Sub("textBoxsSetAngules5",ManejadorForms);
			ManejadorForms->Sub("buttonInitSetAngules",ManejadorForms);
			ManejadorForms->Sub("buttonCancelSetAngules",ManejadorForms);
			SetAngules=false;
		   break;
	                                                case Type::BUTTONINITSETANGULES:
		  
		   for(unsigned i=0;i<6;i++)
		   {
			   s=("textBoxsSetAngules");
			   if(eRror)
			   {
				    break;
			   }
			   s+=to_string(i);
			   char*datA=ManejadorForms->GetForm((char*)s.c_str(),ManejadorForms)->GetEscritura();
			   bool negtv=false,punto=false;
		       for(unsigned i=0;i<strlen(datA);i++)
		            {
					  if(!isdigit(datA[i]))
					     {
						  if(datA[i]=='.'&&punto==false)
						  {
							  punto=true;
						  }
						  else if(datA[i]=='-'&&negtv==false&&i==0)
						     {
							  negtv=true;
						     }
						  else
						     {
							  eRror=true;
							  break;
						     }
					     }
		           }
			   s.clear();
		   }
		   if(eRror)
		      messeng=new MeSSenger("Error ,escritura de angulos incorrecta",position::CENTER_TOP,wigth,height,3,1,0,0,2);
		   else
		   {
			   messeng=new MeSSenger("Cargados Angulos Correctamante",position::CENTER_TOP,wigth,height,3,0,1,0,2);
			   for(unsigned i=0;i<6;i++)
		       {
			   s=("textBoxsSetAngules");
			   s+=to_string(i);
				if(strlen(ManejadorForms->GetForm((char*)s.c_str(),ManejadorForms)->GetEscritura()))
			       angules[i]=(GLfloat)atof(ManejadorForms->GetForm((char*)s.c_str(),ManejadorForms)->GetEscritura());
			    s.clear();
				
			   }
				   
			   corrdCambi=true;
			   if(MostrarAngules)
						{
						
						ManejadorForms->GetForm("labelAngule0",ManejadorForms)->CambiarEscritura((char*)to_string(angules[0]).c_str());
						ManejadorForms->GetForm("labelAngule1",ManejadorForms)->CambiarEscritura((char*)to_string(angules[1]).c_str());
						ManejadorForms->GetForm("labelAngule2",ManejadorForms)->CambiarEscritura((char*)to_string(angules[2]).c_str());
						ManejadorForms->GetForm("labelAngule3",ManejadorForms)->CambiarEscritura((char*)to_string(angules[3]).c_str());
						ManejadorForms->GetForm("labelAngule4",ManejadorForms)->CambiarEscritura((char*)to_string(angules[4]).c_str());
						ManejadorForms->GetForm("labelAngule5",ManejadorForms)->CambiarEscritura((char*)to_string(angules[5]).c_str());
						
						}
		    }
		   
		  

		   break;
	                                                  
		   
		  
	 


	  
	                                                 
	   	                                               case Type::BUTTONINITCOM:
		   ESE_GRS::defaul_menu(-1);
		   break;
	  	                                               case Type::BUTTONCANCELCOM:
		   ManejadorForms->Sub("textBoxCOM",ManejadorForms);
		   ManejadorForms->Sub("textBoxSpeed",ManejadorForms);
		   ManejadorForms->Sub("buttonInitCOM",ManejadorForms);
		   ManejadorForms->Sub("buttonCancelCOM",ManejadorForms);
	       break;
	  	                                               case Type::BUTTONINITSTOPCOM:
		   ESE_GRS::defaul_menu(-2);
		   break;
	  	                                               case Type::BUTTONCANCELSTOPCOM:
			ManejadorForms->Sub("laberDetener",ManejadorForms);
			ManejadorForms->Sub("buttonInitDetener",ManejadorForms);
			ManejadorForms->Sub("buttonCancelDetener",ManejadorForms);
		   break;
													   
		  
	   }
	}
   
  
   if(boton==GLUT_LEFT_BUTTON && state==GLUT_DOWN )//girar al puslar clik dercho con el mouse(misma opcion q el movRat para el primer clic no te varie la rotacion)
   {
	movRatXinit=x;
	movRatYinit=y;
	
   }
	
	glutPostRedisplay();
}
void ESE_GRS::keyboard(unsigned char tecla,int x,int y ){

	if(tecla==8)
	    ManejadorForms->SubText(ManejadorForms);
	else
		ManejadorForms->AddText(tecla,ManejadorForms);

	if(tecla=='l')
		{
		trasladarY+=5;
		SeguirPuntoFinal=false;
	    }
	if(tecla=='p')
	   {
	   trasladarY-=5;
	   SeguirPuntoFinal=false;
	   }


	if(!recibir_serie&&!SetAngules)
	{
	  switch (tecla)
	    {
	
		case '1':
				angules[0]+=(GLfloat)0.9;
				corrdCambi=true;
		break;
		case '2':
				angules[0]-=(GLfloat)0.9;	
				corrdCambi=true;
		break;

		case '3':
				angules[1]+=(GLfloat)0.9;
				corrdCambi=true;
		break;
		case '4':
				angules[1]-=(GLfloat)0.9;
				corrdCambi=true;
		break;

		case '5':
				angules[2]+=(GLfloat)0.9;
				corrdCambi=true;
		break;

		case '6':
				angules[2]-=(GLfloat)0.9;
				corrdCambi=true;
		break;
		case '7':
				angules[3]+=(GLfloat)0.9;
				corrdCambi=true;
		break;
		case '8':
				angules[3]-=(GLfloat)0.9;
				corrdCambi=true;
		break;
		case '9':
				
				angules[4]+=(GLfloat)0.9;
				corrdCambi=true;
		break;

		case '0':
				angules[4]-=(GLfloat)0.9;
				corrdCambi=true;
		break;
		case '-':
				
				angules[5]+=(GLfloat)0.9;
				corrdCambi=true;
		break;

		case '=':
				angules[5]-=(GLfloat)0.9;
				corrdCambi=true;
		break;
		

	     }

	      if(MostrarAngules)
						{
							  ManejadorForms->GetForm("labelAngule0",ManejadorForms)->CambiarEscritura((char*)to_string(angules[0]).c_str());
						      ManejadorForms->GetForm("labelAngule1",ManejadorForms)->CambiarEscritura((char*)to_string(angules[1]).c_str());
						      ManejadorForms->GetForm("labelAngule2",ManejadorForms)->CambiarEscritura((char*)to_string(angules[2]).c_str());
						      ManejadorForms->GetForm("labelAngule3",ManejadorForms)->CambiarEscritura((char*)to_string(angules[3]).c_str());
						      ManejadorForms->GetForm("labelAngule4",ManejadorForms)->CambiarEscritura((char*)to_string(angules[4]).c_str());
						      ManejadorForms->GetForm("labelAngule5",ManejadorForms)->CambiarEscritura((char*)to_string(angules[5]).c_str());
							  
						}


	  DataProcessor::RectificarAngules(angules);
	 }
	 else
      {
	   //messeng=new MeSSenger("Accion no valida ;Conexion por puerto serie ya iniciada",position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,0,0,2);
      }
	
	
	glutPostRedisplay();//refresco y ejecuto el displayFunc()
}
void ESE_GRS::wheel(int boton,int direcc,int x,int y){
	
	if(direcc>0) {
		if(movWheel<20) 
			movWheel+=0.1;
	
	}else {
		
	
	 if(movWheel>1) 
		 movWheel-=0.3;
	
	
	}
		glutPostRedisplay();//refresco y ejecuto el displayFunc()

}
void ESE_GRS::SpecialKeys(int tecla,int x,int y ){
	
	switch (tecla)
	{
	case -1:
		angules[0]=0;
		angules[1]=(GLfloat)-13.8;
        angules[2]=(GLfloat)-44.5;
        angules[3]=(GLfloat)2.04;
		angules[4]=(GLfloat)90;
		angules[5]=(GLfloat)-2.04;
		corrdCambi=true;

		 if(MostrarAngules)
			{
			ManejadorForms->GetForm("labelAngule0",ManejadorForms)->CambiarEscritura((char*)to_string(angules[0]).c_str());
			ManejadorForms->GetForm("labelAngule1",ManejadorForms)->CambiarEscritura((char*)to_string(angules[1]).c_str());
			ManejadorForms->GetForm("labelAngule2",ManejadorForms)->CambiarEscritura((char*)to_string(angules[2]).c_str());
			ManejadorForms->GetForm("labelAngule3",ManejadorForms)->CambiarEscritura((char*)to_string(angules[3]).c_str());
		    ManejadorForms->GetForm("labelAngule4",ManejadorForms)->CambiarEscritura((char*)to_string(angules[4]).c_str());
			ManejadorForms->GetForm("labelAngule5",ManejadorForms)->CambiarEscritura((char*)to_string(angules[5]).c_str());
			}
		
		break;
	case GLUT_KEY_F4:
		if(!recibir_serie)
		{
		angules[0]=0;
        angules[1]=(GLfloat)-13.8;
        angules[2]=(GLfloat)-44.5;
        angules[3]=(GLfloat)2.04;
		angules[4]=(GLfloat)90;
		angules[5]=(GLfloat)-2.04;
		corrdCambi=true;

		 if(MostrarAngules)
			{
			ManejadorForms->GetForm("labelAngule0",ManejadorForms)->CambiarEscritura((char*)to_string(angules[0]).c_str());
			ManejadorForms->GetForm("labelAngule1",ManejadorForms)->CambiarEscritura((char*)to_string(angules[1]).c_str());
			ManejadorForms->GetForm("labelAngule2",ManejadorForms)->CambiarEscritura((char*)to_string(angules[2]).c_str());
			ManejadorForms->GetForm("labelAngule3",ManejadorForms)->CambiarEscritura((char*)to_string(angules[3]).c_str());
		    ManejadorForms->GetForm("labelAngule4",ManejadorForms)->CambiarEscritura((char*)to_string(angules[4]).c_str());
			ManejadorForms->GetForm("labelAngule5",ManejadorForms)->CambiarEscritura((char*)to_string(angules[5]).c_str());
			}
		}
		break;
	case GLUT_KEY_F5:
		if(!recibir_serie)
		{
		/*trasladarX=trasladarZ=0;
		trasladarY=-50;
		angules[0]=0;
        angules[1]=150;
        angules[2]=-150;
        angules[3]=0;
		angules[4]=270;
		angules[5]=270;
		MenuVista(-1);
		*/
		trasladarX=0;
		trasladarY=0;
		trasladarZ=0;
		angules[0]=0;
        angules[1]=0;
        angules[2]=0;
        angules[3]=0;
		angules[4]=0;
		angules[5]=0;
		corrdCambi=true;
		SeguirPuntoFinal=false;
		MenuVista(-1);
		 if(MostrarAngules)
			{
			ManejadorForms->GetForm("labelAngule0",ManejadorForms)->CambiarEscritura((char*)to_string(angules[0]).c_str());
			ManejadorForms->GetForm("labelAngule1",ManejadorForms)->CambiarEscritura((char*)to_string(angules[1]).c_str());
			ManejadorForms->GetForm("labelAngule2",ManejadorForms)->CambiarEscritura((char*)to_string(angules[2]).c_str());
			ManejadorForms->GetForm("labelAngule3",ManejadorForms)->CambiarEscritura((char*)to_string(angules[3]).c_str());
		    ManejadorForms->GetForm("labelAngule4",ManejadorForms)->CambiarEscritura((char*)to_string(angules[4]).c_str());
			ManejadorForms->GetForm("labelAngule5",ManejadorForms)->CambiarEscritura((char*)to_string(angules[5]).c_str());
			}
		}
		else
		   {
		    //messeng=new MeSSenger("Accion no valida ;Conexion por puerto serie ya iniciada",position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,0,0,2);
			trasladarX=0;
			trasladarY=0;
			trasladarZ=0;
			MenuVista(-1);
			SeguirPuntoFinal=false;
		   }
			break;
	case GLUT_KEY_F6:
		//me traslado al final del brazo
		trasladarX=-cooRd[0];
		trasladarY=-cooRd[1];
		trasladarZ=-cooRd[2];
		SeguirPuntoFinal=false;
		break;
		case GLUT_KEY_F7:
			if(!SeguirPuntoFinal)
			{   
				SeguirPuntoFinal=true;
				corrdCambi=true;
			}
			break;
	        
			case GLUT_KEY_LEFT:
				trasladarX+=5;
				SeguirPuntoFinal=false;
			break;
			case GLUT_KEY_RIGHT:
				trasladarX-=5;
				SeguirPuntoFinal=false;
			break;
			case GLUT_KEY_UP:
	            trasladarZ-=5;
				SeguirPuntoFinal=false;
			break;
			case GLUT_KEY_DOWN:
				trasladarZ+=5;
				SeguirPuntoFinal=false;
			break;
	
		
	}
	glutPostRedisplay();//refresco y ejecuto el displayFunc()
}
//////////////////////////MENUS////////////////////////////////////////////////////////
void ESE_GRS::defaul_menu(int opcion){
	switch (opcion)
	{
	case 4:///SET angules
		ManejadorForms->Sub("textBoxCOM",ManejadorForms);
		ManejadorForms->Sub("buttonInitCOM",ManejadorForms);
		ManejadorForms->Sub("buttonCancelCOM",ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules0",(char*)to_string(angules[0]).c_str(),*(new CRD(0,100,0)),110,20,wigth,height),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules1",(char*)to_string(angules[1]).c_str(),*(new CRD(0,125,0)),110,20,wigth,height),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules2",(char*)to_string(angules[2]).c_str(),*(new CRD(0,150,0)),110,20,wigth,height),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules3",(char*)to_string(angules[3]).c_str(),*(new CRD(0,175,0)),110,20,wigth,height),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules4",(char*)to_string(angules[4]).c_str(),*(new CRD(0,200,0)),110,20,wigth,height),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules5",(char*)to_string(angules[5]).c_str(),*(new CRD(0,225,0)),110,20,wigth,height),ManejadorForms);
		ManejadorForms->Add(new Button("buttonInitSetAngules",Type::BUTTONINITSETANGULES,*new CRD(0,250,0),0,1,0,80,10,wigth,height),ManejadorForms);
		ManejadorForms->Add(new Button("buttonCancelSetAngules",Type::BUTTONCANCELSETANGULES,*new CRD(80,250,0),1,0,0,30,10,wigth,height),ManejadorForms);
		//ManejadorForms->Sub("textBoxsCargarMovents",ManejadorForms);
		//ManejadorForms->Sub("buttonInitCargaMovemts",ManejadorForms);
		//ManejadorForms->Sub("buttonCancelCargaMovemts",ManejadorForms);
		//ManejadorForms->Sub("textBoxSpeed",ManejadorForms);
		//ManejadorForms->Sub("buttoninitStopsimulacion",ManejadorForms);
		//ManejadorForms->Sub("radioButtonGroupSpeed",ManejadorForms);
		//ManejadorForms->Sub("labelMovements1",ManejadorForms);
		//ManejadorForms->Sub("labelMovements2",ManejadorForms);
		
		SetAngules=true;
		break;
	case 3://inicio carga de Movents
		/*ManejadorForms->Add(new TextBox("textBoxsCargarMovents",*(new CRD(0,50,0)),70,20,wigth,height),ManejadorForms);
		ManejadorForms->GetForm("textBoxsCargarMovents",ManejadorForms)->CambiarEscritura("mtv.mtv");
		ManejadorForms->Add(new Button("buttonInitCargaMovemts",Type::BUTTONINTICARGAMOVENTS,*(new CRD(0,71,0)),0,1,0,70,10,wigth,height),ManejadorForms);
		ManejadorForms->Add(new Button("buttonCancelCargaMovemts",Type::BUTTONCANCELCARGAMOVENTS,*(new CRD(71,50,0)),1,0,0,10,31,wigth,height),ManejadorForms);
	    ManejadorForms->Sub("textBoxCOM",ManejadorForms);
		ManejadorForms->Sub("textBoxSpeed",ManejadorForms);
		ManejadorForms->Sub("buttonInitCOM",ManejadorForms);
		ManejadorForms->Sub("buttonCancelCOM",ManejadorForms);
		ManejadorForms->Sub("textBoxsSetAngules0",ManejadorForms);
		ManejadorForms->Sub("textBoxsSetAngules1",ManejadorForms);
		ManejadorForms->Sub("textBoxsSetAngules2",ManejadorForms);
		ManejadorForms->Sub("textBoxsSetAngules3",ManejadorForms);
		ManejadorForms->Sub("textBoxsSetAngules4",ManejadorForms);
		ManejadorForms->Sub("textBoxsSetAngules5",ManejadorForms);
		ManejadorForms->Sub("buttonInitSetAngules",ManejadorForms);
		ManejadorForms->Sub("buttonCancelSetAngules",ManejadorForms);
		*/
		break;
	case 0://inicializo botones para INIT COM
		if(SetAngules)
		   {
		   ManejadorForms->Sub("textBoxsSetAngules0",ManejadorForms);
		   ManejadorForms->Sub("textBoxsSetAngules1",ManejadorForms);
		   ManejadorForms->Sub("textBoxsSetAngules2",ManejadorForms);
	   	   ManejadorForms->Sub("textBoxsSetAngules3",ManejadorForms);
		   ManejadorForms->Sub("textBoxsSetAngules4",ManejadorForms);
		   ManejadorForms->Sub("textBoxsSetAngules5",ManejadorForms);
		   ManejadorForms->Sub("buttonInitSetAngules",ManejadorForms);
		   ManejadorForms->Sub("buttonCancelSetAngules",ManejadorForms);
		   }
		  ManejadorForms->Add(new TextBox("textBoxCOM",*(new CRD(0,50,0)),70,20,wigth,height),ManejadorForms);
		  ManejadorForms->AddNewText("textBoxCOM",escrituraCOM,ManejadorForms);
		  ManejadorForms->Add(new TextBox("textBoxSpeed",*(new CRD(0,71,0)),70,20,wigth,height),ManejadorForms);
		  ManejadorForms->AddNewText("textBoxSpeed",escrituraVelocidad,ManejadorForms);
		  ManejadorForms->Add(new Button("buttonInitCOM",Type::BUTTONINITCOM,*(new CRD(0,92,0)),0,1,0,70,10,wigth,height),ManejadorForms);
		  ManejadorForms->Add(new Button("buttonCancelCOM",Type::BUTTONCANCELCOM,*(new CRD(71,50,0)),1,0,0,10,52,wigth,height),ManejadorForms);
	      // ManejadorForms->Sub("textBoxsCargarMovents",ManejadorForms);
		  // ManejadorForms->Sub("buttonInitCargaMovemts",ManejadorForms);
		  // ManejadorForms->Sub("buttonCancelCargaMovemts",ManejadorForms);
		  // ManejadorForms->Sub("labelMovements1",ManejadorForms);
		  // ManejadorForms->Sub("labelMovements2",ManejadorForms);
		  // ManejadorForms->Sub("buttoninitStopsimulacion",ManejadorForms);
		  // ManejadorForms->Sub("radioButtonGroupSpeed",ManejadorForms);
		  // salirSimulacion=true;
		   SetAngules=false;
		   
		  
		   
	break;


	case 1://inicializo botonos para el STOP COM
			ManejadorForms->Add(new Label("laberDetener","Detener?",*new CRD(0,48,0),1,1,1,1,wigth,height),ManejadorForms);	
			ManejadorForms->Add(new Button("buttonInitDetener",Type::BUTTONINITSTOPCOM,*new CRD(0,65,0),0,1,0,(float)strlen("Detener?")*10,10,wigth,height),ManejadorForms);
		    ManejadorForms->Add(new Button("buttonCancelDetener",Type::BUTTONCANCELSTOPCOM,*new CRD((float)strlen("Detener?")*10,50,0),1,0,0,10,25,wigth,height),ManejadorForms);

	break;


	case -1://Inicio el COM
		
        STRLEN=strlen(ManejadorForms->GetForm("textBoxCOM",ManejadorForms)->GetEscritura());
		escrituraCOM=new char[STRLEN+1];
		escrituraCOM[STRLEN]=0;
		for(unsigned i=0;i<STRLEN;i++)
			escrituraCOM[i]=ManejadorForms->GetForm("textBoxCOM",ManejadorForms)->GetEscritura()[i];
		
		STRLEN=strlen(ManejadorForms->GetForm("textBoxSpeed",ManejadorForms)->GetEscritura());
		escrituraVelocidad=new char[STRLEN+1];
		escrituraVelocidad[STRLEN]=0;
		for(unsigned i=0;i<STRLEN;i++)
			escrituraVelocidad[i]=ManejadorForms->GetForm("textBoxSpeed",ManejadorForms)->GetEscritura()[i];

		p=new PuertoSerie (escrituraCOM,atol(escrituraVelocidad));
				
	
		if(p->Error())
		   {
			   string f=string(p->ErrorStr())+string("-")+string(escrituraCOM)+string("-")+string(escrituraVelocidad);
			   msg=new char[f.length()+1];
			   msg[f.length()]=0;
			   for(unsigned i=0;i<f.length();i++)
				   msg[i]=f[i]; 
			
			   messeng=new MeSSenger((char*)f.c_str(),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,5,1,0,0,2);
		   }
		else 
		   {
			  

			  // SalvMov->Clear(SalvMov);
			   msg="Conectado Correctamente...";
			   
		       //subs
			   ManejadorForms->Sub("textBoxCOM",ManejadorForms);
		       ManejadorForms->Sub("textBoxSpeed",ManejadorForms);
		       ManejadorForms->Sub("buttonInitCOM",ManejadorForms);
		       ManejadorForms->Sub("buttonCancelCOM",ManejadorForms);
			   //adds

			   ManejadorForms->Add(new Label("labelCOM",escrituraCOM,*(new CRD(87,-5,0)),0,0,1,0,wigth,height),ManejadorForms);
			   ManejadorForms->Add(new Label("labelSpeedCOM",escrituraVelocidad,*(new CRD(87,5,0)),0,0,1,0,wigth,height),ManejadorForms);
			   ManejadorForms->SetColor("labelESE_GRS",0,1,0,ManejadorForms);
			   ManejadorForms->Add(new Label("labelRecib","Esperando Reedireccionamiento...",*(new CRD((float)(wigth/2-139.5),(float)(height-40),0)),2,0.5,0.5,0.5,wigth,height),ManejadorForms); 
			   
		       ManejadorForms->Add(new RadioButtonGroup("radioButtonGroupProp",*new CRD(10,150,0),wigth,height),ManejadorForms);
      	          ManejadorForms->GetForm("radioButtonGroupProp",ManejadorForms)->AddRB("radioButton1","Puntos",true);
	              ManejadorForms->GetForm("radioButtonGroupProp",ManejadorForms)->AddRB("radioButton2","Lineas");
	              ManejadorForms->GetForm("radioButtonGroupProp",ManejadorForms)->AddRB("radioButton3","Circulo");
		          ManejadorForms->GetForm("radioButtonGroupProp",ManejadorForms)->SetNewProp((float)strlen("Circulo")*9);
	              ManejadorForms->GetForm("radioButtonGroupProp",ManejadorForms)->AddRB("radioButton4","Superficies");
	              ManejadorForms->GetForm("radioButtonGroupProp",ManejadorForms)->AddRB("radioButton5","Curva");
	          ManejadorForms->Add(new RadioButtonGroup("radioButtonGroupRestriccion",*new CRD(10,170+(18*5),0),wigth,height),ManejadorForms);
		          ManejadorForms->GetForm("radioButtonGroupRestriccion",ManejadorForms)->AddRB("radioButton6","Sin resctricciones",true);
	              ManejadorForms->GetForm("radioButtonGroupRestriccion",ManejadorForms)->AddRB("radioButton7","Plano XY");
		          ManejadorForms->GetForm("radioButtonGroupRestriccion",ManejadorForms)->AddRB("radioButton8","Plano XZ");
		          ManejadorForms->GetForm("radioButtonGroupRestriccion",ManejadorForms)->AddRB("radioButton9","Plano YZ");
		      RadioButtonEstilo=RadioButtonRestriccion=0;	 
			 // ManejadorForms->Add(new RadioButton("radioButtonSeguirMovim",*new CRD(10,170+(18*10),0),"Movent",wigth,height),ManejadorForms);
			   

		//
		       recibir_serie=true;
			   t1=new thread(ThreadCOM);
			   contMenuToDraw=-1;
			   messeng=new MeSSenger(msg,position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,0,1,0,2);
			   toSaveSpeed=atoi(escrituraVelocidad);
			   char*newc=new char[strlen(escrituraCOM)-3];
			   newc[strlen(escrituraCOM)-3]=0;
			   for(unsigned i=3,ii=0;i<strlen(escrituraCOM);i++,ii++)
				   newc[ii]=escrituraCOM[i];
			   toSaveCOM=atoi(newc);
			   ESE_GRS::InitMenu();
			  }
	break;


	case -2://detengo el COM
		ManejadorForms->Sub("radioButtonGroupProp",ManejadorForms);
		ManejadorForms->Sub("radioButtonGroupRestriccion",ManejadorForms);
		ManejadorForms->Sub("laberDetener",ManejadorForms);
		ManejadorForms->Sub("buttonInitDetener",ManejadorForms);
		ManejadorForms->Sub("buttonCancelDetener",ManejadorForms);
		//ManejadorForms->Sub("radioButtonSeguirMovim",ManejadorForms);
		//ManejadorForms->Sub("radioButtonGuardarArchivo",ManejadorForms);
		//ManejadorForms->Sub("buttonGurdarMovents",ManejadorForms);
	   // ManejadorForms->Sub("textBoxurdarMovent",ManejadorForms);
		
		recibir_serie=false;
		t1->join();
		ManejadorForms->Sub("labelCOM",ManejadorForms);
		ManejadorForms->Sub("labelSpeedCOM",ManejadorForms);
		ManejadorForms->Sub("labelRecib",ManejadorForms);
		ManejadorForms->SetColor("labelESE_GRS",(GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7,ManejadorForms);
		delete p;
		EsperandoReedireccionar=true;
		ESE_GRS::InitMenu();
	break;
	}
	
	glutPostRedisplay();
}
void ESE_GRS::MenuVista(int opcion){
	switch(opcion){
	case -1://Panoramica
		movESE_GRSX=-45*velGiro;
		movESE_GRSY=-45*velGiro;
		movESE_GRSZ=0*velGiro;
		break;
	case 0://FRONTAl
		movESE_GRSX=-90*velGiro;
		movESE_GRSY=0;
		movESE_GRSZ=-90*velGiro;
		break;
	case 1://TRASERA
		movESE_GRSX=-90*velGiro;
		movESE_GRSY=0;
		movESE_GRSZ=90*velGiro;
		break;
	case 2://Derecha
		movESE_GRSX=-90*velGiro;
		movESE_GRSY=0;
		movESE_GRSZ=180*velGiro;
		break;
	case 3://Izquierda
		movESE_GRSX=-90*velGiro;
		movESE_GRSY=0;
		movESE_GRSZ=0;
		break;
	case 4://Superior
		movESE_GRSX=0;
		movESE_GRSY=0;
		movESE_GRSZ=0;
		break;
	case 5://inferior
		movESE_GRSX=180*velGiro;
		movESE_GRSY=0;
		movESE_GRSZ=0;
		break;
	
	
	
	}	
	glutPostRedisplay();
}
void ESE_GRS::MenuToDraw(int caso){
  if(!recibir_serie)
    {
		if(caso!=-1)
		{
			trasladarY=trasladarX=trasladarZ=0;
		}
     contMenuToDraw=caso;
     }
  else
  {
	  messeng=new MeSSenger("Accion no valida ;Conexion por puerto serie ya iniciada",position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,0,0,2);
  }
glutPostRedisplay();//refresco y ejecuto el displayFunc()
}
void ESE_GRS::MenuPuertoSeie(int opcion){
	
		
}
///////////////////////// DATOS//////////////////////////////////////////////////
void ESE_GRS::recivirDatosCOM(){
	if(recibir_serie)
	   {
		   
		   if(tCOM.InitCiclo(&tCOM)>=0.200)//si ha esperado mas de 0.200 segundos
		   {
		   char*c=p->Recibir();
		   tCOM.ResetT(&tCOM);//reinicio el tiempo del conteo del tiempo de lectura 
		   if(c!=NULL)//si no esta vacio 
		     { 
				 
			  //glutPostRedisplay();
			  unsigned strleN=strlen(c);
		      if(strleN==0)
			     strleN=1;

			  if(boolNeXt)
			     {
			      char*newC=new char[strleN+2];
			      newC[strleN+1]=0;
			      for(unsigned i=0;i<strleN;i++)
				      newC[i+1]=c[i];
			      newC[0]=neXt;
			      c=newC;
			      strleN=strlen(c);
			      boolNeXt=false;
		         }

			   if(strleN%2!=0)
			     {
				  neXt=c[strleN-1];
				  boolNeXt=true;
			     }

			  unsigned strlenFor=strleN%2==0?strleN:strleN-1;

			  for(unsigned i=0;i<strlenFor;i+=2)
			     {
					/* if(!EsperandoReedireccionar&&SalvMov->Enable)
				    {
		
						SalvMov->Add(c[i],SalvMov);
				        SalvMov->Add(c[i+1],SalvMov);
				 
				    }*/
					 //si bit 1  es 1 EJECUTO un codigo y no hago el proceso completo
			        if(DataProcessor::BitData(c[i],1)==1)
					   {
					    //REDIRECCIONAR
					    if(DataProcessor::BitData(c[i],2)==1)
					       {
							SpecialKeys(-1,0,0);
							//ANGULES REDIRECCIOADOS
							messeng=new MeSSenger("REDIRECCIONADO",position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,2,0,1,0,2);
						    EsperandoReedireccionar=false;
							//ManejadorForms->AddNewText("labelRecib","Procesando Datos...",ManejadorForms); 
							ManejadorForms->DesactivateForm("labelRecib",ManejadorForms);
							//ManejadorForms->AddNewCRD("labelRecib",new CRD((float)(wigth/2-strlen("Procesando Datos...")*4.5),(float)(height-40),0),ManejadorForms);
							std::cout<<DataProcessor::printfBits(c[i+1])<<"-"<<DataProcessor::printfBits(c[i])<<"->Redireccionamiento"<<endl;
					       }
			           }
				   else if(EsperandoReedireccionar)
				       {
				       //PARA Q NO SE EJECUTE NADA HASTA Q NO SE REDIRECCIONE
				       }
			        else
			           {
					     
					   std::cout<<DataProcessor::printfBits(c[i+1])<<"-"<<DataProcessor::printfBits(c[i])<<endl;
			            if(DataProcessor::PorcesarDatos(c[i],c[i+1],angules))//ejecuto la lectura de los bits y muevo los angulos
			              {
							corrdCambi=true;
							if(MostrarAngules)
						      {
							 /* clock_t te=clock();
							  ManejadorForms->AddNewText("labelAngule0",(char*)to_string(angules[0]).c_str(),ManejadorForms);
							  ManejadorForms->AddNewText("labelAngule1",(char*)to_string(angules[1]).c_str(),ManejadorForms);
							  ManejadorForms->AddNewText("labelAngule2",(char*)to_string(angules[2]).c_str(),ManejadorForms);
							  ManejadorForms->AddNewText("labelAngule3",(char*)to_string(angules[3]).c_str(),ManejadorForms);
							  ManejadorForms->AddNewText("labelAngule4",(char*)to_string(angules[4]).c_str(),ManejadorForms);
							  ManejadorForms->AddNewText("labelAngule5",(char*)to_string(angules[5]).c_str(),ManejadorForms);
							  cout<<"AddNewText:"<<double(te-clock());
							  te=clock();
							  ManejadorForms->GetForm("labelAngule0",ManejadorForms)->CambiarEscritura((char*)to_string(angules[0]).c_str());
						      ManejadorForms->GetForm("labelAngule1",ManejadorForms)->CambiarEscritura((char*)to_string(angules[1]).c_str());
						      ManejadorForms->GetForm("labelAngule2",ManejadorForms)->CambiarEscritura((char*)to_string(angules[2]).c_str());
						      ManejadorForms->GetForm("labelAngule3",ManejadorForms)->CambiarEscritura((char*)to_string(angules[3]).c_str());
						      ManejadorForms->GetForm("labelAngule4",ManejadorForms)->CambiarEscritura((char*)to_string(angules[4]).c_str());
						      ManejadorForms->GetForm("labelAngule5",ManejadorForms)->CambiarEscritura((char*)to_string(angules[5]).c_str());
						      cout<<"GetForm->CambiarEscritura:"<<double(te-clock());  
							*/}
						  /* //si procesar datos devuelve true es q tengo q pintar
					       if(!NewObjbool)
				              {
					           NewObj=new LoaderObject();
					           NewObjbool=true;
				              }  
				           // NewObj->Add("Vertices segun angulos",NewObj);
                  
					       //Ejemplo
					      /*
					   GLfloat*f=new GLfloat[3];
					   switch (contyy)
					   {
                        case 0:
					   f[0]=100;
					   f[1]=120;
					   f[2]=130;
					   contyy++;
					   NewObj->Add(f,NewObj);
						   break;
						   case 1:
					   f[0]=250;
					   f[1]=260;
					   f[2]=270;
					   contyy++;
					   NewObj->Add(f,NewObj);
						   break;
						   case 2:
					   f[0]=390;
					   f[1]=380;
					   f[2]=300;
					   contyy++;
					   NewObj->Add(f,NewObj);
						   break;
					   default:
						   break;
					   }
					   */
							  CRD*newCorrd=new CRD(cooRd);
							  switch (RadioButtonEstilo)
							  {
							  case 0://PUNTOS



								  break;
							  default:
								  break;
							  }
							 /* if(RadioButtonRestriccion!=LastRBRestriccion)
							     {
								 RadioButtonRestriccion=LastRBRestriccion;
								 igs->SetRestriccion(newCoord,igs);
								 }
							 else
								 {
							     switch (RadioButtonRestriccion)
							       {
							       case 0:

	     						   break;
							       case 1:
								     newCoord->set(newCoord->x,newCoord->y,igs->getCoordRestricion(2,igs))
								  break;
								  case 2:
								     newCoord->set(newCoord->x,newCoord->y,igs->getCoordRestricion(1,igs))
								  break;
								  case 1:
								     newCoord->set(newCoord->x,newCoord->y,igs->getCoordRestricion(0,igs))
								  break;
							      }
							    }
							  */
							  //igs->add(newCoord,igs);

					      ///////
			              }//end if TRUE de ProcesarDatos
					   else
					   {
						//corrdCambi=true;
					   }
			          }//end else
			  }//end for
			 
		   }//end if(!NULL)

		 }//end time>0.200

	  }//end recivir serie
		
}
void ESE_GRS::slavarInitDatos(){
	if(threaDCOM)
	   {
	   recibir_serie=false;
	   t1->join();
	   }
	if(!CargObjct)
	   {
	   ManejadorObject->Salir=true;
	   t1->join();
	   }
	ofstream f;
	f.open("My_Proyecto.onrn",ios::out|ios::binary);
	f.write((char*)&movRatXinit,sizeof(int));
	f.write((char*)&movRatYinit,sizeof(int));
	f.write((char*)&movRatX,sizeof(int));
	f.write((char*)&movRatY,sizeof(int));
	f.write((char*)&movESE_GRSZ,sizeof(int));
	f.write((char*)&angules[0],sizeof(GLfloat));
	f.write((char*)&angules[1],sizeof(GLfloat));
	f.write((char*)&angules[2],sizeof(GLfloat));
	f.write((char*)&angules[3],sizeof(GLfloat));
	f.write((char*)&angules[4],sizeof(GLfloat));
	f.write((char*)&angules[5],sizeof(GLfloat));
	f.write((char*)&movWheel,sizeof(GLdouble));
	f.write((char*)&toSaveCOM,sizeof(unsigned));
	f.write((char*)&toSaveSpeed,sizeof(unsigned));
	f.write((char*)&trasladarX,sizeof(double));
	f.write((char*)&trasladarY,sizeof(double));
	f.write((char*)&trasladarZ,sizeof(double));
	f.close();
}
void ESE_GRS::cargarInitDatos(){
		ifstream f;
	f.open("My_Proyecto.onrn",ios::in|ios::binary);
	if(f.is_open()){
	f.read((char*)&movRatXinit,sizeof(int));
	f.read((char*)&movRatYinit,sizeof(int));
	f.read((char*)&movRatX,sizeof(int));
	f.read((char*)&movRatY,sizeof(int));
	f.read((char*)&movESE_GRSZ,sizeof(int));
	f.read((char*)&angules[0],sizeof(GLfloat));
	f.read((char*)&angules[1],sizeof(GLfloat));
	f.read((char*)&angules[2],sizeof(GLfloat));
	f.read((char*)&angules[3],sizeof(GLfloat));
	f.read((char*)&angules[4],sizeof(GLfloat));
	f.read((char*)&angules[5],sizeof(GLfloat));
	f.read((char*)&movWheel,sizeof(GLdouble));
	f.read((char*)&toSaveCOM,sizeof(unsigned));
	f.read((char*)&toSaveSpeed,sizeof(unsigned));
	f.read((char*)&trasladarX,sizeof(double));
	f.read((char*)&trasladarY,sizeof(double));
	f.read((char*)&trasladarZ,sizeof(double));

	string*c=new string("COM"+to_string(toSaveCOM));
	escrituraCOM=new char(c->length());
	for(unsigned i=0;i<c->length();i++)
		escrituraCOM[i]=c->c_str()[i];
	escrituraCOM[c->length()]=0;

	c=new string(to_string(toSaveSpeed));
	escrituraVelocidad=new char(c->length());
	for(unsigned i=0;i<c->length();i++)
		escrituraVelocidad[i]=c->c_str()[i];
	escrituraVelocidad[c->length()]=0;
	cooRd=ESE_GRS::coordenadas();
	}
	f.close();
	}
void ESE_GRS::SaveObj(char*address,LoaderObject*l){
	fstream f;
	string*c=new string(address);

	f.open(c->c_str(),ios::in);
	
	while(f.is_open())
	{
		static unsigned cont=0;
		c=new string(address);
		string cc;
		cc=c->substr(0,c->find_first_of("."));
		cc+=to_string(cont++)+".obj";
		c=new string(cc);
		f.close();
		f.open(c->c_str(),ios::in);
	}
	
	
		f.close();
		f.open(c->c_str(),ios::out);
		f<<"# gcnew obj file (generated by ESE_GRS)\n";
		for(int i=0;i<l->contv;i++)
			f<<"v "<<l->vertvCargX[i]<<" "<<l->vertvCargY[i]<<" "<<l->vertvCargZ[i]<<"\n";

		for(int i=0;i<l->contf;i++)
			f<<"f "<<l->veRts[0].v[i]<<"/0/0 "<<l->veRts[1].v[i]<<"/0/0 "<<l->veRts[2].v[i]<<"/0/0"<<"\n";
		f<<"# "<<l->contv*3<<" vertices"<<flush;
		f.close();
		cout<<"Guardado Correctamente:"<<c->c_str()<<endl;
	
	
}
/////////////////////////THREADS//////////////////////////////////////////////////
void ESE_GRS::ThreadCOM()
{
	m.lock();
	threaDCOM=true;	
	while(recibir_serie)
	{
	recivirDatosCOM();
	}
	threaDCOM=false;
	m.unlock();

}
void ESE_GRS::ThreadCargObject()
{
	m.lock();
	ManejadorObject->pushByTxt("Entrada_de_Modelos.txt",ManejadorObject);//cargo el txt con las direcciones de los .obj
	CargObjct=true;
	m.unlock();
}
void ESE_GRS::ThreadCargMovent(){
	/*
	m1.lock();
	 SalvMov->Cargar(ManejadorForms->GetForm("textBoxsCargarMovents",ManejadorForms)->GetEscritura(),SalvMov);
	 if(SalvMov->errorCarga)
			   messeng=new MeSSenger("Error direccion o formato no valido",position::CENTER_TOP,wigth,height,3,1,0,0,2);
	  else
		   {
			   string s(ManejadorForms->GetForm("textBoxsCargarMovents",ManejadorForms)->GetEscritura());
			   s+=" Cargado";
			   ManejadorForms->Add(new Label("labelcargadoMovents",(char*)s.c_str(),*new CRD(0,12,0),0,0,1,0,wigth,height),ManejadorForms);
               messeng=new MeSSenger("Cargado Correctamente",position::CENTER_TOP,wigth,height,3,0,1,0,2);
			   ManejadorForms->Sub("textBoxsCargarMovents",ManejadorForms);
		       ManejadorForms->Sub("buttonCancelCargaMovemts",ManejadorForms);
		       ManejadorForms->Sub("buttonInitCargaMovemts",ManejadorForms);
			   moventsCargado=true;
			   ManejadorForms->Add(new RadioButton("buttoninitStopsimulacion",*new CRD(10,120,0),"Iniciar Simulacion",wigth,height),ManejadorForms);
			   ManejadorForms->Add(new RadioButtonGroup("radioButtonGroupSpeed",*new CRD(10,260,0),wigth,height),ManejadorForms);
	           ManejadorForms->GetForm("radioButtonGroupSpeed",ManejadorForms)->AddRB("radioButtonSpeed0.5","0.1s",true);
			   ManejadorForms->GetForm("radioButtonGroupSpeed",ManejadorForms)->AddRB("radioButtonSpeed1","0.5s");
			   ManejadorForms->GetForm("radioButtonGroupSpeed",ManejadorForms)->AddRB("radioButtonSpeed1","1.0s");
			   ManejadorForms->GetForm("radioButtonGroupSpeed",ManejadorForms)->AddRB("radioButtonSpeed2","2.0s");
		       InitStopSimul=false;
			   s=(DataProcessor::printfBits(SalvMov->GETMovimientos(SalvMov)[1]));
		       s+=string(DataProcessor::printfBits(SalvMov->GETMovimientos(SalvMov)[0]));
			   ManejadorForms->Add(new Label("labelMovements1","Redireccionar",*new CRD(10,140,0),1,(GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7,wigth,height),ManejadorForms);
		       ManejadorForms->Add(new Label("labelMovements2",(char*)s.c_str(),*new CRD(10,165,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
		
		   }
	 m1.unlock();
	 */
};
void ESE_GRS::ThreadGuardarMovent()
{
	/*
	m1.lock();
	SalvMov->Guardar(ManejadorForms->GetForm("textBoxurdarMovent",ManejadorForms)->GetEscritura(),SalvMov);
    SalvMov->Enable=false;
	messeng=new MeSSenger("Guardado Corectamente",position::CENTER_TOP,wigth,height,3,0,1,0,2); 
    ManejadorForms->GetForm("radioButtonSeguirMovim",ManejadorForms)->CambiarEscritura("Guardar Movent");
    ManejadorForms->GetForm("radioButtonSeguirMovim",ManejadorForms)->CambiarChecket();
	ManejadorForms->Sub("radioButtonGuardarArchivo",ManejadorForms);
	ManejadorForms->Sub("textBoxurdarMovent",ManejadorForms);
	ManejadorForms->Sub("buttonGurdarMovents",ManejadorForms);
	m1.unlock();
	*/

};
void ESE_GRS::ThreadSimular(){
	   /* m1.lock();
		string s="Redireccionar";
		string s1;
		s1=(DataProcessor::printfBits(SalvMov->GETMovimientos(SalvMov)[1]));
		s1+=string(DataProcessor::printfBits(SalvMov->GETMovimientos(SalvMov)[0]));
		
		ManejadorForms->GetForm("labelMovements1",ManejadorForms)->CambiarEscritura((char*)s.c_str());
		ManejadorForms->GetForm("labelMovements2",ManejadorForms)->CambiarEscritura((char*)s1.c_str());
				  
		
		//REEEDIRECCIONAR
		for(unsigned i=0;i<SalvMov->GETCont(SalvMov);i+=2)
		{
			bool conTinue=false;
			while (!conTinue)
			{
				if(salirSimulacion)
					break;
				if(TSimular.InitCiclo(&TSimular)>=(RadioButtonSpeed==0?0.1:RadioButtonSpeed==1?0.5:RadioButtonSpeed==2?1.0:2.0))
	           {
				   cooRd=coordenadas();
				   if(!corrdCambi)
							corrdCambi=true;
				   s=(DataProcessor::printfBits(SalvMov->GETMovimientos(SalvMov)[i+1]));
				   s+=string(DataProcessor::printfBits(SalvMov->GETMovimientos(SalvMov)[i]));
				   if(i!=SalvMov->GETCont(SalvMov)-2)
				   {
				    s1= (DataProcessor::printfBits(SalvMov->GETMovimientos(SalvMov)[i+3]));
					s1+=string(DataProcessor::printfBits(SalvMov->GETMovimientos(SalvMov)[i+2]));
				   }
				   else
					   s1="............End............";
				   ManejadorForms->GetForm("labelMovements1",ManejadorForms)->CambiarEscritura((char*)s.c_str());
				   ManejadorForms->GetForm("labelMovements2",ManejadorForms)->CambiarEscritura((char*)s1.c_str());
				   TSimular.ResetT(&TSimular);
				   char*c=new char[3];
				   c[2]=0;
				   c[0]=SalvMov->GETMovimientos(SalvMov)[i];
				   c[1]=SalvMov->GETMovimientos(SalvMov)[i+1];
				   conTinue=true;
				   if(DataProcessor::PorcesarDatos(c[i],c[i+1],angules))
				   {
				   
				   }
				  
				   
			   }
			
			}
			if(salirSimulacion)
					break;
		}
		salirSimulacion=false;
		messeng=new MeSSenger("Simulacion Finalizada",position::CENTER_TOP,wigth,height,3,0,1,0,3);
		ManejadorForms->GetForm("buttoninitStopsimulacion",ManejadorForms)->CambiarEscritura("Iniciar Simulacion");
		ManejadorForms->GetForm("buttoninitStopsimulacion",ManejadorForms)->CambiarChecket();
		InitStopSimul=false;
		
		m1.unlock();
		*/
}
////////////////////////////SIN USO/////////////////////////////////////
void ESE_GRS::cargarDatosFromTXT(){
	//cargo los datos de los angArtic's del txt
	fstream f;
	f.open("Entrada_de_angArtic.txt",ios::in);
	if(f.is_open())
	{
	char*line=new char[15];
    bool letra=false;
	bool negativo=false;
	for(int y=0;y<4;y++)
	  {
	  f>>line;
	  for(unsigned int i=0;i<strlen(line);i++)
		   {
			if(i==0 && line[0]=='-')
			   {
			   char*newdata=new char[strlen(line)-1];
			   for(unsigned int ii=0;ii<strlen(newdata);ii++)
			   newdata[ii]=line[ii+1];
			   line=newdata;
			   negativo=true;
			   }
			if(!isdigit(line[i])) 
			   {
				letra=true;
			    break;
		       } 
		   }
		    if(letra==false)
	    	   {
				   switch (y)
				   {
					    case 0:
						   negativo==false?angules[0]=(GLfloat)atof(line):angules[0]=-(GLfloat)atof(line);
					   break;
				   case 1:
					   negativo==false?angules[1]=(GLfloat)atof(line):angules[1]=-(GLfloat)atof(line);
					   break;
					   case 2:
						   negativo==false?angules[2]=(GLfloat)atof(line):angules[2]=-(GLfloat)atof(line);
					   break;
					   case 3:
						   negativo==false?angules[3]=(GLfloat)atof(line):angules[3]=-(GLfloat)atof(line);
					   break;
					  

				   }
			    
          	   }

			negativo=false;
			letra=false;
	 }             
	}
	else
	   {
		f.open("Entrada_de_angArtic.txt",ios::out);
	    f<<"0"<<endl<<"150"<<endl<<"-130"<<endl<<-45;
	   }
	            
	      	f.close();
}
double* ESE_GRS:: coordenadas()
  {
	  //L1- 43.95;L5-51.65;D5-11.2;
	  double cosFi1,senFi1,cosFi2,senFi2,cosFi3,senFi3,cosFi4,senFi4,cosFi5,senFi5,cosFi6,senFi6;

cosFi1=cos((angules[0]+180)*PI/180);
senFi1=sin((angules[0]+180)*PI/180);
cosFi2=cos(angules[1]*PI/180);
senFi2=sin(angules[1]*PI/180);
cosFi3=cos((angules[2]-90)*PI/180);
senFi3=sin((angules[2]-90)*PI/180);
cosFi4=cos(angules[3]*PI/180);
senFi4=sin(angules[3]*PI/180);
cosFi5=cos((angules[4]+90)*PI/180);
senFi5=sin((angules[4]+90)*PI/180);
cosFi6=cos(angules[5]*PI/180);
senFi6=sin(angules[5]*PI/180);
	  double*coord=new double[3];
	 /* coord[0]=(463*sin((Z0+180)*PI/180))/200 + 150*cos((Z0+180)*PI/180)*cos(Z1*PI/180) - (1783*cos(Z3*PI/180)*sin((Z0+180)*PI/180))/200 + 177*cos(Z5*PI/180)*(sin((Z4+90)*PI/180)*(cos((Z0+180)*PI/180)*cos(Z1*PI/180)*sin((Z2-90)*PI/180) + cos((Z0+180)*PI/180)*cos((Z2-90)*PI/180)*sin(Z1*PI/180)) - cos((Z4+90)*PI/180)*(sin((Z0+180)*PI/180)*sin(Z3*PI/180) - cos(Z3*PI/180)*(cos((Z0+180)*PI/180)*cos(Z1*PI/180)*cos((Z2-90)*PI/180) - cos((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180)))) - 53*sin((Z0+180)*PI/180)*sin(Z3*PI/180) + 53*cos(Z3*PI/180)*(cos((Z0+180)*PI/180)*cos(Z1*PI/180)*cos((Z2-90)*PI/180) - cos((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180)) - (10329*cos((Z4+90)*PI/180)*(cos((Z0+180)*PI/180)*cos(Z1*PI/180)*sin((Z2-90)*PI/180) + cos((Z0+180)*PI/180)*cos((Z2-90)*PI/180)*sin(Z1*PI/180)))/200 - (1783*sin(Z3*PI/180)*(cos((Z0+180)*PI/180)*cos(Z1*PI/180)*cos((Z2-90)*PI/180) - cos((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180)))/200 + (sin((Z4+90)*PI/180)*(cos((Z0+180)*PI/180)*cos(Z1*PI/180)*sin((Z2-90)*PI/180) + cos((Z0+180)*PI/180)*cos((Z2-90)*PI/180)*sin(Z1*PI/180)))/500 - (cos((Z4+90)*PI/180)*(sin((Z0+180)*PI/180)*sin(Z3*PI/180) - cos(Z3*PI/180)*(cos((Z0+180)*PI/180)*cos(Z1*PI/180)*cos((Z2-90)*PI/180) - cos((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180))))/500 - (10329*sin((Z4+90)*PI/180)*(sin((Z0+180)*PI/180)*sin(Z3*PI/180) - cos(Z3*PI/180)*(cos((Z0+180)*PI/180)*cos(Z1*PI/180)*cos((Z2-90)*PI/180) - cos((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180))))/200 + 177*sin(Z5*PI/180)*(cos(Z3*PI/180)*sin((Z0+180)*PI/180) + sin(Z3*PI/180)*(cos((Z0+180)*PI/180)*cos(Z1*PI/180)*cos((Z2-90)*PI/180) - cos((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180))) + (451*cos((Z0+180)*PI/180)*cos(Z1*PI/180)*cos((Z2-90)*PI/180))/2 - (151*cos((Z0+180)*PI/180)*cos(Z1*PI/180)*sin((Z2-90)*PI/180))/500 - (151*cos((Z0+180)*PI/180)*cos((Z2-90)*PI/180)*sin(Z1*PI/180))/500 - (451*cos((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180))/2;
      coord[1]=(1783*cos((Z0+180)*PI/180)*cos(Z3*PI/180))/200 - (463*cos((Z0+180)*PI/180))/200 + 150*cos(Z1*PI/180)*sin((Z0+180)*PI/180) + 53*cos((Z0+180)*PI/180)*sin(Z3*PI/180) + 53*cos(Z3*PI/180)*(cos(Z1*PI/180)*cos((Z2-90)*PI/180)*sin((Z0+180)*PI/180) - sin((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180)) - (10329*cos((Z4+90)*PI/180)*(cos(Z1*PI/180)*sin((Z0+180)*PI/180)*sin((Z2-90)*PI/180) + cos((Z2-90)*PI/180)*sin((Z0+180)*PI/180)*sin(Z1*PI/180)))/200 + 177*cos(Z5*PI/180)*(sin((Z4+90)*PI/180)*(cos(Z1*PI/180)*sin((Z0+180)*PI/180)*sin((Z2-90)*PI/180) + cos((Z2-90)*PI/180)*sin((Z0+180)*PI/180)*sin(Z1*PI/180)) + cos((Z4+90)*PI/180)*(cos((Z0+180)*PI/180)*sin(Z3*PI/180) + cos(Z3*PI/180)*(cos(Z1*PI/180)*cos((Z2-90)*PI/180)*sin((Z0+180)*PI/180) - sin((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180)))) - (1783*sin(Z3*PI/180)*(cos(Z1*PI/180)*cos((Z2-90)*PI/180)*sin((Z0+180)*PI/180) - sin((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180)))/200 + (sin((Z4+90)*PI/180)*(cos(Z1*PI/180)*sin((Z0+180)*PI/180)*sin((Z2-90)*PI/180) + cos((Z2-90)*PI/180)*sin((Z0+180)*PI/180)*sin(Z1*PI/180)))/500 + (cos((Z4+90)*PI/180)*(cos((Z0+180)*PI/180)*sin(Z3*PI/180) + cos(Z3*PI/180)*(cos(Z1*PI/180)*cos((Z2-90)*PI/180)*sin((Z0+180)*PI/180) - sin((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180))))/500 + (10329*sin((Z4+90)*PI/180)*(cos((Z0+180)*PI/180)*sin(Z3*PI/180) + cos(Z3*PI/180)*(cos(Z1*PI/180)*cos((Z2-90)*PI/180)*sin((Z0+180)*PI/180) - sin((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180))))/200 - 177*sin(Z5*PI/180)*(cos((Z0+180)*PI/180)*cos(Z3*PI/180) - sin(Z3*PI/180)*(cos(Z1*PI/180)*cos((Z2-90)*PI/180)*sin((Z0+180)*PI/180) - sin((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180))) + (451*cos(Z1*PI/180)*cos((Z2-90)*PI/180)*sin((Z0+180)*PI/180))/2 - (151*cos(Z1*PI/180)*sin((Z0+180)*PI/180)*sin((Z2-90)*PI/180))/500 - (151*cos((Z2-90)*PI/180)*sin((Z0+180)*PI/180)*sin(Z1*PI/180))/500 - (451*sin((Z0+180)*PI/180)*sin(Z1*PI/180)*sin((Z2-90)*PI/180))/2;
	  coord[2]= (151*sin((Z1)*(PI/180))*sin((Z2-90)*(PI/180)))/500 - (151*cos((Z1)*(PI/180))*cos((Z2-90)*(PI/180)))/500 - (451*cos((Z1)*(PI/180))*sin((Z2-90)*(PI/180)))/2 - (451*cos((Z2-90)*(PI/180))*sin((Z1)*(PI/180)))/2 - 150*sin((Z1)*(PI/180)) - 53*cos((Z3)*(PI/180))*(cos((Z1)*(PI/180))*sin((Z2-90)*(PI/180)) + cos((Z2-90)*(PI/180))*sin((Z1)*(PI/180))) - (10329*cos((Z4+90)*(PI/180))*(cos((Z1)*(PI/180))*cos((Z2-90)*(PI/180)) - sin((Z1)*(PI/180))*sin((Z2-90)*(PI/180))))/200 + (1783*sin((Z3)*(PI/180))*(cos((Z1)*(PI/180))*sin((Z2-90)*(PI/180)) + cos((Z2-90)*(PI/180))*sin((Z1)*(PI/180))))/200 + (sin((Z4+90)*(PI/180))*(cos((Z1)*(PI/180))*cos((Z2-90)*(PI/180)) - sin((Z1)*(PI/180))*sin((Z2-90)*(PI/180))))/500 + 177*cos((Z5)*(PI/180))*(sin((Z4+90)*(PI/180))*(cos((Z1)*(PI/180))*cos((Z2-90)*(PI/180)) - sin((Z1)*(PI/180))*sin((Z2-90)*(PI/180))) - cos((Z3)*(PI/180))*cos((Z4+90)*(PI/180))*(cos((Z1)*(PI/180))*sin((Z2-90)*(PI/180)) + cos((Z2-90)*(PI/180))*sin((Z1)*(PI/180)))) - (10329*cos((Z3)*(PI/180))*sin((Z4+90)*(PI/180))*(cos((Z1)*(PI/180))*sin((Z2-90)*(PI/180)) + cos((Z2-90)*(PI/180))*sin((Z1)*(PI/180))))/200 - 177*sin((Z3)*(PI/180))*sin((Z5)*(PI/180))*(cos((Z1)*(PI/180))*sin((Z2-90)*(PI/180)) + cos((Z2-90)*(PI/180))*sin((Z1)*(PI/180))) - (cos((Z3)*(PI/180))*cos((Z4+90)*(PI/180))*(cos((Z1)*(PI/180))*sin((Z2-90)*(PI/180)) + cos((Z2-90)*(PI/180))*sin((Z1)*(PI/180))))/500 + 437/10;
	  */
	  coord[0]=(463*senFi1)/200 + 150*cosFi1*cosFi2 - (1783*cosFi4*senFi1)/200 + 177*cosFi6*(senFi5*(cosFi1*cosFi2*senFi3 + cosFi1*cosFi3*senFi2) - cosFi5*(senFi1*senFi4 - cosFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3))) - 53*senFi1*senFi4 + 53*cosFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3) - (10329*cosFi5*(cosFi1*cosFi2*senFi3 + cosFi1*cosFi3*senFi2))/200 - (1783*senFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3))/200 + (senFi5*(cosFi1*cosFi2*senFi3 + cosFi1*cosFi3*senFi2))/500 - (cosFi5*(senFi1*senFi4 - cosFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3)))/500 - (10329*senFi5*(senFi1*senFi4 - cosFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3)))/200 + 177*senFi6*(cosFi4*senFi1 + senFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3)) + (451*cosFi1*cosFi2*cosFi3)/2 - (151*cosFi1*cosFi2*senFi3)/500 - (151*cosFi1*cosFi3*senFi2)/500 - (451*cosFi1*senFi2*senFi3)/2;
	  coord[1]=(1783*cosFi1*cosFi4)/200 - (463*cosFi1)/200 + 150*cosFi2*senFi1 + 53*cosFi1*senFi4 + 53*cosFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3) - (10329*cosFi5*(cosFi2*senFi1*senFi3 + cosFi3*senFi1*senFi2))/200 + 177*cosFi6*(senFi5*(cosFi2*senFi1*senFi3 + cosFi3*senFi1*senFi2) + cosFi5*(cosFi1*senFi4 + cosFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3))) - (1783*senFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3))/200 + (senFi5*(cosFi2*senFi1*senFi3 + cosFi3*senFi1*senFi2))/500 + (cosFi5*(cosFi1*senFi4 + cosFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3)))/500 + (10329*senFi5*(cosFi1*senFi4 + cosFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3)))/200 - 177*senFi6*(cosFi1*cosFi4 - senFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3)) + (451*cosFi2*cosFi3*senFi1)/2 - (151*cosFi2*senFi1*senFi3)/500 - (151*cosFi3*senFi1*senFi2)/500 - (451*senFi1*senFi2*senFi3)/2;
	  coord[2]=(151*senFi2*senFi3)/500 - (151*cosFi2*cosFi3)/500 - (451*cosFi2*senFi3)/2 - (451*cosFi3*senFi2)/2 - 150*senFi2 - 53*cosFi4*(cosFi2*senFi3 + cosFi3*senFi2) - (10329*cosFi5*(cosFi2*cosFi3 - senFi2*senFi3))/200 + (1783*senFi4*(cosFi2*senFi3 + cosFi3*senFi2))/200 + (senFi5*(cosFi2*cosFi3 - senFi2*senFi3))/500 + 177*cosFi6*(senFi5*(cosFi2*cosFi3 - senFi2*senFi3) - cosFi4*cosFi5*(cosFi2*senFi3 + cosFi3*senFi2)) - (10329*cosFi4*senFi5*(cosFi2*senFi3 + cosFi3*senFi2))/200 - 177*senFi4*senFi6*(cosFi2*senFi3 + cosFi3*senFi2) - (cosFi4*cosFi5*(cosFi2*senFi3 + cosFi3*senFi2))/500 + 437/10;
	  coord[2]+=0.7;
	  return coord; 
  }


