
#ifndef _FASEUM_H
#define _FASEUM_H

#include "FaseAbstract.h"
#include "Define.h"

class FaseUm : public FaseAbstract
{
  public:
    FaseUm(TipoLutador tipo);

    virtual ~FaseUm();

    virtual void iniciar();

};
#endif
