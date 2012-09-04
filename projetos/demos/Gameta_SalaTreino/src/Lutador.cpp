#include "Lutador.h"

Lutador::Lutador()
{
    aceleracao=10.0f;
    piscante = 0;
}

Lutador::~Lutador()
{
}

void Lutador::setBateu()
{
    vida--;
    piscante=20;
    if (vida<=0) {
       setEstado(MORRENDO);
       vida=0;
    }

}

void Lutador::update(GBF::Kernel::Input::InputSystem * input)
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

        case ATERRISANDO:
            doAterrisando();
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
    if (!getSprite(getSpriteNome())->animation.isEnd()){
        getSprite(getSpriteNome())->animation.processManual();
    }

    if (point.y>=alturaPulo.corrente){
        point.y-=6;//10;
    } else {
        delay.action--;
        if (delay.action<=0) {
            setEstado(CAINDO);
            getSprite(getSpriteNome(CAINDO))->animation.setBegin();
        }
    }

    if (pulo!=FRACO){
        if (input->keyboard->isKey(SDLK_RIGHT)){
            //posicao.x+=10;
            //posicao.x+= std::pow((posicao.y/3),(1.0/3.0));
            //posicao.x+= std::pow(posicao.y,1.0/3.0);
            //posicao.x+=posicao.y-17;
            point.x+=std::pow(point.y,1.0/3.0);
        } else if ((input->keyboard->isKey(SDLK_LEFT))){
            point.x-=std::pow(point.y,1.0/3.0);
            //posicao.x-= std::pow((posicao.y/3),(1.0/3.0));
        }
    }

    ifCaindo();
    ifImpulsionando();
}

void Lutador::doAndandoFrente()
{
    point.x+=1;
    getSprite(getSpriteNome())->animation.processManual();

    setEstado(PARADO);

    ifAndandoFrente();
    ifPulando();
    ifCorrendo();
    ifAndandoTras();
}

void Lutador::doAndandoTras()
{
    point.x-=1;
    getSprite(getSpriteNome())->animation.processManual();

    setEstado(PARADO);

    ifAndandoTras();
    ifPulando();
    ifRecuando();
    ifAndandoFrente();
}

void Lutador::doCorrendo()
{
    point.x+=10;

    if (getSprite(getSpriteNome())->animation.isEnd()){
        setEstado(PARADO);
    } else {
        getSprite(getSpriteNome())->animation.processManual();
    }

    ifPulando();
    ifAndandoTras();
}

void Lutador::doRecuando()
{
    point.x-=10;

    if (getSprite(getSpriteNome())->animation.isEnd()){
        setEstado(PARADO);
    } else {
        getSprite(getSpriteNome())->animation.processManual();
    }

    ifPulando();
    ifAndandoFrente();
}

void Lutador::doCaindo()
{
    if (point.y<104){
        point.y+=aceleracao;
        if (!getSprite(getSpriteNome())->animation.isEnd()){
            getSprite(getSpriteNome())->animation.processManual();
        }
        aceleracao+=1.5;
    } else {
        ifAterrisando();
    }
}

void Lutador::doAterrisando()
{
    if (getSprite(getSpriteNome())->animation.isEnd()){
        setEstado(PARADO);
    } else {
        getSprite(getSpriteNome())->animation.processManual();
    }
}

void Lutador::doImpulsionando()
{
    if (point.x<80){
        point.x+=4;
        point.y-=4;

        if (!getSprite(getSpriteNome())->animation.isEnd()){
            getSprite(getSpriteNome())->animation.processManual();
        }

    } else {
        setEstado(CAINDO);
    }
}

void Lutador::doMorrendo()
{
    if (!getSprite(getSpriteNome(MORRENDO))->animation.isEnd()){
        getSprite(getSpriteNome(MORRENDO))->animation.processManual();
    } else {
        active = false;
    }
}

void Lutador::setEstado(Estado estado)
{
    this->estado=estado;
}

void Lutador::ifAndandoFrente()
{
    if (input->keyboard->isKey(SDLK_RIGHT)){
        setEstado(ANDANDO_FRENTE);
    }
}

void Lutador::ifAndandoTras()
{
    if (input->keyboard->isKey(SDLK_LEFT)){
        setEstado(ANDANDO_TRAS);
    }
}

void Lutador::ifCorrendo()
{
    if ((input->keyboard->isKey(SDLK_LSHIFT)) && (input->keyboard->isKey(SDLK_RIGHT))){
        setEstado(CORRENDO);
        getSprite(getSpriteNome(CORRENDO))->animation.setBegin();
    }
}

void Lutador::ifRecuando()
{
    if ((input->keyboard->isKey(SDLK_LSHIFT)) && (input->keyboard->isKey(SDLK_LEFT))){
        setEstado(RECUANDO);
        getSprite(getSpriteNome(RECUANDO))->animation.setBegin();
    }
}

void Lutador::ifImpulsionando()
{
    if ((input->keyboard->isKey(SDLK_LEFT))&&(point.x<=20)){
        setEstado(IMPULSIONANDO);
        getSprite(getSpriteNome(IMPULSIONANDO))->animation.setBegin();
        getSprite(getSpriteNome(CAINDO))->animation.setBegin();
    }
}

void Lutador::ifMorrendo()
{//Refinar codigo do estado
    setEstado(MORRENDO);
    life=false;
    getSprite(getSpriteNome(MORRENDO))->animation.setBegin();
}

void Lutador::ifPulando()
{
    getSprite(getSpriteNome(PULANDO))->animation.setBegin();

    switch (estado){
        case PARADO:
                if (input->keyboard->isKey(SDLK_UP)){
                    setEstado(PULANDO);
                    delay.action=12;
                    alturaPulo.corrente=alturaPulo.fraco;
                    pulo=FRACO;
                    aceleracao=8.0f;
                }
            break;
        case CORRENDO:
        case RECUANDO:
                if (input->keyboard->isKey(SDLK_UP)){
                    setEstado(PULANDO);
                    delay.action=6;
                    alturaPulo.corrente=alturaPulo.super;
                    pulo=SUPER;
                    aceleracao=12.0f;
                }
            break;
        case ANDANDO_FRENTE:
        case ANDANDO_TRAS:
        default:
                if (input->keyboard->isKey(SDLK_UP)){
                    setEstado(PULANDO);
                    delay.action=10;
                    alturaPulo.corrente=alturaPulo.normal;
                    pulo=NORMAL;
                    aceleracao=10.0f;
                }
            break;
    }
}

void Lutador::ifCaindo()
{
    if (input->keyboard->isKey(SDLK_DOWN)){
        setEstado(CAINDO);
    }
}

void Lutador::ifAterrisando()
{
    point.y=114;
    getSprite(getSpriteNome(ATERRISANDO))->animation.setBegin();
    setEstado(ATERRISANDO);
}

std::string Lutador::getSpriteNome()
{
    return getSpriteNome(estado);
}

int Lutador::getVida()
{
    return vida;
}
