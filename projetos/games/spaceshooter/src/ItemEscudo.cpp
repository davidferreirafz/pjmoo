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
#include "ItemEscudo.h"

ItemEscudo::ItemEscudo()
{
    GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("tiles");
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(129,9,32,24,4,8));
    delete (spriteFactory);

    velocidade  = 1;
    bonus       = 5;

    selecionarPosicao();
    path = PathFactory::criar(PATH_DOWN);
}
ItemEscudo::~ItemEscudo()
{
    //UtilLog::getInstance()->status("[ItemEscudo]");
}
EnumItem ItemEscudo::getTipo()
{
    return ITEM_ESCUDO;
}
std::string ItemEscudo::getHelp()
{
    return "item_escudo";
}

