
#ifndef _CABECA_H
#define _CABECA_H

#include "MembroBase.h"
#include <GBF/GraphicSystemImage.h>

#include <cmath>


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
