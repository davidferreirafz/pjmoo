
#ifndef _CONTROLE_H
#define _CONTROLE_H

#include "FaseAbstract.h"
#include <GBF/InputSystem.h>

#include <GBF/SpriteItem.h>

#include <GBF/TimerSystemCronometroDecrescente.h>

#include "FaseFactory.h"

class Controle
{
  private:
    int faseNumero;

    FaseAbstract * fase;


  public:
    //Construtor
    Controle();

    //Destrutor
    virtual ~Controle();

    void iniciar();

    bool carregarFase();

    void mudarFase();

    bool isGameOver();

    bool isFaseFinalizada();

    void executar(InputSystem * input);

    void desenhar();

    void carregar();


  protected:
    SpriteItem * fight;

    TimerSystemCronometroDecrescente tempoEspera;

};
#endif
