#pragma once
#include <fstream>
#include "GL\freeglut.h"
#include"CRD.h"
using namespace std;
class IGSClass
{
private:
	unsigned S,G,D,P,ContDs,ContPs,LastD,LastP;
	CRD*puntoRestriccion;
public:
	CRD*Vertex;
	unsigned*NewLine,*NewPoint;
	unsigned cant,cont,cantNL,contNL,cantNP,contNP;
	IGSClass(void)
{
	S=G=D=P=LastP=ContDs=ContPs=LastD=cont=contNL=contNP=0;
	cant=100;
	cantNL=cantNP=100;
	Vertex=new CRD[cant]; 
	NewLine=new unsigned[cantNL];
	NewPoint=new unsigned[cantNP];
};
	~IGSClass(){};
	static void Draw(bool PintLinSusp,unsigned RadioButtonCant,CRD*cooRd,IGSClass*igs){
	if(igs->cont)
	   {
        glColor3f(1,1,1);
	    for(unsigned RBC=0;RBC<RadioButtonCant;RBC++)
	       switch (RBC)
	        {
	      case 0://Puntos
			  glPointSize(3);
	          glBegin(GL_POINTS);
			  for(unsigned i=0;i<igs->cont;i++)//PUNTOS//Siempre pinto todos los puntos
	             {
			     glVertex3f((GLfloat)igs->Vertex[i].x,(GLfloat)igs->Vertex[i].y,(GLfloat)igs->Vertex[i].z);
	             }
	          glEnd();
	      case 1://Lineas
			  glPointSize(3);
		     glBegin(GL_LINE_STRIP);
	         for(unsigned i=0;i<igs->cont;i++)//LINEAS
	           {
				   bool contin=false;
				   for(unsigned ii=0;ii<igs->contNP;ii++)//si ese vetice es solo un punto
				   {
					   if(igs->NewPoint[ii]==i)
			           {
						   contin=true;
						   break;
				       }
				   
				   }
				   if(contin)//si era un punto subo al siguinete elemento del for
					   continue;
		        for(unsigned ii=0;ii<igs->contNL;ii++)//si este vertice es una nueva linea
		           {
			         if(igs->NewLine[ii]==i)
			           {
				        glEnd();//cambio a line strip de nuevo para q no cuente el ultimo elemento por donde va el for del arreglo de vertices
				        glBegin(GL_LINE_STRIP);
			          }
		           }
		        glVertex3f((GLfloat)igs->Vertex[i].x,(GLfloat)igs->Vertex[i].y,(GLfloat)igs->Vertex[i].z);//pinto el vertice para recta strip
	          }
		     glEnd();
	         if(PintLinSusp)//LINEAS SUSPENSIVAS
	           {
	            glBegin(GL_LINES);
	            double a,b,c,d,e,f;
	            a=igs->Vertex[igs->cont-1].x;
	            b=igs->Vertex[igs->cont-1].y;
	            c=igs->Vertex[igs->cont-1].z;
	            d=cooRd->x-igs->Vertex[igs->cont-1].x;
	            e=cooRd->y-igs->Vertex[igs->cont-1].y;
	            f=cooRd->z-igs->Vertex[igs->cont-1].z;
	            for(unsigned i=0;i<=9;i++)
	               glVertex3f((GLfloat)(a+i*(d/9)),(GLfloat)(b+i*(e/9)),(GLfloat)(c+i*(f/9)));
	            glEnd();
	           }
		    break;

		  case 2:
			  break;
	       }
	    } 


};;
	static void add(CRD v,IGSClass*igs)
{
	
	
	if(igs->cont>=igs->cant)
	{
		
		CRD*newdata=new CRD[igs->cant+100];
		igs->cant+=100;
		for(unsigned i=0;i<igs->cont;i++)
		{
			newdata[i]=igs->Vertex[i];
			newdata[i]=igs->Vertex[i];
			newdata[i]=igs->Vertex[i];
		}
		igs->Vertex=newdata;
	}
	igs->Vertex[igs->cont++]=v;



};
	static void NewLINE(IGSClass*igs)
   {
   
       if(igs->contNL>=igs->cantNL)
	     {
		  unsigned*NewData=new unsigned[igs->cantNL+10];
		  igs->cantNL+=10;
		  for(unsigned i=0;i<igs->contNL;i++)
			 NewData[i]=igs->NewLine[i];
		  igs->NewLine=NewData;
	      }
	igs->NewLine[igs->contNL++]=igs->cont;
	

   };
	static void NewPOINT(IGSClass*igs){
 if(igs->contNP>=igs->cantNP)
	     {
		  unsigned*NewData=new unsigned[igs->cantNP+10];
		  igs->cantNP+=10;
		  for(unsigned i=0;i<igs->contNP;i++)
			 NewData[i]=igs->NewPoint[i];
		  igs->NewPoint=NewData;
	      }
	igs->NewPoint[igs->contNP++]=igs->cont;
};;
	static void End(char*c,IGSClass*igs)
{
	if(igs->cont>1)
	{
		/*CRD newCRD(igs->Vertex[0]);
		for(unsigned i=0;i<igs->cont;i++)
		{
			igs->Vertex[i].x-=newCRD.x;
			igs->Vertex[i].y-=newCRD.y;
			igs->Vertex[i].z-=newCRD.z;
		}
		*/

	fstream f;
	f.open(c,ios::out);
	f<<"                                                                        S      1\n";
	f<<",,,6HnewIgs,7HESE-GRS,7Hunknow,32,38,7,99,15,,1.,2,2HMMG,1,0.08,15H20201G      1\n";
    f<<"208.195031,0.01,10000.,7Hunknow,,11,0,15H20201209.03140;                G      2\n";
	f<<"     406       1                       2                        00000000D      1\n";
    f<<"     406                       1       3                               0D      2\n";
	igs->LastD++;
	igs->ContDs=2;
	unsigned addic=2;
	if((igs->cont+1)%2!=0)
		addic=1;
	
	for(unsigned i=0;i<=igs->cont+1+addic;i+=2)
	   {
		igs->LastD++;
		igs->ContDs++;
	    if(igs->LastD<10)
	    	f<<"     110       ";
	    else if(igs->LastD<100)
		   f<<"     110      ";
		else
		   f<<"     110     ";
	    f<<igs->LastD;
        f<<"                       2                        00000000D    ";
		if(igs->ContDs<10)
		   f<<"  ";
		else if(igs->ContDs<100)
		 f<<" ";
	    f<<igs->ContDs++<<endl;
	    
        f<<"     110       0               1       0                               0D    ";
	    if(igs->ContDs<10)
		   f<<"  ";
		else if(igs->ContDs<100)
		 f<<" ";
	    f<<igs->ContDs<<endl;
	   }
	igs->ContDs++;
	igs->LastD++;
	if(igs->LastD<10)
		f<<"     314       ";
	else if(igs->LastD<100)
		f<<"     314      ";
	else
		f<<"     314     ";
	f<<igs->LastD;
	 f<<"                                                00000200D    ";
	 if(igs->ContDs<10)
		   f<<"  ";
	 else if(igs->ContDs<100)
		 f<<" ";
	 f<<igs->ContDs++<<endl;
     f<<"     314                       1       0                               0D    ";
	 if(igs->ContDs<10)
		f<<"  ";
	 else if(igs->ContDs<100)
		 f<<" ";
	 f<<igs->ContDs<<endl;
	 f<<"406,2,0,7HBoceto1;                                                     1P      1\n";
	 igs->ContPs=1;
	 igs->LastP=1;
	 unsigned sum;
	 string s;
	 for(unsigned i=1;i<igs->cont;i++)
	 {
		
		for(unsigned y=0;y<igs->contNL;y++)
		{
			if(igs->NewLine[y]==i)
				{
					if(i+1==igs->cont)
					break;

					i++;
					break;
					
			    }
		}
		  
		
		
		 sum=3;
		 igs->ContPs+=2;
	     igs->LastP++;
		 f<<"110,";
	     s=to_string(igs->Vertex[i-1].x);
	     f<<s<<",";
	     sum+=s.length()+1;
	     s=to_string(igs->Vertex[i-1].y);
	     f<<s<<",";
	     sum+=s.length()+1;
	     s=to_string(igs->Vertex[i-1].z);
	     f<<s<<",";
	     sum+=s.length()+1;
	     s=to_string(igs->Vertex[i].x);
	     f<<s<<",";
	     sum+=s.length()+1;
	     s=to_string(igs->Vertex[i].y);
	     f<<s<<",";
	     sum+=s.length()+1;
	     s=to_string(igs->Vertex[i].z);
	     f<<s<<","<<";";
	     sum+=s.length()+2;
	     sum=68-sum;
	     for(unsigned i=0;i<sum;i++)
		   f<<" ";
	     if(igs->ContPs<10)
		   f<<"  ";
	     else if(igs->ContPs<100)
		    f<<" ";
	     f<<igs->ContPs;
	     f<<"P";
	     f<<"    ";
	     if(igs->LastP<10)
		    f<<"  ";
	     else if(igs->LastP<100)
		    f<<" ";
	     f<<igs->LastP;
	     f<<endl;
		 
	}
	 /*
	 for(int i=0;i<igs->cont-1;i++)
	 {
		 sum=3;
		 igs->ContPs+=2;
	     igs->LastP++;
		 f<<"110,";
	 s=to_string(igs->Vertex[i].x);
	 
	 f<<s<<",";
	 sum+=s.length()+1;
	 s=to_string(igs->Vertex[i].y);
	 f<<s<<",";
	 sum+=s.length()+1;
	 s=to_string(igs->Vertex[i].z);
	 f<<s<<",";
	 sum+=s.length()+1;
	 s=to_string(igs->Vertex[i+1].x);
	 f<<s<<",";
	 sum+=s.length()+1;
	 s=to_string(igs->Vertex[i+1].y);
	 f<<s<<",";
	 sum+=s.length()+1;
	 s=to_string(igs->Vertex[i+1].z);
	 f<<s<<","<<";";
	 sum+=s.length()+2;
	 sum=68-sum;
	 for(int i=0;i<sum;i++)
		 f<<" ";
	 if(igs->ContPs<10)
		 f<<"  ";
	 else if(igs->ContPs<100)
		 f<<" ";
	 f<<igs->ContPs;
	 f<<"P";
	 f<<"    ";
	 if(igs->LastP<10)
		 f<<"  ";
	 else if(igs->LastP<100)
		 f<<" ";
	 f<<igs->LastP;
	   f<<endl;
	 }
	 */

	 
	 f<<"314,74.9019607843137,74.9019607843137,74.9019607843137,;             ";
	 igs->ContPs+=2;
	 if(igs->ContPs<10)
		 f<<"  ";
	 else if(igs->ContPs<100)
		 f<<" ";
	 f<<igs->ContPs<<"P    ";
	 if(igs->LastP<10)
		 f<<"  ";
	 else if(igs->LastP<100)
		 f<<" ";
	 igs->LastP++;
	 f<<igs->LastP<<endl;

	 f<<"S      1G      2D    ";
	 if(igs->ContDs<10)
		 f<<"  ";
	 else if(igs->ContDs<100)
		 f<<" ";
	 f<<igs->ContDs<<"P    ";
	 if((igs->ContPs+1)/2<10	)
		 f<<"  ";
	 else if((igs->ContPs+1)/2<100)
		 f<<" ";
	 f<<(igs->ContPs+1)/2;

	 f<<"                                        T      1";
    f.close();	
    }
	else
		std::cout<<"ERror no puede haber un solo vertice";
		
};
	static void Clear(IGSClass*igs){igs=new IGSClass;}
	static void SetRestriccion(CRD*crd,IGSClass*igs){
		igs->puntoRestriccion=new CRD(*crd);
	}
	static double getCoordRestricion(unsigned opcion,IGSClass*igs){
		switch (opcion)
		{
		case 0:
			return igs->puntoRestriccion->x;
			break;
		case 1:
			return igs->puntoRestriccion->y;
			break;
		case 2:
			return igs->puntoRestriccion->z;
			break;
	   }
	}
	static void CancelLastPoint(IGSClass*igs){
if(igs->cont>0)
		{
		for(unsigned i=0;i<igs->contNP;i++)
		{
			if(igs->NewPoint[i]==igs->cont-1)
			{
				for(unsigned ii=i;ii<igs->contNP-1;i++)
					igs->NewPoint[i]=igs->NewPoint[i+1];
				igs->contNP--;
			}
		}
		for(unsigned i=0;i<igs->contNL;i++)
		{
			if(igs->NewLine[i]==igs->cont-1)
			{
				for(unsigned ii=i;ii<igs->contNL-1;ii++)
					igs->NewLine[ii]=igs->NewLine[ii+1];
				igs->contNL--;
			}
		}

		
			igs->cont--;
		}
};;
	static double* Media(IGSClass*igs){
    double*d=new double[3];
	d[0]=0;
	d[1]=0;
	d[2]=0;
	
	for(unsigned i=0;i<igs->cont;i++)
	{
		d[0]+=igs->Vertex[i].x;
		d[1]+=igs->Vertex[i].y;
		d[2]+=igs->Vertex[i].z;
	}
	d[0]/=igs->cont;
	d[1]/=igs->cont;
	d[2]/=igs->cont;
	return d;
};
	
};

