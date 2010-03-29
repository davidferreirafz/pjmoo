#include "Inimigo.h"

Inimigo::Inimigo()
{
    GBF::Image::SpriteFactory *spriteFactory = new GBF::Image::SpriteFactory("sprites");

    addMainSprite(spriteFactory->createSpriteCharacter(0,77,32,32,3,6));
    getMainSprite()->setQtdDirecoes(1);
    getMainSprite()->animation.setAutomatic(true);

    delete (spriteFactory);

    iniciar();
}

Inimigo::~Inimigo()
{
}

void Inimigo::update(GBF::Kernel::Input::InputSystem * input)
{
    point.y+=velocidade;

    if (point.y>640){
        iniciar();
    }
}

void Inimigo::iniciar()
{
    GBF::Dimension d = getDimension();

    GBF::Point p;
    p.y= 0 - d.h;
    p.x= rand() % (640 - d.w);

    setPoint(p);

    velocidade=2+rand()%5;
}
