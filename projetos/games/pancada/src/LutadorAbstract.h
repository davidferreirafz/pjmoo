
#ifndef _LUTADORABSTRACT_H
#define _LUTADORABSTRACT_H

#include <GBF/ImageBase.h>

#include <GBF/GBF.h>

#include "LuvaAbstract.h"
#include <GBF/InputSystem.h>

#include "Cabeca.h"
#include "LuvaDireita.h"
#include "LuvaEsquerda.h"
#include <GBF/PSManager.h>

#include <GBF/Personagem.h>

#include "EfeitoSangue.h"
#include "CabecaFactory.h"
#include "Define.h"

class LutadorAbstract : public Personagem::Personagem
{
  public:
    //Construtor
    LutadorAbstract();

    //Destrutor
    virtual ~LutadorAbstract();

    static void setRingue(GBF::Area ringue);

    void iniciar(int x, int y);

    //Desenha na tela
    virtual void desenhar();

    //O lutador está na olhando pra cima
    void olharCima();

    //O lutador está na olhando pra baixo
    void olharBaixo();

    GBF::Ponto getPosicao();

    virtual void setPosicao(int x, int y);

    GBF::Area getArea();

    bool socouAdversario(LutadorAbstract * adversario);

    bool levouSoco(LuvaAbstract * luva);

    void mover(GBF::Kernel::Input::InputSystem * input, LutadorAbstract * adversario);

    bool isNocaute();

    //Retorna a energia vital do lutador
    int getEnergia();


  protected:
    Cabeca * cabeca;

    GBF::Dimensao dimensao;

    LuvaDireita * luvadireita;

    LuvaEsquerda * luvaesquerda;

    static ParticleSystem::PSManager * particleManager;

    static GBF::Area ringue;

    bool choqueAdversario(GBF::Area aCorpoAdversario);

    //checka com limites do ringue
    void checklimites();


  private:
    int energia;

    void resetar();


  protected:
    //Anda para Baixo(Tela)
    void andarBaixo();

    //Anda para Cima(Tela)
    void andarCima();

    //Anda para Esquerda(Tela)
    void andarEsquerda();

    //Anda para Direita(Tela)
    void andarDireita();


  public:
    //Realiza o soco
    void socarDireita(bool soca);

    //Realiza o soco
    void socarEsquerda(bool soca);


  private:
    //Anda para Cima(Tela)
    void andarCima(int passos);

    //Anda para Cima(Tela)
    void andarBaixo(int passos);

    //Anda para Cima(Tela)
    void andarDireita(int passos);

    //Anda para Cima(Tela)
    void andarEsquerda(int passos);


  protected:
    virtual void visao(const GBF::Area & adversario);

};
#endif
