#include "InterfaceObjeto.h"

InterfaceObjeto::InterfaceObjeto()
{
    gsGFX = GBF::Kernel::Graphic::GraphicSystem::getInstance()->gfx;
}

InterfaceObjeto::~InterfaceObjeto()
{
    //dtor
}
bool InterfaceObjeto::colidiu(Regiao b)
{
    Regiao a=getAreaColisao();

    if ((a.posicao.x + a.dimensao.w >= b.posicao.x)&&
        (a.posicao.x <= b.posicao.x + b.dimensao.w)&&
        (a.posicao.y + a.dimensao.h >= b.posicao.y)&&
        (a.posicao.y <= b.posicao.y + b.dimensao.h)){
            return true;
    } else {
        return false;
    }
}
