
#ifndef _USERINTERFACEESTILOVISUALSOLIDO_H
#define _USERINTERFACEESTILOVISUALSOLIDO_H

#include <GBF/GBF_define.h>

#include "UserInterfaceEstiloVisual.h"
#include <GBF/UtilColor.h>


class UserInterfaceVisualSolido : public UserInterfaceVisual
{
  public:
    UserInterfaceVisualSolido();

    UserInterfaceVisualSolido(const UserInterfaceVisualSolido & base);

    virtual ~UserInterfaceVisualSolido();

    void setCorFundo(const CorPaleta & r, const CorPaleta & g, const CorPaleta & b);

    //Desenha o EstiloVisual do Componente
    virtual void desenhar();

    virtual UserInterfaceVisual * clone();


  protected:
    RGB corFundo;

};
#endif
