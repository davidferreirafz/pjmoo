
#ifndef _USERINTERFACEESTILOVISUAL_H
#define _USERINTERFACEESTILOVISUAL_H

#include <GBF/GBF_define.h>

#include <GBF/UtilColor.h>

#include <GBF/GraphicSystemGFX.h>


class UserInterfaceVisual
{
  public:
    UserInterfaceVisual();

    UserInterfaceVisual(const UserInterfaceVisual & base);

    virtual ~UserInterfaceVisual();

    void setCorBorda(const CorPaleta & r, const CorPaleta & g, const CorPaleta & b);

    //Aplica o efeito visual
    virtual void aplicar(const Ponto & posicao, const Dimensao & dimensao);

    //Desenha o EstiloVisual do Componente
    virtual void desenhar() = 0;

    virtual UserInterfaceVisual * clone() = 0;


  protected:
    RGB corBorda;

    Ponto posicao;

    Dimensao dimensao;

    static GraphicSystemGFX * gsGFX;

};
#endif
