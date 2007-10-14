
#ifndef _HUDTEMPO_H
#define _HUDTEMPO_H

#include "HUDAbstract.h"

class HUDTempo : public HUDAbstract
{
  public:
    HUDTempo();

    virtual ~HUDTempo();

    void desenhar(int tempo);

};
#endif
