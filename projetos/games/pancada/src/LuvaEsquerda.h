
#ifndef _LUVAESQUERDA_H
#define _LUVAESQUERDA_H

#include "LuvaAbstract.h"

class LuvaEsquerda : public LuvaAbstract
{
  public:
    LuvaEsquerda();

    virtual ~LuvaEsquerda();

    virtual void setPosicao(int x, int y);

};
#endif
