#include "Canhao.h"

Canhao::Canhao(int x, int y)
{
    GBF::Image::SpriteFactory *spriteFactory = new GBF::Image::SpriteFactory("fumaca");
    fumaca = spriteFactory->createSpriteItem(0, 0, 69, 63, 7, 1);
    fumaca->animation.setAutomatic(true);
    delete(spriteFactory);

    spriteFactory = new GBF::Image::SpriteFactory("bala");
    bala = spriteFactory->createSpriteItem(0, 0, 24, 20, 0, 0);
    bala->animation.setAutomatic(true);
    delete(spriteFactory);

    posicao.x = x;
    posicao.y = y;

    fumaca->setPoint(x, y);
    tempo.setInitialTime(2);
    tempo.setUnit(GBF::Kernel::Timer::TIME_SECOND_HALF);
    tempo.setReset();

    ativo = false;
    balaAtiva = false;
    ultimoDisparo = false;
    inicializar();
}

Canhao::~Canhao()
{
    delete(fumaca);
    delete(bala);
}

void Canhao::inicializar()
{
    if (!isBala()) {
        posicaoBala.x = posicao.x - 10;
        posicaoBala.y = posicao.y + 1;

        bala->setPoint(posicaoBala);

        tempo.setReset();

        balaAtiva = false;
        ultimoDisparo = false;
    }
}

void Canhao::setNivel(int nivel)
{
    tempo.setInitialTime(5 - nivel);
    velocidade = 10 + (4 * nivel);
}

void Canhao::update()
{
    tempo.update();

    if (tempo.isFinish()){
        posicaoBala.x -= 6;

        if (!isBala()){
            posicaoBala.x = posicao.x - 10;
            posicaoBala.y = posicao.y + 1;
            fumaca->animation.setBegin();
            tempo.setReset();
            balaAtiva = true;
        }

        if (posicaoBala.x <0){
            desativarBala();
        }
        /*if (posicaoBala.x < 0){
            posicaoBala.x = posicao.x - 10;
            posicaoBala.y = posicao.y + 1;
            fumaca->animation.setBegin();
            tempo.setReset();
            balaAtiva = true;
        }*/
    }

    if (ultimoDisparo){
        posicaoBala.x -= 6;
        if (posicaoBala.x<0){
            ultimoDisparo = false;
            setAtivar(false);
        }
    }

}

void Canhao::draw()
{
    if ((tempo.isFinish()&&(balaAtiva))){
        bala->draw(posicaoBala.x, posicaoBala.y);
        if (!fumaca->animation.isEnd()){
            fumaca->draw(posicao.x - 30, posicao.y - 20);
        }

#ifdef DEBUG
        GBF::Area r = getAreaColisao();
        gsGFX->setColor(255, 0, 0);
        gsGFX->rectangle(r.left,r.top,r.right,r.bottom);
#endif
    }
}

GBF::Area Canhao::getAreaColisao()
{
    GBF::Area regiao;

    regiao.left = 1;
    regiao.top = 1;
    regiao.right = 22;
    regiao.bottom = 15;

    ////////////
    regiao.left = posicaoBala.x + regiao.left;
    regiao.top = posicaoBala.y + regiao.top;

    return regiao;
}

void Canhao::desativarBala()
{
    balaAtiva = false;
}

bool Canhao::isBala()
{
    return balaAtiva;
}

bool Canhao::isAtivo()
{
    return ativo;
}
void Canhao::setAtivar(bool ativo)
{
    if (this->ativo!=ativo){
        this->ativo=ativo;

        if (!this->ativo){
            if (isBala()){
                ultimoDisparo=true;
            } else if (!ativo){
                inicializar();
            }
        }
    }
}

