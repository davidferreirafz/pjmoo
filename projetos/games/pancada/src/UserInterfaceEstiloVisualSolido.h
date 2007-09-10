
#ifndef _USERINTERFACEESTILOVISUALSOLIDO_H
#define _USERINTERFACEESTILOVISUALSOLIDO_H

#include <GBF/GBF_define.h>

#include <GBF/UtilColor.h>

#include "UserInterfaceEstiloVisual.h"

class UserInterfaceEstiloVisualSolido : public UserInterfaceEstiloVisual
{
  public:
    UserInterfaceEstiloVisualSolido();

    virtual ~UserInterfaceEstiloVisualSolido();

    void setCorFundo(const CorPaleta & r, const CorPaleta & g, const CorPaleta & b);

    //Desenha o EstiloVisual do Componente
    virtual void desenhar(const Ponto & posicao, const Dimensao & dimensao);
    virtual void aplicar(Ponto posicao, Dimensao dimensao);


  protected:
    RGB corFundo;

};
#endif
