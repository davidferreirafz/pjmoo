#include "Jogador.h"



Jogador::Jogador()
{
    GBF::Image::SpriteFactory *spriteFactory = new GBF::Image::SpriteFactory("personagem_parado");
    addMainSprite(spriteFactory->createSpriteCharacter(0, 0, 42, 98, 5, 10));
    getMainSprite()->animation.setAutomatic(true);
    delete(spriteFactory);

    spriteFactory = new GBF::Image::SpriteFactory("personagem_andando");
    addSprite(spriteFactory->createSpriteCharacter(0, 0, 50, 98, 10, 2), "andando");
    getSprite("andando")->animation.setAutomatic(false);
    delete(spriteFactory);

    spriteFactory = new GBF::Image::SpriteFactory("personagem_recuando");
    addSprite(spriteFactory->createSpriteCharacter(0, 0, 69, 96, 4, 2), "recuando");
    getSprite("recuando")->animation.setAutomatic(false);
    delete(spriteFactory);

    spriteFactory = new GBF::Image::SpriteFactory("personagem_correndo");
    addSprite(spriteFactory->createSpriteCharacter(0, 0, 84, 86, 4, 2), "correndo");
    getSprite("correndo")->animation.setAutomatic(false);
    delete(spriteFactory);

    spriteFactory = new GBF::Image::SpriteFactory("personagem_morrendo");
    addSprite(spriteFactory->createSpriteCharacter(0, 0, 115, 80, 4, 1), "morrendo");
    getSprite("morrendo")->animation.setAutomatic(false);
    delete(spriteFactory);

    spriteFactory = new GBF::Image::SpriteFactory("personagem_pulando");
    addSprite(spriteFactory->createSpriteCharacter(0, 0, 74, 101, 4, 1), "pulando");
    getSprite("pulando")->animation.setAutomatic(false);
    delete(spriteFactory);

    spriteFactory = new GBF::Image::SpriteFactory("personagem_caindo");
    addSprite(spriteFactory->createSpriteCharacter(0, 0, 80, 105, 2, 1), "caindo");
    getSprite("caindo")->animation.setAutomatic(false);

    addSprite(spriteFactory->createSpriteCharacter(160, 0, 80, 105, 1, 2), "aterrisando");
    getSprite("aterrisando")->animation.setAutomatic(false);
    delete(spriteFactory);

    spriteFactory = new GBF::Image::SpriteFactory("personagem_impulsionando");
    addSprite(spriteFactory->createSpriteCharacter(0, 0, 65, 75, 2, 4), "impulsionando");
    getSprite("impulsionando")->animation.setAutomatic(false);
    delete(spriteFactory);


    setPoint(100, 114);

    setEstado(PARADO);
    delay.action = 6;
    alturaPulo.super  = 64;
    alturaPulo.normal = 90;
    alturaPulo.fraco  = 122;
    alturaPulo.corrente = alturaPulo.normal;
}

Jogador::~Jogador()
{
}

void Jogador::inicializar()
{
    setEstado(PARADO);
    vida = 10;
    active = true;
}

void Jogador::limites()
{
    if (point.x < 20){
        point.x = 20;
    } else {
        int d = getSprite(Lutador::getSpriteNome())->getTamanho().w;
        if (point.x > 304 - 20 - d){
            point.x = 304 - 20 - d;
        }
    }
    if (point.y <= 30){
        point.y = 30;
    }
}

void Jogador::draw()
{
    GBF::Point ponto = ajustar();

    /*if (!vivo){
        if(!getSprite("morrendo")->animacao.isFim()){
            getSprite("morrendo")->animacao.processarManual();
        }
    }*/
    if (piscante>0){
        piscante--;
        if (piscante % 4 ==0){
            return;
        }
    }

    switch (estado){
        case CORRENDO:
            getSprite(Lutador::getSpriteNome())->draw(ponto.x - 10, ponto.y);
            getSprite(Lutador::getSpriteNome())->draw(ponto.x - 5, ponto.y);
            getSprite(Lutador::getSpriteNome())->draw(ponto.x, ponto.y);
            break;
        case RECUANDO:
            getSprite(Lutador::getSpriteNome())->draw(ponto.x + 10, ponto.y);
            getSprite(Lutador::getSpriteNome())->draw(ponto.x + 5, ponto.y);
            getSprite(Lutador::getSpriteNome())->draw(ponto.x, ponto.y);
            break;
        default:
            getSprite(Lutador::getSpriteNome())->draw(ponto.x, ponto.y);
            break;
    }

#ifdef DEBUG
    GBF::Area r = getAreaColisao();

    gsGFX->setColor(255, 178, 0);
    gsGFX->rectangle(r.left, r.top, r.right, r.bottom);

    GBF::Dimension d = getSprite(Lutador::getSpriteNome())->getTamanho();
    gsGFX->setColor(0, 255, 0);
    gsGFX->rectangle(ponto.x, ponto.y, d.w, d.h);
#endif
}

GBF::Point Jogador::ajustar()
{
    GBF::Point ponto;

    switch (estado){
        case MORRENDO   :
            ponto.x = point.x;
            ponto.y = point.y + 20;
            break;
        case PULANDO    :
            ponto.x = point.x - 10;
            ponto.y = point.y;
            break;
        case CAINDO     :
            ponto.x = point.x - 20;
            ponto.y = point.y;
            break;
        case ATERRISANDO:
            ponto.x = point.x - 26;
            ponto.y = point.y - 8;
            break;
        case CORRENDO   :
            ponto.x = point.x;
            ponto.y = point.y + 16;
            break;
        case RECUANDO   :
            ponto.x = point.x;
            ponto.y = point.y + 10;
            break;
        default:
            ponto.x = point.x;
            ponto.y = point.y;
            break;
    }

    return ponto;
}

std::string Jogador::getSpriteNome(Estado estado)
{
    static std::string aliasSprite;

    switch (estado)
    {
        case ANDANDO_FRENTE:
        case ANDANDO_TRAS:
            aliasSprite = "andando";
            break;
        case RECUANDO:
            aliasSprite = "recuando";
            break;
        case CORRENDO:
            aliasSprite = "correndo";
            break;
        case MORRENDO:
            aliasSprite = "morrendo";
            break;
        case PULANDO:
            aliasSprite = "pulando";
            break;
        case CAINDO:
            aliasSprite = "caindo";
            break;
        case ATERRISANDO:
            aliasSprite = "aterrisando";
            break;
        case IMPULSIONANDO:
            aliasSprite = "impulsionando";
            break;
        case PARADO:
        default:
            aliasSprite = GBF_CHARACTER_MAIN_SPRITE;
            break;
    }

    return aliasSprite;
}

GBF::Area Jogador::getAreaColisao()
{
    GBF::Area regiao;

    switch (estado)
    {
        case ANDANDO_FRENTE:
        case ANDANDO_TRAS:
            regiao.left = 10;
            regiao.top = 2;
            regiao.right = 28;
            regiao.bottom = 94;
            break;
        case RECUANDO:
            regiao.left = 2;
            regiao.top = 15;
            regiao.right = 44;
            regiao.bottom = 70;
            break;
        case CORRENDO:
            regiao.left = 28;
            regiao.top = 20;
            regiao.right = 52;
            regiao.bottom = 52;
            break;
        case MORRENDO:
            regiao.left = 20;
            regiao.top = 45;
            regiao.right = 70;
            regiao.bottom = 25;
            break;
        case PULANDO:
            regiao.left = 18;
            regiao.top = 6;
            regiao.right = 32;
            regiao.bottom = 52;
            break;
        case CAINDO:
            regiao.left = 28;
            regiao.top = 14;
            regiao.right = 24;
            regiao.bottom = 78;
            break;
        case ATERRISANDO:
            regiao.left = 30;
            regiao.top = 45;
            regiao.right = 30;
            regiao.bottom = 55;
            break;
        case IMPULSIONANDO:
            regiao.left = 10;
            regiao.top = 10;
            regiao.right = 46;
            regiao.bottom = 52;
            break;
        case PARADO:
        default:
            regiao.left = 10;
            regiao.top = 2;
            regiao.right = 22;
            regiao.bottom = 94;
            break;
    }

    GBF::Point p = ajustar();

    regiao.left += p.x;
    regiao.top  += p.y;

    return regiao;
}

bool Jogador::colidiu(GBF::Area b)
{
    bool resultado = false;

    if (estado != MORRENDO){
        resultado = InterfaceObjeto::colidiu(b);
    }

    return resultado;
}

