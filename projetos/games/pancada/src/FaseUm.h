
#ifndef _FASEUM_H
#define _FASEUM_H

#include <GBF/SoundSystem.h>

#include "FaseAbstract.h"
#include "LutadorPC.h"
#include "LutadorPlayer.h"

class FaseUm : public FaseAbstract
{
  public:
    FaseUm(TipoLutador tipo);

    virtual ~FaseUm();

    virtual void iniciar();


};
#endif
