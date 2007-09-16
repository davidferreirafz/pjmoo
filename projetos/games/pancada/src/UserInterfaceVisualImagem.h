
#ifndef _USERINTERFACEESTILOVISUALIMAGEM_H
#define _USERINTERFACEESTILOVISUALIMAGEM_H

#include <GBF/GBF_define.h>

#include "UserInterfaceEstiloVisual.h"
#include <GBF/FrameLayer.h>

#include <GBF/GraphicSystemImageBufferManager.h>

#include <GBF/SpriteFactory.h>


enum UserInterfaceVisualTipoBackground {
  BACKGROUND_LINES =0,
  BACKGROUND_RINGS =1,
  BACKGROUND_CHESS =2,
  BAKCGROUND_SQUARE =3
};
class UserInterfaceVisualImagem : public UserInterfaceVisual
{
  public:
    UserInterfaceVisualImagem();

    UserInterfaceVisualImagem(const UserInterfaceVisualImagem & base);

    virtual ~UserInterfaceVisualImagem();

    //Aplica o efeito visual
    virtual void aplicar(const Ponto & posicao, const Dimensao & dimensao);

    //Desenha o EstiloVisual do Componente
    virtual void desenhar();

    virtual UserInterfaceVisual * clone();

    //Define o estilo de background a ser utilizado
    void setTipoBackground(UserInterfaceVisualTipoBackground tipo);


  protected:
    FrameLayer * background;

    static GraphicSystemImageBufferManager * gsImageBufferManager;

    //Tipo de Background a ser utilizado
    UserInterfaceVisualTipoBackground tipoBackground;

};
#endif
