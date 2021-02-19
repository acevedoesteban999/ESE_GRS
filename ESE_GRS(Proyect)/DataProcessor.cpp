#include "DataProcessor.h"
DataProcessor::DataProcessor()
{
}

bool DataProcessor::BitData(char Byte,unsigned posttion)
{
	if((Byte & 0x01<<posttion)==0)
		return 0;
	return 1;

}
void DataProcessor::RectificarAngules(GLfloat*angules){
	
	//comprobar angulos
	if(angules[0]>=360  )
		angules[0]-=360;
	else if(angules[0]<=-360)
		angules[0]+=360;
	if(angules[1]>=360  )
		angules[1]-=360;
	else if(angules[1]<=-360)
		angules[1]+=360;
	if(angules[2]>=360  )
		angules[2]-=360;
	else if(angules[2]<=-360)
		angules[2]+=360;
	if(angules[3]>=360  )
		angules[3]-=360;
	else if(angules[3]<=-360)
		angules[3]+=360;
	if(angules[4]>=360  )
		angules[4]-=360;
	else if(angules[4]<=-360)
		angules[4]+=360;
	if(angules[5]>=360  )
		angules[5]-=360;
	else if(angules[5]<=-360)
		angules[5]+=360;


}
bool DataProcessor::PorcesarDatos(char ByteLow,char ByteHigh,GLfloat*angules)
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
						 angules[i-2]+=0.9;
					 else
						 angules[i-2]-=0.9;
					 RectificarAngules(angules);
			       }	
		         break;      	
	   }//end switch
	
	}//end for
	if(BitData(ByteHigh,1)==1)
	     return true;

	return false;

}
char* DataProcessor::printfBits(char c)
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
}