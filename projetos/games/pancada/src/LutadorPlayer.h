
#ifndef _LUTADORPLAYER_H
#define _LUTADORPLAYER_H

#include "LutadorAbstract.h"
#include <GBF/InputSystem.h>


class LutadorPlayer : public LutadorAbstract
{
  public:
    LutadorPlayer();

    virtual ~LutadorPlayer();

    virtual void acao(GBF::Kernel::Input::InputSystem * input);

};
#endif
