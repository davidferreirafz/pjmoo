#ifndef IA_H
#define IA_H

#include <cmath>

#include <GBF/GBF_define.h>
#include <GBF/SpriteFactory.h> //definição de Area


#include "define.h"



class IA
{
    public:
        static Decisao pensar(Area visao, Area areaVisaoBola, int raioVisao, Efeito efeito);
        static Area converter(Dimensao dimensao, Ponto ponto);
    protected:
    private:
};



#endif // IA_H
