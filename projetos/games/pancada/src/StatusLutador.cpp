//***************************************************************************
//  Pancada <Game - Boxing Style>
//  Copyright (C) 2007 by David Ferreira - FZ
//  davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net
//***************************************************************************
//    Este programa é software livre; você pode redistribuí-lo e/ou
//    modificá-lo sob os termos da Licença Pública Geral GNU, conforme
//    publicada pela Free Software Foundation; tanto a versão 2 da
//    Licença como (a seu critério) qualquer versão mais nova.
//***************************************************************************
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the
//    Free Software Foundation, Inc.,
//    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//***************************************************************************
#include "StatusLutador.h"

//Construtor
StatusLutador::StatusLutador()
{
    GBF::Image::SpriteFactory  *spriteFactory = new GBF::Image::SpriteFactory("interface");

    pontuacao     = spriteFactory->createSpriteItem( 0,306,62,44,1,1);
    statusEnergia = spriteFactory->createSpriteItem(63,306,12, 2,1,1);

    delete(spriteFactory);

    spriteFactory = new GBF::Image::SpriteFactory("personagem");

    icone = spriteFactory->createSpriteItem(454,361,30,37,5,1);

    delete(spriteFactory);
}
//Destrutor
StatusLutador::~StatusLutador()
{
    if (pontuacao){
        delete(pontuacao);
    }
    if (statusEnergia){
        delete(statusEnergia);
    }
    if (icone){
        delete(icone);
    }
}
void StatusLutador::iconeLutador(TipoLutador lutador)
{
    icone->setFrame(lutador);
}
