#pragma once
#include "CRD.h"
#include <math.h>
#include "Items.h"
class Plano
{
public:
	Items**items;
	unsigned contItems,cantItems;
	char*name;
	bool NewItem;
	ItemsType NextitType;
	CRD*PuntoCentro;
	CRD*PuntosCrearPlano;
	CRD*puNt1,*puNt2,*puNt3,*puNt4;
	float distmax,trasladarplano;
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
	  contItems=0;
	  cantItems=100;
	  items=new Items*[cantItems];
	  NewItem=true;
	  trasladarplano=0;
	};
	Plano(char*name,CRD*Punt1,CRD*Punt2,CRD*Punt3,bool restring=false){
		contItems=0;
		cantItems=100;
		items=new Items*[cantItems];
		NewItem=true;
		trasladarplano=0;
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
	~Plano(void){};
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
	static void add(CRD*vertex,Plano*p,bool BocetoGeneral=false){
		//if(p->RestringirAlPlano)
		//{
		//	Sistema_Cartesiano::add(CoordRestringida(vertex,p),p);
		//	p->ActualiWidthHeight(&CoordRestringida(vertex,p),p);
		//}
		//else
		//  Sistema_Cartesiano::add(*vertex,p);
		
		
		
		if(p->NewItem)
		{
			p->NewItem=false;
			p->contItems++;
			if(p->contItems>=p->cantItems)
			{
				Items**newItems=new Items*[p->cantItems+100];
				p->cantItems+=100;
				for(unsigned i=0;i<p->contItems;i++)
					newItems[i]=p->items[i];
				delete[] p->items;
				p->items=newItems;
			}
		   
		   switch (p->NextitType)
		   {
		    case ItemsType::POINTSS:
			   p->items[p->contItems-1]=new Points();
			break;
		    case ItemsType::LINE_STRIP:
			   p->items[p->contItems-1]=new Strip_Line();
			break;
		   }
		}
		if(BocetoGeneral)
			  p->items[p->contItems-1]->Add(vertex);
		else
		   p->items[p->contItems-1]->Add(&Plano::CoordRestringida(vertex,p));
	};
	static void Draw(CRD*cooRd,Plano*p,bool pintarPlano=false,bool proyectpunt=false,bool BocetoGenral=false){
		if(p->RestringirAlPlano&&pintarPlano&&p->pintarPlano)
		{
		glColor3f((GLfloat)0.5,(GLfloat)0.5,(GLfloat)0.5);
		glBegin(GL_QUAD_STRIP);
		glVertex3f((GLfloat)p->puNt1->x+p->trasladarplano,(GLfloat)p->puNt1->y+p->trasladarplano,(GLfloat)p->puNt1->z+p->trasladarplano);
		glVertex3f((GLfloat)p->puNt2->x+p->trasladarplano,(GLfloat)p->puNt2->y+p->trasladarplano,(GLfloat)p->puNt2->z+p->trasladarplano);
		glVertex3f((GLfloat)p->puNt3->x+p->trasladarplano,(GLfloat)p->puNt3->y+p->trasladarplano,(GLfloat)p->puNt3->z+p->trasladarplano);
		glVertex3f((GLfloat)p->puNt4->x+p->trasladarplano,(GLfloat)p->puNt4->y+p->trasladarplano,(GLfloat)p->puNt4->z+p->trasladarplano);
		glEnd();
		glColor3f((GLfloat)0.7,(GLfloat)0.7,(GLfloat)0.7);
		glBegin(GL_LINES);
		glVertex3f((GLfloat)p->PuntoCentro->x+(GLfloat)p->A/10,(GLfloat)p->PuntoCentro->y+(GLfloat)p->B/10,(GLfloat)p->PuntoCentro->z+(GLfloat)p->C/10);
		glVertex3f((GLfloat)p->PuntoCentro->x-(GLfloat)p->A/10,(GLfloat)p->PuntoCentro->y-(GLfloat)p->B/10,(GLfloat)p->PuntoCentro->z-(GLfloat)p->C/10);
		glEnd();
		
		}
		if(proyectpunt)
		{
			glPointSize(2);
			glColor3f(0,1,0);
	        CRD puntVerd=p->CoordRestringida(cooRd,p);
	        glBegin(GL_POINTS);
  	          glVertex3f((GLfloat)puntVerd.x,(GLfloat)puntVerd.y,(GLfloat)puntVerd.z);
		    glEnd();
		    glPointSize(1);
			if(p->contItems&&!p->NewItem)
			{
			   if(p->items[p->contItems-1]->t==ItemsType::LINE_STRIP)
			   {
				  
				  glLineWidth(2);
			      glColor3f(0,1,0);
			      glBegin(GL_LINES);
	              double a,b,c,d,e,f;
			      a=p->items[p->contItems-1]->PoIntS[p->items[p->contItems-1]->cont-1].x;
	              b=p->items[p->contItems-1]->PoIntS[p->items[p->contItems-1]->cont-1].y;
	              c=p->items[p->contItems-1]->PoIntS[p->items[p->contItems-1]->cont-1].z;
	              d=p->CoordRestringida(cooRd,p).x-a;
	              e=p->CoordRestringida(cooRd,p).y-b;
	              f=p->CoordRestringida(cooRd,p).z-c;
	    	      for(unsigned i=0;i<=9;i++)
	                 glVertex3f((GLfloat)(a+i*(d/9)),(GLfloat)(b+i*(e/9)),(GLfloat)(c+i*(f/9)));
			      glEnd();
				   glLineWidth(1);
			   }
			}
		 }
		if(BocetoGenral)
		{
		if(p->contItems&&!p->NewItem)
			{
			if(p->items[p->contItems-1]->t==ItemsType::LINE_STRIP)
			   {
				  
				  glLineWidth(2);
			      glColor3f(1,1,1);
			      glBegin(GL_LINES);
	              double a,b,c,d,e,f;
			      a=p->items[p->contItems-1]->PoIntS[p->items[p->contItems-1]->cont-1].x;
	              b=p->items[p->contItems-1]->PoIntS[p->items[p->contItems-1]->cont-1].y;
	              c=p->items[p->contItems-1]->PoIntS[p->items[p->contItems-1]->cont-1].z;
				  d=cooRd->x-a;
	              e=cooRd->y-b;
	              f=cooRd->z-c;
	    	      for(unsigned i=0;i<=9;i++)
	                 glVertex3f((GLfloat)(a+i*(d/9)),(GLfloat)(b+i*(e/9)),(GLfloat)(c+i*(f/9)));
			      glEnd();
				   glLineWidth(1);
			   }
		   }
		}

		//Sistema_Cartesiano::Draw(cooRd,p,p->RestringirAlPlano,p->RestringirAlPlano?&Plano::CoordRestringida(cooRd,p):new CRD(0,0,0),proyectpunt);
	  	for(unsigned i=0;i<p->contItems;i++)
		  p->items[i]->Draw();
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
	a[0]=CRD(p->CoordRestringida(new CRD(p->PuntoCentro->x+p->distmax+50,p->PuntoCentro->y,p->PuntoCentro->z),p));
	a[1]=CRD(p->CoordRestringida(new CRD(p->PuntoCentro->x,p->PuntoCentro->y+p->distmax+50,p->PuntoCentro->z),p));
	a[2]=CRD(p->CoordRestringida(new CRD(p->PuntoCentro->x,p->PuntoCentro->y,p->PuntoCentro->z+p->distmax+50),p));
	unsigned mayor=0,mediano=0;
	for(unsigned i=0;i<3;i++)
	{
		float nor=Plano::Norma(&a[i]);
		if(nor>=Plano::Norma(&a[mayor]))
			mayor=i;
		/*else if(nor>=Plano::Norma(&a[mediano]))
			mediano=i;*/
	}
	mediano=mayor==0?1:0;
	for(unsigned i=0;i<3;i++)
	{
		if(i==mayor)
			continue;
		float nor=Plano::Norma(&a[i]);
		if(nor>=Plano::Norma(&a[mediano]))
			mediano=i;
	}
	vectorAltura=a[mayor]-*p->PuntoCentro;
	vectorAncho=a[mediano]-*p->PuntoCentro;
	p->puNt1=new CRD(*p->PuntoCentro+vectorAltura+vectorAncho);
	p->puNt2=new CRD(*p->PuntoCentro+vectorAltura-vectorAncho);
	p->puNt3=new CRD(*p->PuntoCentro+(vectorAltura*-1)+vectorAncho);
	p->puNt4=new CRD(*p->PuntoCentro+(vectorAltura*-1)-vectorAncho);
	}
	static void ActualizaItem(ItemsType it,Plano*p)
	{
	p->NextitType=it;
	p->NewItem=true;
	}
	static void verPlanoRotado(float cant,Plano*p)
	{
		 p->trasladarplano=cant;
	}
	static void CancelLastPoint(Plano*p){
		if(p->contItems==0)
		{
			p->NewItem=true;
			return;
		}
		if(p->items[p->contItems-1]->cont==0)
		{
			p->contItems--;
			if(p->contItems==0)
			   p->NewItem=true;
		}
		p->items[p->contItems-1]->cont--;
	}
    
};

