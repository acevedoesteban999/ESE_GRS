#include "TimeDuration.h"
#include <iostream>

TimeDuration::TimeDuration(void)
{
	TimE=0;
	
	tBool=false;
}
float TimeDuration::InitCiclo(TimeDuration*TimeDurat){
	if(TimeDurat->tBool)
	      {
			  TimeDurat->TimE+=(((float)clock()-TimeDurat->TimeClock)/CLOCKS_PER_SEC);
			  TimeDurat->TimeClock=(float)clock();
			 return (float)TimeDurat->TimE; 
	       }
	 else
		 {
			TimeDurat->TimeClock=(float)clock();
			TimeDurat->tBool=true;
			return 0;
	     }
}
bool TimeDuration::Ciclo(TimeDuration*TimeDurat)
{
	if(TimeDurat->tBool)
	{
		TimeDurat->TimE-=(((float)clock()-TimeDurat->TimeClock)/CLOCKS_PER_SEC);
		
		
		
			 if(TimeDurat->TimE>0)
			 {
				 TimeDurat->TimeClock=(float)clock();
				
				return false;
			 }
				TimeDurat->ResetT(TimeDurat);
	
	}
	return true;
}

