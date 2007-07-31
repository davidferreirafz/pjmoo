////    Pacanda - Based boxing game
////    Copyright (C) 2004-2006 David de Almeida Ferreira
////
////    This is free software; you can redistribute it and/or
////    modify it under the terms of the GNU General Public
////    License as published by the Free Software Foundation; either
////    version 2 of the License, or (at your option) any later version.
////
////    David de Almeida Ferreira (F-Z)
////        davidferreira@uol.com.br or davidferreira.fz@gmail.com
////        http://pjmoo.codigolivre.org.br
////////////////////////////////////////////////////////////////////////

#ifndef _LUTADORPLAYER_H
#define _LUTADORPLAYER_H

#include "LutadorAbstract.h"
#include <GBF/InputSystem.h>


class LutadorPlayer : public LutadorAbstract
{
  public:
    LutadorPlayer();

    virtual ~LutadorPlayer();

    virtual void acao(InputSystem * input);


};
#endif
