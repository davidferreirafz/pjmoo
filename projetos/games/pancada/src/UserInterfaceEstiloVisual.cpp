
#include "UserInterfaceEstiloVisual.h"

UserInterfaceVisual::UserInterfaceVisual() 
{
    if (gsGFX==NULL){
        gsGFX = GraphicSystemGFX::getInstance();
    }

}
UserInterfaceVisual::UserInterfaceVisual(const UserInterfaceVisual & base) 
{
    posicao  = base.posicao;
    dimensao = base.dimensao;
    corBorda = base.corBorda;
}
UserInterfaceVisual::~UserInterfaceVisual() 
{
}
void UserInterfaceVisual::setCorBorda(const CorPaleta & r, const CorPaleta & g, const CorPaleta & b) 
{
    corBorda.r=r;
    corBorda.g=g;
    corBorda.b=b;
}
//Aplica o efeito visual
void UserInterfaceVisual::aplicar(const Ponto & posicao, const Dimensao & dimensao) 
{
    this->dimensao=dimensao;
    this->posicao=posicao;
}
GraphicSystemGFX * UserInterfaceVisual::gsGFX =NULL;

