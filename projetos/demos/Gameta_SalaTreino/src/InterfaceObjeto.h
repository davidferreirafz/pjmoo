#ifndef INTERFACEOBJETO_H
#define INTERFACEOBJETO_H

#include <GBF/GBFramework.h>

struct Regiao
{
    GBF::Ponto posicao;
    GBF::Dimensao dimensao;
};


class InterfaceObjeto
{
    public:
        InterfaceObjeto();
        virtual ~InterfaceObjeto();
        virtual bool colidiu(Regiao regiao);
        virtual Regiao getAreaColisao()=0;
    protected:
        GBF::Kernel::Graphic::GFX * gsGFX;
    private:
};

#endif // INTERFACEOBJETO_H
