
#ifndef _HUDLUTADOR_H
#define _HUDLUTADOR_H

#include "HUDAbstract.h"
#include <GBF/SpriteItem.h>

#include <GBF/GraphicSystem.h>

#include <GBF/SpriteFactory.h>


class HUDLutador : public HUDAbstract
{
  public:
    //Construtor
    HUDLutador();

    //Destrutor
    virtual ~HUDLutador();

    virtual void desenhar(int pontos, int round, int energia) = 0;


  protected:
    SpriteItem * pontuacao;

    SpriteItem * statusEnergia;

};
#endif
