
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

    spriteFactory = new GBF::Imagem::SpriteFactory("personagem_correndo");
    adicionarSprite(spriteFactory->criarSpritePersonagem(0,0,84,86,4,2),"correndo");
    getSprite("correndo")->animacao.setAutomatico(false);
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
    adicionarSprite(spriteFactory->criarSpritePersonagem(0,0,80,105,2,1),"caindo");
    getSprite("caindo")->animacao.setAutomatico(false);

    adicionarSprite(spriteFactory->criarSpritePersonagem(160,0,80,105,1,2),"aterrisando");
    getSprite("aterrisando")->animacao.setAutomatico(false);
    delete(spriteFactory);

    spriteFactory = new GBF::Imagem::SpriteFactory("personagem_impulsionando");
    adicionarSprite(spriteFactory->criarSpritePersonagem(0,0,65,75,2,4),"impulsionando");
    getSprite("impulsionando")->animacao.setAutomatico(false);
    delete(spriteFactory);

    setPosicao(100,114);

    setEstado(PARADO);
    delay.acao=6;
    alturaPulo.super  = 64;
    alturaPulo.normal = 90;
    alturaPulo.fraco  =122;
    alturaPulo.corrente=alturaPulo.normal;
}
Jogador::~Jogador()
{
}
void Jogador::inicializar()
{
    setEstado(PARADO);
    vida=1;
    ativo=true;

}
void Jogador::limites()
{
    if (posicao.x<20){
        posicao.x=20;
    } else {
        int d = getSprite(Lutador::getSpriteNome())->getTamanho().w;
        if (posicao.x>304-20-d){
            posicao.x=304-20-d;
        }
    }
    if (posicao.y<=30){
        posicao.y=30;
    }

   /* if (input->teclado->isKey(SDLK_m)){
        onMorrer();
    } else if(input->teclado->isKey(SDLK_r)){
        estado=PARADO;
        vivo=true;
    }*/
}

void Jogador::desenhar()
{
    GBF::Ponto ponto = ajustar();

    /*if (!vivo){
        if(!getSprite("morrendo")->animacao.isFim()){
            getSprite("morrendo")->animacao.processarManual();
        }
    }*/
    switch (estado){
case CORRENDO:
    getSprite(Lutador::getSpriteNome())->desenhar(ponto.x-10,ponto.y);
    getSprite(Lutador::getSpriteNome())->desenhar(ponto.x-5,ponto.y);
   getSprite(Lutador::getSpriteNome())->desenhar(ponto.x,ponto.y);     break;
case RECUANDO:
    getSprite(Lutador::getSpriteNome())->desenhar(ponto.x+10,ponto.y);
    getSprite(Lutador::getSpriteNome())->desenhar(ponto.x+5,ponto.y);
   getSprite(Lutador::getSpriteNome())->desenhar(ponto.x,ponto.y);     break;
default:
    getSprite(Lutador::getSpriteNome())->desenhar(ponto.x,ponto.y);
break;
    }

#ifdef DEBUG
    Regiao r= getAreaColisao();

    gsGFX->setColor(255,178,0);
    gsGFX->retangulo(r.posicao.x,r.posicao.y,r.dimensao.w,r.dimensao.h);

    GBF::Dimensao d = getSprite(Lutador::getSpriteNome())->getTamanho();
    gsGFX->setColor(0,255,0);
    gsGFX->retangulo(ponto.x,ponto.y,d.w,d.h);
#endif
}

GBF::Ponto Jogador::ajustar()
{
    GBF::Ponto ponto;

    switch (estado){
        case MORRENDO   :  ponto.x=posicao.x;     ponto.y=posicao.y+20;  break;
        case PULANDO    :  ponto.x=posicao.x-10;  ponto.y=posicao.y;     break;
        case CAINDO     :  ponto.x=posicao.x-20;  ponto.y=posicao.y;     break;
        case ATERRISANDO:  ponto.x=posicao.x-26;  ponto.y=posicao.y-8;   break;
        case CORRENDO   :  ponto.x=posicao.x;     ponto.y=posicao.y+16;  break;
        case RECUANDO   :  ponto.x=posicao.x;     ponto.y=posicao.y+10;  break;
        default:           ponto.x=posicao.x;     ponto.y=posicao.y;     break;
    }

    return ponto;
}

std::string Jogador::getSpriteNome(Estado estado)
{
    std::string aliasSprite;

    switch (estado)
    {
        case ANDANDO_FRENTE:
        case ANDANDO_TRAS:
                aliasSprite="andando";
            break;
        case RECUANDO:
                aliasSprite="recuando";
            break;
        case CORRENDO:
                aliasSprite="correndo";
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
        case ATERRISANDO:
                aliasSprite="aterrisando";
            break;
        case IMPULSIONANDO:
                aliasSprite="impulsionando";
            break;
        case PARADO:
        default:
                aliasSprite="principal";
            break;
    }

    return aliasSprite;
}
Regiao Jogador::getAreaColisao()
{
    Regiao regiao;

    switch (estado)
    {
        case ANDANDO_FRENTE:
        case ANDANDO_TRAS:
                regiao.posicao.x=10;    regiao.posicao.y=2;
                regiao.dimensao.w=28;   regiao.dimensao.h=94;
            break;
        case RECUANDO:
                regiao.posicao.x=2;     regiao.posicao.y=15;
                regiao.dimensao.w=44;   regiao.dimensao.h=70;
            break;
        case CORRENDO:
                regiao.posicao.x=28;    regiao.posicao.y=20;
                regiao.dimensao.w=52;   regiao.dimensao.h=52;
            break;
        case MORRENDO:
                regiao.posicao.x=20;    regiao.posicao.y=45;
                regiao.dimensao.w=70;   regiao.dimensao.h=25;
            break;
        case PULANDO:
                regiao.posicao.x=18;    regiao.posicao.y=6;
                regiao.dimensao.w=32;   regiao.dimensao.h=52;
            break;
        case CAINDO:
                regiao.posicao.x=28;    regiao.posicao.y=14;
                regiao.dimensao.w=24;   regiao.dimensao.h=78;
            break;
        case ATERRISANDO:
                regiao.posicao.x=30;    regiao.posicao.y=45;
                regiao.dimensao.w=30;   regiao.dimensao.h=55;
            break;
        case IMPULSIONANDO:
                regiao.posicao.x=10;    regiao.posicao.y=10;
                regiao.dimensao.w=46;   regiao.dimensao.h=52;
            break;
        case PARADO:
        default:
                regiao.posicao.x=10;   regiao.posicao.y=2;
                regiao.dimensao.w=22;  regiao.dimensao.h=94;
            break;
    }

    ////////////
    GBF::Ponto p=ajustar();

    regiao.posicao.x=p.x+regiao.posicao.x;
    regiao.posicao.y=p.y+regiao.posicao.y;

    return regiao;
}

bool Jogador::colidiu(Regiao b)
{
    bool resultado = false;

    if (estado!=MORRENDO){
        resultado=InterfaceObjeto::colidiu(b);
    }

    return resultado;
}

