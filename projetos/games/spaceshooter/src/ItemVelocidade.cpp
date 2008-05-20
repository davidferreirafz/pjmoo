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
#include "ItemVelocidade.h"


ItemVelocidade::ItemVelocidade()
{
    GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("tiles");
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(258,294,32,24,4,8));
    delete (spriteFactory);

    velocidade  = 3;
    bonus       = 1;

    selecionarPosicao();
    path = PathFactory::criar(PATH_DOWN);
}
ItemVelocidade::~ItemVelocidade()
{
    //UtilLog::getInstance()->status("[ItemVelocidade]");
}
EnumItem ItemVelocidade::getTipo()
{
    return ITEM_VELOCIDADE;
}
std::string ItemVelocidade::getHelp()
{
    return "item_velocidade";
}
