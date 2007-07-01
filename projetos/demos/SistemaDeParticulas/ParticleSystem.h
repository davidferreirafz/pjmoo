#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <GBF/GBF.h>

struct Particula
{
    bool ativa;
    PontoVirtual posicao;
    PontoVirtual velocidade;
    PontoVirtual posicaoAntiga;
    int energia;
    CorPaleta r;
    CorPaleta g;
    CorPaleta b;
};

class ParticleSystem
{
public:
	/** Construtor */
	ParticleSystem();
	/** Destrutor */
	~ParticleSystem();
	/** Inicializar*/
	void inicializar();
    virtual void criar()=0;
	virtual void atualizar()=0;
    virtual void desenhar();
    bool isTerminou();
    void setPosicao(int x, int y);
    
protected:
    static GraphicSystem* graphicSystem;
    int quantidade;
    float ambienteVento;
    float ambienteGravidade;
    Ponto posicao;
    Particula particulas[500];
};

#endif // PARTICLESYSTEM_H
