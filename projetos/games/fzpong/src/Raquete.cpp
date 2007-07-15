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
    adaptarVelocidade();
}
//Posiciona Raquete
void Raquete::preparar() 
{
    //Se for do lado direito da tela
    if (lado==LADO_DIREITO){
        setPosicao(getAreaTela().right-getDimensao().w,(getAreaTela().bottom/2)-(getDimensao().h/2));
    //Se for do lado esquerdo da tela
    } else {
        setPosicao(0,(getAreaTela().bottom/2)-(getDimensao().h/2));
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
bool Raquete::isColisao(PersonagemAbstract * personagem) 
{
    bool retorno = false;

//Se raquete no lado direito da tela
    if (lado==LADO_DIREITO){
        /*if ((personagem->getPosicao().x+personagem->getDimensao().w >= posicao.x)&&
            (posicao.y + getDimensao().h >= personagem->getPosicao().y)&&
            (posicao.y <= personagem->getPosicao().y + personagem->getDimensao().h)){*/
        if ((posicao.x + getDimensao().w >= personagem->getPosicao().x) &&
            (posicao.x <= personagem->getPosicao().x + personagem->getDimensao().w) &&
            (posicao.y + getDimensao().h >= personagem->getPosicao().y) &&
            (posicao.y <= personagem->getPosicao().y + personagem->getDimensao().h)){
                retorno = true;
        }
//Se raquete no lado esquerdo da tela
    } else {
        /*if ((personagem->getPosicao().x <= posicao.x+getDimensao().w)&&
            (posicao.y + getDimensao().h >= personagem->getPosicao().y)&&
            (posicao.y <= personagem->getPosicao().y + personagem->getDimensao().h)){*/
        if ((posicao.x + getDimensao().w >= personagem->getPosicao().x) &&
            (posicao.x <= personagem->getPosicao().x + personagem->getDimensao().w) &&
            (posicao.y + getDimensao().h >= personagem->getPosicao().y) &&
            (posicao.y <= personagem->getPosicao().y + personagem->getDimensao().h)){
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
Bola Raquete::getVisaoBola() 
{
    return *visaoBola;
}
void Raquete::adaptarVelocidade() 
{
    int vb = visaoBola->getVelocidade();

    if (vb<0){
        vb= - vb;
    }

    velocidade= int((vb) * 0.9);
}
Bola * Raquete::visaoBola =NULL;

