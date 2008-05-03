#ifndef TECLADO_DEFINE_INCLUDED
#define TECLADO_DEFINE_INCLUDED

#include <GBF/GBF_define.h>

#include <string>

struct UIFonteReferencia
{
    std::string nome;
    Dimensao dimensao;
};

struct UIFonteExtendida : public UIFonteReferencia
{
    Ponto posicao;
};

struct UICursor
{
    bool show;
    Ponto posicao;
};


#endif // TECLADO_DEFINE_INCLUDED
