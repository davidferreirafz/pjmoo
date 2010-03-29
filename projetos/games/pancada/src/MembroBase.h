
#ifndef _MEMBROBASE_H
#define _MEMBROBASE_H

#include <GBF/SpriteCharacter.h>

#include <GBF/ImageBase.h>

#include <GBF/GBF.h>


class MembroBase
{
  public:
    MembroBase();

    virtual ~MembroBase();

    void setCima();

    void setBaixo();

    void setSprite(GBF::Image::Sprite::SpriteCharacter * sprite);

    virtual void setPosicao(int x, int y) = 0;

    GBF::Area getArea();

    GBF::Point getPosicao();

    virtual void desenhar();


  protected:
    GBF::Point posicao;

    GBF::Image::Sprite::SpriteCharacter * sprite;

};
#endif
