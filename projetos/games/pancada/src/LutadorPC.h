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

#ifndef _LUTADORPC_H
#define _LUTADORPC_H

#include "LutadorAbstract.h"
#include <GBF/InputSystem.h>


class LutadorPC : public LutadorAbstract
{
  public:
    LutadorPC(TipoLutador tipo);

    virtual ~LutadorPC();

    virtual void acao(InputSystem * input);


};
#endif
