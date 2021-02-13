#include "IGSClass.h"
#include <math.h>
#include <string>
#include <iostream>
using namespace std;
IGSClass::IGSClass(void)
{
	S=G=D=P=LastP=ContDs=ContPs=LastD=cont=contNL=0;
	cant=100;
	cantNL=10;
	Vertex=new CRD[cant]; 
	NewLine=new unsigned[cantNL];
}
void IGSClass::NewLINE(IGSClass*igs)
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
	

   }
void IGSClass::add(CRD v,IGSClass*igs)
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



}
void IGSClass::End(char*c,IGSClass*igs)
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
		
}
