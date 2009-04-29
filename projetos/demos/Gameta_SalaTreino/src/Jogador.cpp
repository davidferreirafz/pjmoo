
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

    spriteFactory = new GBF::Imagem::SpriteFactory("personagem_impulso");
    adicionarSprite(spriteFactory->criarSpritePersonagem(0,0,65,75,2,4),"impulso");
    getSprite("impulso")->animacao.setAutomatico(false);
    delete(spriteFactory);

    setPosicao(100,114);

    estado=PARADO;
    delay.acao=6;
    alturaPulo.super  = 64;
    alturaPulo.normal = 90;
    alturaPulo.fraco  =122;
    alturaPulo.corrente=alturaPulo.normal;
}
Jogador::~Jogador()
{
}
void Jogador::acao(GBF::Kernel::Input::InputSystem * input)
{
    if ((estado==PULANDO)||(estado==CAINDO)){
        if (input->teclado->isKey(SDLK_RIGHT)){
            posicao.x+=10;
        } else if ((input->teclado->isKey(SDLK_LEFT))){
            posicao.x-=10;
            if ((posicao.x<=20)&&(estado!=CAINDO)){
                onImpulso();
            }
        }
        if (estado==PULANDO){
            acaoPular();
        } else if (estado==CAINDO){
            acaoCair();
        }
    } else if (estado==IMPULSO){
            acaoImpulso();
    } else if(vivo){
        estado=PARADO;
        if (input->teclado->isKey(SDLK_RIGHT)){
            if (input->teclado->isKey(SDLK_LSHIFT)){
                acaoCorrer();
            } else {
                acaoAndar(1);
            }
            getSprite(getAliasSprite())->animacao.processarManual();

        } else if (input->teclado->isKey(SDLK_LEFT)){
            if (input->teclado->isKey(SDLK_LSHIFT)){
                acaoRecuar();
            } else {
                acaoAndar(-1);
            }
            getSprite(getAliasSprite())->animacao.processarManual();
        }

//        if ((estado!=PULANDO)&&(estado!=CAINDO)){
        if (input->teclado->isKey(SDLK_c)){
            onPular(SUPER);
        } else if (input->teclado->isKey(SDLK_x)){
            onPular(NORMAL);
        } else if (input->teclado->isKey(SDLK_z)){
            onPular(FRACO);
        }
//        }
    }

    if (posicao.x<20){
        posicao.x=20;
    } else {
        int d = getSprite(getAliasSprite())->getTamanho().w;
        if (posicao.x>304-20-d){
            posicao.x=304-20-d;
        }
    }
    if (posicao.y<=30){
        posicao.y=30;
    }

    if (input->teclado->isKey(SDLK_m)){
        onMorrer();
    } else if(input->teclado->isKey(SDLK_r)){
        estado=PARADO;
        vivo=true;
    }
}

void Jogador::desenhar()
{
    GBF::Ponto ponto = ajustar();

    if (!vivo){
        if(!getSprite("morrendo")->animacao.isFim()){
            getSprite("morrendo")->animacao.processarManual();
        }
    }

    getSprite(getAliasSprite())->desenhar(ponto.x,ponto.y);
}

GBF::Ponto Jogador::ajustar()
{
    GBF::Ponto ponto;

    switch (estado){
        case MORRENDO:  ponto.x=posicao.x;     ponto.y=posicao.y+20;  break;
        case PULANDO :  ponto.x=posicao.x-20;  ponto.y=posicao.y;     break;
        case CAINDO  :  ponto.x=posicao.x-20;  ponto.y=posicao.y;     break;
        case AVANCO  :  ponto.x=posicao.x;     ponto.y=posicao.y+16;  break;
        default:        ponto.x=posicao.x;     ponto.y=posicao.y;     break;
    }

    return ponto;
}

void Jogador::onPular(TipoPulo tipo)
{
    if ((estado!=PULANDO)&&(estado!=CAINDO)) {

        estado=PULANDO;
        getSprite("pulando")->animacao.setInicio();

        switch (tipo){
            case FRACO:
                    delay.acao=12;
                    alturaPulo.corrente=alturaPulo.fraco;
                break;
            case SUPER:
                    delay.acao=6;
                    alturaPulo.corrente=alturaPulo.super;
                break;
            case NORMAL:
            default:
                    delay.acao=10;
                    alturaPulo.corrente=alturaPulo.normal;
                break;
        }
    }
}

void Jogador::acaoPular()
{
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
}

void Jogador::onMorrer()
{
    estado=MORRENDO;
    vivo=false;
    getSprite("morrendo")->animacao.setInicio();
}

void Jogador::acaoCair()
{
    if (posicao.y<110){
        posicao.y+=6;
        if (!getSprite(getAliasSprite())->animacao.isFim()){
            getSprite(getAliasSprite())->animacao.processarManual();
        }
    } else {
        estado=PARADO;
    }
}

void Jogador::onImpulso()
{
    estado=IMPULSO;
    getSprite("impulso")->animacao.setInicio();
    getSprite("caindo")->animacao.setInicio();
}
void Jogador::acaoImpulso()
{
    if (posicao.x<100){
        posicao.x+=4;
        posicao.y-=4;
        if (!getSprite(getAliasSprite())->animacao.isFim()){
            getSprite(getAliasSprite())->animacao.processarManual();
        }
    } else {
        estado=CAINDO;
    }
}

void Jogador::acaoCorrer()
{
    posicao.x+=10;
    estado=AVANCO;
}

void Jogador::acaoAndar(int passo)
{
    posicao.x+=passo;
    estado=ANDANDO;
}

void Jogador::acaoRecuar()
{
    posicao.x-=10;
    estado=RECUO;
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
        case IMPULSO:
                aliasSprite="impulso";
            break;
        case PARADO:
        default:
                aliasSprite="principal";
            break;
    }

    return aliasSprite;
}

