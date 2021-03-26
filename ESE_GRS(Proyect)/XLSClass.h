#include <direct.h>
#include <ostream>
#include "libxl.h"
#include "StackBoceto.h"
using namespace libxl;
using namespace std;
class XLSClass
{	
public:
	XLSClass(){
	};
	~XLSClass(){};
	static bool Salvar(Plano**Planos,unsigned*elements,unsigned cantElements)
	{
		Book*book=xlCreateBook();
		if(book)
		{
			Sheet*sheet=book->addSheet("Sheet1");
			if(sheet)
			{
				mkdir("ESE_GRS-XLS");
				for(unsigned i=0;i<cantElements;i++)
				{
					sheet->writeStr(1,0,"X");
					sheet->writeStr(1,1,"Y");
					sheet->writeStr(1,2,"Z");
					unsigned row=2;
					for(unsigned j=0;j<Planos[elements[i]]->contItems;j++)
					{
						for(unsigned k=0;k<Planos[elements[i]]->items[j]->cont;k++)
						{
						sheet->writeNum(row,0,Planos[elements[i]]->items[j]->PoIntS[k].x);
						sheet->writeNum(row,1,Planos[elements[i]]->items[j]->PoIntS[k].y);
						sheet->writeNum(row++,2,Planos[elements[i]]->items[j]->PoIntS[k].z);
						}
					}
					
					string s="ESE_GRS-XLS/";
					s+=Planos[elements[i]]->name;
					s+=".xls";
					book->save((char*)s.c_str());
					book->release();
					book=xlCreateBook();
					sheet=book->addSheet("Sheet1");
					
				}
				book->release();
			}
			else
				return false;
		}
		else 
			return false;
		return true;
	};


};

