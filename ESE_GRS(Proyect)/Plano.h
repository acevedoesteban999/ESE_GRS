#pragma once
#include "CRD.h"
#include <math.h>
#include "Sistema_Cartesiano.h"
class Plano:public Sistema_Cartesiano
{
public:
	char*name;
	CRD*PuntoCentro;
	CRD*PuntosCrearPlano;
	CRD*puNt1,*puNt2,*puNt3,*puNt4;
	float distmax;
	double A,B,C,D;//Secuencia Ax+By+Cz+D=0
	bool RestringirAlPlano,pintarPlano;
	Plano(char*name){
		pintarPlano=true;
	 this->name=new char[strlen(name)+1];
		this->name[strlen(name)]=0;
		for(unsigned i=0;i<strlen(name);i++)
			this->name[i]=name[i];
	  PuntoCentro=new CRD;
	  PuntosCrearPlano=new CRD[4];
	  RestringirAlPlano=false;
	};
	Plano(char*name,CRD*Punt1,CRD*Punt2,CRD*Punt3,bool restring=false){
		pintarPlano=true;
		PuntosCrearPlano=new CRD[4];
		CRD vectorA,vectorB,vectorProyect,vectorC,vectorD;
		CRD pnt4,puntofinal;
		vectorD=*Punt2-*Punt1;
		//PuntosCrearPlano[0]=Punt1;
		PuntosCrearPlano[1]=*Punt2+vectorD;
		vectorD=*Punt3-*Punt2;
		PuntosCrearPlano[2]=*Punt3+vectorD;
		vectorA=*Punt3-*Punt1;
        vectorB=*Punt2-*Punt1;
		double a_punt_b=vectorA.x*vectorB.x+vectorA.y*vectorB.y+vectorA.z*vectorB.z;
		double long_a=sqrt(pow(vectorA.x,2)+pow(vectorA.y,2)+pow(vectorA.z,2));
		vectorProyect=vectorA*(a_punt_b/pow(long_a,2));
		pnt4=*Punt1+vectorProyect;
		vectorC=pnt4-*Punt2;
		vectorC=vectorC*2;
		puntofinal=*Punt2+vectorC;
		vectorD=puntofinal-*Punt3;
		PuntosCrearPlano[3]=puntofinal+vectorD;
		vectorD=*Punt1-puntofinal;
		PuntosCrearPlano[0]=*Punt1+vectorD;
		
		
		this->name=new char[strlen(name)+1];
		this->name[strlen(name)]=0;
		for(unsigned i=0;i<strlen(name);i++)
			this->name[i]=name[i];
		RestringirAlPlano=restring;
		PuntoCentro=new CRD((*Punt1+*Punt2+*Punt3)/3);
	CRD v1,v2;
	double d1,d2,d3,d4,d5,d6;
	v1.x=Punt1->x-Punt2->x;
	v1.y=Punt1->y-Punt2->y;
	v1.z=Punt1->z-Punt2->z;
	v2.x=Punt1->x-Punt3->x;
	v2.y=Punt1->y-Punt3->y;
	v2.z=Punt1->z-Punt3->z;
	d1=v1.y*v2.z;
	d2=v1.z*v2.y;
	d3=v1.x*v2.z;
	d4=v1.z*v2.x;
	d5=v1.x*v2.y;
	d6=v1.y*v2.x;
	this->A=d1-d2;
	this->B=-(d3-d4);
	this->C=d5-d6;
	this->D=-(A*PuntoCentro->x+B*PuntoCentro->y+C*PuntoCentro->z);
	if(A<0)
	{
	A*=-1;
	B*=-1;
	C*=-1;
	D*=-1;
	}
	while((A>100||A<-100)||(B>100||B<-100)||(C>100||C<-100))
	{
		A/=10;
		B/=10;
		C/=10;
		D/=10;
	}
	distmax=100;
	Plano::ActualiWidthHeight(Punt1,this);
	Plano::ActualiWidthHeight(Punt2,this);
	Plano::ActualiWidthHeight(Punt3,this);

	
};
	~Plano(void){
		delete PuntoCentro;
	};
	static CRD Distncia(CRD*punt,Plano*p){
	CRD puntPlano,V;
	double A=p->A,B=p->B,C=p->C,D=p->D;
	double t=(-D-A*punt->x-B*punt->y-C*punt->z)/(A*A+B*B+C*C);//calculo el parametro t como la inteseccion de la recta creada por le punot y la normal del plano y el plano
	puntPlano.x=punt->x+A*t;//calculo la coordenada x el punto de interseccion entre la recta y el plano
	puntPlano.y=punt->y+B*t;//calculo la coordenada y el punto de interseccion entre la recta y el plano
	puntPlano.z=punt->z+C*t;//calculo la coordenada z el punto de interseccion entre la recta y el plano
	//hallo el vector 
	V.x=puntPlano.x-punt->x;
	V.y=puntPlano.y-punt->y;
	V.z=puntPlano.z-punt->z;
	//calculo la norma	
	double norma=sqrt(V.x*V.x+V.y*V.y+V.z*V.z);
	return V;

};
	static double DistnciaReal(CRD*punt,Plano*p){
    double denomin=sqrt((p->A*p->A)+(p->B*p->B)+(p->C*p->C));
	double real=(p->A*punt->x+p->B*punt->y+p->C*punt->z+p->D)/denomin;
	return real;
};
	static CRD CoordRestringida(CRD*coord,Plano*p)
	{
		CRD a(*coord),b(Distncia(coord,p));
		a.x+=b.x;
		a.y+=b.y;
		a.z+=b.z;
		return a;
	}
	static void add(CRD*vertex,Plano*p){
		if(p->RestringirAlPlano)
		{
			Sistema_Cartesiano::add(CoordRestringida(vertex,p),p);
			p->ActualiWidthHeight(&CoordRestringida(vertex,p),p);
		}
		else
		   Sistema_Cartesiano::add(*vertex,p);
	};
	static void Draw(CRD*cooRd,Plano*p,bool pintarPlano=false,bool proyectpunt=false){
		if(p->RestringirAlPlano&&pintarPlano&&p->pintarPlano)
		{
		
	//	punt1=Plano::CoordRestringida(punt1,p);
	//	punt2=Plano::CoordRestringida(punt2,p);
	//	punt3=Plano::CoordRestringida(punt3,p);
	//	punt4=Plano::CoordRestringida(punt4,p);

		glColor3f((GLfloat)0.5,(GLfloat)0.5,(GLfloat)0.5);
		glBegin(GL_QUAD_STRIP);
		glVertex3f((GLfloat)p->puNt1->x,(GLfloat)p->puNt1->y,(GLfloat)p->puNt1->z);
		glVertex3f((GLfloat)p->puNt2->x,(GLfloat)p->puNt2->y,(GLfloat)p->puNt2->z);
		glVertex3f((GLfloat)p->puNt3->x,(GLfloat)p->puNt3->y,(GLfloat)p->puNt3->z);
		glVertex3f((GLfloat)p->puNt4->x,(GLfloat)p->puNt4->y,(GLfloat)p->puNt4->z);
		glEnd();
		glColor3f((GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);
		glBegin(GL_LINES);
		glVertex3f((GLfloat)p->PuntoCentro->x+(GLfloat)p->A/10,(GLfloat)p->PuntoCentro->y+(GLfloat)p->B/10,(GLfloat)p->PuntoCentro->z+(GLfloat)p->C/10);
		glVertex3f((GLfloat)p->PuntoCentro->x-(GLfloat)p->A/10,(GLfloat)p->PuntoCentro->y-(GLfloat)p->B/10,(GLfloat)p->PuntoCentro->z-(GLfloat)p->C/10);
		glEnd();
		/*
		b=new CRD(p->CoordRestringida(*new CRD(100,100,-100),p));
		
		c=new CRD(p->CoordRestringida(*new CRD(100,-100,100),p));
		
		d=new CRD(p->CoordRestringida(*new CRD(100,-100,-100),p));
		
		e=new CRD(p->CoordRestringida(*new CRD(-100,100,100),p));
			
		f=new CRD(p->CoordRestringida(*new CRD(-100,100,-100),p));
		
		g=new CRD(p->CoordRestringida(*new CRD(-100,-100,100),p));

		h=new CRD(p->CoordRestringida(*new CRD(-100,-100,-100),p));
		

		glVertex3f((GLfloat)a->x,(GLfloat)a->y,(GLfloat)a->z);
		glVertex3f((GLfloat)b->x,(GLfloat)b->y,(GLfloat)b->z);
		glVertex3f((GLfloat)c->x,(GLfloat)c->y,(GLfloat)c->z);
		glVertex3f((GLfloat)d->x,(GLfloat)d->y,(GLfloat)d->z);
		glVertex3f((GLfloat)e->x,(GLfloat)e->y,(GLfloat)e->z);
		glVertex3f((GLfloat)f->x,(GLfloat)f->y,(GLfloat)f->z);
		glVertex3f((GLfloat)g->x,(GLfloat)g->y,(GLfloat)g->z);
		glVertex3f((GLfloat)h->x,(GLfloat)h->y,(GLfloat)h->z);

		glColor3f((GLfloat)1,(GLfloat)0,(GLfloat)0);
		glVertex3f(100,100,100);
		glVertex3f(100,100,-100);
		glVertex3f(100,-100,100);
		glVertex3f(100,-100,-100);
		glVertex3f(-100,100,100);
		glVertex3f(-100,100,-100);
		glVertex3f(-100,-100,100);
		glVertex3f(-100,-100,-100);
		glEnd();
		glColor3f((GLfloat)0.5,(GLfloat)0.5,(GLfloat)0.5);*/
		/*for(unsigned i=0;i<4;i++)
		  glVertex3f((GLfloat)p->PuntosCrearPlano[i].x,(GLfloat)p->PuntosCrearPlano[i].y,(GLfloat)p->PuntosCrearPlano[i].z);
		//glVertex3f((GLfloat)p->PuntosCrearPlano[0].x,(GLfloat)p->PuntosCrearPlano[0].y,(GLfloat)p->PuntosCrearPlano[0].z);
		glVertex3f((GLfloat)p->PuntosCrearPlano[1].x,(GLfloat)p->PuntosCrearPlano[1].y,(GLfloat)p->PuntosCrearPlano[1].z);
		//glVertex3f((GLfloat)p->PuntosCrearPlano[2].x,(GLfloat)p->PuntosCrearPlano[2].y,(GLfloat)p->PuntosCrearPlano[2].z);
		glEnd();
		glColor3f(1,1,0);
		glBegin(GL_LINES);
		glVertex3f(p->PuntoCentro->x,p->PuntoCentro->y,p->PuntoCentro->z);
		glVertex3f(p->PuntoCentro->x+p->A/100,p->PuntoCentro->y+p->B/100,p->PuntoCentro->z+p->C/100);
		glVertex3f(p->PuntoCentro->x,p->PuntoCentro->y,p->PuntoCentro->z);
		glVertex3f(p->PuntoCentro->x-p->A/100,p->PuntoCentro->y-p->B/100,p->PuntoCentro->z-p->C/100);
		glEnd();
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex3f(p->PuntoCentro->x+p->A/100,p->PuntoCentro->y+p->B/100,p->PuntoCentro->z+p->C/100);
		glVertex3f(p->PuntoCentro->x-p->A/100,p->PuntoCentro->y-p->B/100,p->PuntoCentro->z-p->C/100);
		glEnd();
		glPointSize(1);
		*/
		}
		Sistema_Cartesiano::Draw(cooRd,p,p->RestringirAlPlano,p->RestringirAlPlano?&Plano::CoordRestringida(cooRd,p):new CRD(0,0,0),proyectpunt);
	}
	static char*EcucaionPlano(Plano*p){
		string s;
		char*a;
		s=to_string(p->A)+"A"+(p->B>0?"+":"")+to_string(p->B)+"B"+(p->C>0?"+":"")+to_string(p->C)+"D";
		a=new char[s.length()+1];
		a[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			a[i]=s[i];
		return a;
	};
	static CRD*AngulosDirectores(CRD*vect,Plano*p){
	CRD*f=new CRD;
	float norma=Plano::Norma(vect);
	if(!norma)
		return new CRD(0,0,0);
	f->x=(float)(acos(vect->x/norma)*180/PI);
	f->y=(float)(acos(vect->y/norma)*180/PI);
	f->z=(float)(acos(vect->z/norma)*180/PI);
	return f;
	}
	static float AngEntreVectores(CRD*vect1,CRD*vect2)
	{
		float prodpunt=(float)(vect1->x*vect2->x+vect1->y*vect2->y+vect1->z*vect2->z);
		float prodnorma=(float)(sqrt(pow(vect1->x,2)+pow(vect1->y,2)+pow(vect1->z,2))*sqrt(pow(vect2->x,2)+pow(vect2->y,2)+pow(vect2->z,2)));
		if(prodnorma==0)
			prodnorma=1;
		float cosang=(float)(prodpunt/prodnorma);
		float ang=(float)(acos(cosang)*180/PI);
		return ang;
	}
	static CRD* RotarAlPlano(Plano*p){
		CRD*vect=new CRD(p->A,p->B,p->C);
		CRD *Toreturn=new CRD(*p->AngulosDirectores(vect,p));
		Plano plxy("xy",new CRD(1,0,0),new CRD(0,1,0),new CRD(0,0,0));
		CRD proyxy=plxy.CoordRestringida(vect,&plxy);
		float angproyecxyvectnorm=Plano::AngEntreVectores(vect,&proyxy);
		CRD*angsxy=plxy.AngulosDirectores(&proyxy,&plxy);
		Toreturn->x=90-angproyecxyvectnorm;
		Toreturn->y=0;
		Toreturn->z=angsxy->y;
		return Toreturn;
	}
	static float Norma(CRD*vect)
	{
		return (float)sqrt(pow(vect->x,2)+pow(vect->y,2)+pow(vect->z,2));
	}
	static float Distncia(CRD*punt1,CRD*punt2)
	{
		float toReturn=(float)sqrt(pow(punt1->x-punt2->x,2)+pow(punt1->y-punt2->y,2)+pow(punt1->z-punt2->z,2));
		return toReturn;
	}
	static void ActualiWidthHeight(CRD*punt,Plano*p){
	float dist=Plano::Distncia(p->PuntoCentro,punt);
	if(dist>p->distmax+50)
		p->distmax=dist;
	CRD*a=new CRD[3],vectorAltura,vectorAncho;
	a[0]=CRD(p->CoordRestringida(new CRD(p->PuntoCentro->x+p->distmax+100,p->PuntoCentro->y,p->PuntoCentro->z),p));
	a[1]=CRD(p->CoordRestringida(new CRD(p->PuntoCentro->x,p->PuntoCentro->y+p->distmax+100,p->PuntoCentro->z),p));
	a[2]=CRD(p->CoordRestringida(new CRD(p->PuntoCentro->x,p->PuntoCentro->y,p->PuntoCentro->z+p->distmax+100),p));
	unsigned mayor=2,mediano=1;
	for(unsigned i=0;i<3;i++)
	{
		float nor=Plano::Norma(&a[i]);
		if(nor>=Plano::Norma(&a[mayor]))
			mayor=i;
		else if(nor>=Plano::Norma(&a[mediano]))
			mediano=i;
	}
	vectorAltura=a[mayor]-*p->PuntoCentro;
	vectorAncho=a[mediano]-*p->PuntoCentro;
	
	p->puNt1=new CRD(*p->PuntoCentro+vectorAltura+vectorAncho);
	p->puNt2=new CRD(*p->PuntoCentro+vectorAltura-vectorAncho);
	p->puNt3=new CRD(*p->PuntoCentro+(vectorAltura*-1)+vectorAncho);
	p->puNt4=new CRD(*p->PuntoCentro+(vectorAltura*-1)-vectorAncho);





	}
    
};

