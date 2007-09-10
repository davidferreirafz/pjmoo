
#ifndef _USERINTERFACEESTILOVISUAL_H
#define _USERINTERFACEESTILOVISUAL_H

#include <GBF/GBF_define.h>

#include <GBF/UtilColor.h>

#include <GBF/GraphicSystemGFX.h>


class UserInterfaceEstiloVisual
{
  public:
    UserInterfaceEstiloVisual();

    virtual ~UserInterfaceEstiloVisual();

    void setCorBorda(const CorPaleta & r, const CorPaleta & g, const CorPaleta & b);

    //Aplica o efeito visual
    virtual void aplicar(Ponto posicao, Dimensao dimensao)=0;

    //Desenha o EstiloVisual do Componente
    virtual void desenhar(const Ponto & posicao, const Dimensao & dimensao) = 0;


  protected:
    RGB corBorda;

    static GraphicSystemGFX * gsGFX;

};
#endif
