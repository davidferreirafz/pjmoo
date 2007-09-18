
#ifndef _USERINTERFACEBOTAO_H
#define _USERINTERFACEBOTAO_H

#include <string>

#include <GBF/GBF_define.h>

#include "UserInterfaceComponente.h"
#include "UserInterfaceObjetoTexto.h"

class UserInterfaceBotao : public UserInterfaceComponente
{
  public:
    UserInterfaceBotao(std::string fonte, std::string chaveTexto, const SDLKey & tecla);

    virtual ~UserInterfaceBotao();

    //Desenha o bot�o
    void desenhar(const Ponto & posicao);

    //Retorna a tecla correspondente ao bot�o
    SDLKey getTecla();


  protected:
    SDLKey tecla;

    UserInterfaceObjetoTexto botao;

};
#endif
