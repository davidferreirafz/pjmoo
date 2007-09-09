
#ifndef _FASEABSTRACT_H
#define _FASEABSTRACT_H

#include <GBF/ParticleSystemManager.h>

#include <GBF/WriteSystemManager.h>

#include <GBF/FrameLayer.h>

#include <GBF/TimerSystemCronometroDecrescente.h>

#include "LutadorAbstract.h"
#include "Placar.h"
#include "HUDTempo.h"
#include "StatusPC.h"
#include "StatusPlayer.h"
#include <GBF/FrameLayerManager.h>

#include <GBF/InputSystem.h>


class Round
{
  public:
    int atual;

    int ultimo;

    inline void setPrimeiro() {
            atual=1;
        };

    inline bool isUltimo() {
            if (atual==ultimo){
                return true;
            } else {
                return false;
            }
        };

    inline void proximo() {
            atual++;
        };

    inline void setMaximo(int maximo) {
            ultimo=maximo;
        };

    inline int get() {
            return atual;
        };

};
class FaseAbstract
{
  protected:
    static ParticleSystemManager * particleManager;

    static WriteSystemManager * wsManager;

    FrameLayer * ringue;

    TimerSystemCronometroDecrescente cronometroAuxiliar;

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

};
#endif
