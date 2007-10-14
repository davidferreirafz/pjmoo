
#include "FaseFactory.h"

//criar fabrica de fase baseada no conceito de prototype

FaseAbstract * FaseFactory::criarFase(int numero)

{
    FaseAbstract * fase = NULL;
    switch(numero){
        case 1:
            fase = new FaseUm(Mascarado);
            fase->setTotalRound(3);
        break;
        case 2:
            fase = new FaseUm(Punk);
            fase->setTotalRound(5);
        break;
        case 3:
            fase = new FaseUm(Cobra);
            fase->setTotalRound(7);
        break;
        case 4:
            fase = new FaseUm(Skar);
            fase->setTotalRound(9);
        break;
        default:
            return NULL;
    }

    return fase;
}
bool FaseFactory::isProximaFase(int faseAtual)

{
    if (faseAtual<MAX_FASE){
        return true;
    } else {
        return false;
    }
}
const int FaseFactory::MAX_FASE;

