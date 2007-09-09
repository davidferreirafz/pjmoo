
#ifndef _STATUSPC_H
#define _STATUSPC_H

#include "HUDLutador.h"

class StatusPC : public HUDLutador
{
  public:
    //Construtor
    StatusPC();

    //Destrutor
    virtual ~StatusPC();

    //Desenha a barra de informações do PC
    void desenhar(int pontos, int round, int energia);

};
#endif
