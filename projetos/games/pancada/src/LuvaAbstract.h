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

#ifndef _LUVAABSTRACT_H
#define _LUVAABSTRACT_H

#include <GBF/GraphicSystem.h>

#include <GBF/SpriteFactory.h>

#include "MembroBase.h"

//Tipos de Efeitos
enum EnumLuva {
  LUVA_ESQUERDA,
  LUVA_DIREITA
};
class LuvaAbstract : public MembroBase
{
  protected:
    EnumLuva eLuva;


  private:
    bool soco;


  public:
    //Construtor
    LuvaAbstract();

    //Destrutor
    virtual ~LuvaAbstract();

    void setSoco(bool soco);

    bool isSoco();

    bool isLuvaDireita();

    bool isLuvaEsquerda();


};
#endif
