#include "Lutador.h"

Lutador::Lutador()
{
    //ctor
}

Lutador::~Lutador()
{
    //dtor
}
void Lutador::setBateu()
{
    setEstado(MORRENDO);
}

void Lutador::acao(GBF::Kernel::Input::InputSystem * input)
{
    this->input=input;
    switch(estado){

        case ANDANDO_FRENTE:
            doAndandoFrente();
        break;

        case ANDANDO_TRAS:
            doAndandoTras();
        break;

        case RECUANDO:
            doRecuando();
        break;

        case CORRENDO:
            doCorrendo();
        break;

        case PULANDO:
            doPulando();
        break;

        case CAINDO:
            doCaindo();
        break;

        case IMPULSIONANDO:
            doImpulsionando();
        break;

        case MORRENDO:
            doMorrendo();
        break;

        case PARADO:
        default:
            doParado();
        break;
    }

    limites();
}


void Lutador::doParado()
{
    ifPulando();
    ifAndandoFrente();
    ifAndandoTras();
}
void Lutador::doPulando()
{
    if (!getSprite(getSpriteNome())->animacao.isFim()){
        getSprite(getSpriteNome())->animacao.processarManual();
    }

    if (posicao.y>=alturaPulo.corrente){
        posicao.y-=10;
    } else {
        delay.acao--;
        if (delay.acao<=0) {
            setEstado(CAINDO);
            getSprite(getSpriteNome(CAINDO))->animacao.setInicio();
        }
    }

    if (pulo!=FRACO){
        if (input->teclado->isKey(SDLK_RIGHT)){
            posicao.x+=10;
        } else if ((input->teclado->isKey(SDLK_LEFT))){
            posicao.x-=10;
        }
    }

    ifCaindo();
    ifImpulsionando();
}
void Lutador::doAndandoFrente()
{
    posicao.x+=1;
    getSprite(getSpriteNome())->animacao.processarManual();

    setEstado(PARADO);

    ifAndandoFrente();
    ifPulando();
    ifCorrendo();
    ifAndandoTras();
}

void Lutador::doAndandoTras()
{
    posicao.x-=1;
    getSprite(getSpriteNome())->animacao.processarManual();

    setEstado(PARADO);

    ifAndandoTras();
    ifPulando();
    ifRecuando();
    ifAndandoFrente();
}

void Lutador::doCorrendo()
{
    posicao.x+=10;

    if (getSprite(getSpriteNome())->animacao.isFim()){
        setEstado(PARADO);
    } else {
        getSprite(getSpriteNome())->animacao.processarManual();
    }

    ifPulando();
    ifAndandoTras();
}

void Lutador::doRecuando()
{
    posicao.x-=10;

    if (getSprite(getSpriteNome())->animacao.isFim()){
        setEstado(PARADO);
    } else {
        getSprite(getSpriteNome())->animacao.processarManual();
    }

    ifPulando();
    ifAndandoFrente();
}

void Lutador::doCaindo()
{
    if (posicao.y<110){
        posicao.y+=6;
        if (!getSprite(getSpriteNome())->animacao.isFim()){
            getSprite(getSpriteNome())->animacao.processarManual();
        }
    } else {
        setEstado(PARADO);
    }
}

void Lutador::doImpulsionando()
{
    if (posicao.x<80){
        posicao.x+=4;
        posicao.y-=4;

        if (!getSprite(getSpriteNome())->animacao.isFim()){
            getSprite(getSpriteNome())->animacao.processarManual();
        }

    } else {
        setEstado(CAINDO);
    }
}

void Lutador::doMorrendo()
{
    if (!getSprite(getSpriteNome(MORRENDO))->animacao.isFim()){
        getSprite(getSpriteNome(MORRENDO))->animacao.processarManual();
    }
}

void Lutador::setEstado(Estado estado)
{
    this->estado=estado;
}

void Lutador::ifAndandoFrente()
{
    if (input->teclado->isKey(SDLK_RIGHT)){
        setEstado(ANDANDO_FRENTE);
    }
}
void Lutador::ifAndandoTras()
{
    if (input->teclado->isKey(SDLK_LEFT)){
        setEstado(ANDANDO_TRAS);
    }
}
void Lutador::ifCorrendo()
{
    if ((input->teclado->isKey(SDLK_LSHIFT)) && (input->teclado->isKey(SDLK_RIGHT))){
        setEstado(CORRENDO);
        getSprite(getSpriteNome(CORRENDO))->animacao.setInicio();
    }
}
void Lutador::ifRecuando()
{
    if ((input->teclado->isKey(SDLK_LSHIFT)) && (input->teclado->isKey(SDLK_LEFT))){
        setEstado(RECUANDO);
        getSprite(getSpriteNome(RECUANDO))->animacao.setInicio();
    }
}
void Lutador::ifImpulsionando()
{
    if ((input->teclado->isKey(SDLK_LEFT))&&(posicao.x<=20)){
        setEstado(IMPULSIONANDO);
        getSprite(getSpriteNome(IMPULSIONANDO))->animacao.setInicio();
        getSprite(getSpriteNome(CAINDO))->animacao.setInicio();
    }
}
void Lutador::ifMorrendo()
{//Refinar codigo do estado
    setEstado(MORRENDO);
    vivo=false;
    getSprite(getSpriteNome(MORRENDO))->animacao.setInicio();
}
void Lutador::ifPulando()
{
    getSprite(getSpriteNome(PULANDO))->animacao.setInicio();

    switch (estado){
        case PARADO:
                if (input->teclado->isKey(SDLK_UP)){
                    setEstado(PULANDO);
                    delay.acao=12;
                    alturaPulo.corrente=alturaPulo.fraco;
                    pulo=FRACO;
                }
            break;
        case CORRENDO:
        case RECUANDO:
                if (input->teclado->isKey(SDLK_UP)){
                    setEstado(PULANDO);
                    delay.acao=6;
                    alturaPulo.corrente=alturaPulo.super;
                    pulo=SUPER;
                }
            break;
        case ANDANDO_FRENTE:
        case ANDANDO_TRAS:
        default:
                if (input->teclado->isKey(SDLK_UP)){
                    setEstado(PULANDO);
                    delay.acao=10;
                    alturaPulo.corrente=alturaPulo.normal;
                    pulo=NORMAL;
                }
            break;
    }
}
void Lutador::ifCaindo()
{
    if (input->teclado->isKey(SDLK_DOWN)){
        setEstado(CAINDO);
    }
}

std::string Lutador::getSpriteNome()
{
    return getSpriteNome(estado);
}

