
#ifndef _FASEFACTORY_H
#define _FASEFACTORY_H

#include "FaseAbstract.h"
#include "FaseUm.h"

class FaseFactory
{
  private:
    static const int MAX_FASE =  1;


  public:
    static bool isProximaFase(int faseAtual);

    static FaseAbstract * criarFase(int numero);


};
#endif
