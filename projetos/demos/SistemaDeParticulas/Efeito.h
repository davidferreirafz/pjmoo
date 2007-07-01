#ifndef _EFEITO_H_
#define _EFEITO_H_
#include <deque>
#include <GBF/GBF_define.h>
#include <GBF/GraphicSystem.h>
#include "SystemColor.h"

struct Particula
{
	PontoVirtual velocidade;
	PontoVirtual posicao;
	int energia;
	HSV cor;
	bool ativa;
};

class Efeito
{
public:
    Efeito();
    void setQuantidade(int quantidade);
	virtual bool isTerminou();
	virtual void desenhar();
	virtual void criar(int x, int y)=0;
	virtual void atualizar()=0;
    
protected:
//	Particula particula[500];
	std::deque<Particula> lista;
	
    static GraphicSystem* graphicSystem;
};

#endif






