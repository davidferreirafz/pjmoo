///***************************************************************************
// *   FZPong <Game - Pong Clone>                                            *
// *   Copyright (C) 2007 by David Ferreira - FZ                             *
// *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
// ***************************************************************************
// *   Este programa � software livre; voc� pode redistribu�-lo e/ou         *
// *   modific�-lo sob os termos da Licen�a P�blica Geral GNU, conforme      *
// *   publicada pela Free Software Foundation; tanto a vers�o 2 da          *
// *   Licen�a como (a seu crit�rio) qualquer vers�o mais nova.              *
// ***************************************************************************
// *   This program is free software; you can redistribute it and/or modify  *
// *   it under the terms of the GNU General Public License as published by  *
// *   the Free Software Foundation; either version 2 of the License, or     *
// *   (at your option) any later version.                                   *
// *                                                                         *
// *   You should have received a copy of the GNU General Public License     *
// *   along with this program; if not, write to the                         *
// *   Free Software Foundation, Inc.,                                       *
// *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
// ***************************************************************************/
#include "Jogador.h"

Jogador::Jogador()
{
    GBF::Image::SpriteFactory *spriteFactory = new GBF::Image::SpriteFactory("personagem");

    addMainSprite(spriteFactory->createSpriteCharacter(0,21,14,80,1,1));
    delete(spriteFactory);

}
Jogador::~Jogador()
{

    //dtor
}
void Jogador::update(GBF::Kernel::Input::InputSystem * input)
{
    if ((input->keyboard->isKey(SDLK_UP))||(input->joystick->isAxeUp())){
        subir();
    } else if ((input->keyboard->isKey(SDLK_DOWN))||(input->joystick->isAxeDown())){
        descer();
    }
}
GBF::Point Jogador::saque()
{
    GBF::Point saque;

    saque.x=point.x-getVisaoBola().getDimension().w;
    saque.y=point.y+rand()%(getDimension().h-getVisaoBola().getDimension().h);

    return saque;
}
