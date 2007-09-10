
#include "UserInterfaceEstiloVisual.h"

UserInterfaceEstiloVisual::UserInterfaceEstiloVisual()
{
    if (gsGFX==NULL){
        gsGFX = GraphicSystemGFX::getInstance();
    }

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

GraphicSystemGFX * UserInterfaceEstiloVisual::gsGFX =NULL;

