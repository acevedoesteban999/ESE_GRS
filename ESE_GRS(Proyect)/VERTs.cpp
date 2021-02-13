
#include "GL\freeglut.h"
class VERTs
{
public:
	VERTs(){};
	~VERTs(){delete[] v/*,Ys,Zs*/;};
	GLfloat *v;
	//GLfloat *Ys,*Zs;
};
