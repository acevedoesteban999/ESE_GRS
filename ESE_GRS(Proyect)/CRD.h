#pragma once
class CRD
{
public:
	CRD(void){};
	CRD(double x,double y,double z){this->x=x;this->y=y;this->z=z;}
	CRD(double*coords){
	this->x=coords[0];
	this->y=coords[1];
	this->z=coords[2];
	
	}
	double x,y,z;
	static void set(float x,float y,float z,CRD*crd){crd->x=x;crd->y=y;crd->z=z;}
};

