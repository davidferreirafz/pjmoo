
#include "UserInterfaceEstiloVisual.h"

UserInterfaceEstiloVisual::UserInterfaceEstiloVisual() 
{
    if (gsGFX==NULL){
        gsGFX = GraphicSystemGFX::getInstance();
    }

}
UserInterfaceEstiloVisual::UserInterfaceEstiloVisual(const UserInterfaceEstiloVisual & base) 
{
    posicao  = base.posicao;
    dimensao = base.dimensao;
    corBorda = base.corBorda;
}
UserInterfaceEstiloVisual::~UserInterfaceEstiloVisual() 
{
}
void UserInterfaceEstiloVisual::setCorBorda(const CorPaleta & r, const CorPaleta & g, const CorPaleta & b) 
{
    corBorda.r=r;
    corBorda.g=g;
    corBorda.b=b;
}
//Aplica o efeito visual
void UserInterfaceEstiloVisual::aplicar(const Ponto & posicao, const Dimensao & dimensao) 
{
    this->dimensao=dimensao;
    this->posicao=posicao;
}
GraphicSystemGFX * UserInterfaceEstiloVisual::gsGFX =NULL;

