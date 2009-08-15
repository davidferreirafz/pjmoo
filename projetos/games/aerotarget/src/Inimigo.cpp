#include "Inimigo.h"

Inimigo::Inimigo()
{
    GBF::Imagem::SpriteFactory *spriteFactory = new GBF::Imagem::SpriteFactory("sprites");

    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,77,32,32,3,6));
    getSpritePrincipal()->setQtdDirecoes(1);
    getSpritePrincipal()->animacao.setAutomatico(true);

    delete (spriteFactory);

    iniciar();
}

Inimigo::~Inimigo()
{
}

void Inimigo::acao(GBF::Kernel::Input::InputSystem * input)
{
    posicao.y+=velocidade;

    if (posicao.y>640){
        iniciar();
    }
}

void Inimigo::iniciar()
{
    GBF::Dimensao d = getDimensao();

    GBF::Ponto p;
    p.y= 0 - d.h;
    p.x= rand() % (640 - d.w);

    setPosicao(p);

    velocidade=2+rand()%5;
}
