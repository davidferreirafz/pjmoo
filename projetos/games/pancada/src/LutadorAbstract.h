
#ifndef _LUTADORABSTRACT_H
#define _LUTADORABSTRACT_H

#include <GBF/GraphicSystemImage.h>

#include <GBF/GBF_define.h>

#include "LuvaAbstract.h"
#include <GBF/InputSystem.h>

#include "Cabeca.h"
#include "LuvaDireita.h"
#include "LuvaEsquerda.h"
#include <GBF/ParticleSystemManager.h>

#include <GBF/PersonagemControlado.h>

#include "EfeitoSangue.h"
#include "CabecaFactory.h"
#include "Define.h"

class LutadorAbstract : public PersonagemControlado
{
  public:
    //Construtor
    LutadorAbstract();

    //Destrutor
    virtual ~LutadorAbstract();

    static void setRingue(Area ringue);

    void iniciar(int x, int y);

    //Desenha na tela
    virtual void desenhar();

    //O lutador está na olhando pra cima
    void olharCima();

    //O lutador está na olhando pra baixo
    void olharBaixo();

    Ponto getPosicao();

    virtual void setPosicao(int x, int y);

    Area getArea();

    bool socouAdversario(LutadorAbstract * adversario);

    bool levouSoco(LuvaAbstract * luva);

    void mover(InputSystem * input, LutadorAbstract * adversario);

    bool isNocaute();

    //Retorna a energia vital do lutador
    int getEnergia();


  protected:
    Cabeca * cabeca;

    Dimensao dimensao;

    LuvaDireita * luvadireita;

    LuvaEsquerda * luvaesquerda;

    static ParticleSystemManager * particleManager;

    static Area ringue;

    bool choqueAdversario(Area aCorpoAdversario);

    //checka com limites do ringue
    void checklimites();


  private:
    int energia;

    void resetar();

};
#endif
