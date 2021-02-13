/*#include "PuertoSerie.h"
using namespace std;

int main()
{
	
	PuertoSerie puerto("COM1",9600);
	if(puerto.Error()==true)
	  {
		cout<<puerto.ErrorStr()<<endl;
	    system("pause");
	    return 0;
	  }
	cout<<"Esperando Datos"<<endl;
	do
	   {
		char*cad=puerto.Recibir();
		if(cad!=NULL)
			{
				cout<<cad<<endl;
		    }
	   }while(1);
	
		return 0;
}
*/