#include "ESE_GRS.h"
///////////////////////////////////////////////////////////VARIABLES GLOBALES////////////////////////////////////////////////////
bool recibir_serie=false;
bool CargObjct=false,cargMenu=false;
bool EsperandoReedireccionar=true;
bool threaDCOM=false,MostrarAngules=false,SeguirPuntoFinal=false;
bool SetAngules=false;
bool Pint=false;
bool RotarAlPlanoContrar=false;
bool errInitMenubool=false;
bool boolMenuToDraw=false;
bool cursor=false;
bool deFult=true;
bool ModoLogger=false;
bool Boxf1=false;
char byt;bool bytBool=false;
char*toSaveCOM="COM2",*toSaveIp="127.0.0.1";
unsigned toSaveSpeed=9600,toSavePort=55555;
unsigned STRLEN,BoxInterfazPricipal=0,RadioButtonRestriccion=0;
unsigned bocetoARemover=0,RadioButtomPintar=0,PlanoChecket=0,bocetoACrear=0,BoxInterfaz0=0;
int interfaz=0;
int contMenuToDraw=-1;
int contt=0;
int Window=0;
int Initheight,Initwigth;
float movRatXinit=25,movRatYinit=0,movRatX=10,movRatY=0;
float velGiro=3;
float &movESE_GRSX=movRatX,&movESE_GRSY=movRatY,movESE_GRSZ=25;
float height,wigth;
double trasladarX=0,trasladarY=0,trasladarZ=0;
GLfloat angules[6]={0,0,55,0,0,0};
GLfloat heightOrtho,wigthOrtho;
GLdouble movWheel=1;
Language idioma=ENGLISH;
///////////////////OBJECTS//////////////////////////////////////
CRD*cooRd=new CRD(0,0,0);
StackLoaderObject*ManejadorObject=new StackLoaderObject();
Connection*p=new PuertoSerie();
TimeDuration tCOM(true);
StackBoceto*Proyect1=new StackBoceto();
thread*t1=new thread();
mutex m;
MeSSenger*messeng=new MeSSenger;
StackForms*ManejadorForms=new StackForms();
///////////////////////////////////////////////////////////METODOS//////////////////////////////////////////////////////////////

///////////////////DESTRUCTOR GLOBAL/////////////////////////////////////////////////
char*Frases(unsigned frase)
{
	switch (idioma)
	{
	case ENGLISH:
			switch (frase)
			{
			   case 0:
				return "Edit Sketchs";
				break;
		       case 1:
				return "Save Sketchs";
				break;
			   case 2:
				return "Sketchs:" ;
				break;
			   case 3:
				return "Total View" ;
				break;
				case 4:
				return "Add" ;
				break;
				case 5:
				return "Sub" ;
				break;
				case 6:
				return "English" ;
				break;
				case 7:
				return "Points" ;
				break;
				case 8:
				return "Lines" ;
				break;
				case 9:
				return "StripLine" ;
				break;
				case 10:
				return "Splines" ;
				break;
				case 11:
				return "Cancel" ;
				break;
				case 12:
				return "Show" ;
				break;
				case 13:
				return "To Create: " ;
				break;
				case 14:
				return "New Plane" ;
				break;
				case 15:
				return "Free Plane" ;
				break;
				case 16:
				return "Plane XY" ;
				break;
				case 17:
				return "Plane XZ" ;
				break;
				case 18:
				return "Plane YZ" ;
				break;
				case 19:
				return "Default" ;
				break;
				case 20:
				return "End Point" ;
				break;
				case 21:
				return "Sketch_" ;
				break;
				case 22:
				return "Fsketch_" ;
				break;
				case 23:
				return "Points:" ;
				break;
				case 24:
				return "To Remove:  " ;
				break;
				case 25:
				return "TCP_IP" ;
				break;
				case 26:
				return "Serial Port" ;
				break;
				case 27:
				return "Finish?" ;
				break;
				case 28:
				return "To Save:" ;
				break;
				case 29:
				return "All Sketchs" ;
				break;
				case 30:
				return "Panoramic" ;
				break;
				case 31:
				return "Frontal(XY)" ;
				break;
				case 32:
				return "Posterior(-XY)" ;
				break;
				case 33:
				return "Rigth(ZY)" ;
				break;
				case 34:
				return "Left(-ZY)" ;
				break;
				case 35:
				return "Top(X-Z)";
				break;
				case 36:
				return "Bottom (XZ)";
				break;
				case 37:
				return "Join Pieces";
				break;
				case 38:
				return "Star Connection";
				break;
				case 39:
				return "View";
				break;
				case 40:
				return "Model to Draw";
				break;
				case 41:
				return "Set Angules";
				break;
				case 42:
				return "Language";
				break;
				case 43:
				return "Stop Connection";
				break;
				case 44:
				return "Error, name in use";
				break;
				case 45:
				return "Finish Connection";  
				break;
				case 46:
				return "Saved at .../ESE_GRS-XLS/";
				break;
				case 47:
				return "Error trying to save files";
				break;
				case 48:
				return "Error ,wrong inmput";
				break;
				case 49:
				return "Has been loaded successfully";
				break;
				case 50:
				return "Error ;Connection already established";
				break;
				case 51:
				return "Correct Redirection";
				break;
				case 52:
				return "Details";
				break;
				case 53:
				return "->Check";
				break;
				case 54:
				return "->Error:Advance verification";
				break;
				case 55:
				return "->Error:Delayed verification";
				break;
				case 56:
				return "Code:";
				break;
				case 57:
				return "->Redirection";
				break;
				case 58:
				return "->Next Focus";
				break;
				case 59:
				return "->Focus Click";
				break;
				case 60:
				return "->Button Acept";
				case 61:
				return "->Button Cancel";
				break;
				case 62:
				return "Some language changes will not be applied until reboot"; 
				break;
				case 63:
				return ":Error;there is no functionality programmed for that input";
				break;
				case 64:
				return "!!!!!!!!!Waiting for Redirection!!!!!!!!!";
				break;
				case 65:
				return "Waiting for Redirection";
				break;
				case 66:
				return "Language changed to English";
				break;
				case 67:
				return "Spanish";
				break;
				case 68:
				return "Enable Mode Logger";
				break;
				case 69:
				return "Disable Mode Logger";
				break;
				case 70:
				return "BSpline";
				break;
				case 71:
				return "F1-Help";
				break;
				case 72:
				return "F2-Show / Hide Pices(.obj)";
				break;
				case 73:
				return "F3-Rotate to Plane (Only for drawing interface)";
				break;
				case 74:
				return "F4-Panoramic view with articulation angles at 0 (No connection established)";
				break;
				case 75:
				return "F5-Panoramic view with Redirection (No connection established)";
				break;
				case 76:
				return "F6-Go to the end point of the arm";
				break;
				case 77:
				return "F7-Follow to end point of arm";
				break;
				case 78:
				return "F8-Go to a 'Average' between all the points of a plane (Only for drawing interface)";
				break;
				case 79:
				return "Ends Connection";
				break;
				case 80:
				return "";
				break;
				case 81:
				return "";
				break;
				case 82:
				return "";
				break;
				case 83:
				return "";
				break;
				case 84:
				return "";
				break;
				case 85:
				return "";
				break;
				case 86:
				return "";
				break;
				case 87:
				return "";
				break;
				case 88:
				return "";
				break;
				case 89:
				return "";
				break;
				case 90:
				return "";
				break;


			default:
				return "Not Find";
				break;
			}
		break;
	case SPANISH:
			switch (frase)
			{
			   case 0:
				return "Editar Bocetos";
				break;
		       case 1:
				return "Salvar Bocetos";
				break;
			   case 2:
				return "Bocetos:" ;
				break;
			   case 3:
				return "Vista Total" ;
				break;
				case 4:
				return "Agregar" ;
				break;
				case 5:
				return "Quitar" ;
				break;
				case 6:
				return "English" ;
				break;
				case 7:
				return "Puntos" ;
				break;
				case 8:
				return "Lineas" ;
				break;
				case 9:
				return "StripLine" ;
				break;
				case 10:
				return "Splines" ;
				break;
				case 11:
				return "Cancelar" ;
				break;
				case 12:
				return "Mostrar" ;
				break;
				case 13:
				return "A Crear: " ;
				break;
				case 14:
				return "Plano Nuevo" ;
				break;
				case 15:
				return "Plano Libre" ;
				break;
				case 16:
				return "Plano XY" ;
				break;
				case 17:
				return "Plano XZ" ;
				break;
				case 18:
				return "Plano YZ" ;
				break;
				case 19:
				return "Por defecto" ;
				break;
				case 20:
				return "Punto Fianal" ;
				break;
				case 21:
				return "Boceto_" ;
				break;
				case 22:
				return "Fboceto_" ;
				break;
				case 23:
				return "Puntos:" ;
				break;
				case 24:
				return "A Remover:  " ;
				break;
				case 25:
				return "TCP_IP" ;
				break;
				case 26:
				return "Puerto Serie" ;
				break;
				case 27:
				return "Terminar?" ;
				break;
				case 28:
				return "A Salvar:" ;
				break;
				case 29:
				return "Todos los Bocetos" ;
				break;
				case 30:
				return "Panoramica" ;
				break;
				case 31:
				return "Frontal(XY)" ;
				break;
				case 32:
				return "Posterior(-XY)" ;
				break;
				case 33:
				return "Derecha(ZY)" ;
				break;
				case 34:
				return "Izquierda(-ZY)" ;
				break;
				case 35:
				return "Superior(X-Z)";
				break;
				case 36:
				return "Inferior(XZ)";
				break;
				case 37:
				return "Unir Piezas";
				break;
				case 38:
				return "Inicar Conexion";
				break;
				case 39:
				return "Vista";
				break;
				case 40:
				return "Modelo a Pintar";
				break;
				case 41:
				return "Poner Angulos";
				break;
				case 42:
				return "Idioma";
				break;
				case 43:
				return "Detener Conexion";
				break;
				case 44:
				return "Error; nombre en uso";
				break;
				case 45:
				return "Conexion finalizada";  
				break;
				case 46:
				return "Salvado en  .../ESE_GRS-XLS/";
				break;
				case 47:
				return "Error tratando de salvar los archivos";
				break;
				case 48:
				return "Error; Entrada Incorrecta";
				break;
				case 49:
				return "Se ha cargado correctamente";
				break;
				case 50:
				return "Error; Conexion ya Establecida";
				break;
				case 51:
				return "Redireccionado correctamente";
				break;
				case 52:
				return "Detalles";
				break;
				case 53:
				return "->Verificacion";
				break;
				case 54:
				return "->Error:Verificacion Adelantada";
				break;
				case 55:
				return "->Error:Verificacion Atrasada";
				break;
				case 56:
				return "Codigo:";
				break;
				case 57:
				return "->Redireccionamiento";
				break;
				case 58:
				return "->Siguiente Focus";
				break;
				case 59:
				return "->Focus Click";
				break;
				case 60:
				return "->Boton Aceptar";
				case 61:
				return "->Boton Cancelar";
				break;
				case 62:
				return "Algunos cambios de idoma no se aplicaran hasta el reinicio";
				break;
				case 63:
				return ":Error;No hay Funcionaidad para dicha Entrada";
				break;
				case 64:
				return "!!!!!!!!!Esperando Redireccionar!!!!!!!!!";
				break;
				case 65:
				return "Esperando Redireccionar";
				break;
				case 66:
				return "Idioma cambiado a Spanish";
				break;
				case 67:
				return "Spanish";
				break;
				case 68:
				return "Habilitar Modo Registro";
				break;
				case 69:
				return "Deshabilitar Modo Registro";
				break;
				case 70:
				return "BSpline";
				break;
				case 71:
				return "F1-Ayuda";
				break;
				case 72:
				return "F2-Mostrar / Ocultar Piezas (.obj)";
				break;
				case 73:
				return "F3-Rotar al plano (Solo para interfaz de dibujo)";
				break;
				case 74:
				return "F4-Vista panoramica con angulos de articulacion en 0 (Sin conexion establecida)";
				break;
				case 75:
				return "F5-Vista panoramica con Redireccionamiento (Sin conexion establecida)";
				break;
				case 76:
				return "F6-Ir al punto final del brazo";
				break;
				case 77:
				return "F7-Seguir al punto final del brazo";
				break;
				case 78:
				return "F8-Ir a una 'Media' entre todos los punto de un plano (Solo para interfaz de dibujo)";
				break;
				case 79:
				return "Conexion Finalizada";
				break;
				case 80:
				return "";
				break;
				case 81:
				return "";
				break;
				case 82:
				return "";
				break;
				case 83:
				return "";
				break;
				case 84:
				return "";
				break;
				case 85:
				return "";
				break;
				case 86:
				return "";
				break;
				case 87:
				return "";
				break;
				case 88:
				return "";
				break;
				case 89:
				return "";
				break;
				case 90:
				return "";
				break;
				default:
				return "No Encontrado";
				break;

			}
		break;
	}
	///////////////////////////////////////////////////////////
	return "NULL";
	
}
void DestruirVariablesGlobales()
{
	if(recibir_serie||!ManejadorObject->Salir)
	{
		recibir_serie=false;
		p->CloseConnection();
		ManejadorObject->Salir=true;
		t1->join();   
	}
	delete ManejadorForms;
	delete messeng;
	delete Proyect1;
	if(p->EstaConectado())
		p->CloseConnection();	
	delete p;
	delete ManejadorObject;
	delete cooRd;
	delete toSaveCOM,toSaveIp;
}	
////////////////CONTRUCTOR Y DESTRUCTOR//////////////////////////////////////////////
ESE_GRS::ESE_GRS(){
	//Constructor

	//funciones d inicialiacion del GLUT(OPENGL)
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);//inicio con cloes del rgb,doble buffer y buffer de profundidad
	Initheight=GetSystemMetrics (SM_CYSCREEN);//obtener tama�o y de pantalla
	Initwigth=GetSystemMetrics (SM_CXSCREEN);//obtener tama�o x de pantalla
	glutInitWindowPosition(0,0);//inicio de ventana de glut en 0,0 
	glutInitWindowSize(Initwigth-100,Initheight-100);//tama�o de la ventana
	height=(float)Initheight-100;
	wigth=(float)Initheight-100;
	Window=glutCreateWindow("ESE_GRS");//creo e inicio la ventana
	glEnable(GL_DEPTH_TEST);//acivo el buffer de profundidad

	
	/////////////////////////FUNCIONES POR DEFECTO/////////////////
	
	//funciones pedfinidad por el usuario para q GLUT las llame al realiarse un evento  
	glutDisplayFunc(display);//refescar pantalla
	glutMotionFunc(movRaton);//movimiento del raton
	glutMouseFunc(teclaRaton);//clics del raton
	glutReshapeFunc(reshape);//cambiar tama�o de pantalla
	glutMouseWheelFunc(wheel);//ruedita del mouse
	glutKeyboardFunc(keyboard);//teclado con teclas ASCLL
	glutSpecialFunc(SpecialKeys);//teclado con teclas speciales(Contl,Space,flechitas entre otras)
	glutIdleFunc(Idle);//al no recivir eventos
	glutCloseFunc(salvarInitDatos);//al cerrarse
	glutPassiveMotionFunc(movPasiveRaton);	//al moverse pasivamente el mause(al desplazar emouse por la ventana de la app)
	//////////////////////////INICIO MATRISES///////////////////////////////
	initProyecc();//inicializo el tipo de proyeccion y sus dimenciones
	cargarInitDatos();//cargar datos q se guardaron en un archivo .onrn q se guarda al cerrarse y hace q inicie donde lo dejastes(inicie el rotado lo demas tengo q programarlo)
	//InitMenu();
	t1=new thread(ThreadCargObject);
	ManejadorForms->Add(new Label("labelESE_GRS","ESE_GRS",*(new CRD(0,0,0)),1,(GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7,wigth,height),ManejadorForms);
	ManejadorForms->Add(new RadioButton("radioButtonMostrarAngules",*new CRD(0,0,0),Frases(52),wigth,height,true),ManejadorForms);
	ManejadorForms->SetlabelColor("radioButtonMostrarAngules",(GLfloat)0.8,(GLfloat)0.8,(GLfloat)0.8,ManejadorForms);
	MostrarAngules=true;
	ManejadorForms->Add(new Label("labelAngule0",(char*)to_string(angules[0]).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelAngule1",(char*)to_string(angules[1]).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelAngule2",(char*)to_string(angules[2]).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelAngule3",(char*)to_string(angules[3]).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelAngule4",(char*)to_string(angules[4]).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelAngule5",(char*)to_string(angules[5]).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelCoordX",(char*)(string("x:")+to_string(cooRd->x)).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelCoordY",(char*)(string("y:")+to_string(cooRd->y)).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	ManejadorForms->Add(new Label("labelCoordZ",(char*)(string("z:")+to_string(cooRd->z)).c_str(),*new CRD(0,0,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
    ManejadorForms->Add(Interfaz(0),ManejadorForms);

	StackAnimation*sa=new StackAnimation("StackAnimation1");
	sa->STANSetAnimation("InitAnimation1",CRD(0,100,0),150,100,0,0,-50,0,0,0,1);
	sa->STANSetAnimation("InitAnimation2",CRD(0,100,0),150,100,0,0,-25,1,0,0,1);
	sa->STANSetAnimation("InitAnimation3",CRD(0,100,0),150,100,0,0,0,0,1,0,1);
	sa->STANSetAnimation("InitAnimation4",CRD(0,100,0),150,100,0,0,25,0,0,1,1);
	sa->STANSetAnimation("InitAnimation5",CRD(0,100,0),150,100,0,0,50,1,1,1,1);
	ManejadorForms->Add(sa,ManejadorForms);
}
ESE_GRS::~ESE_GRS(){
		//no hace falta explicar VERDAD?
	DestruirVariablesGlobales();
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
	 if(errInitMenubool)
	 {
	 errInitMenubool=false;
	 InitMenu();
	 }
	 //inicio la proyeccion
	 initProyecc();
	
	
	 ManejadorObject->setAnguleArt1(angules,ManejadorObject);////agrego los angulos de rotacion a mi ManejadorObject
	 
	 wheelAndRotate();//me giro y acerco o alejo 
}
bool ESE_GRS::IniciarCargObjetos(){
	
	if(!CargObjct)
	{
		string g=string("Cargando Objetos ")+to_string(ManejadorObject->contLoaderObject)+string("/13 (")+to_string(ManejadorObject->contLoaderObject*100/13)+string("%)");
		ManejadorForms->GetForm("StackAnimation1",ManejadorForms)->NewTotalProp(0,0);
		ManejadorForms->GetForm("StackAnimation1",ManejadorForms)->Draw();
		text("ESE_GRS",-20,150,0,(GLfloat)0.9,(GLfloat)0.9,(GLfloat)0.9,true,true);
		text((char*)g.c_str(),-55,100,0,(GLfloat)0.8,(GLfloat)0.8,(GLfloat)0.8,true);
		glutPostRedisplay();
		return false;
	}   
	else
	    {
		   InitMenu();
		   glutPostRedisplay();
		   cargMenu=true;
		   ManejadorForms->Sub("StackAnimation1",ManejadorForms);
		   return true;
	    }


	       
	
	
	    


}
void ESE_GRS::InitMenu(){
	//inicializo y configuro los munu y subenu
	int SubMenuVista=glutCreateMenu(MenuVista);//Inicio de Submenus
	glutAddMenuEntry(Frases(30),-1);
	glutAddMenuEntry(Frases(31),0);
	glutAddMenuEntry(Frases(32),1);
	glutAddMenuEntry(Frases(33),2);
	glutAddMenuEntry(Frases(34),3);
	glutAddMenuEntry(Frases(35),4);
	glutAddMenuEntry(Frases(36),5);

	int subMenuIdioma=glutCreateMenu(MenuIdioma);
	glutAddMenuEntry(Frases(6), 0);
	glutAddMenuEntry(Frases(67), 1);

	int subMenuToDraw=glutCreateMenu(MenuToDraw);
	glutAddMenuEntry(Frases(37), - 1);
	for (int ii=0;ii<ManejadorObject->contLoaderObject;ii++)
	glutAddMenuEntry(ManejadorObject->Stack[ii]->nameStr.c_str(),ii);

	glutCreateMenu(default_menu);//aqui creo el menu general donde van todos los submenus
	if(!recibir_serie)
	{
		glutAddMenuEntry(Frases(38),0);//iniicar conexion
		glutAddSubMenu(Frases(39),SubMenuVista);//Vista
		glutAddSubMenu(Frases(40),subMenuToDraw);//To draw
		if(ModoLogger)
		   glutAddMenuEntry(Frases(69),-8);//modo registro
		else
			glutAddMenuEntry(Frases(68),-9);//modo registro
		glutAddSubMenu(Frases(42),subMenuIdioma);//idioma								 
		glutAddMenuEntry(Frases(41),4);//set angues
	}
	else
	{
		glutAddSubMenu(Frases(39),SubMenuVista);//Vista
		if(ModoLogger)
		   glutAddMenuEntry(Frases(69),-8);//modo registro
		else
			glutAddMenuEntry(Frases(68),-9);//modo registro
		glutAddMenuEntry(Frases(43),1);//Detener
		
	}
	
	

	glutAttachMenu(GLUT_RIGHT_BUTTON);//espaecifico con q tecla se activa el evento
}
void ESE_GRS::wheelAndRotate(){
	//procedimientos de rotacion y acercamiento y alejamiento de la camara con el mouse
	glScalef((GLfloat)movWheel,(GLfloat)movWheel,(GLfloat)movWheel);
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
		//void Evalua_Spline_Natural(float nptos,float *param[3][4],float ndiv)
		/*float nptos=4;
		float *param[3][4];
		float ndiv;
		int i,j;
		float aux[3],u;
		glBegin(GL_LINE_STRIP);
		for(i=0;i<nptos-1;i++)
			for(unsigned j=0;j<=ndiv;j++)
			{
				u=j/ndiv;
				aux[0]=param[i][0][0]+u*(param[i][0][1]+u*(param[i][0][2]+u*param[i][0][3]));
				aux[1]=param[i][1][0]+u*(param[i][1][1]+u*(param[i][1][2]+u* param[i][1][3]));
				aux[2]=param[i][2][0]+u*(param[i][2][1]+u*(param[i][2][2]+u* param[i][2][3]));
			}
		glEnd();*/


	    // recivirDatosCOM();//recivo y proceso la entrada del puerto serie
		Inicializar();//iniciaizo proyeccin luces y pongo los angulos del brazo 
		Entorno();
		ManejadorObject->draw(ManejadorObject,contMenuToDraw);
		//primero trasladar segun corrdenadas de la matriz de traslacion y rotacion del brazo 
		//glTranslatef((GLfloat)cooRd->x,(GLfloat)cooRd->y,(GLfloat)cooRd->z);
		if(contMenuToDraw<0)
		{
			//es neceario el PuchMatrix para q la coordenada del OpenGL quede donde va,y no desplazada segun la coordenad del matlab
			//No inicamos el LoadIdentity porq ya la matriz llega a aki vacia,pero rotalda y escladada por whellAndRotate();
			glPushMatrix();
			//glTranslated(cooRd->x,cooRd->y,cooRd->z);
			glPointSize((GLfloat)(contMenuToDraw==-1?(GLfloat)2:5));
		    glColor3d(0,0,0);
			glBegin(GL_POINTS);
			glVertex3f((GLfloat)cooRd->x,(GLfloat)cooRd->y,(GLfloat)cooRd->z);
			glEnd();
			glPopMatrix();
		
		//las coordenadas no lleban una identidad,ya q cuando se sacan en el loaderObject,
		//se obtienen con una identidad ya y en este punto del codigo todavia esta la coordenada de la modelview_matrix esta en 000,
		//pero si tiene un wheel y una rotacion,
		//por lo tanto se cargan sin mas para q se ejecute correctamante el WheelandRotate();
		
		//glTranslated(ManejadorObject->CoordReales[0],ManejadorObject->CoordReales[1],ManejadorObject->CoordReales[2]);
	
	//	glColor3d(1,1,1);
	//	glBegin(GL_POINTS);
	//	glVertex3f((GLfloat)ManejadorObject->CoordReales[0],(GLfloat)ManejadorObject->CoordReales[1],(GLfloat)ManejadorObject->CoordReales[2]);
	//	glEnd();
		}
		////Inicio los .obj y pongo el caartel de Cargando///////////////////////////////////////////
		
		
		
	}//end of carga de objetos
	
    glFlush();//siempre lleva esto no de q es bien 
	glutSwapBuffers();
	
}
void ESE_GRS::Entorno(){
	  glPushMatrix();
	  glLoadIdentity();
	  if(SeguirPuntoFinal)
	  {
	     trasladarX=-cooRd->x;
	     trasladarY=-cooRd->y;
	     trasladarZ=-cooRd->z;
	  }
		if(!Pint)
		{
			Pint=true;
			glutPostRedisplay();
		}
	  messeng->Drawing_and_Decremt(messeng);
	  text("o",-2.0,-1.5,2*wigth-1,(GLfloat)0.8,(GLfloat)0.8,(GLfloat)0.8);
	  ManejadorForms->DrawForms(ManejadorForms);
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
      Proyect1->Draw(Proyect1,(interfaz==2)?true:false);
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
void ESE_GRS::ShowAngules(){
	                  if(MostrarAngules)
						{
						 ManejadorForms->GetForm("labelAngule0",ManejadorForms)->AddNewText((char*)to_string(angules[0]).c_str());
						 ManejadorForms->GetForm("labelAngule1",ManejadorForms)->AddNewText((char*)to_string(angules[1]).c_str());
						 ManejadorForms->GetForm("labelAngule2",ManejadorForms)->AddNewText((char*)to_string(angules[2]).c_str());
						 ManejadorForms->GetForm("labelAngule3",ManejadorForms)->AddNewText((char*)to_string(angules[3]).c_str());
						 ManejadorForms->GetForm("labelAngule4",ManejadorForms)->AddNewText((char*)to_string(angules[4]).c_str());
						 ManejadorForms->GetForm("labelAngule5",ManejadorForms)->AddNewText((char*)to_string(angules[5]).c_str());
						 ManejadorForms->GetForm("labelCoordX",ManejadorForms)->AddNewText((char*)(string("x:")+to_string(cooRd->x)).c_str());	
						 ManejadorForms->GetForm("labelCoordY",ManejadorForms)->AddNewText((char*)(string("y:")+to_string(cooRd->y)).c_str());
						 ManejadorForms->GetForm("labelCoordZ",ManejadorForms)->AddNewText((char*)(string("z:")+to_string(cooRd->z)).c_str());
						}
}
Box* ESE_GRS::Interfaz(unsigned interfzAponer,INTERFZType t){
	Box*box=new Box("BoxInterfazPricipal",*new CRD(10,170,0),wigth,height);
	Forms*f=new Box();
	Proyect1->Pintar_NoPintar_LineaSuspensiva(false,Proyect1);
	bool desactivaAcept=false,desactiaCancel=false;
	string s;
	unsigned*ifIntefaz7;
	if(interfzAponer==7)
		ifIntefaz7=new unsigned(interfaz);
	switch(t)
	{
	case INTERFZType::ACEPT:////////////////////////////////ACEPT//////////////////////////////////
		switch (interfaz)
		{
		case 0:	 ////////INTERFAZ0///////////
			if(BoxInterfaz0==0)
				interfaz=1;
			else
				interfaz=6;
			break;
		case -5: /////////////Add menu bocetos////
			bool Err;
			if(bocetoACrear==0)
			{
				Proyect1->contNPl=0;
				ManejadorForms->Add(Interfaz(-1),ManejadorForms);
				break;
			}
			else if(bocetoACrear==1)
			{
				Err=false;
				for(unsigned i=0;i<Proyect1->contB;i++)
				{
					if(!strcmp(Proyect1->bocetos[i]->name,ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetEscritura("textBoxNewBoceto")))
					{
						messeng=new MeSSenger(Frases(44),CENTER_TOP,wigth,height,3,1,0,0,2);
						ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxSetFocusColorTimer("textBoxNewBoceto");
						box->Cancelar(box);
						Err=true;
						break;
					}
				}
				if(Err)
					break;


				Proyect1->Add(new Plano(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetEscritura("textBoxNewBoceto")),Proyect1);
				interfaz=1;
				ManejadorForms->ActivateRB("BoxInterfazPricipal","radioButonRemoveBoceto",ManejadorForms);
				Proyect1->ResetNewPlano(Proyect1);
				Proyect1->PlanoCheckeeado=Proyect1->contB-1;
				break;
			}
			
		//////No pongo break para el case -5 para q entre en el case -1 y ejecute su contenindo

		case -1:////////////////ADD BOCETO///////////////
			Err=false;
			for(unsigned i=0;i<Proyect1->contB;i++)
			{
				if(!strcmp(Proyect1->bocetos[i]->name,ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetEscritura("textBoxNewBoceto")))
				{
					messeng=new MeSSenger(Frases(44),CENTER_TOP,wigth,height,3,1,0,0,2);
					ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxSetFocusColorTimer("textBoxNewBoceto");
					box->Cancelar(box);
					Err=true;
					break;
				}
			}
			if(Err)
				break;

			Proyect1->Add(new Plano(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetEscritura("textBoxNewBoceto"),&Proyect1->coorNewPlano[0],&Proyect1->coorNewPlano[1],&Proyect1->coorNewPlano[2],Proyect1->NewPlanoType),Proyect1);
			//contCoordNewPlano=0;
			interfaz=1;
			ManejadorForms->ActivateRB("BoxInterfazPricipal","radioButonRemoveBoceto",ManejadorForms);
			Proyect1->ResetNewPlano(Proyect1);
			Proyect1->PlanoCheckeeado=Proyect1->contB-1;
		break;

		case -2:////////////////REMOVE BOCETO///////////////
		 	Proyect1->Sub(Proyect1->bocetos[bocetoARemover]->name,Proyect1);
			Proyect1->PlanoCheckeeado=Proyect1->contB;
		    interfaz=1;
		break;

		case 3:////////////////INIT CONNECTION///////////////
			default_menu(-1);
		    box->SetName("BoxInterfazConnections",box);
		    box->Destruir(box);
		    ManejadorForms->Sub("BoxInterfazConnectionsButtonAcept",ManejadorForms);
		    ManejadorForms->Sub("BoxInterfazConnectionsButtonCancel",ManejadorForms);
		    ManejadorForms->Add(Interfaz(0),ManejadorForms);
			default_menu(-5);
		    return box;
		break;

		case 4:////////////////STOP CONNECTION///////////////
			default_menu(-2);
		    box->SetName("BoxInterfazDetenerConnection",box);
		    box->Destruir(box);
	 	    ManejadorForms->Sub("BoxInterfazDetenerConnectionButtonAcept",ManejadorForms);
		    ManejadorForms->Sub("BoxInterfazDetenerConnectionButtonCancel",ManejadorForms);
		    ManejadorForms->Add(Interfaz(0),ManejadorForms);
			default_menu(-5);
			messeng=new MeSSenger(Frases(45),position::CENTER_TOP,wigth,height,3,1,1,0,2);
		    return box;
		break;
		case 6:
			unsigned u1,cOnT,*u;
			u1=0;
			cOnT=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetCont()-1;
			u=new unsigned[cOnT];
			u1=0;
			for(unsigned i=0;i<cOnT;i++)
			{
				s="RadioButtonSketch"+i;
				if(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBChecket((char*)s.c_str()))
					u[u1++]=i;
			}
			bool All;
			
			if(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBChecket("RadioButtonAllSketchs"))
				All=true;
			else
				All=false;
			if(XLSClass::Salvar(Proyect1->bocetos,u,u1,All,All?Proyect1->contB:0))
				messeng=new MeSSenger( Frases(46),position::CENTER_TOP,wigth,height,3,0,1,0,2);
			else
				messeng=new MeSSenger( Frases(47),position::CENTER_TOP,wigth,height,5,1,0,0,2);
			delete u;
			interfaz=0;
			break;

		default:
			if(interfaz<2)
			   interfaz++;
			break;
		}	
		break;
	case INTERFZType::CANCEL://////////////////////////////CANCEL//////////////////////////////
		switch (interfaz)
		{
		case -5:
			interfaz=1;
			Proyect1->ResetNewPlano(Proyect1);
			break;
		case -1:////////////////ADD BOCETO///////////////
			interfaz=-5;
			Proyect1->ResetNewPlano(Proyect1);
			break;

		case -2:////////////////REMOVE BOCETO///////////////
			interfaz=1;
			break;

		case 3:////////////////INIT CONNECTION///////////////
			box->SetName("BoxInterfazConnections",box);
			box->Destruir(box);
			ManejadorForms->Sub("BoxInterfazConnectionsButtonAcept",ManejadorForms);
		    ManejadorForms->Sub("BoxInterfazConnectionsButtonCancel",ManejadorForms);
			ManejadorForms->Add(Interfaz(0),ManejadorForms);
			default_menu(-5);
			return box;
			break;

		case 4:////////////////STOP CONNECTION///////////////
			box->SetName("BoxInterfazDetenerConnection",box);
			box->Destruir(box);
			ManejadorForms->Sub("BoxInterfazDetenerConnectionButtonAcept",ManejadorForms);
		    ManejadorForms->Sub("BoxInterfazDetenerConnectionButtonCancel",ManejadorForms);
			ManejadorForms->Add(Interfaz(0),ManejadorForms);
			default_menu(-5);
			return box;
			break;
		case 6:
			interfaz=0;
			break;

		default:
			if(interfaz>0)
			   interfaz--;
			break;
		}
	break;

	case INTERFZType::SPECIFIC:	/////////////////////////////////SPECIFIC/////////////////////////////
			interfaz=interfzAponer;
		break;
	}
	switch (interfaz)
	{
	case 0://///////////////////////////INTERFAZ_0////////////////////////
		Proyect1->SetDraw(false,Proyect1);
		f=new Label("LabelInterfaz0","ESE_GRS:",*new CRD(0,0,0),2,0,0,0,wigth,height);
		box->AddForm(f,box);
		f=new RadioButtonGroup("radioButtonGroupInterfaz0",*new CRD(0,0,0),wigth,height);
		f->RBGAddRB("radioButtonEditSketchs",Frases(0),BoxInterfaz0==0?true:false);
		f->RBGAddRB("radioButtonSaveSketchs",Frases(1),BoxInterfaz0==1?true:false);
		if(Proyect1->contB==0)
			f->RBGActivDesactRB("radioButtonSaveSketchs",false);
		desactiaCancel=true;
		box->AddForm(f,box);
		break;
	case 1://///////////////////////////INTERFAZ_1////////////////////////
		Proyect1->SetDrawAll(false,Proyect1);
		Proyect1->SetDraw(true,Proyect1);
		f=new Label("LabelInterfaz1",Frases(2),*new CRD(0,0,0),2,0,0,0,wigth,height);
		box->AddForm(f,box);
		f=new RadioButtonGroup("radioButtonGroupInterfaz1",*new CRD(10,150,0),wigth,height);
		f->RBGAddRB("RadioButtonVistaGeneral",Frases(3),true);
		for(unsigned i=0;i<Proyect1->contB;i++)
		{
			s="radioButtonBoceto"+to_string(i);
			f->RBGAddRB((char*)s.c_str(),Proyect1->bocetos[i]->name,(Proyect1->PlanoCheckeeado==i && Proyect1->PlanoCheckeeado!=Proyect1->contB)?true:false);
		}
		if(f->RBGGetRBChecket("RadioButtonVistaGeneral"))
			desactivaAcept=true;
		box->AddForm(f,box);
		f=new RadioButton("radioButtonAgregarBoceto",*new CRD(0,0,0),Frases(4),wigth,height);
		if(!recibir_serie)
		   f->ActivateDesactivate(false);															
		box->AddForm(f,box,10);
		f=new RadioButton("radioButtonRemoverBoceto",*new CRD(0,0,0),Frases(5),wigth,height);
		if(Proyect1->contB==0)
			f->ActivateDesactivate(false);
		box->AddForm(f,box,10);
		if(!recibir_serie)
			desactivaAcept=true;
		break;
	case 2://///////////////////////////INTERFAZ_2////////////////////////
		Proyect1->ActualizaLastCood(cooRd,Proyect1); 
		Plano::ActualiWidthHeight(cooRd,Proyect1->BocetoActual(Proyect1));
		Proyect1->SetDraw(true,Proyect1);
		RadioButtomPintar=0;
		s=(Proyect1->BocetoActual(Proyect1)->name);
		s+=":";
		f=new Label("LabelInterfaz2",(char*)s.c_str(),*new CRD(0,0,0),1,0,0,0,wigth,height);
		box->AddForm(f,box);
		f=new RadioButtonGroup("radioButtonGroupInterfaz2",*new CRD(10,150,0),wigth,height);
		ItemsType checket;
		checket=Proyect1->BocetoActual(Proyect1)->items->t;
		f->RBGAddRB("radioButonAddPunto",Frases(7),checket==ItemsType::POINTSS||checket==ItemsType::ITEMS?true:false);
		f->RBGAddRB("radioButonAddLines",Frases(8),checket==ItemsType::LINES?true:false);
		f->RBGAddRB("radioButonAddStipLine",Frases(9),checket==ItemsType::LINE_STRIP?true:false);
		f->RBGAddRB("radioButonAddSpline",Frases(10),checket==ItemsType::SPLINE?true:false);
		f->RBGAddRB("radioButonAddBSpline",Frases(70),checket==ItemsType::BSPLINE?true:false);
		box->AddForm(f,box);
		f=new RadioButton("RadioButtomCancelLast",*new CRD(0,0,0),Frases(11),wigth,height);
		if(!Proyect1->BocetoActual(Proyect1)->items->cont)
			f->ActivateDesactivate(false);
		box->AddForm(f,box,10);
		if(Plano::IsRestring(Proyect1->BocetoActual(Proyect1)))
		{
			f=new RadioButton("RadioButtomMostrarPlano",*new CRD(0,0,0),Frases(12),wigth,height,true);
			box->AddForm(f,box,10);
		}
		desactivaAcept=true;
		
		break;
	case -5://///////////////////////////////////INTERFAZ_-5/////////////////////////
		Proyect1->SetDraw(false,Proyect1);
		f=new Label("LabelInterfaz-5",Frases(13),*new CRD(0,0,0),2,0,0,0,wigth,height);
		box->AddForm(f,box);
		f=new RadioButtonGroup("RadioButtonInterfaz-5",*new CRD(0,0,0),wigth,height);
		f->RBGAddRB("RadioButtonPlanoXY",Frases(14),bocetoACrear==0?true:false);
		f->RBGAddRB("RadioButtonPlanoFree",Frases(15),bocetoACrear==1?true:false);
		f->RBGAddRB("RadioButtonPlanoXY",Frases(16),bocetoACrear==2?true:false);
		f->RBGAddRB("RadioButtonPlanoXY",Frases(17),bocetoACrear==3?true:false);
		f->RBGAddRB("RadioButtonPlanoXY",Frases(18),bocetoACrear==4?true:false);
		box->AddForm(f,box);
		
		if(bocetoACrear!=0)
		{
			if(bocetoACrear>1)
			{
				f=new RadioButtonGroup("RadioButtonGroupPlanoPosittion",CRD(0,0,0),wigth,height);
				f->RBGAddRB("RadioButtonDefault",Frases(19),deFult?true:false);
				f->RBGAddRB("RadioButtonEndPoint",Frases(20),!deFult?true:false);
				box->AddForm(f,box);
			}
			s=(bocetoACrear==1?Frases(22):Frases(21))+to_string(Proyect1->contB);
			f=new TextBox("textBoxNewBoceto",*new CRD(0,0,0),box->Wigth-10,wigth,height,(char*)s.c_str(),10);
			box->AddForm(f,box);
		}
		box->BoxSetFocus(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetFocus());
		break;
	case -1:////////////////////////////////////////INTERFAZ_-1//////////////////////Add New Specific Boceto
		Proyect1->SetDraw(false,Proyect1);
		s=Frases(23)+to_string(Proyect1->contNPl)+"/3";
		f=new Label("LabelInterfaz-1",(char*)s.c_str(),*new CRD(0,0,0),1,0,0,0,wigth,height);
		box->AddForm(f,box);
		for(unsigned i=0;i<Proyect1->contNPl;i++)
		{
			s=("["+to_string(Proyect1->coorNewPlano[i].x)+";"+to_string(Proyect1->coorNewPlano[i].y)+";"+to_string(Proyect1->coorNewPlano[i].z)+"]");
			f=new Label((char*)string("LabelPunto"+to_string(i)).c_str(),(char*)s.c_str(),*new CRD(0,0,0),1,0,0,0,wigth,height);
		    box->AddForm(f,box);
		}
		if(Proyect1->contNPl==3)
		{
			s=Frases(21)+to_string(Proyect1->contB);
			f=new TextBox("textBoxNewBoceto",*new CRD(0,0,0),box->Wigth-10,wigth,height,(char*)s.c_str());
		    box->AddForm(f,box);
		}
		desactivaAcept=true;
		break;
	case -2://///////////////////////////INTERFAZ_-2////////////////////////REMOVE BOCETO
		bocetoARemover=0;
		Proyect1->SetDraw(true,Proyect1);
		s=Frases(24);
		f=new Label("LabelInterfaz-2",(char*)s.c_str(),*new CRD(0,0,0),2,0,0,0,wigth,height);
		box->AddForm(f,box);
		f=new RadioButtonGroup("radioButtonGroupInterfaz-2",*new CRD(10,150,0),wigth,height);
		for(unsigned i=0;i<Proyect1->contB;i++)
		{
			s="radioButtonBoceto"+to_string(i);
			f->RBGAddRB((char*)s.c_str(),Proyect1->bocetos[i]->name,i==0?1:0);
		}
		Proyect1->PlanoCheckeeado=0;
		box->AddForm(f,box);
		break;
	case 3://///////////////////////////INTERFAZ_3////////////////////////
		box->SetName("BoxInterfazConnections",box);
		box->SetCRD(new CRD(10,40,0),box);
		f=new TextBox("textBoxChar",*new CRD(0,0,0),100,wigth,height,p->GetType()==ConnectionType::TCP_IP_CLIENT?toSaveIp:toSaveCOM,15);
		box->AddForm(f,box);
		f=new TextBox("textBoxUnsigned",*new CRD(0,0,0),100,wigth,height,p->GetType()==ConnectionType::TCP_IP_CLIENT?(char*)to_string(toSavePort).c_str():(char*)to_string(toSaveSpeed).c_str(),10,TextBoxType::UNSIGNEDCONTENT);
		box->AddForm(f,box);
		f=new RadioButtonGroup("RadioButtonGroupConnectionType",*new CRD(0,0,0),wigth,height);
		f->RBGAddRB("RadioButtomEternet",Frases(25),p->GetType()==ConnectionType::TCP_IP_CLIENT?1:0);
		f->RBGAddRB("RadioButtomSerialPort",Frases(26),p->GetType()==ConnectionType::SERIAL_PORT?1:0);
		box->AddForm(f,box);
		break;
	case 4://///////////////////////////INTERFAZ_4////////////////////////
		box->SetName("BoxInterfazDetenerConnection",box);
		box->SetCRD(new CRD(10,100,0),box);
		f=new Label("LabelInterfaz4",Frases(27),*new CRD(0,0,0),1,0,0,0,wigth,height);
		box->AddForm(f,box);
		
		break;
	case 6:
		Proyect1->SetDraw(false,Proyect1);
		f=new Label("labelSelectSketsh",Frases(28),CRD(0,0,0),2,0,0,0,wigth,height);
		box->AddForm(f,box);
		for(unsigned i=0;i<Proyect1->contB;i++)
		{
			s="RadioButtonSketch"+i;
			f=new RadioButton((char*)s.c_str(),CRD(0,0,0),Proyect1->bocetos[i]->name,wigth,height,true);
			box->AddForm(f,box);
		}
		if(Proyect1->contB>1)
		{
			f=new RadioButton("RadioButtonAllSketchs",CRD(0,0,0),Frases(29),wigth,height);
		box->AddForm(f,box);
		}
		break; 
	case 7:	  //F1
		interfaz=*ifIntefaz7;
		if(!Boxf1)
		{
			Boxf1=true;
			box=new Box("BoxHelp",CRD(0,0,0),wigth,height);
			box->Wigth=100;
			f=new Label("Labelf1",Frases(71),CRD(0,0,0),1,0,0,0,wigth,height);
			box->AddForm(f,box);
			f=new Label("Labelf2",Frases(72),CRD(0,0,0),1,0,0,0,wigth,height);
			box->AddForm(f,box);
			f=new Label("Labelf3",Frases(73),CRD(0,0,0),1,0,0,0,wigth,height);
			box->AddForm(f,box);
			f=new Label("Labelf4",Frases(74),CRD(0,0,0),1,0,0,0,wigth,height);
			box->AddForm(f,box);
			f=new Label("Labelf5",Frases(75),CRD(0,0,0),1,0,0,0,wigth,height);
			box->AddForm(f,box);
			f=new Label("Labelf6",Frases(76),CRD(0,0,0),1,0,0,0,wigth,height);
			box->AddForm(f,box);
			f=new Label("Labelf7",Frases(77),CRD(0,0,0),1,0,0,0,wigth,height);
			box->AddForm(f,box);
			f=new Label("Labelf8",Frases(78),CRD(0,0,0),1,0,0,0,wigth,height);
			box->AddForm(f,box);
			f=new Button("ButonCancelHelp",Type::BUTTON,CRD(0,0,0),1,0,0,box->Wigth,25,wigth,height);
			box->AddForm(f,box);
			box->SetCoordElementProp("Labelf1",&(*box->BoxGetElementCoord("Labelf1")+*(new CRD(box->Wigth/2,0,0))-*(new CRD(strlen(Frases(71))*4.5,0,0))));
			box->SetCoordElementProp("Labelf2",&(*box->BoxGetElementCoord("Labelf2")+*(new CRD(box->Wigth/2,0,0))-*(new CRD(strlen(Frases(72))*4.5,0,0))));
			box->SetCoordElementProp("Labelf3",&(*box->BoxGetElementCoord("Labelf3")+*(new CRD(box->Wigth/2,0,0))-*(new CRD(strlen(Frases(73))*4.5,0,0))));
			box->SetCoordElementProp("Labelf4",&(*box->BoxGetElementCoord("Labelf4")+*(new CRD(box->Wigth/2,0,0))-*(new CRD(strlen(Frases(74))*4.5,0,0))));
			box->SetCoordElementProp("Labelf5",&(*box->BoxGetElementCoord("Labelf5")+*(new CRD(box->Wigth/2,0,0))-*(new CRD(strlen(Frases(75))*4.5,0,0))));
			box->SetCoordElementProp("Labelf6",&(*box->BoxGetElementCoord("Labelf6")+*(new CRD(box->Wigth/2,0,0))-*(new CRD(strlen(Frases(76))*4.5,0,0))));
			box->SetCoordElementProp("Labelf7",&(*box->BoxGetElementCoord("Labelf7")+*(new CRD(box->Wigth/2,0,0))-*(new CRD(strlen(Frases(77))*4.5,0,0))));
			box->SetCoordElementProp("Labelf8",&(*box->BoxGetElementCoord("Labelf8")+*(new CRD(box->Wigth/2,0,0))-*(new CRD(strlen(Frases(78))*4.5,0,0))));
			box->SetWigthElementProp("ButonCancelHelp",box->Wigth-5);
			box->NewCRD(new CRD(wigth/2-box->Wigth/2,height/2-box->Height/2,0));
			box->SetProfundidad(1);
			box->BoxSetDrawLineForElement(false);
			return box;
		}
		else
		{
			Boxf1=false;
			Forms::SetName("BoxHelp",box);
			Forms::Destruir(box);
			return box;
		}
		//break;
	}
	//////////////////////////////////////////////////////BUTTONS////////////////////////////////////////////////////
	string ss,ss1;
	ss=ss1=box->name;
	ss+="ButtonAcept";
	ss1+="ButtonCancel";
	ManejadorForms->Add(new Button((char*)ss.c_str(),Type::BUTTONACEPTRB,*new CRD(box->coord->x-6,box->coord->y+box->Height+5,box->coord->z),0,1,0,box->Wigth+6,10,box->TotalWigth,box->TotalHeight),ManejadorForms);
	ManejadorForms->Add(new Button((char*)ss1.c_str(),Type::BUTTONCANCELRB,*new CRD(box->coord->x+box->Wigth,box->coord->y-6,box->coord->z),1,0,0,10,box->Height+21,box->TotalWigth,box->TotalHeight),ManejadorForms);
	if(desactivaAcept)
		ManejadorForms->DesactivateForm("BoxInterfazPricipalButtonAcept",ManejadorForms);
	if(desactiaCancel)
		ManejadorForms->DesactivateForm("BoxInterfazPricipalButtonCancel",ManejadorForms);
	return box;
}
/////////////////////FUNCIONES DE GLUT A LLAMAR POR DEFECTO////////////////////////////
void ESE_GRS::reshape(int x,int y){
	wigth=(float)x;height=(float)y;
	ManejadorForms->NewTotalsProp((float)x,(float)y,ManejadorForms);
	ManejadorForms->GetForm("radioButtonMostrarAngules",ManejadorForms)->NewCRD(new CRD(wigth-120,8,0));
	ManejadorForms->GetForm("labelAngule0",ManejadorForms)->NewCRD(new CRD(wigth-120,25,0));
	ManejadorForms->GetForm("labelAngule1",ManejadorForms)->NewCRD(new CRD(wigth-120,40,0));
	ManejadorForms->GetForm("labelAngule2",ManejadorForms)->NewCRD(new CRD(wigth-120,55,0));
	ManejadorForms->GetForm("labelAngule3",ManejadorForms)->NewCRD(new CRD(wigth-120,70,0));
	ManejadorForms->GetForm("labelAngule4",ManejadorForms)->NewCRD(new CRD(wigth-120,85,0));
	ManejadorForms->GetForm("labelAngule5",ManejadorForms)->NewCRD(new CRD(wigth-120,100,0));
	ManejadorForms->GetForm("labelCoordX",ManejadorForms)->NewCRD(new CRD(wigth-120,115,0));
	ManejadorForms->GetForm("labelCoordY",ManejadorForms)->NewCRD(new CRD(wigth-120,130,0));
	ManejadorForms->GetForm("labelCoordZ",ManejadorForms)->NewCRD(new CRD(wigth-120,145,0));

	glViewport(0,0,x,y);//creo una zona de la ventana con el contenido  
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
void ESE_GRS::movRaton(GLsizei x,GLsizei y){

	

   movRatY+=(float)x-movRatXinit;
   movRatX+=(float)y-movRatYinit;
   movRatXinit=(float)x;
   movRatYinit=(float)y;
   if(Proyect1->contB)
	   Plano::verPlanoRotado(0,Proyect1->BocetoActual(Proyect1));
   glutPostRedisplay();//refresco y ejecuto el displayFunc()
}
void ESE_GRS::movPasiveRaton(GLsizei x,GLsizei y)
{
	switch (ManejadorForms->FormsPasiveMouse((int)x,(int)y,ManejadorForms))
	{
	case Type::BUTTONACEPTRB:
	case Type::BUTTONINITSETANGULES:	
	case Type::RADIOBUTTON:
	case Type::BUTTONCANCELSETANGULES:
	case Type::BUTTONCANCELRB:
		if(!cursor)
		{
			glutSetCursor( GLUT_CURSOR_HELP);
			cursor=true;
		}
	break;
	case Type::TEXTBOX:
		glutSetCursor( GLUT_CURSOR_TEXT);
		cursor=true;
		break;
	default:
		if(cursor)
		{
			glutSetCursor(GLUT_CURSOR_INHERIT);
			cursor=false;
		}
	break;
	} 
};
void ESE_GRS::Idle(){
   if(recibir_serie||ManejadorForms->GetEstoyEscribindo())
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
	   case Type::BOX:
		   if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("BoxInterfazConnections",ManejadorForms)))
		   {
			   if(interfaz==3)//interfaz 3
			   {
				  if(ManejadorForms->GetForm("BoxInterfazConnections",ManejadorForms)->BoxGetElemChecket()==2)
				  {
					 p->SetType(ManejadorForms->GetForm("BoxInterfazConnections",ManejadorForms)->BoxGetRBGChecket("RadioButtonGroupConnectionType")?ConnectionType::SERIAL_PORT:ConnectionType::TCP_IP_CLIENT,p);
				     ManejadorForms->Add(Interfaz(3),ManejadorForms);
				  }
			   }
		   }	
		   else if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("BoxHelp",ManejadorForms)))
		   {
			   if(ManejadorForms->GetForm("BoxHelp",ManejadorForms)->BoxGetElemChecket()==8)
			   {
				   SpecialKeys(GLUT_KEY_F1,0,0);
			   }
		   }
		   else if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)))
		   {
			   BoxInterfazPricipal=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetElemChecket();
			   Proyect1->Pintar_NoPintar_LineaSuspensiva(false,Proyect1);
			   switch (interfaz)
			   {
			   case 0: //////////////////////////INTERFAZ 0
					if(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetElemChecket()==1)
						BoxInterfaz0=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBGChecket("radioButtonGroupInterfaz0");
					break;
			   case 1://////////////////////////INTERFAZ 1
				   switch (BoxInterfazPricipal)
				   {
				   case 1:////////////SELECC BOCETO
					   PlanoChecket=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBGChecket("radioButtonGroupInterfaz1");
					   if(PlanoChecket==0)
					   {
						    Proyect1->SetDrawAll(true,Proyect1);
							ManejadorForms->DesactivateForm("BoxInterfazPricipalButtonAcept",ManejadorForms);
					   }
					   else
					   {
						    if(recibir_serie)
								ManejadorForms->ActivateForm("BoxInterfazPricipalButtonAcept",ManejadorForms);
							Proyect1->SetDrawAll(false,Proyect1);
							Proyect1->PlanoCheckeeado=PlanoChecket-1;
							Proyect1->BocetoActual(Proyect1)->pintarPlano=true;
					   }
					   break;
				   case 2:///////////////////// ADD BOCETO
					   if(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetActiveDesact("radioButtonAgregarBoceto"))
					   {
					      Proyect1->contNPl=0;
						  bocetoACrear=0;
					      ManejadorForms->Add(Interfaz(-5),ManejadorForms);
					   }
					   break;
				   case 3://////////////REMOVE BOCETO
					   if(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetActiveDesact("radioButtonRemoverBoceto"))
					     {
							 PlanoChecket=Proyect1->PlanoCheckeeado;
							 ManejadorForms->Add(Interfaz(-2),ManejadorForms);
					     }
					   break;
				   }
				   break;
			   case 2://///////////////////////INTERFAZ 2/////
				    switch (BoxInterfazPricipal)
					{
					case 1:////////////RADIOBUTTONGROUP ITEMS
						RadioButtomPintar=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBGChecket("radioButtonGroupInterfaz2");
						if(RadioButtomPintar==0)///POINTS
							Plano::ActualizaItem(ItemsType::POINTSS,Proyect1->BocetoActual(Proyect1));
						else if(RadioButtomPintar==1)//LINES
							Plano::ActualizaItem(ItemsType::LINES,Proyect1->BocetoActual(Proyect1));
						else if(RadioButtomPintar==2)//STRIP_LINE
							Plano::ActualizaItem(ItemsType::LINE_STRIP,Proyect1->BocetoActual(Proyect1));
						else if(RadioButtomPintar==3)//SPLINE
							Plano::ActualizaItem(ItemsType::SPLINE,Proyect1->BocetoActual(Proyect1));
						else if(RadioButtomPintar==4)//BSPLINE
							Plano::ActualizaItem(ItemsType::BSPLINE,Proyect1->BocetoActual(Proyect1));
						break;
					case 2:///////CANCEL Point
						if(	ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetActiveDesact("RadioButtomCancelLast"))
						{
						Plano::CancelLastPoint(Proyect1->BocetoActual(Proyect1));
						if(!Proyect1->BocetoActual(Proyect1)->items->cont)
							ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxSetActivateDesactivate("RadioButtomCancelLast",false);
						}
						ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxCambiarChecketRB("RadioButtomCancelLast");
						break;
					case 3://Mostrar\ocultar Plano
						Proyect1->Pintar_NoPintar_LineaSuspensiva(true,Proyect1);
						if(ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBChecket("RadioButtomMostrarPlano"))
							Proyect1->BocetoActual(Proyect1)->pintarPlano=true;
						else
							Proyect1->BocetoActual(Proyect1)->pintarPlano=false;
						break;
					}
				   break;
			   case -2:   /////////////REMOVER BOCETO///////INTEFAZ-2////
				    bocetoARemover=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBGChecket("radioButtonGroupInterfaz-2");
					Proyect1->PlanoCheckeeado=bocetoARemover;
				break;
			   case -5:	///////////////SELECT NEW PLANO/////////
				   switch (BoxInterfazPricipal)
				   {
					 case 1:
						   bocetoACrear=ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBGChecket("RadioButtonInterfaz-5");
						   switch (bocetoACrear)
						   {
							   
							   case 0:///NEW PLANO////
										Proyect1->AddNewType(TypePlano::SPECIFICPLANE,Proyect1);
										Proyect1->ResetNewPlano(Proyect1);
								   break;
							   case 1:///FREE Plano///
										Proyect1->AddNewType(TypePlano::FREE,Proyect1);
										Proyect1->ResetNewPlano(Proyect1);
								   break;
							   case 2:////XY//////
										Proyect1->ResetNewPlano(Proyect1);
										Proyect1->contNPl=4;	    
										Proyect1->AddNewType(TypePlano::XY,Proyect1);
										Proyect1->ActualizaNewPlanoToCreate(cooRd,Proyect1,deFult);
								   break;
								case 3:///XZ//////
										Proyect1->AddNewType(TypePlano::XZ,Proyect1);
										Proyect1->ResetNewPlano(Proyect1);
										Proyect1->contNPl=4;
										Proyect1->ActualizaNewPlanoToCreate(cooRd,Proyect1,deFult);
								   break;
								case 4:///YZ//////
										Proyect1->AddNewType(TypePlano::YZ,Proyect1);
										Proyect1->ResetNewPlano(Proyect1);
										Proyect1->contNPl=4;
										Proyect1->ActualizaNewPlanoToCreate(cooRd,Proyect1,deFult);
								   break;
						   }
						   ManejadorForms->Add(Interfaz(-5),ManejadorForms); 
						break;
					 case 2:
						 if(bocetoACrear>1)
						 {
							 deFult= ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxGetRBGChecket("RadioButtonGroupPlanoPosittion")==0?true:false;
							 Proyect1->ActualizaNewPlanoToCreate(cooRd,Proyect1,deFult);
						 }
						 break;
					}
				   break;
				} 
			}

		   break;



		   	/////////////////////////////////////////////////////////RADIOBUTTONGROUP//////////////////////////////////////////////////////////
		    case Type::RADIOBUTTONGROUP:
	
			 break;

														  
			 /////////////////////////////////////////////////////////RADIOBUTTON//////////////////////////////////////////////////////////
		     case Type::RADIOBUTTON:
			       if(Forms::IsPulsdo((float)x,(float)y,ManejadorForms->GetForm("radioButtonMostrarAngules",ManejadorForms)))
				       {
					   if(!MostrarAngules)
					   {   
						MostrarAngules=true;
						ManejadorForms->Add(new Label("labelAngule0",(char*)to_string(angules[0]).c_str(),*new CRD(wigth-120,25,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	                    ManejadorForms->Add(new Label("labelAngule1",(char*)to_string(angules[1]).c_str(),*new CRD(wigth-120,40,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	                    ManejadorForms->Add(new Label("labelAngule2",(char*)to_string(angules[2]).c_str(),*new CRD(wigth-120,55,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	                    ManejadorForms->Add(new Label("labelAngule3",(char*)to_string(angules[3]).c_str(),*new CRD(wigth-120,70,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	                    ManejadorForms->Add(new Label("labelAngule4",(char*)to_string(angules[4]).c_str(),*new CRD(wigth-120,85,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	                    ManejadorForms->Add(new Label("labelAngule5",(char*)to_string(angules[5]).c_str(),*new CRD(wigth-120,100,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	                    ManejadorForms->Add(new Label("labelCoordX",(char*)(string("x:")+to_string(cooRd->x)).c_str(),*new CRD(wigth-120,115,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	                    ManejadorForms->Add(new Label("labelCoordY",(char*)(string("y:")+to_string(cooRd->y)).c_str(),*new CRD(wigth-120,130,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
	                    ManejadorForms->Add(new Label("labelCoordZ",(char*)(string("z:")+to_string(cooRd->z)).c_str(),*new CRD(wigth-120,145,0),1,(GLfloat)0.4,(GLfloat)0.4,(GLfloat)0.4,wigth,height),ManejadorForms);
					   }
					else
					{
						ManejadorForms->Sub("labelAngule0",ManejadorForms);
						ManejadorForms->Sub("labelAngule1",ManejadorForms);
						ManejadorForms->Sub("labelAngule2",ManejadorForms);
						ManejadorForms->Sub("labelAngule3",ManejadorForms);
						ManejadorForms->Sub("labelAngule4",ManejadorForms);
						ManejadorForms->Sub("labelAngule5",ManejadorForms);
						ManejadorForms->Sub("labelCoordX",ManejadorForms);
						ManejadorForms->Sub("labelCoordY",ManejadorForms);
						ManejadorForms->Sub("labelCoordZ",ManejadorForms);
						MostrarAngules=false;
					}
				}		
		   break;
		                                //////////////////////////////BUTTONS////////////////////
		    case Type::BUTTONACEPTRB:
			ManejadorForms->Add(Interfaz(0,INTERFZType::ACEPT),ManejadorForms);
			break;

			case Type::BUTTONCANCELRB:
			ManejadorForms->Add(Interfaz(0,INTERFZType::CANCEL),ManejadorForms);
			break;

	        case Type::BUTTONCANCELSETANGULES:
			default_menu(3);
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
		      messeng=new MeSSenger(Frases(48),position::CENTER_TOP,wigth,height,3,1,0,0,2);
		   else
		   {
			   messeng=new MeSSenger(Frases(49),position::CENTER_TOP,wigth,height,3,0,1,0,2);
			   for(unsigned i=0;i<6;i++)
		       {
			   s=("textBoxsSetAngules");
			   s+=to_string(i);
				if(strlen(ManejadorForms->GetForm((char*)s.c_str(),ManejadorForms)->GetEscritura()))
			       angules[i]=(GLfloat)atof(ManejadorForms->GetForm((char*)s.c_str(),ManejadorForms)->GetEscritura());
			    s.clear();
				
			   }
				   
			   CalcularCoordenadas();
			   CalcularCoordenadas();
			   ShowAngules();
		    }
		   break;     
	   }
	}
   
  
   if(boton==GLUT_LEFT_BUTTON && state==GLUT_DOWN )//girar al puslar clik dercho con el mouse(misma opcion q el movRat para el primer clic no te varie la rotacion)
   {
	movRatXinit=(float)x;
	movRatYinit=(float)y;
	
   }
	
	glutPostRedisplay();
}
void ESE_GRS::keyboard(unsigned char tecla,int x,int y ){
  if(ManejadorForms->GetEstoyEscribindo())
  {
	if(tecla==8)
	    ManejadorForms->SubText(ManejadorForms);
	else
		ManejadorForms->AddText(tecla,ManejadorForms);
  }
  else
  {
	if(tecla=='>')
	{
	   trasladarY+=5;
	   SeguirPuntoFinal=false;
    }
	if(tecla=='<')
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
			CalcularCoordenadas();
		break;
		case '2':
			angules[0]-=(GLfloat)0.9;	
			CalcularCoordenadas();
		break;

		case '3':
			angules[1]+=(GLfloat)0.9;
			CalcularCoordenadas();
		break;
		case '4':
			angules[1]-=(GLfloat)0.9;
			CalcularCoordenadas();
		break;

		case '5':
			angules[2]+=(GLfloat)0.9;
			CalcularCoordenadas();
		break;

		case '6':
			angules[2]-=(GLfloat)0.9;
			CalcularCoordenadas();
		break;
		case '7':
			angules[3]+=(GLfloat)0.9;
			CalcularCoordenadas();
		break;
		case '8':
			angules[3]-=(GLfloat)0.9;
			CalcularCoordenadas();
		break;
		case '9':	
			angules[4]+=(GLfloat)0.9;
			CalcularCoordenadas();
		break;

		case '0':
			angules[4]-=(GLfloat)0.9;
			CalcularCoordenadas();
		break;
		case '-':			
			angules[5]+=(GLfloat)0.9;
			CalcularCoordenadas();
		break;

		case '=':
			angules[5]-=(GLfloat)0.9;
			CalcularCoordenadas();
		break;
	    }

	    ShowAngules();
	    DataProcessor::RectificarAngules(angules);

		

	 }
	 else
     {
	    //messeng=new MeSSenger("Accion no valida ;Conexion por puerto serie ya iniciada",position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,0,0,2);
     }
	 CRD*CoordElement;
	 double*ElementCoord;
	 switch (tecla)
	 {
	    case 's':
 			ManejadorForms->NextFocus("BoxInterfazPricipal",ManejadorForms);
	 	break;
		case 'w':
			ElementCoord=ManejadorForms->FocusClick("BoxInterfazPricipal",ManejadorForms);
			teclaRaton(GLUT_LEFT_BUTTON,GLUT_UP,(int)ElementCoord[0],(int)ElementCoord[1]);
		break;
		case 'q':
			CoordElement=ManejadorForms->GetForm("BoxInterfazPricipalButtonAcept",ManejadorForms)->GetCoord(ManejadorForms->GetForm("BoxInterfazPricipalButtonAcept",ManejadorForms));
			teclaRaton(GLUT_LEFT_BUTTON,GLUT_UP,(int)CoordElement->x,(int)CoordElement->y);
		break;
		case 'e':
			CoordElement=ManejadorForms->GetForm("BoxInterfazPricipalButtonCancel",ManejadorForms)->GetCoord(ManejadorForms->GetForm("BoxInterfazPricipalButtonCancel",ManejadorForms));
			teclaRaton(GLUT_LEFT_BUTTON,GLUT_UP,(int)CoordElement->x,(int)CoordElement->y);
		break;
	  }
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
		CalcularCoordenadas();
		ShowAngules();
	break;
	case GLUT_KEY_F1:
		ManejadorForms->Add(Interfaz(7),ManejadorForms);
		break;

	case GLUT_KEY_F2:	 //Ocultar Piezas
			if(!boolMenuToDraw)
			{
			   contMenuToDraw=-2;
			   boolMenuToDraw=true;
			}
			else
			{
			   contMenuToDraw=-1;
			   boolMenuToDraw=false;
			}
	break;

	case GLUT_KEY_F3:	  //Girar al Plano(Solo interfaz 2 && boceto!=0)
		if(interfaz==2&&Plano::IsRestring(Proyect1->BocetoActual(Proyect1)))
		{
			CRD*toMove=Plano::RotarAlPlano(Proyect1->BocetoActual(Proyect1));
			movESE_GRSX=(float)toMove->x*velGiro;
			movESE_GRSY=(float)toMove->y*velGiro;
			movESE_GRSZ=(float)toMove->z*velGiro;
			if(RotarAlPlanoContrar)
			{
				movESE_GRSX+=180*velGiro;
				movESE_GRSY+=180*velGiro;
				movESE_GRSZ+=180*velGiro;
				RotarAlPlanoContrar=false;
				Plano::verPlanoRotado((float)0.1,Proyect1->BocetoActual(Proyect1));
			}
			else
			{
				RotarAlPlanoContrar=true;
				Plano::verPlanoRotado((float)-0.1,Proyect1->BocetoActual(Proyect1));
			}
		}
	break;

	case GLUT_KEY_F4:	//"Reedireccionamiento"
		if(!recibir_serie)
		{
			angules[0]=0;
			angules[1]=(GLfloat)-13.8;
			angules[2]=(GLfloat)-44.5;
			angules[3]=(GLfloat)2.04;
			angules[4]=(GLfloat)90;
			angules[5]=(GLfloat)-2.04;
			CalcularCoordenadas();
			ShowAngules();
		}
		else
		{
			trasladarX=0;
			trasladarY=0;
			trasladarZ=0;
			MenuVista(-1);
			SeguirPuntoFinal=false;
		}
	break;

	case GLUT_KEY_F5:	   //Todos los angulos a 0
		if(!recibir_serie)
		{
		   trasladarX=0;
		   trasladarY=0;
		   trasladarZ=0;
		   angules[0]=0;
           angules[1]=0;
           angules[2]=0;
           angules[3]=0;
	 	   angules[4]=0;
		   angules[5]=0;
		   SeguirPuntoFinal=false;
		   MenuVista(-1);
		   CalcularCoordenadas();
		   ShowAngules();
		}
		else
		{
			trasladarX=0;
			trasladarY=0;
			trasladarZ=0;
			MenuVista(-1);
			SeguirPuntoFinal=false;
		}
	break;

	case GLUT_KEY_F6:	//Ir al punto final del brazo
		trasladarX=-cooRd->x;
		trasladarY=-cooRd->y;
		trasladarZ=-cooRd->z;
		SeguirPuntoFinal=false;
	break;

	case GLUT_KEY_F7:	 //Seguir el punto final del brazo
		if(!SeguirPuntoFinal)
		{   
			SeguirPuntoFinal=true;
			CalcularCoordenadas();
		}
		break;
	case GLUT_KEY_F8:
		if(interfaz==2)
		{
			CRD*toTraslated;
			toTraslated=new CRD(Plano::Media(Proyect1->BocetoActual(Proyect1)));
			trasladarX=-toTraslated->x;
			trasladarY=-toTraslated->y;
			trasladarZ=-toTraslated->z;
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
void ESE_GRS::default_menu(int opcion){
	switch (opcion)
	{
	case 4:///SET angules
	    default_menu(-6);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules0",*(new CRD(0,175,0)),110,wigth,height,(char*)to_string(angules[0]).c_str(),9,TextBoxType::FLOATCONTENT),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules1",*(new CRD(0,200,0)),110,wigth,height,(char*)to_string(angules[1]).c_str(),9,TextBoxType::FLOATCONTENT),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules2",*(new CRD(0,225,0)),110,wigth,height,(char*)to_string(angules[2]).c_str(),9,TextBoxType::FLOATCONTENT),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules3",*(new CRD(0,250,0)),110,wigth,height,(char*)to_string(angules[3]).c_str(),9,TextBoxType::FLOATCONTENT),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules4",*(new CRD(0,275,0)),110,wigth,height,(char*)to_string(angules[4]).c_str(),9,TextBoxType::FLOATCONTENT),ManejadorForms);
		ManejadorForms->Add(new TextBox("textBoxsSetAngules5",*(new CRD(0,300,0)),110,wigth,height,(char*)to_string(angules[5]).c_str(),9,TextBoxType::FLOATCONTENT),ManejadorForms);
		ManejadorForms->Add(new Button("buttonInitSetAngules",Type::BUTTONINITSETANGULES,*new CRD(0,325,0),0,1,0,80,10,wigth,height),ManejadorForms);
		ManejadorForms->Add(new Button("buttonCancelSetAngules",Type::BUTTONCANCELSETANGULES,*new CRD(80,325,0),1,0,0,30,10,wigth,height),ManejadorForms);
		SetAngules=true;
		break;
	case 3://Cancel setangules
		    default_menu(-5);
		break;

	case 0://inicializo botones para INIT CONNECTION
		  default_menu(-5);
		  ManejadorForms->Add(Interfaz(3),ManejadorForms);
		  default_menu(-6); 
	break;


	case 1://inicializo botonos para el STOP CONNECTION
		    ManejadorForms->Add(Interfaz(4),ManejadorForms);
			default_menu(-6);
	break;


	case -1://Inicio la conexion
		default_menu(-5);
		if(p->GetType()==ConnectionType::SERIAL_PORT)
		{
		   p=new PuertoSerie();
		}
		else if(p->GetType()==ConnectionType::TCP_IP_CLIENT)
			p=new TcP_ip_Client();
		if(!p->inicializa( ManejadorForms->GetForm("BoxInterfazConnections",ManejadorForms)->BoxGetEscritura("textBoxChar"),atol(ManejadorForms->GetForm("BoxInterfazConnections",ManejadorForms)->BoxGetEscritura("textBoxUnsigned"))))
		  {
			  string f=string(p->ErrorStr());
			   char*msg=new char[f.length()+1];
			   msg[f.length()]=0;
			   for(unsigned i=0;i<f.length();i++)
				   msg[i]=f[i]; 
			   messeng=new MeSSenger((char*)f.c_str(),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,5,1,0,0,2);
		   }
		else 
		   {
			   char*msg=p->GetMesage(p);
			   if(ModoLogger)cout<<endl<<p->getChar()<<"::"<<p->getunsigned()<<endl;
		      //add

			   StackAnimation*sa=new StackAnimation("StackAnimationsConnection");
			   sa->STANSetAnimation("AnimacionRoja",*new CRD(wigth-100,height-50,0),75,100,wigth,height,-25,1,0,0,1.5);
			   sa->STANSetAnimation("AnimacionVerde",*new CRD(wigth-100,height-50,0),75,100,wigth,height,0,0,1,0,1.5);
			   sa->STANSetAnimation("AnimacionAzul",*new CRD(wigth-100,height-50,0),75,100,wigth,height,25,0,0,1,1.5);
			   ManejadorForms->Add(sa,ManejadorForms);
			   ManejadorForms->MoveOnReshape("StackAnimationsConnection",true,ManejadorForms);


		       recibir_serie=true;
			   t1=new thread(ThreadCOM);
			   contMenuToDraw=-1;
			   messeng=new MeSSenger(msg,position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,0,1,0,2);
			   if(p->GetType()==ConnectionType::SERIAL_PORT)
		       {
				   toSaveCOM=new char[strlen(p->getChar())+1];
				   toSaveCOM[strlen(p->getChar())]=0;
				   for(unsigned i=0;i<strlen(p->getChar());i++)
					   toSaveCOM[i]=p->getChar()[i];
				   toSaveSpeed=p->getunsigned();
		       }
		       else if(p->GetType()==ConnectionType::TCP_IP_CLIENT)
			   {
				   toSaveIp=new char[strlen(p->getChar())+1];
				   toSaveIp[strlen(p->getChar())]=0;
				   for(unsigned i=0;i<strlen(p->getChar());i++)
					   toSaveIp[i]=p->getChar()[i];
				   toSavePort=p->getunsigned();
			   }
			   ESE_GRS::InitMenu();
			  }
	break;


	case -2://detengo la conexion 		  
		ManejadorForms->Sub("StackAnimationsConnection",ManejadorForms);
		recibir_serie=false;
		p->CloseConnection();
		ManejadorForms->Sub("labelCOM",ManejadorForms);
		ManejadorForms->Sub("labelSpeedCOM",ManejadorForms);
		ManejadorForms->Sub("labelRecib",ManejadorForms);
		ManejadorForms->SetColor("labelESE_GRS",(GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7,ManejadorForms);	
		EsperandoReedireccionar=true;
		ESE_GRS::InitMenu();
		default_menu(-5);
		if(ModoLogger)cout<<endl<<Frases(79)<<endl;
	break;
	case -5:    //Muestro Menu
		    default_menu(-7);
			ManejadorForms->SetDraw(false,"BoxInterfazPricipal",ManejadorForms);
			ManejadorForms->SetDraw(false,"BoxInterfazPricipalButtonAcept",ManejadorForms);
			ManejadorForms->SetDraw(false,"BoxInterfazPricipalButtonCancel",ManejadorForms);
		    InitMenu();
		break;

	case -6:	//Oculto Menu
			ManejadorForms->SetDraw(true,"BoxInterfazPricipal",ManejadorForms);
			ManejadorForms->SetDraw(true,"BoxInterfazPricipalButtonAcept",ManejadorForms);
			ManejadorForms->SetDraw(true,"BoxInterfazPricipalButtonCancel",ManejadorForms);
		    InitMenu();
		break;
	case -7:	//Oculto SetAngules
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
		   SetAngules=false;
		   }
		break;
	case -8:
		ModoLogger=false;
		InitMenu();
		break;
	case -9:
		ModoLogger=true;
		InitMenu();
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
	  messeng=new MeSSenger(Frases(50),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,3,1,0,0,2);
  }
glutPostRedisplay();//refresco y ejecuto el displayFunc()
}
void ESE_GRS::MenuPuertoSeie(int opcion){
	
		
}
void ESE_GRS::MenuIdioma(int opcion)
{
	switch (opcion)
	{
	case 0:
		idioma=Language::ENGLISH;
		break;
	case 1:
		idioma=Language::SPANISH;
		break;
	default:
		idioma=Language::ENGLISH;
		break;
	}
	messeng=new MeSSenger(Frases(62),position::CENTER_TOP,wigth,height,3,1,1,0,2);
	if(ModoLogger)cout<<Frases(66)<<endl;
	glutPostRedisplay();

}
///////////////////////// DATOS//////////////////////////////////////////////////
void ESE_GRS::recivirDatosCOM(){
	if(recibir_serie)
	   { 
		     /*COMANDOS
		     (7)-00000111->Redireccionar
			 (11)00001111->CambiarFocus de la caja
			 (15)00001011->Click al Focus
			 (19)00010011->AceptButton
			 (23)00010111->CancelButton
			 */
			
	      char*c=p->Recibir();//Recivo un dato
		  if(p->Error()&&recibir_serie)	 //Si algo dio error(Actualmente solo para conexiones TCP_IP)
			{
				if(ModoLogger)cout<<p->ErrorStr()<<endl;
				messeng=new MeSSenger(p->ErrorStr(),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,2,1,1,0,2);
				default_menu(-2);
				ManejadorForms->Add(Interfaz(0),ManejadorForms);
				ManejadorForms->Sub("BoxInterfazDetenerConnection",ManejadorForms);
	 	        ManejadorForms->Sub("BoxInterfazDetenerConnectionButtonAcept",ManejadorForms);
		        ManejadorForms->Sub("BoxInterfazDetenerConnectionButtonCancel",ManejadorForms);
		  		errInitMenubool=true;
				return;
		    }
		   if(c!=NULL)//si no esta vacio  
		     {
			  unsigned strleN=strlen(c);
			  c=Verificacion(c,&strleN); //Add y/o guado el error los errores arrasrtandos
		      for(unsigned i=0;i<strleN;i+=2)	//Un for por si llegan mas de 2 bytes
			  {
				contt++;
				if(ModoLogger)cout<<DataProcessor::printfBits(c[i+1])<<"-"<<DataProcessor::printfBits(c[i])<<"-["<<contt<<"]-";
				if(strleN/2>1)
					if(ModoLogger)cout<<"{"<<i/2+1<<"/"<<strleN/2<<"}"<<"("<<strleN<<")-";
				if(c[i]!=7)
				{
					if(contt%11==0&&!EsperandoReedireccionar)///////////VERIFICACION//////////
					{
						if(DataProcessor::BitData(c[i],0)==0||DataProcessor::BitData(c[i+1],0)==0)
						{
							if(ModoLogger)cout<<Frases(53)<<endl;
						if(contt>10000)
							contt=0;
						continue;
						}
						if(ModoLogger)cout<<Frases(55)<<endl;
						messeng=new MeSSenger(Frases(55),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,20,1,0,0,2);
						continue;
					}
	   				if(!EsperandoReedireccionar&&(DataProcessor::BitData(c[i],0)==0||DataProcessor::BitData(c[i+1],0)==0))	///////////VERIFICACION//////////
					{
						if(ModoLogger)cout<<Frases(54)<<endl;
						messeng=new MeSSenger(Frases(54),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,20,1,0,0,2);
						continue;
					}
				 }
				 if(DataProcessor::BitData(c[i],1)==1)////////////////////////////////////CODIGO//////////////////////////////
				 {
				     double*a;	
					 CRD*aa;
					 if(ModoLogger)cout<<Frases(56)<<(unsigned)c[i];
				     switch (c[i])
					 {
					   case 7://////////////////////////////REDIRECCIONAR////////////////////////////
							SpecialKeys(-1,0,0);
						    messeng=new MeSSenger(Frases(51),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,2,0,1,0,2);
						    EsperandoReedireccionar=false;
							if(ModoLogger)cout<<Frases(57);
							CalcularCoordenadas();
						    ShowAngules();
							Proyect1->ActualizaLastCood(cooRd,Proyect1); 
							if(interfaz==-5)
								Proyect1->ActualizaNewPlanoToCreate(cooRd,Proyect1,deFult);
							contt=0;
					   break;
					
					   case 11:  //////////////////////////////////Next Focus/////////////////////////
						   ManejadorForms->NextFocus("BoxInterfazPricipal",ManejadorForms);
						   if(ModoLogger)cout<<Frases(58);
					   break;			
					   case 15:   //////////////////////////////////Focus Click//////////////
						   a=ManejadorForms->FocusClick("BoxInterfazPricipal",ManejadorForms);
			               teclaRaton(GLUT_LEFT_BUTTON,GLUT_UP,(int)a[0],(int)a[1]);
						   if(ModoLogger)cout<<Frases(59);
					   break;
						   
					   case 19:  //////////////////////////////////Acept Button//////////////////////////
						   aa=ManejadorForms->GetForm("BoxInterfazPricipalButtonAcept",ManejadorForms)->GetCoord(ManejadorForms->GetForm("BoxInterfazPricipalButtonAcept",ManejadorForms));
			               teclaRaton(GLUT_LEFT_BUTTON,GLUT_UP,(int)aa->x,(int)aa->y);
						   if(ModoLogger)cout<<Frases(60);
			  	       break;

					   case 23://////////////////////////////////Cancel Button//////////////////////////
							aa=ManejadorForms->GetForm("BoxInterfazPricipalButtonCancel",ManejadorForms)->GetCoord(ManejadorForms->GetForm("BoxInterfazPricipalButtonCancel",ManejadorForms));
			                teclaRaton(GLUT_LEFT_BUTTON,GLUT_UP,(int)aa->x,(int)aa->y);
							if(ModoLogger)cout<<Frases(61);
					   break;

					   default:
						   if(ModoLogger)cout<<Frases(63);
					   break;
					 }
					 if(EsperandoReedireccionar)//PARA Q SE SEPA Q NO SE HA REDIRECCIONADO    
				     {
						 if(ModoLogger)cout<<Frases(64);
						 messeng=new MeSSenger(Frases(65),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,2,1,1,0,2);
					 }
			     }
				 else if(EsperandoReedireccionar)//PARA Q NO SE EJECUTE NADA HASTA Q NO SE REDIRECCIONE
				 {
					 messeng=new MeSSenger(Frases(65),position::CENTER_TOP,(GLfloat)wigth,(GLfloat)height,2,1,1,0,2);
					 if(ModoLogger)cout<<Frases(64);
				 }
			     else/////////////MOVER Y/O PINTAR
			     {
				    bool pintar=DataProcessor::PorcesarDatos(c[i],c[i+1],angules);//ejecuto la lectura de los bits y muevo los angulos(true es pintar)
		  	        CalcularCoordenadas();
			        ShowAngules();
					if(interfaz==2)//Actualizo la ultima coordenada en el StackBoceto
				       Proyect1->ActualizaLastCood(cooRd,Proyect1);
					else if(interfaz==-5)
						Proyect1->ActualizaNewPlanoToCreate(cooRd,Proyect1,deFult);
						 
					if(pintar) 
					{ 
					   if(interfaz==-1&&Proyect1->contNPl<3) //interfaz de Add new Boceto
					   {
						   Proyect1->AddPuntoNewPlano(cooRd,Proyect1);
						   ManejadorForms->Add(Interfaz(-1),ManejadorForms);
						   if(Proyect1->contNPl==3)
							   ManejadorForms->ActivateForm("BoxInterfazPricipalButtonAcept",ManejadorForms);
					   }
					   else if(interfaz==2)//Interfaz de Dibujo
				       {
				          ManejadorForms->GetForm("BoxInterfazPricipal",ManejadorForms)->BoxSetActivateDesactivate("RadioButtomCancelLast",true); 
						  Proyect1->AddPoint(*cooRd,Proyect1);
					   }
			        }//end if(pintar)		
			     }//end else
			     if(ModoLogger)cout<<"("<<tCOM.Incrementa(&tCOM)<<")"<<endl;
		         tCOM.ResettIncrementa(&tCOM);
		      }//end for
		   }//end if(!NULL)
	    }//end recivir serie	
}
void ESE_GRS::salvarInitDatos(){
   if(recibir_serie||!ManejadorObject->Salir)
      {
	   recibir_serie=false;
	   ManejadorObject->Salir=true;
	   p->CloseConnection();
	   t1->join();
      }
    recibir_serie=false;
	fstream f;
	f.open("ESE_GRS.onrn",ios::out|ios::binary);
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
	f.write((char*)&trasladarX,sizeof(double));
	f.write((char*)&trasladarY,sizeof(double));
	f.write((char*)&trasladarZ,sizeof(double));

	char*a=new char[strlen(toSaveCOM)+1];
	a[strlen(toSaveCOM)]=0;
	for(unsigned i=0;i<strlen(toSaveCOM);i++)
	   a[i]=toSaveCOM[i];
	unsigned b=strlen(a);
	f.write((char*)&b,sizeof(unsigned));
	f.write((char*)a,b);
	f.write((char*)&toSaveSpeed,sizeof(unsigned));
	a=new char[strlen(toSaveIp)+1];
	a[strlen(toSaveIp)]=0;
	for(unsigned i=0;i<strlen(toSaveIp);i++)
	   a[i]=toSaveIp[i];
	b=strlen(a);
	f.write((char*)&b,sizeof(unsigned));
	f.write((char*)a,b);
	f.write((char*)&toSavePort,sizeof(unsigned));
	f.write((char*)&idioma,sizeof(Language));
	f.close();
	DestruirVariablesGlobales();
}
void ESE_GRS::cargarInitDatos(){
	fstream f;
	f.open("ESE_GRS.onrn",ios::in|ios::binary);
	if(f.is_open())
	{
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
	   f.read((char*)&trasladarX,sizeof(double));
	   f.read((char*)&trasladarY,sizeof(double));
	   f.read((char*)&trasladarZ,sizeof(double));
	   char*a=new char[1024];
	   unsigned b=0,c=0;
	   char*d=new char[1024];
	   unsigned e=0,g=0;
	   f.read((char*)&b,sizeof(unsigned));
	   f.read(a,b);
	   a[b]=0;
	   f.read((char*)&c,sizeof(unsigned));

	   f.read((char*)&e,sizeof(unsigned));
	   f.read(d,e);
	   d[e]=0;
	    f.read((char*)&g,sizeof(unsigned));
		toSaveCOM=new char[strlen(a)+1];
		toSaveCOM[strlen(a)]=0;
		for(unsigned i=0;i<strlen(a);i++)
			toSaveCOM[i]=a[i];
		toSaveSpeed=c;
		toSaveIp=new char[strlen(d)+1];
		toSaveIp[strlen(d)]=0;
		for(unsigned i=0;i<strlen(d);i++)
			toSaveIp[i]=d[i];
		toSavePort=g;
	    CalcularCoordenadas();
		f.read((char*)&idioma,sizeof(Language));
	    f.close();
	}
	
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
		if(ModoLogger)cout<<"Guardado Correctamente:"<<c->c_str()<<endl;
	
	
}
char* ESE_GRS::Verificacion(char*c,unsigned*strleN){
	char*cc=new char[strlen(c)];
	cc[strlen(c)]=0;
	for(unsigned i=0;i<strlen(c);i++)
		cc[i]=c[i];
	unsigned RealStrleN=*strleN;
			  bool adjunt=false;
			  if(bytBool)
			         {
				     if(*strleN%2==0)
				        adjunt=true;
					 if(ModoLogger)cout<<"Se ha adjuntado {"<<DataProcessor::printfBits(byt)<<"} a {"<<DataProcessor::printfBits(cc[0])<<"}"<<endl;
					 char*newc=new char[*strleN+2];
				     newc[*strleN+1]=0;
					 newc[0]=cc[0];
				     newc[1]=byt;
				     for(unsigned i=1;i<*strleN;i++)
					     newc[i+1]=cc[i];
				     cc=newc;
				     *strleN=strlen(cc);
				     bytBool=false;
			        }
			  if((*strleN)%2!=0)
			       {
				     if(!bytBool)
				        {
						if(ModoLogger)cout<<"Cuidado,ha llegado "<<RealStrleN<<" bytes"<<(adjunt?"(+1)porque se ha adjuntado un elemento q estaba en espera,":",")<<"{"<<DataProcessor::printfBits(cc[*strleN-1])<<"}=>esperando a adjuntarse"<<endl;
						adjunt=false;
						byt=cc[*strleN-1];
				        cc[*strleN-1]=0;
				        *strleN=strlen(cc);
				        bytBool=true;
				        }
			       }
			  return cc;
}
void ESE_GRS::CalcularCoordenadas()
  {
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
	 
      cooRd->x=(463*senFi1)/200 + 150*cosFi1*cosFi2 - (1783*cosFi4*senFi1)/200 + 177*cosFi6*(senFi5*(cosFi1*cosFi2*senFi3 + cosFi1*cosFi3*senFi2) - cosFi5*(senFi1*senFi4 - cosFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3))) - 53*senFi1*senFi4 + 53*cosFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3) - (10329*cosFi5*(cosFi1*cosFi2*senFi3 + cosFi1*cosFi3*senFi2))/200 - (1783*senFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3))/200 + (senFi5*(cosFi1*cosFi2*senFi3 + cosFi1*cosFi3*senFi2))/500 - (cosFi5*(senFi1*senFi4 - cosFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3)))/500 - (10329*senFi5*(senFi1*senFi4 - cosFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3)))/200 + 177*senFi6*(cosFi4*senFi1 + senFi4*(cosFi1*cosFi2*cosFi3 - cosFi1*senFi2*senFi3)) + (451*cosFi1*cosFi2*cosFi3)/2 - (151*cosFi1*cosFi2*senFi3)/500 - (151*cosFi1*cosFi3*senFi2)/500 - (451*cosFi1*senFi2*senFi3)/2;
	  cooRd->y=(1783*cosFi1*cosFi4)/200 - (463*cosFi1)/200 + 150*cosFi2*senFi1 + 53*cosFi1*senFi4 + 53*cosFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3) - (10329*cosFi5*(cosFi2*senFi1*senFi3 + cosFi3*senFi1*senFi2))/200 + 177*cosFi6*(senFi5*(cosFi2*senFi1*senFi3 + cosFi3*senFi1*senFi2) + cosFi5*(cosFi1*senFi4 + cosFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3))) - (1783*senFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3))/200 + (senFi5*(cosFi2*senFi1*senFi3 + cosFi3*senFi1*senFi2))/500 + (cosFi5*(cosFi1*senFi4 + cosFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3)))/500 + (10329*senFi5*(cosFi1*senFi4 + cosFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3)))/200 - 177*senFi6*(cosFi1*cosFi4 - senFi4*(cosFi2*cosFi3*senFi1 - senFi1*senFi2*senFi3)) + (451*cosFi2*cosFi3*senFi1)/2 - (151*cosFi2*senFi1*senFi3)/500 - (151*cosFi3*senFi1*senFi2)/500 - (451*senFi1*senFi2*senFi3)/2;
	  cooRd->z=(151*senFi2*senFi3)/500 - (151*cosFi2*cosFi3)/500 - (451*cosFi2*senFi3)/2 - (451*cosFi3*senFi2)/2 - 150*senFi2 - 53*cosFi4*(cosFi2*senFi3 + cosFi3*senFi2) - (10329*cosFi5*(cosFi2*cosFi3 - senFi2*senFi3))/200 + (1783*senFi4*(cosFi2*senFi3 + cosFi3*senFi2))/200 + (senFi5*(cosFi2*cosFi3 - senFi2*senFi3))/500 + 177*cosFi6*(senFi5*(cosFi2*cosFi3 - senFi2*senFi3) - cosFi4*cosFi5*(cosFi2*senFi3 + cosFi3*senFi2)) - (10329*cosFi4*senFi5*(cosFi2*senFi3 + cosFi3*senFi2))/200 - 177*senFi4*senFi6*(cosFi2*senFi3 + cosFi3*senFi2) - (cosFi4*cosFi5*(cosFi2*senFi3 + cosFi3*senFi2))/500 + 437/10;
	  cooRd->z+=0.7;
  }
/////////////////////////THREADS//////////////////////////////////////////////////
void ESE_GRS::ThreadCOM()
{
	m.lock();
	while(recibir_serie&&p->EstaConectado())
	 recivirDatosCOM();
	m.unlock();

}
void ESE_GRS::ThreadCargObject()
{
	m.lock();
	ManejadorObject->pushByTxt("Entrada_de_Modelos.txt",ManejadorObject);//cargo el txt con las direcciones de los .obj
	CargObjct=true;
	ManejadorObject->Salir=true;
	system("cls");
	m.unlock();
}






				













