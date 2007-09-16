
#ifndef _USERINTERFACEESTILOVISUALSOLIDO_H
#define _USERINTERFACEESTILOVISUALSOLIDO_H

#include <GBF/GBF_define.h>

#include <GBF/UtilColor.h>

#include "UserInterfaceEstiloVisual.h"

class UserInterfaceEstiloVisualSolido : public UserInterfaceEstiloVisual
{
  public:
    UserInterfaceEstiloVisualSolido();

    UserInterfaceEstiloVisualSolido(const UserInterfaceEstiloVisualSolido & base);

    virtual ~UserInterfaceEstiloVisualSolido();

    void setCorFundo(const CorPaleta & r, const CorPaleta & g, const CorPaleta & b);

    //Desenha o EstiloVisual do Componente
    virtual void desenhar();


  protected:
    RGB corFundo;


  public:
    virtual UserInterfaceEstiloVisual * clone();

};
#endif
