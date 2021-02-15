#include <ctime>
#pragma once
class TimeDuration
{
public:
	bool tBool;
	float TimE,TimeClock;
	TimeDuration(void);
	TimeDuration(bool InitIncrementa){if(InitIncrementa)this->tBool=true;this->TimeClock=(float)clock();};
	TimeDuration(float t){this->tBool=true,this->TimE=t;TimeClock=(float)clock();};
	static float Incrementa(TimeDuration*TimeDurat);
	static bool  Decrementa(TimeDuration*TimeDurat);
	static void  InitDecrementa(TimeDuration*TimeDurat,float tiMe);
	static void ResetT(TimeDuration*TimeDurat){TimeDurat->TimeClock=0;TimeDurat->tBool=false;TimeDurat->TimE=0;};
	static void ResettIncrementa(TimeDuration*TimeDurat){TimeDurat->TimE=0;};

};

