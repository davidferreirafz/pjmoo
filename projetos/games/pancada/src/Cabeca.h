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

#ifndef _CABECA_H
#define _CABECA_H

#include <cmath>

#include "MembroBase.h"

class Cabeca : public MembroBase
{
  public:
    //* Construtor 
    Cabeca();

    //Destrutor 
    virtual ~Cabeca();

    bool isColisao(Area aSoco);

    virtual void setPosicao(int x, int y);


};
#endif
