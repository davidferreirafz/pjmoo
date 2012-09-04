#ifndef INTERFACEOBJETO_H
#define INTERFACEOBJETO_H

#include <GBF/GBFramework.h>
/*
struct Regiao
{
    GBF::Point posicao;
    GBF::Dimension dimensao;
};
*/
class InterfaceObjeto
{
    public:
        InterfaceObjeto();
        virtual ~InterfaceObjeto();
        virtual bool colidiu(GBF::Area regiao);
        virtual GBF::Area getAreaColisao() = 0;

    protected:
        GBF::Kernel::Graphic::GFX * gsGFX;

    private:
};

#endif // INTERFACEOBJETO_H
