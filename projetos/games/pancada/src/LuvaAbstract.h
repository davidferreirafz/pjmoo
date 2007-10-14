
#ifndef _LUVAABSTRACT_H
#define _LUVAABSTRACT_H

#include "MembroBase.h"
#include <GBF/GraphicSystem.h>

#include <GBF/SpriteFactory.h>


//Tipos de Efeitos
enum TipoLuva {
  LUVA_ESQUERDA,
  LUVA_DIREITA
};
class LuvaAbstract : public MembroBase
{
  protected:
    TipoLuva eLuva;


  private:
    bool soco;


  public:
    //Construtor
    LuvaAbstract();

    //Destrutor
    virtual ~LuvaAbstract();

    void setSoco(bool soco);

    bool isSoco();

    bool isLuvaDireita();

    bool isLuvaEsquerda();

};
#endif
