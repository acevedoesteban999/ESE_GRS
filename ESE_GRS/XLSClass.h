#pragma once
#include <direct.h>
#include <ostream>
#include "libxl.h"
#include "StackBoceto.h"
#include "DataProcessor.h"
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
	static void SalvarGrabar(float GrabarAngles[6],char*bytes,unsigned GrabarCont)
	{
		Book*book=xlCreateBook();
		if(book)
		{
			Sheet*sheet=book->addSheet("Sheet1");
			if(sheet)
			{
					mkdir("ESE_GRS-XLS");
					sheet->writeStr(1,0,"Higt Byte");
					sheet->writeStr(1,1,"Low Byte");
					sheet->writeStr(1,2,"Q1");
					sheet->writeStr(1,3,"Q2");
					sheet->writeStr(1,4,"Q3");
					sheet->writeStr(1,5,"Q4");
					sheet->writeStr(1,6,"Q5");
					sheet->writeStr(1,7,"Q6");


					sheet->writeStr(2,0," ");
					sheet->writeStr(2,1," ");
					sheet->writeNum(2,2,GrabarAngles[0]);
					sheet->writeNum(2,3,GrabarAngles[1]);
					sheet->writeNum(2,4,GrabarAngles[2]);
					sheet->writeNum(2,5,GrabarAngles[3]);
					sheet->writeNum(2,6,GrabarAngles[4]);
					sheet->writeNum(2,7,GrabarAngles[5]);
					unsigned row=3;
					for(unsigned j=0;j<GrabarCont;j++)
					{	
						DataProcessor::PorcesarDatos(bytes[j],bytes[j+1],GrabarAngles);
						
						sheet->writeStr(row,0,DataProcessor::printfBits(bytes[j+1]));
						sheet->writeStr(row,1,DataProcessor::printfBits(bytes[j]));
						sheet->writeNum(row,2,GrabarAngles[0]);
						sheet->writeNum(row,3,GrabarAngles[1]);
						sheet->writeNum(row,4,GrabarAngles[2]);
						sheet->writeNum(row,5,GrabarAngles[3]);
						sheet->writeNum(row,6,GrabarAngles[4]);
						sheet->writeNum(row++,7,GrabarAngles[5]);
					}
					unsigned contttttt=0;
					string s="ESE_GRS-XLS/";
					s+="Grabar";
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
							s=s.substr(0,s.length()-4-(contttttt==0?0:contttttt<10?2:3));
							s+=string("_")+to_string(contttttt++);
							s+=".xls";
						}
						f.close();
					}while (exist);
					book->save((char*)s.c_str());
					book->release();
			}
		}
	}

};

