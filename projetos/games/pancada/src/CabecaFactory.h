
#ifndef _CABECAFACTORY_H
#define _CABECAFACTORY_H

#include "Cabeca.h"
#include "Define.h"
#include <GBF/GraphicSystem.h>

#include <GBF/SpriteFactory.h>


class CabecaFactory
{
  public:
    CabecaFactory();

    virtual ~CabecaFactory();

    Cabeca * criar(TipoLutador tipo);

};
#endif
