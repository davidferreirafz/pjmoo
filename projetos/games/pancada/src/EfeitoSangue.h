
#ifndef _EFEITOSANGUE_H
#define _EFEITOSANGUE_H

#include <GBF/ParticleSystemSprite.h>
#include <GBF/GraphicSystemImageBufferManager.h>
#include <GBF/SpriteFactory.h>

class EfeitoSangue : public ParticleSystemSprite
{
  public:
    virtual ~EfeitoSangue();

    EfeitoSangue();

    void executar();
    void criar(int x, int y);


};

#endif
