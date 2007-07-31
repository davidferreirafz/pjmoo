
#ifndef _EFEITOSANGUE_H
#define _EFEITOSANGUE_H

#include "EfeitoAbstract.h"
#include <GBF/GraphicSystemImageBufferManager.h>
#include <GBF/SpriteFactory.h>

class EfeitoSangue : public EfeitoAbstract
{
  public:
    virtual ~EfeitoSangue();

    EfeitoSangue();


};
//Tipos de Efeitos
enum EnumEfeito {
  EFEITO_SANGUE
};
#endif
