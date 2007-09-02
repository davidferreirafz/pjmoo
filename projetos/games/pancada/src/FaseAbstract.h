
#ifndef _FASEABSTRACT_H
#define _FASEABSTRACT_H


#include <GBF/TimerSystemCronometroDecrescente.h>
#include <GBF/ParticleSystemManager.h>
#include <GBF/FrameLayer.h>
#include <GBF/WriteSystemManager.h>
#include <GBF/InputSystem.h>
#include <GBF/FrameLayerManager.h>

#include "Placar.h"
#include "LutadorAbstract.h"



//Status de Roundes
enum EnumRound {
  ROUND_NULL =0,
  ROUND_UM   =1,
  ROUND_DOIS =2,
  ROUND_TRES =3,
  ROUND_TERMINOU =4
};

class Round
{
  public:
    int atual;
    int ultimo;
    bool prorrogacao;

    void setProrrogacao()
    {
        prorrogacao=true;
    }

    void setPrimeiro()
    {
        atual=1;
    }

    bool isUltimo()
    {
        if (atual==ultimo){
            return true;
        } else {
            return false;
        }
    }

    void proximo()
    {
        atual++;
    }

    void setMaximo(int maximo)
    {
        ultimo=maximo;
    }

    int get()
    {
        return atual;
    }
};

class FaseAbstract
{
  public:



  protected:
    LutadorAbstract * lutadorPlayer;

    LutadorAbstract * lutadorPC;


    TimerSystemCronometroDecrescente cronometroAuxiliar;

    FrameLayer * ringue;

    //FrameLayer * status;
    Placar placar;

    static WriteSystemManager * wsManager;
    static ParticleSystemManager * particleManager;

    Round round;

  private:
    EnumRound eRound;



  public:
    FaseAbstract();

    virtual ~FaseAbstract();

    bool isGameOver();

    bool isFaseFinalizada();

    bool isFimRound();
    bool isNocaute();
    bool isProximoRound();
    void proximoRound();

    int getRound();

    void executar(InputSystem * input);

    void primeiroRound();

  protected:



  public:
    //* Inicia a fase
    virtual void iniciar() = 0;
    void desenhar();

  private:
    // so para virar de costas corretamente
    void ordenacao();


};
#endif
