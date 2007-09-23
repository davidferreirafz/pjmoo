
#include "UserInterfaceBotao.h"

UserInterfaceBotao::UserInterfaceBotao(std::string fonte, std::string chaveTexto, const SDLKey & tecla)
{
    botao.setFonte(fonte);
    botao.setChaveTexto(chaveTexto);
    this->tecla=tecla;
}
UserInterfaceBotao::~UserInterfaceBotao()
{
}
//Desenha o botão
void UserInterfaceBotao::desenhar(const Ponto & posicao)
{
    Dimensao dimensao = wsManager->getFonte(botao.getFonte())->getDimensao();
    int tamanhoTexto = wsManager->getLarguraLinha(botao.getFonte(),botao.getChaveTexto());

    int posicaoTextoHorizontal = int(posicao.x - tamanhoTexto);
    int posicaoTextoVertical   = int(posicao.y - (dimensao.h * 1.2));

    wsManager->escreverLocalizado(botao.getFonte(),posicaoTextoHorizontal,posicaoTextoVertical,botao.getChaveTexto());
}
//Retorna a tecla correspondente ao botão
SDLKey UserInterfaceBotao::getTecla()
{
    return tecla;
}
