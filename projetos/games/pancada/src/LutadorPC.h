
#ifndef _LUTADORPC_H
#define _LUTADORPC_H

#include "LutadorAbstract.h"
#include "Define.h"
#include <GBF/InputSystem.h>


class LutadorPC : public LutadorAbstract
{
  public:
    LutadorPC(TipoLutador tipo);

    virtual ~LutadorPC();

    virtual void acao(InputSystem * input);

};
#endif
