#ifndef _EXPLOSAO_H_
#define _EXPLOSAO_H_
#include "Efeito.h"


class Explosao : public Efeito
{
public:
	void criar(int x, int y);
	void atualizar();
	
protected:
    Ponto origem;
    static const int raio = 50;
};

#endif



