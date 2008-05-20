
#ifndef _MEMBROBASE_H
#define _MEMBROBASE_H

#include <GBF/SpritePersonagem.h>

#include <GBF/ImageBase.h>

#include <GBF/GBF.h>


class MembroBase
{
  public:
    MembroBase();

    virtual ~MembroBase();

    void setCima();

    void setBaixo();

    void setSprite(GBF::Imagem::Sprite::SpritePersonagem * sprite);

    virtual void setPosicao(int x, int y) = 0;

    GBF::Area getArea();

    GBF::Ponto getPosicao();

    virtual void desenhar();


  protected:
    GBF::Ponto posicao;

    GBF::Imagem::Sprite::SpritePersonagem * sprite;

};
#endif
