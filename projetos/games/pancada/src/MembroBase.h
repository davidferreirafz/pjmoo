
#ifndef _MEMBROBASE_H
#define _MEMBROBASE_H

#include <GBF/SpritePersonagem.h>

#include <GBF/GraphicSystemImage.h>

#include <GBF/GBF_define.h>


class MembroBase
{
  public:
    MembroBase();

    virtual ~MembroBase();

    void setCima();

    void setBaixo();

    void setSprite(SpritePersonagem * sprite);

    virtual void setPosicao(int x, int y) = 0;

    Area getArea();

    Ponto getPosicao();

    virtual void desenhar();


  protected:
    Ponto posicao;

    SpritePersonagem * sprite;

};
#endif
