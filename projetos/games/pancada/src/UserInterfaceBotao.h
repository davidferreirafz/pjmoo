
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

    //Desenha o botão
    void desenhar(const Ponto & posicao);

    //Retorna a tecla correspondente ao botão
    SDLKey getTecla();


  protected:
    SDLKey tecla;

    UserInterfaceObjetoTexto botao;

};
#endif
