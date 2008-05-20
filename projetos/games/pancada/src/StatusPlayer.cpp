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
#include "StatusPlayer.h"

//Construtor
StatusPlayer::StatusPlayer()
{
    GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("interface");

    painel = spriteFactory->criarSpriteItem(0,0,45,264,1,1);

    delete(spriteFactory);

    iconeLutador(FZ);
}
//Destrutor
StatusPlayer::~StatusPlayer()
{

}
//Desenha a barra de informações do jogador
void StatusPlayer::desenhar(int pontos, int round, int energia)
{
    painel->desenhar(0,0);
    icone->desenhar(7,8);
    pontuacao->desenhar(45,0);

    int barraEnergia=int((energia*83)/100);

    for (int se=0;se<barraEnergia;se++){
        statusEnergia->desenhar(7,253-(2*se));
    }

    wsManager->escrever("kiloton16",52,18,"%03d",pontos);
    wsManager->escrever("kiloton16",6,64, "%02d",round);
}
