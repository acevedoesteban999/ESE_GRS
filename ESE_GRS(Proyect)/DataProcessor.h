#include "GL\freeglut.h"
class DataProcessor
{
public:
	DataProcessor();
	static bool BitData(char Byte,unsigned posittion);
	static bool PorcesarDatos(char ByteLow,char ByteHigh,GLfloat*angules);
	static void RectificarAngules(GLfloat*angules);
	static char* printfBits(char c);
};

