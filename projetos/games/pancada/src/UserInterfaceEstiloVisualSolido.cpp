
#include "UserInterfaceEstiloVisualSolido.h"

UserInterfaceVisualSolido::UserInterfaceVisualSolido() 
{
}
UserInterfaceVisualSolido::UserInterfaceVisualSolido(const UserInterfaceVisualSolido & base):UserInterfaceVisual(base) 
{
    corFundo=base.corFundo;
}
UserInterfaceVisualSolido::~UserInterfaceVisualSolido() 
{
}
void UserInterfaceVisualSolido::setCorFundo(const CorPaleta & r, const CorPaleta & g, const CorPaleta & b) 
{
    corFundo.r=r;
    corFundo.g=g;
    corFundo.b=b;
}
//Desenha o EstiloVisual do Componente
void UserInterfaceVisualSolido::desenhar() 
{
    gsGFX->setColor(corFundo.r,corFundo.g,corFundo.b);
    gsGFX->retanguloPreenchido(posicao.x,posicao.y,dimensao.w,dimensao.h);

    gsGFX->setColor(corBorda.r,corBorda.g,corBorda.b);
    gsGFX->retangulo(posicao.x,posicao.y,dimensao.w,dimensao.h);
}
UserInterfaceVisual * UserInterfaceVisualSolido::clone() 
{
   return new UserInterfaceVisualSolido(*this);
}
