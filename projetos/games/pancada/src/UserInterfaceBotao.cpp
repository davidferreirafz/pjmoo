
#include "UserInterfaceBotao.h"

UserInterfaceBotao::UserInterfaceBotao(std::string fonte, std::string chaveTexto) 
{
    botao.setFonte(fonte);
    botao.setChaveTexto(chaveTexto);
}
UserInterfaceBotao::~UserInterfaceBotao() 
{
}
//Desenha o botão
void UserInterfaceBotao::desenhar(const Ponto & posicao) 
{
    Dimensao dimensao = wsManager->getFonte(botao.getFonte())->getDimensao();

    int posicaoTextoHorizontal = posicao.x;
    int posicaoTextoVertical  = posicao.y - (dimensao.h * 1.2);

    wsManager->escreverLocalizado(botao.getFonte(),posicaoTextoHorizontal,posicaoTextoVertical,botao.getChaveTexto());

}
