
#include "UserInterfaceEstiloVisualSolido.h"

UserInterfaceEstiloVisualSolido::UserInterfaceEstiloVisualSolido() 
{
}
UserInterfaceEstiloVisualSolido::UserInterfaceEstiloVisualSolido(const UserInterfaceEstiloVisualSolido & base):UserInterfaceEstiloVisual(base) 
{
    corFundo=base.corFundo;
}
UserInterfaceEstiloVisualSolido::~UserInterfaceEstiloVisualSolido() 
{
}
void UserInterfaceEstiloVisualSolido::setCorFundo(const CorPaleta & r, const CorPaleta & g, const CorPaleta & b) 
{
    corFundo.r=r;
    corFundo.g=g;
    corFundo.b=b;
}
//Desenha o EstiloVisual do Componente
void UserInterfaceEstiloVisualSolido::desenhar() 
{
    gsGFX->setColor(corFundo.r,corFundo.g,corFundo.b);
    gsGFX->retanguloPreenchido(posicao.x,posicao.y,dimensao.w,dimensao.h);

    gsGFX->setColor(corBorda.r,corBorda.g,corBorda.b);
    gsGFX->retangulo(posicao.x,posicao.y,dimensao.w,dimensao.h);
}
UserInterfaceEstiloVisual * UserInterfaceEstiloVisualSolido::clone() 
{
   return new UserInterfaceEstiloVisualSolido(*this);
}
