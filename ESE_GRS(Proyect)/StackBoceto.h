#pragma once
#include "Plano.h"
class StackBoceto{
public:
	Plano**bocetos;
	CRD*coord,*coorNewPlano;
	unsigned contNPl,cantB,contB,PlanoCheckeeado;
	bool draw;

	StackBoceto(){
		contB=contNPl=0;
		cantB=10;
		bocetos=new Plano*[cantB];
		bocetos[contB++]=new Plano("Boceto general");
		PlanoCheckeeado=0;
		coord=new CRD(0,0,0);
		coorNewPlano=new CRD[3];
		draw=true;
	};
	~StackBoceto(){delete []bocetos;};
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
		b->bocetos[b->PlanoCheckeeado]->Pintar_NoPintar_LineaSuspensiva(pintarNoPintar,b->bocetos[b->PlanoCheckeeado]);
	}
	static void ActualizaPinarLineasSuspensivas(CRD*coord,StackBoceto*b){
		b->coord=new CRD(*coord);
		if(b->BocetoActual(b)->cont-1==b->BocetoActual(b)->NewPoint[b->BocetoActual(b)->contNP-1]||b->BocetoActual(b)->cont-1==b->BocetoActual(b)->NewLine[b->BocetoActual(b)->contNP-1])
			b->BocetoActual(b)->Pintar_NoPintar_LineaSuspensiva(false,b->BocetoActual(b));
		else if(!b->BocetoActual(b)->PintLinSusp)
			b->BocetoActual(b)->Pintar_NoPintar_LineaSuspensiva(true,b->BocetoActual(b));
	}
	static void AddPoint(CRD coord,StackBoceto*b,bool NEWPOINT=false,bool NEWLINE=false){
		if(NEWPOINT||NEWLINE)
		{
		if(NEWLINE)
			b->bocetos[b->PlanoCheckeeado]->NewLINE(b->bocetos[b->PlanoCheckeeado]);
		if(NEWPOINT)
			b->bocetos[b->PlanoCheckeeado]->NewPOINT(b->bocetos[b->PlanoCheckeeado]);
		}
		  b->bocetos[b->PlanoCheckeeado]->add(&coord,b->bocetos[b->PlanoCheckeeado]);
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
		if(!b->PlanoCheckeeado)
		 for(unsigned i=0;i<b->contB;i++)
			 b->bocetos[i]->Draw(b->coord,b->bocetos[i]);
		else
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
			sb->coorNewPlano=new CRD[3];
			sb->coorNewPlano[sb->contNPl++]=*coord;
			break;
		case 1:
			sb->coorNewPlano[sb->contNPl++]=*coord;
			break;
		case 2:
			sb->coorNewPlano[sb->contNPl++]=*coord;
			break;
		}
		
	};
	static void ResetNewPlano(StackBoceto*sb){
		sb->contNPl=0;
	};
};