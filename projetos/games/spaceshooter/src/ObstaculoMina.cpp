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
#include "ObstaculoMina.h"


ObstaculoMina::ObstaculoMina()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();

    SpriteFactory * spriteFactory   = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,49,32,32,7,2));
    delete (spriteFactory);

    velocidade = OBSTACULO_MINA_MIN + (rand()%OBSTACULO_MINA_MAX);
    resistencia = 8;
    danos       = 4;

    selecionarPosicao();
    path = PathFactory::criar(PATH_DOWN);
}
ObstaculoMina::~ObstaculoMina()
{
    //UtilLog::getInstance()->status("[ObstaculoMina]");
}


