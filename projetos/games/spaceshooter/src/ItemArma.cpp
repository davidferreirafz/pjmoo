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
#include "ItemArma.h"

ItemArma::ItemArma()
{
    GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("tiles");
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,9,32,24,4,8));
    delete (spriteFactory);

    velocidade = 2;
    bonus      = 4;

    selecionarPosicao();
    path = PathFactory::criar(PATH_DOWN);
}
ItemArma::~ItemArma()
{
    //UtilLog::getInstance()->status("[ItemArma]");
}
EnumItem ItemArma::getTipo()
{
    return ITEM_ARMA;
}
std::string ItemArma::getHelp()
{
    return "item_arma";
}



