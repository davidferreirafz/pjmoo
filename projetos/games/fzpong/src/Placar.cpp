/***************************************************************************
 *   FZPong <Game - Pong Clone>                                            *
 *   Copyright (C) 2007 by David Ferreira - FZ                             *
 *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
 ***************************************************************************
 *   Este programa é software livre; você pode redistribuí-lo e/ou         *
 *   modificá-lo sob os termos da Licença Pública Geral GNU, conforme      *
 *   publicada pela Free Software Foundation; tanto a versão 2 da          *
 *   Licença como (a seu critério) qualquer versão mais nova.              *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "Placar.h"

SoundSystem* Placar::soundSystem=NULL;

Placar::Placar()
{
    iniciar();
	if (!soundSystem){
		soundSystem = SoundSystem::getInstance();
	}
}

Placar::~Placar()
{
    //dtor
}

void Placar::iniciar()
{
    jogador=0;
    cpu=0;
    partidaJogador=0;
    partidaCPU=0;
}

void Placar::novaPartida()
{
    if (jogador>cpu){
        vitoriaJogador();
    } else if (jogador<cpu){
        vitoriaCPU();
    }
    jogador=0;
    cpu=0;
}

void Placar::pontuarJogador()
{
    soundSystem->fxManager->playPanEffect("ponto",640);
    jogador++;
}

void Placar::pontuarCPU()
{
    soundSystem->fxManager->playPanEffect("ponto",0);
    cpu++;
}

int Placar::getJogador()
{
    return jogador;
}

int Placar::getCPU()
{
    return cpu;
}

void Placar::vitoriaJogador()
{
    partidaJogador++;
}

void Placar::vitoriaCPU()
{
    partidaCPU++;
}

int Placar::getVitoriaJogador()
{
    return partidaJogador;
}

int Placar::getVitoriaCPU()
{
    return partidaCPU;
}

