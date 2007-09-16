
#ifndef _USERINTERFACEESTILOVISUALIMAGEM_H
#define _USERINTERFACEESTILOVISUALIMAGEM_H

#include <GBF/GBF_define.h>

#include "UserInterfaceEstiloVisual.h"
#include <GBF/FrameLayer.h>

#include <GBF/GraphicSystemImageBufferManager.h>

#include <GBF/SpriteFactory.h>


class UserInterfaceEstiloVisualImagem : public UserInterfaceEstiloVisual
{
  public:
    UserInterfaceEstiloVisualImagem();

    UserInterfaceEstiloVisualImagem(const UserInterfaceEstiloVisualImagem & base);

    virtual ~UserInterfaceEstiloVisualImagem();

    //Aplica o efeito visual
    virtual void aplicar(const Ponto & posicao, const Dimensao & dimensao);

    //Desenha o EstiloVisual do Componente
    virtual void desenhar();


  protected:
    FrameLayer * background;

    static GraphicSystemImageBufferManager * gsImageBufferManager;


  public:
    virtual UserInterfaceEstiloVisual * clone();

};
#endif
