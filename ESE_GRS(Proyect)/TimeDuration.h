#include <ctime>
#pragma once
class TimeDuration
{
public:
	bool tBool;
	float TimE,TimeClock;
	TimeDuration(void);
	TimeDuration(float t){this->tBool=true,this->TimE=t;TimeClock=(float)clock();};
	static float InitCiclo(TimeDuration*TimeDurat);
	static bool  Ciclo(TimeDuration*TimeDurat);
	static void ResetT(TimeDuration*TimeDurat){TimeDurat->TimeClock=0;TimeDurat->tBool=false;TimeDurat->TimE=0;};
	

};

