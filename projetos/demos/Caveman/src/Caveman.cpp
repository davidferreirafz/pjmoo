
#include "Caveman.h"



Caveman::Caveman()
{
    GBF::Imagem::SpriteFactory *spriteFactory = new GBF::Imagem::SpriteFactory("personagem");

    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,0,40,64,4,4));
    getSpritePrincipal()->setQtdDirecoes(2);
    getSpritePrincipal()->animacao.setAutomatico(false);
    getSpritePrincipal()->setDirecao(GBF::Imagem::Sprite::DR_DIREITA);

    delete(spriteFactory);

    pulando = false;
    caindo = true;
    aceleracao = 5;
    saltoVelocidade.y = 0;
    deslocamento = 0;
}
Caveman::~Caveman()
{
}
void Caveman::acao(GBF::Kernel::Input::InputSystem * input)
{
    if (input->teclado->isKey(SDLK_RIGHT)){
        getSpritePrincipal()->setDirecao(GBF::Imagem::Sprite::DR_DIREITA);
        posicao.x+=4+deslocamento;
    } else if (input->teclado->isKey(SDLK_LEFT)){
        getSpritePrincipal()->setDirecao(GBF::Imagem::Sprite::DR_ESQUERDA);
        posicao.x-=4+deslocamento;
    }

    if ((input->teclado->isKey(SDLK_UP)&&(!pulando)&&(!caindo))){
        saltoVelocidade.y=30;
        pulando = true;
        deslocamento=0;
        inicioSalto = posicao;
    } else if (input->teclado->isKey(SDLK_DOWN)){

    }
    //std::cout << " velocidade.y:" << saltoVelocidade.y << " posicao.y:" << posicao.y <<std::endl;

    if (pulando){
        if (saltoVelocidade.y>=0){
            saltoVelocidade.y -= aceleracao;

        }
        if (posicao.y>=inicioSalto.y+(getDimensao().h*0.6)){
            saltoVelocidade.y = -aceleracao;
            caindo = true;
            pulando = false;
        }

        posicao.y -= saltoVelocidade.y;
    } else {
        posicao.y += aceleracao*1.5;
    }
    caindo=true;
}

void Caveman::setPisouChao()
{
    pulando = false;
    caindo = false;
    deslocamento = 0;
    saltoVelocidade.y=0;
    getSpritePrincipal()->animacao.setAutomatico(false);
}

void Caveman::setBateuCabeca(){
    pulando = false;
    caindo = true;
    getSpritePrincipal()->animacao.setAutomatico(true);
}


