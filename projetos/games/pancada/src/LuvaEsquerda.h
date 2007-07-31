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

#ifndef _LUVAESQUERDA_H
#define _LUVAESQUERDA_H

#include "LuvaAbstract.h"

class LuvaEsquerda : public LuvaAbstract
{
  public:
    LuvaEsquerda();

    virtual ~LuvaEsquerda();

    virtual void setPosicao(int x, int y);


};
#endif
