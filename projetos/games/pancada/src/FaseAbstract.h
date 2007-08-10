
#ifndef _FASEABSTRACT_H
#define _FASEABSTRACT_H

#include "Placar.h"
#include "LutadorAbstract.h"
#include <GBF/TimerSystemCronometroDecrescente.h>

#include <GBF/FrameLayer.h>

#include <GBF/WriteSystemManager.h>

#include <GBF/InputSystem.h>

#include <GBF/FrameLayerManager.h>

#include "EfeitoContainer.h"


//Status de Roundes
enum EnumRound {
  ROUND_NULL =0,
  ROUND_UM   =1,
  ROUND_DOIS =2,
  ROUND_TRES =3,
  ROUND_TERMINOU =4
};
class FaseAbstract
{
  public:
    Placar placar;


  protected:
    LutadorAbstract * lutadorPlayer;

    LutadorAbstract * lutadorPC;


    TimerSystemCronometroDecrescente cronometroAuxiliar;

    FrameLayer * ringue;

    //FrameLayer * status;

    static WriteSystemManager * wsManager;


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
