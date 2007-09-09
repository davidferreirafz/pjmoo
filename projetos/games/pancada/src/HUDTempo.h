
#ifndef _HUDTEMPO_H
#define _HUDTEMPO_H

#include "HUDAbstract.h"
#include <GBF/GraphicSystemImageBufferManager.h>

#include <GBF/SpriteFactory.h>


class HUDTempo : public HUDAbstract
{
  public:
    HUDTempo();

    virtual ~HUDTempo();

    void desenhar(int tempo);

};
#endif
