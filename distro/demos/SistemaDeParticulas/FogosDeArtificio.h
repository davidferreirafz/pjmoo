#ifndef _FOGOSDEARTIFICIO_H_
#define _FOGOSDEARTIFICIO_H_
#include "Efeito.h"


class FogosDeArtificio : public Efeito
{
public:
	void criar(int x, int y);
	void atualizar();   

protected:
    Ponto origem;
    static const int raio = 100;
};

#endif


