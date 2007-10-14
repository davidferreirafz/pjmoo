
#ifndef _FASEABSTRACT_H
#define _FASEABSTRACT_H

#include "LutadorAbstract.h"
#include "Placar.h"
#include "Round.h"
#include "HUDTempo.h"
#include "StatusPC.h"
#include "StatusPlayer.h"
#include <GBF/InputSystem.h>

#include <GBF/FrameLayer.h>

#include <GBF/WriteSystemManager.h>

#include <GBF/TimerSystemCronometroDecrescente.h>

#include <GBF/ParticleSystemManager.h>

#include <GBF/FrameLayerManager.h>

#include "LutadorPlayer.h"
#include "LutadorPC.h"
#include <GBF/SoundSystem.h>


class FaseAbstract
{
  protected:
    LutadorAbstract * lutadorPC;

    LutadorAbstract * lutadorPlayer;

    Placar placar;

    Round round;

    HUDTempo statusTempo;

    StatusPC statusPC;

    StatusPlayer statusPlayer;


  private:
    // so para virar de costas corretamente
    void ordenacao();


  public:
    //Destrutor
    FaseAbstract();

    //Construtor
    virtual ~FaseAbstract();

    //* Inicia a fase
    virtual void iniciar() = 0;

    bool isGameOver();

    bool isFaseFinalizada();

    bool isFimRound();

    bool isNocaute();

    bool isProximoRound();

    void proximoRound();

    int getRound();

    void executar(InputSystem * input);

    void primeiroRound();

    void desenhar();

    void setTotalRound(int total);


  protected:
    FrameLayer * ringue;

    static WriteSystemManager * wsManager;

    TimerSystemCronometroDecrescente cronometroAuxiliar;

    static ParticleSystemManager * particleManager;

};
#endif
