
#ifndef _LUTADORPC_H
#define _LUTADORPC_H

#include "LutadorAbstract.h"
#include "Define.h"
#include <GBF/InputSystem.h>

#include <GBF/ImageBase.h>


class LutadorPC : public LutadorAbstract
{
  public:
    LutadorPC(TipoLutador tipo);

    virtual ~LutadorPC();

    virtual void update(GBF::Kernel::Input::InputSystem * input);


  protected:
    virtual void visao(const GBF::Area & adversario);

};
#endif
