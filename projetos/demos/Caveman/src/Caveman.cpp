
#include "Caveman.h"



Caveman::Caveman()
{
    GBF::Imagem::SpriteFactory *spriteFactory = new GBF::Imagem::SpriteFactory("personagem");

    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,0,40,64,4,4));
    getSpritePrincipal()->setQtdDirecoes(2);
    getSpritePrincipal()->animacao.setAutomatico(false);

    delete(spriteFactory);

    pulando = false;
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

    if ((input->teclado->isKey(SDLK_UP)&&(pulando==false))){
        saltoVelocidade.y=30;
        pulando = true;
        deslocamento=0;
        //posicao.y-=4;
        inicioSalto = posicao;
    } else if (input->teclado->isKey(SDLK_DOWN)){
        //posicao.y+=4;
    }

    //aumentar velocidade da queda do pulo
    //quando o personagem cai do brick a velocidade está boa, mas quando ele pula, fica
    //planando.
    if (pulando){
        //std::cout << " iniciou y:"  << posicao.y;
        if (saltoVelocidade.y>=0){
            saltoVelocidade.y -= aceleracao;
        } else
        if (posicao.y>=inicioSalto.y+(getDimensao().h*0.6)){
            saltoVelocidade.y = -10;
        }

        posicao.y -= saltoVelocidade.y;
        //std::cout << " salto: "<< saltoVelocidade.y;

        //std::cout << " pulou y:"  << posicao.y <<std::endl;

    } else {
        posicao.y += 10;
    }


}

void Caveman::setParouCair()
{
    pulando = false;
    deslocamento = 0;
    saltoVelocidade.y=0;
}



