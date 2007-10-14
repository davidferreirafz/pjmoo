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
#include "Cabeca.h"

//* Construtor 

//* Construtor 
Cabeca::Cabeca(){
    sprite=NULL;
}

//Destrutor 

//Destrutor 
Cabeca::~Cabeca(){
}

bool Cabeca::isColisao(Area aSoco) 
{
	float qx, qy, qr; //para guardar o quadrado de x, y e raio

	Area aCabeca   = getArea();

	//quadrado da distância em x
	qx = std::pow(float((aSoco.left + aSoco.right/2) - (aCabeca.left + aCabeca.right/2)), 2);
	//quadrado da distância em y	
	qy = std::pow(float((aSoco.top + aSoco.bottom/2) - (aCabeca.top  + aCabeca.bottom/2)), 2);
	//quadrado da soma dos raios	
	qr = std::pow(float(70), 2);

	if (qx + qy <= qr){
		return true;	
	} else {
		return false;
	}
}
void Cabeca::setPosicao(int x, int y) 
{
	posicao.x=x+47;
	posicao.y=y;
}
