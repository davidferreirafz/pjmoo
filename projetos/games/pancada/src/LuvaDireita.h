
#ifndef _LUVADIREITA_H
#define _LUVADIREITA_H

#include "LuvaAbstract.h"

class LuvaDireita : public LuvaAbstract
{
  public:
    LuvaDireita();

    virtual ~LuvaDireita();

    virtual void setPosicao(int x, int y);

};
#endif
