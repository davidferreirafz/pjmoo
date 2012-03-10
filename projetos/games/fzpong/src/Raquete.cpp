///***************************************************************************
// *   FZPong <Game - Pong Clone>                                            *
// *   Copyright (C) 2007 by David Ferreira - FZ                             *
// *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
// ***************************************************************************
// *   Este programa é software livre; você pode redistribuí-lo e/ou         *
// *   modificá-lo sob os termos da Licença Pública Geral GNU, conforme      *
// *   publicada pela Free Software Foundation; tanto a versão 2 da          *
// *   Licença como (a seu critério) qualquer versão mais nova.              *
// ***************************************************************************
// *   This program is free software; you can redistribute it and/or modify  *
// *   it under the terms of the GNU General Public License as published by  *
// *   the Free Software Foundation; either version 2 of the License, or     *
// *   (at your option) any later version.                                   *
// *                                                                         *
// *   You should have received a copy of the GNU General Public License     *
// *   along with this program; if not, write to the                         *
// *   Free Software Foundation, Inc.,                                       *
// *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
// ***************************************************************************/
#include "Raquete.h"

//Construtor
Raquete::Raquete()
{
    velocidade = 10;
}
//Destrutor
Raquete::~Raquete()
{
}
//Inicia raquete
void Raquete::iniciar()
{
    preparar();
}
//Posiciona Raquete
void Raquete::preparar()
{
    //Se for do lado direito da tela
    if (lado==LADO_DIREITO){
        setPoint(getAreaTela().right-getDimension().w,(getAreaTela().bottom/2)-(getDimension().h/2));
    //Se for do lado esquerdo da tela
    } else {
        setPoint(0,(getAreaTela().bottom/2)-(getDimension().h/2));
    }
}
void Raquete::setBola(Bola * bola)
{
    visaoBola=bola;
}
void Raquete::setLado(Lado valor)
{
    lado=valor;
}
bool Raquete::isCollision(Character * personagem)
{
    bool retorno = false;

//Se raquete no lado direito da tela
    if (lado==LADO_DIREITO){
        if ((point.x + getDimension().w >= personagem->getPoint().x) &&
            (point.x <= personagem->getPoint().x + personagem->getDimension().w) &&
            (point.y + getDimension().h >= personagem->getPoint().y) &&
            (point.y <= personagem->getPoint().y + personagem->getDimension().h)){
                retorno = true;
        }
//Se raquete no lado esquerdo da tela
    } else {
        if ((point.x + getDimension().w >= personagem->getPoint().x) &&
            (point.x <= personagem->getPoint().x + personagem->getDimension().w) &&
            (point.y + getDimension().h >= personagem->getPoint().y) &&
            (point.y <= personagem->getPoint().y + personagem->getDimension().h)){
                retorno = true;
        }
    }

    return retorno;
}
int Raquete::getVelocidade()
{
    return velocidade;
}
void Raquete::setVelocidade(int valor)
{
    velocidade=valor;
}
void Raquete::subir()
{
    point.y-=getVelocidade();

    if (point.y<=getAreaTela().top){
        point.y=getAreaTela().top;
    }
}
void Raquete::descer()
{
    point.y+=getVelocidade();
    if (point.y+getDimension().h>=getAreaTela().bottom){
        point.y=getAreaTela().bottom-getDimension().h;
    }
}
bool Raquete::isBateuParede()
{
    bool bateu = false;

    if ((point.y+getDimension().h>=getAreaTela().bottom)||(point.y<=getAreaTela().top)){
        bateu=true;
    }

    return bateu;
}
Bola Raquete::getVisaoBola()
{
    return *visaoBola;
}

Bola * Raquete::visaoBola =NULL;

