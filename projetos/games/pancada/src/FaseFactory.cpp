
#include "FaseFactory.h"

const int FaseFactory::MAX_FASE;

bool FaseFactory::isProximaFase(int faseAtual)
{
    if (faseAtual<MAX_FASE){
        return true;
    } else {
        return false;
    }
}
FaseAbstract * FaseFactory::criarFase(int numero)
{
    switch(numero){
        case 1:
            return new FaseUm();
        break;
        default:
            return NULL;
    }
}
