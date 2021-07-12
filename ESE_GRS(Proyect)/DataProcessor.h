#pragma once
#include "ESE_GRS.h"
class DataProcessor
{
public:
	DataProcessor(){};
	~DataProcessor(){};
	static bool BitData(char Byte,unsigned posttion)
    {
	if((Byte & 0x01<<posttion)==0)
		return 0;
	return 1;

    };
	static bool PorcesarDatos(char ByteLow,char ByteHigh,GLfloat*angles)
{

	for(int i=2;i<8;i++)
	{
		switch (i)
		{
		  case 2:
		  case 3:
		  case 4:
		  case 5:
		  case 6:
		  case 7:
			    if(BitData(ByteLow,i)==1)
			       {
				     if(BitData(ByteHigh,i)==1)
						 angles[i-2]+=(GLfloat)0.9;
					 else
						 angles[i-2]-=(GLfloat)0.9;
					 RectificarAngules(angles);
			       }	
		         break;      	
	   }//end switch
	
	}//end for
	if(BitData(ByteHigh,1)==1)
	     return true;

	return false;

};
	static void RectificarAngules(GLfloat*angles){
	
	//comprobar angulos
	if(angles[0]>=360  )
		angles[0]-=360;
	else if(angles[0]<=-360)
		angles[0]+=360;
	if(angles[1]>=360  )
		angles[1]-=360;
	else if(angles[1]<=-360)
		angles[1]+=360;
	if(angles[2]>=360  )
		angles[2]-=360;
	else if(angles[2]<=-360)
		angles[2]+=360;
	if(angles[3]>=360  )
		angles[3]-=360;
	else if(angles[3]<=-360)
		angles[3]+=360;
	if(angles[4]>=360  )
		angles[4]-=360;
	else if(angles[4]<=-360)
		angles[4]+=360;
	if(angles[5]>=360  )
		angles[5]-=360;
	else if(angles[5]<=-360)
		angles[5]+=360;


};
	static char* printfBits(char c)
{
	char*f=new char[9];
	f[8]=0;
	for(int i=0;i<8;i++)
	  {
		  if(BitData(c,i)==0)
			  f[7-i]='0';
		  else
			  f[7-i]='1';
	  }
		return f;
};
};

