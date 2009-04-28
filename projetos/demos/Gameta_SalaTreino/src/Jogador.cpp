
#include "Jogador.h"



Jogador::Jogador()
{
    GBF::Imagem::SpriteFactory *spriteFactory = new GBF::Imagem::SpriteFactory("personagem_parado");
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,0,42,98,5,10));
    getSpritePrincipal()->animacao.setAutomatico(true);
    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("personagem_andando");
    adicionarSprite(spriteFactory->criarSpritePersonagem(0,0,50,98,10,2),"andando");
    getSprite("andando")->animacao.setAutomatico(false);
    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("personagem_recuando");
    adicionarSprite(spriteFactory->criarSpritePersonagem(0,0,69,96,4,2),"recuando");
    getSprite("recuando")->animacao.setAutomatico(false);
    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("personagem_avancando");
    adicionarSprite(spriteFactory->criarSpritePersonagem(0,0,84,86,4,2),"avancando");
    getSprite("avancando")->animacao.setAutomatico(false);
    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("personagem_morrendo");
    adicionarSprite(spriteFactory->criarSpritePersonagem(0,0,115,80,4,1),"morrendo");
    getSprite("morrendo")->animacao.setAutomatico(false);
    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("personagem_pulando");
    adicionarSprite(spriteFactory->criarSpritePersonagem(0,0,74,101,4,1),"pulando");
    getSprite("pulando")->animacao.setAutomatico(false);
    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("personagem_caindo");
    adicionarSprite(spriteFactory->criarSpritePersonagem(0,0,80,105,3,1),"caindo");
    getSprite("caindo")->animacao.setAutomatico(false);
    delete(spriteFactory);

    setPosicao(100,114);

    estado=PARADO;
    delay.acao=6;
    alturaPulo.a=64;
    alturaPulo.b=90;
    alturaPulo.c=122;
    alturaPulo.corrente=alturaPulo.a;
}
Jogador::~Jogador()
{
}
void Jogador::acao(GBF::Kernel::Input::InputSystem * input)
{
        //estado=PARADO;
    if (input->teclado->isKey(SDLK_RIGHT)){
        if (input->teclado->isKey(SDLK_LSHIFT)){
            posicao.x+=10;
            estado=AVANCO;
        } else {
            posicao.x+=1;
            estado=ANDANDO;
        }
        getSprite(getAliasSprite())->animacao.processarManual();

    } else if (input->teclado->isKey(SDLK_LEFT)){
        if (input->teclado->isKey(SDLK_LSHIFT)){
            posicao.x-=10;
            estado=RECUO;
        } else {
            posicao.x-=1;
            estado=ANDANDO;
        }
        getSprite(getAliasSprite())->animacao.processarManual();
    }

    if ((estado!=PULANDO)&&(estado!=CAINDO)){
        if (input->teclado->isKey(SDLK_c)){
            estado=PULANDO;
            getSprite("pulando")->animacao.setInicio();
            delay.acao=6;
            alturaPulo.corrente=alturaPulo.a;
        } else if (input->teclado->isKey(SDLK_x)){
            estado=PULANDO;
            getSprite("pulando")->animacao.setInicio();
            delay.acao=10;
            alturaPulo.corrente=alturaPulo.b;
        } else if (input->teclado->isKey(SDLK_z)){
            estado=PULANDO;
            getSprite("pulando")->animacao.setInicio();
            delay.acao=12;
            alturaPulo.corrente=alturaPulo.c;
        }
    } else  if(input->teclado->isKey(SDLK_m)){
        estado=MORRENDO;
        vivo=false;
        getSprite("morrendo")->animacao.setInicio();
    } else if(input->teclado->isKey(SDLK_r)){
        estado=PARADO;
        vivo=true;
    }


    if (posicao.x<20){
        posicao.x=20;
    } else {
        int d = getSprite(getAliasSprite())->getTamanho().w;
        if (posicao.x>304-20-d){
            posicao.x=304-20-d;
        }
    }

    if (estado==PULANDO){
        if (!getSprite(getAliasSprite())->animacao.isFim()){
            getSprite(getAliasSprite())->animacao.processarManual();
        }
        if (posicao.y>=alturaPulo.corrente){
            posicao.y-=10;
        } else {
            delay.acao--;
            if (delay.acao<=0) {
                estado=CAINDO;
                getSprite("caindo")->animacao.setInicio();
            }
        }

    } else if (estado==CAINDO){
        if (posicao.y<110){
            posicao.y+=6;
        if (!getSprite(getAliasSprite())->animacao.isFim()){
            getSprite(getAliasSprite())->animacao.processarManual();
        }
        } else {
            estado=PARADO;
        }
    }
}

void Jogador::desenhar()
{
    if (vivo){
        getSprite(getAliasSprite())->desenhar(posicao.x,posicao.y);
    } else {
        if(!getSprite("morrendo")->animacao.isFim()){
            getSprite("morrendo")->animacao.processarManual();
        }
        getSprite("morrendo")->desenhar(posicao.x,posicao.y+20);
    }
}


std::string Jogador::getAliasSprite(){

    std::string aliasSprite;

    switch (estado)
    {
        case ANDANDO:
                aliasSprite="andando";
            break;
        case RECUO:
                aliasSprite="recuando";
            break;
        case AVANCO:
                aliasSprite="avancando";
            break;
        case MORRENDO:
                aliasSprite="morrendo";
            break;
        case PULANDO:
                aliasSprite="pulando";
            break;
        case CAINDO:
                aliasSprite="caindo";
            break;
        case PARADO:
        default:
                aliasSprite="principal";
            break;
    }

    return aliasSprite;
}

