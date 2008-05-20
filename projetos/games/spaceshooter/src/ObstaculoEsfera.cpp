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
#include "ObstaculoEsfera.h"


ObstaculoEsfera::ObstaculoEsfera()
{
GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("personagem");
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,481,34,33,4,40));
    delete (spriteFactory);

    velocidade  = OBSTACULO_ESFERA_MIN + (rand()%OBSTACULO_ESFERA_MAX);
    resistencia = 30;
    danos       = 3;

    selecionarPosicao();
    path = PathFactory::criar(PATH_DOWN);
}
ObstaculoEsfera::~ObstaculoEsfera()
{
    //UtilLog::getInstance()->status("[ObstaculoEsfera]");
}

