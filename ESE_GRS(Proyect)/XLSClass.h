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
	static bool Salvar(Plano**Planos,unsigned*elements,unsigned cantElements,bool All=false,unsigned allCont=0)
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
					for(unsigned j=0;j<Planos[elements[i]]->items->cont;j++)
					{	
						sheet->writeNum(row,0,Planos[elements[i]]->items->PoIntS[j].x);
						sheet->writeNum(row,1,Planos[elements[i]]->items->PoIntS[j].y);
						sheet->writeNum(row++,2,Planos[elements[i]]->items->PoIntS[j].z);
					}
					
					string s="ESE_GRS-XLS/";
					s+=Planos[elements[i]]->name;
					s+=".xls";
					fstream f;
					bool exist;
					unsigned cont=0;
					do
					{
					f.open((char*)s.c_str(),ios::in);
					exist=f.is_open();
					if(exist)
					{
						s=s.substr(0,s.length()-4-(cont==0?0:cont<10?2:3));
						s+=string("_")+to_string(cont);
						s+=".xls";
						cont++;
					}
					f.close();
					}while (exist);
					book->save((char*)s.c_str());
					book->release();
					book=xlCreateBook();
					sheet=book->addSheet("Sheet1");
					
				}
				if(All)
				{
					sheet->writeStr(1,0,"X");
					sheet->writeStr(1,1,"Y");
					sheet->writeStr(1,2,"Z");
					unsigned row=2;
					for(unsigned i=0;i<allCont;i++)
					{
						for(unsigned j=0;j<Planos[i]->items->cont;j++)
						{	
							sheet->writeNum(row,0,Planos[elements[i]]->items->PoIntS[j].x);
							sheet->writeNum(row,1,Planos[elements[i]]->items->PoIntS[j].y);
							sheet->writeNum(row++,2,Planos[elements[i]]->items->PoIntS[j].z);
						}
					}
					string s="ESE_GRS-XLS/";
					s+="All_Sketchs";
					s+=".xls";
					fstream f;
					bool exist;
					unsigned cont=0;
					do
					{
					f.open((char*)s.c_str(),ios::in);
					exist=f.is_open();
					if(exist)
					{
						s=s.substr(0,s.length()-4-(cont==0?0:cont<10?2:3));
						s+=string("_")+to_string(cont);
						s+=".xls";
						cont++;
					}
					f.close();
					}while (exist);
					

					
					
					
					
					book->save((char*)s.c_str());
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

