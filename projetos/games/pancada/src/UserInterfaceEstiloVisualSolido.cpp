
#include "UserInterfaceEstiloVisualSolido.h"

UserInterfaceEstiloVisualSolido::UserInterfaceEstiloVisualSolido()
{
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
void UserInterfaceEstiloVisualSolido::desenhar(const Ponto & posicao, const Dimensao & dimensao)
{
    gsGFX->setColor(corFundo.r,corFundo.g,corFundo.b);
    gsGFX->retanguloPreenchido(posicao.x,posicao.y,dimensao.w,dimensao.h);

    gsGFX->setColor(corBorda.r,corBorda.g,corBorda.b);
    gsGFX->retangulo(posicao.x,posicao.y,dimensao.w,dimensao.h);
}

void UserInterfaceEstiloVisualSolido::aplicar(Ponto posicao, Dimensao dimensao)
{
}

