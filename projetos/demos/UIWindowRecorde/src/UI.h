#ifndef TECLADO_DEFINE_INCLUDED
#define TECLADO_DEFINE_INCLUDED

#include <GBF/GBF.h>

#include <string>

struct UIFonteReferencia
{
    std::string nome;
    GBF::Dimensao dimensao;
};

struct UIFonteExtendida : public UIFonteReferencia
{
    GBF::Ponto posicao;
};

struct UICursor
{
    bool show;
    GBF::Ponto posicao;
};


#endif // TECLADO_DEFINE_INCLUDED
