#include "CRD.h"
#include <iostream>
class Matriz
{
    class fila
	{
	public:
		float*elementsFila;
		float result;
		unsigned size;
		fila(){
			size=0;
			elementsFila=new float[1];
			result=0;
			
		};
		~fila(){};
		fila operator*(float num)
		{
			fila f=*this;
			f.elementsFila=new float[this->size];
			for(unsigned i=0;i<f.size;i++)
			   f.elementsFila[i]=this->elementsFila[i];
					
			for(unsigned i=0;i<f.size;i++)
			   f.elementsFila[i]*=num;
			f.result*=num;
			return f;
		}
		fila operator/(float num)
		{
			fila f=*this;
			f.elementsFila=new float[this->size];
			for(unsigned i=0;i<f.size;i++)
			   f.elementsFila[i]=this->elementsFila[i];

			for(unsigned i=0;i<f.size;i++)
			   f.elementsFila[i]/=num;
			f.result/=num;
			return f;
		}
		fila operator+(fila f)
		{
			for(unsigned i=0;i<f.size;i++)
				this->elementsFila[i]+=f.elementsFila[i];
			this->result+=f.result;
			return *this;
		}
		fila operator-(fila f)
		{
			for(unsigned i=0;i<f.size;i++)
				this->elementsFila[i]-=f.elementsFila[i];
			this->result-=f.result;
			return *this;
		}
		void Cambiar(fila*f,fila*f1){
			fila ff=*f;
			*f=*f1;
			*f1=ff;
		};
	};
private:
	fila*Filas;
	unsigned size;
public:
	Matriz(unsigned Size,float*Elements,float*Result){
		Filas=new fila[Size];
		unsigned contE=0;
		size=Size;
		for(unsigned i=0;i<Size;i++)
		{
			Filas[i].result=Result[i];
			Filas[i].elementsFila=new float[Size];
			Filas[i].size=Size;
			for(unsigned j=0;j<Size;j++)
				Filas[i].elementsFila[j]=Elements[contE++];
		}
		/*MostrarMatriz(this);
		float*result=Solucion_ReduccionFilas();
		std::cout<<"Resultado:"<<std::endl;
		for(unsigned i=0;i<size;i++)
			std::cout<<result[i]<<" ";
		std::cout<<std::endl;*/
		
	};
	~Matriz(){};
	
	
	float*Solucion_ReduccionFilas()
	{
		Matriz*m=new Matriz(*this);
		for(unsigned i=0;i<m->size;i++)
		{
			for(unsigned j=0;j<m->size;j++)
		    {
			   if(j==i)
				   continue;
			   float Factor=m->Filas[j].elementsFila[i]/m->Filas[i].elementsFila[i];
			   m->Filas[j]=(m->Filas[i]*Factor - m->Filas[j]);
		    }
			//MostrarMatriz(&m);
		}
		
		float*toReturn=new float[size];
		for(unsigned i=0;i<size;i++)
			toReturn[i]=(float)(m->Filas[i].result/Filas[i].elementsFila[i]);
		return toReturn;
	}
	static void MostrarMatriz(Matriz*m){
	for(unsigned i=0;i<m->size;i++)
		           {
			          for(unsigned j=0;j<m->size;j++)
			             std::cout<<m->Filas[i].elementsFila[j]<<" ";
			           std::cout<<"["<<m->Filas[i].result<<"]"<<std::endl;
		           }
				   std::cout<<"|||||||||||||||||||||||||||||||||||||||||||||||||||"<<std::endl;
	}
};