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

#ifndef _CABECAFACTORY_H
#define _CABECAFACTORY_H

#include "Cabeca.h"
#include <GBF/SpriteFactory.h>

#include <GBF/GraphicSystemImageBufferManager.h>


class CabecaFactory
{
  public:
    CabecaFactory();

    virtual ~CabecaFactory();

    Cabeca * criar(int tipo);


};
#endif
