
#ifndef _FASEFACTORY_H
#define _FASEFACTORY_H

#include "FaseAbstract.h"
#include "FaseUm.h"

class FaseFactory
{
  public:
    static FaseAbstract * criarFase(int numero);

    static bool isProximaFase(int faseAtual);


  private:
    static const int MAX_FASE =   1;

};
#endif
