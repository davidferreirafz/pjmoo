#include "Jogador.h"

Jogador::Jogador()
{
    GBF::Image::SpriteFactory *spriteFactory = new GBF::Image::SpriteFactory("sprites");

    addMainSprite(spriteFactory->createSpriteCharacter(0,0,59,43,3,6));
    getMainSprite()->setQtdDirecoes(1);
    getMainSprite()->animation.setAutomatic(true);

    delete (spriteFactory);

    setPoint(320,400);
}

Jogador::~Jogador()
{
    //dtor
}

void Jogador::update(GBF::Kernel::Input::InputSystem * input)
{
    if (input->keyboard->isKey(SDLK_RIGHT)){
        point.x+=4;
    } else if (input->keyboard->isKey(SDLK_LEFT)){
        point.x-=4;
    }
}
