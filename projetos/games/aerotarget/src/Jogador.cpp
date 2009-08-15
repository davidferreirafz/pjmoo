#include "Jogador.h"

Jogador::Jogador()
{
    GBF::Imagem::SpriteFactory *spriteFactory = new GBF::Imagem::SpriteFactory("sprites");

    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,0,59,43,3,6));
    getSpritePrincipal()->setQtdDirecoes(1);
    getSpritePrincipal()->animacao.setAutomatico(true);

    delete (spriteFactory);

    setPosicao(320,400);
}

Jogador::~Jogador()
{
    //dtor
}

void Jogador::acao(GBF::Kernel::Input::InputSystem * input)
{
    if (input->teclado->isKey(SDLK_RIGHT)){
        posicao.x+=4;
    } else if (input->teclado->isKey(SDLK_LEFT)){
        posicao.x-=4;
    }
}
