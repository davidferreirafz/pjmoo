/***************************************************************************
 *   Copyright (C) 2005-2006 by David Ferreira                             *
 *   davidferreira@uol.com.br - davidferreira.fz@gmail.com                 *
 *   http://pjmoo.codigolivre.org.br                                       *
 *       http://davidferreira.fz.googlepages.com                           *
 *                                                                         *
 *   Este programa é um software livre; você pode redistribui-lo e/ou      *
 *   modifica-lo dentro dos termos da Licença Pública Geral (GPL) GNU      *
 *   como publicada pela Fundação do Software Livre (FSF); na versão 2 da  *
 *   Licença.                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "ObstaculoAsteroid.h"

ObstaculoAsteroid::ObstaculoAsteroid()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();

    SpriteFactory * spriteFactory   = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,82,32,32,4,8));
    delete (spriteFactory);

    velocidade  = OBSTACULO_ASTEROID_MIN + (rand()%OBSTACULO_ASTEROID_MAX);
//    velocidade+=getVelocidadeBase();

    resistencia = 1;
    danos       = 1;

    selecionarPosicao();
    path = PathFactory::criar(PATH_DOWN);
}
ObstaculoAsteroid::~ObstaculoAsteroid()
{
    //UtilLog::getInstance()->status("[ObstaculoAsteroid]");
}

