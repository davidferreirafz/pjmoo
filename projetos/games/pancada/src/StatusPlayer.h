
#ifndef _STATUSPLAYER_H
#define _STATUSPLAYER_H

#include "HUDLutador.h"

class StatusPlayer : public HUDLutador
{
  public:
    //Construtor
    StatusPlayer();

    //Destrutor
    virtual ~StatusPlayer();

    //Desenha a barra de informações do jogador
    void desenhar(int pontos, int round, int energia);

};
#endif
