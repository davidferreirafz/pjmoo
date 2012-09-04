#include "InterfaceObjeto.h"

InterfaceObjeto::InterfaceObjeto()
{
    gsGFX = GBF::Kernel::Graphic::GraphicSystem::getInstance()->gfx;
}

InterfaceObjeto::~InterfaceObjeto()
{
}

bool InterfaceObjeto::colidiu(GBF::Area b)
{
    GBF::Area a=getAreaColisao();

    if ((a.left + a.right >= b.left)&&
        (a.left <= b.left + b.right)&&
        (a.top + a.bottom >= b.top)&&
        (a.top <= b.top + b.bottom)){
            return true;
    } else {
        return false;
    }
}
