
#ifndef _USERINTERFACEBOTAO_H
#define _USERINTERFACEBOTAO_H

#include "UserInterfaceObjetoTexto.h"
#include <string>

#include <GBF/GBF_define.h>

#include "UserInterfaceComponente.h"

class UserInterfaceBotao : public UserInterfaceComponente
{
  protected:
    UserInterfaceObjetoTexto botao;


  public:
    UserInterfaceBotao(std::string fonte, std::string chaveTexto);

    virtual ~UserInterfaceBotao();

    //Desenha o botão
    void desenhar(const Ponto & posicao);

};
#endif
