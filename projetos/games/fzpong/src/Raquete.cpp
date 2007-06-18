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
#include "Raquete.h"

Bola* Raquete::visaoBola=NULL;

Raquete::Raquete()
{
    velocidade = 10;
}

Raquete::~Raquete()
{
    //dtor
}

void Raquete::setVelocidade(int valor)
{
    velocidade=valor;
}

int Raquete::getVelocidade()
{
    return velocidade;
}

void Raquete::subir()
{
    posicao.y-=getVelocidade();

    if (posicao.y<=getAreaTela().top){
        posicao.y=getAreaTela().top;
    }
}

void Raquete::descer()
{
    posicao.y+=getVelocidade();
    if (posicao.y+getDimensao().h>=getAreaTela().bottom){
        posicao.y=getAreaTela().bottom-getDimensao().h;
    }
}

bool Raquete::isBateuParede()
{
    bool bateu = false;

    if ((posicao.y+getDimensao().h>=getAreaTela().bottom)||(posicao.y<=getAreaTela().top)){
        bateu=true;
    }

    return bateu;
}

void Raquete::setBola(Bola *bola)
{
    visaoBola=bola;
}

Bola Raquete::getVisaoBola()
{
    return *visaoBola;
}

