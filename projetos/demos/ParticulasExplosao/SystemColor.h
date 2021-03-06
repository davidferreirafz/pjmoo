// Class automatically generated by Dev-C++ New Class wizard

#ifndef SYSTEMCOLOR_H
#define SYSTEMCOLOR_H

#include <math.h>
#include <GBF/Cor.h>


struct RGB
{
    int r;
    int g;
    int b;

};
struct RGBf
{
    float r;
    float g;
    float b;

};
struct HSV
{
	float h;
	float s;
	float v;
};


class SystemColor
{
public:
	static HSV forHSV(RGB cor);
	static RGB forRGB(HSV cor);

protected:
	static int menor(int valor1, int valor2);
	static int maior(int valor1, int valor2);


};

#endif // SYSTEMCOLOR_H
