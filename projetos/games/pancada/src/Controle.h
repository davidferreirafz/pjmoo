
#ifndef _CONTROLE_H
#define _CONTROLE_H

#include "FaseAbstract.h"
#include <GBF/InputSystem.h>

#include "FaseFactory.h"
#include <GBF/TimerSystemCronometroDecrescente.h>


class Controle
{
  private:
    int faseNumero;

    FaseAbstract * fase;


  public:
    //Construtor
    Controle();

    // Destrutor
    virtual ~Controle();

    void iniciar();

    bool carregarFase();
    void mudarFase();

    bool isGameOver();

    bool isFaseFinalizada();

    void executar(InputSystem * input);

    void desenhar();
    void carregar();


  private:
    SpriteItem *fight;

  protected:
    TimerSystemCronometroDecrescente tempoEspera;


};
#endif
