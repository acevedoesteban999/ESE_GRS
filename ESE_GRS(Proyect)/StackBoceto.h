#pragma once
#include "Plano.h"

class StackBoceto{
public:
	Plano**bocetos;
	CRD*coord,*coorNewPlano;
	TypePlano NewPlanoType;
	unsigned contNPl,cantB,contB,PlanoCheckeeado;
	bool draw,drawAll;
	StackBoceto(){
		contB=contNPl=0;
		cantB=10;
		bocetos=new Plano*[cantB];
		//bocetos[contB++]=new Plano("Principal Sketch");
		PlanoCheckeeado=0;
		coord=new CRD(0,0,0);
		coorNewPlano=new CRD[3];
		draw=true;
		drawAll=false;
		NewPlanoType=TypePlano::SPECIFICPLANE;
	};
	~StackBoceto(){};
	static void SetDrawAll(bool drawall,StackBoceto*sb){sb->drawAll=drawall;};
	static void Add(Plano*p,StackBoceto*b)
	{

		for(unsigned i=0;i<b->contB;i++)
			if(!strcmp(b->bocetos[i]->name,p->name))
				b->Sub(b->bocetos[i]->name,b);

		if(b->contB>=b->cantB)
		{
			Plano**Newp=new Plano*[b->cantB+10];
			b->cantB+=10;
			for(unsigned i=0;i<b->contB;i++)
				Newp[i]=b->bocetos[i];
			delete b->bocetos;
			b->bocetos=Newp;
		}
		b->bocetos[b->contB++]=p;
	
	
	}
	static void Pintar_NoPintar_LineaSuspensiva(bool pintarNoPintar,StackBoceto*b){
//		b->bocetos[b->PlanoCheckeeado]->Pintar_NoPintar_LineaSuspensiva(pintarNoPintar,b->bocetos[b->PlanoCheckeeado]);
	}
	static void ActualizaLastCood(CRD*coord,StackBoceto*b){
	b->coord=new CRD(*coord);
	if(b->contB)
	   b->BocetoActual(b)->ActualiWidthHeight(&Plano::CoordRestringida(b->coord,b->BocetoActual(b)),b->BocetoActual(b));
	}
	static void AddPoint(CRD coord,StackBoceto*b){
		b->BocetoActual(b)->add(&coord,b->BocetoActual(b));
	}
	static void Sub(char*name,StackBoceto*b)
	{
		for(int i=(int)b->contB-1;i>=0;i--)
		{
			if(!strcmp(name,b->bocetos[i]->name))
			{

				for(unsigned ii=i;ii<b->contB-1;ii++)
					b->bocetos[ii]=b->bocetos[ii+1];
				b->contB--;
				b->bocetos[b->contB]->~Plano();
				break;
			}
		}
	}
	static void Draw(StackBoceto*b,bool proyectpunt=false){
		if(b->contNPl)
		{
			glColor3f(1,1,1);
			glPointSize(4);
			glLineWidth(3);
			if(b->contNPl==1)
			{
			   glBegin(GL_POINTS);
				glVertex3f((GLfloat)b->coorNewPlano[0].x,(GLfloat)b->coorNewPlano[0].y,(GLfloat)b->coorNewPlano[0].z);
			}
			else
			{
			glBegin(GL_LINE_LOOP);
			for(unsigned i=0;i<b->contNPl;i++)
				glVertex3f((GLfloat)b->coorNewPlano[i].x,(GLfloat)b->coorNewPlano[i].y,(GLfloat)b->coorNewPlano[i].z);
			}
			glEnd();
			glPointSize(1);
			glLineWidth(1);
			
		}
		if(b->draw)
		{
		if(b->drawAll)
			 for(unsigned i=0;i<b->contB;i++)
				 b->bocetos[i]->Draw(b->coord,b->bocetos[i],false,false,true);
		else if(b->contB&&b->PlanoCheckeeado!=b->contB)
			b->bocetos[b->PlanoCheckeeado]->Draw(b->coord,b->bocetos[b->PlanoCheckeeado],true,proyectpunt);
		}
	};
	static void SetPlanoCheckeeado(unsigned plano,StackBoceto*b){
		b->PlanoCheckeeado=plano;
	};
	static Plano*BocetoActual(StackBoceto*sb){return sb->bocetos[sb->PlanoCheckeeado];};
	static void SetDraw(bool draw,StackBoceto*sb)
	{
		sb->draw=draw;
	}
	static void AddPuntoNewPlano(CRD*coord,StackBoceto*sb){
		switch (sb->contNPl)
		{
		case 0:
			sb->coorNewPlano=new CRD[4];
			sb->coorNewPlano[sb->contNPl++]=*coord;
			break;
		case 1:
			sb->coorNewPlano[sb->contNPl++]=*coord;
			break;
		case 2:
			sb->coorNewPlano[sb->contNPl++]=*coord;
			break;
		case 3:
			sb->coorNewPlano[sb->contNPl++]=*coord;
			break;
		}
		
	};
	static void ResetNewPlano(StackBoceto*sb){
		sb->contNPl=0;
	};
	static void AddNewType(TypePlano tp,StackBoceto*sb){sb->NewPlanoType=tp;};
	static void ActualizaNewPlanoToCreate(CRD*newCoorPlano,StackBoceto*sb,bool defAult)
	{
		
		for(unsigned i=0;i<sb->contNPl;i++)
		{
			switch (sb->NewPlanoType)
			{
				case TypePlano::XY:
					if(defAult==true)
					{
						switch (i)
						{
						case 0:
							sb->coorNewPlano[i].z=0;
							sb->coorNewPlano[i].x=200;
							sb->coorNewPlano[i].y=200;
							break;
						case 1:
							sb->coorNewPlano[i].z=0;
							sb->coorNewPlano[i].x=200;
							sb->coorNewPlano[i].y=-200;
							break;
						case 2:
							sb->coorNewPlano[i].z=0;
							sb->coorNewPlano[i].x=-200;	
							sb->coorNewPlano[i].y=-200;
							break;
						case 3:
							sb->coorNewPlano[i].z=0;
							sb->coorNewPlano[i].x=-200;
							sb->coorNewPlano[i].y=200;
							break;
						}
					}
					else
					{
						switch (i)
						{
						case 0:
							sb->coorNewPlano[i].z=newCoorPlano->z;
							sb->coorNewPlano[i].x=200+newCoorPlano->x;
							sb->coorNewPlano[i].y=200+newCoorPlano->y;
							break;
							
						case 1:
							sb->coorNewPlano[i].z=newCoorPlano->z;
							sb->coorNewPlano[i].x=200+newCoorPlano->x;
							sb->coorNewPlano[i].y=-200+newCoorPlano->y;
							break;
							
						case 2:
							sb->coorNewPlano[i].z=newCoorPlano->z;
							sb->coorNewPlano[i].x=-200+newCoorPlano->x;
							sb->coorNewPlano[i].y=-200+newCoorPlano->y;
							break;
							
						case 3:
							sb->coorNewPlano[i].z=newCoorPlano->z;
							sb->coorNewPlano[i].x=-200+newCoorPlano->x;
							sb->coorNewPlano[i].y=200+newCoorPlano->y;
							break;
						}
						
					}
				break;
				case TypePlano::XZ:
					if(defAult==true)
					{
						switch (i)
						{
						case 0:
							sb->coorNewPlano[i].y=0;
							sb->coorNewPlano[i].x=200;
							sb->coorNewPlano[i].z=200;
							break;
						case 1:
							sb->coorNewPlano[i].y=0;
							sb->coorNewPlano[i].x=200;
							sb->coorNewPlano[i].z=-200;
							break;
						case 2:
							sb->coorNewPlano[i].y=0;
							sb->coorNewPlano[i].x=-200;	
							sb->coorNewPlano[i].z=-200;
							break;
						case 3:
							sb->coorNewPlano[i].y=0;
							sb->coorNewPlano[i].x=-200;
							sb->coorNewPlano[i].z=200;
							break;
						}
					}
					else
					{
						switch (i)
						{
						case 0:
							sb->coorNewPlano[i].y=newCoorPlano->y;
							sb->coorNewPlano[i].x=200+newCoorPlano->x;
							sb->coorNewPlano[i].z=200+newCoorPlano->z;
							break;
							
						case 1:
							sb->coorNewPlano[i].y=newCoorPlano->y;
							sb->coorNewPlano[i].x=200+newCoorPlano->x;
							sb->coorNewPlano[i].z=-200+newCoorPlano->z;
							break;
							
						case 2:
							sb->coorNewPlano[i].y=newCoorPlano->y;
							sb->coorNewPlano[i].x=-200+newCoorPlano->x;
							sb->coorNewPlano[i].z=-200+newCoorPlano->z;
							break;
							
						case 3:
							sb->coorNewPlano[i].y=newCoorPlano->y;
							sb->coorNewPlano[i].x=-200+newCoorPlano->x;
							sb->coorNewPlano[i].z=200+newCoorPlano->z;
							break;
						}
						
					}
					/*if(defAult==true)
					{
						sb->coorNewPlano[i].y=0;
						sb->coorNewPlano[i].x=200;
						sb->coorNewPlano[i].z=200;
					}
					else
					{
						sb->coorNewPlano[i].y=newCoorPlano->y;
						sb->coorNewPlano[i].x=200+newCoorPlano->x;
						sb->coorNewPlano[i].z=200+newCoorPlano->z;
					}*/
				break;
				case TypePlano::YZ:
					if(defAult==true)
					{
						switch (i)
						{
						case 0:
							sb->coorNewPlano[i].x=0;
							sb->coorNewPlano[i].y=200;
							sb->coorNewPlano[i].z=200;
							break;
						case 1:
							sb->coorNewPlano[i].x=0;
							sb->coorNewPlano[i].y=200;
							sb->coorNewPlano[i].z=-200;
							break;
						case 2:
							sb->coorNewPlano[i].x=0;
							sb->coorNewPlano[i].y=-200;	
							sb->coorNewPlano[i].z=-200;
							break;
						case 3:
							sb->coorNewPlano[i].x=0;
							sb->coorNewPlano[i].y=-200;
							sb->coorNewPlano[i].z=200;
							break;
						}
					}
					else
					{
						switch (i)
						{
						case 0:
							sb->coorNewPlano[i].x=newCoorPlano->x; 
							sb->coorNewPlano[i].y=200+newCoorPlano->y;
							sb->coorNewPlano[i].z=200+newCoorPlano->z;
							break;
							
						case 1:
							sb->coorNewPlano[i].x=newCoorPlano->x;
							sb->coorNewPlano[i].y=200+newCoorPlano->y;
							sb->coorNewPlano[i].z=-200+newCoorPlano->z;
							break;
							
						case 2:
							sb->coorNewPlano[i].x=newCoorPlano->x;
							sb->coorNewPlano[i].y=-200+newCoorPlano->y;
							sb->coorNewPlano[i].z=-200+newCoorPlano->z;
							break;
							
						case 3:
							sb->coorNewPlano[i].x=newCoorPlano->x;
							sb->coorNewPlano[i].y=-200+newCoorPlano->y;
							sb->coorNewPlano[i].z=200+newCoorPlano->z;
							break;
						}
						
					}
					/*if(defAult==true)
					{
						sb->coorNewPlano[i].x=0;
						sb->coorNewPlano[i].y=200;
						sb->coorNewPlano[i].z=200;
					}
					else
					{
						sb->coorNewPlano[i].x=newCoorPlano->x;
						sb->coorNewPlano[i].y=200+newCoorPlano->y;
						sb->coorNewPlano[i].z=200+newCoorPlano->z;
					}*/
				break;
			}
		}
		
	}
};