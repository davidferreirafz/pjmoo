////    Pacanda - Based boxing game
////    Copyright (C) 2004-2006 David de Almeida Ferreira
////
////    This is free software; you can redistribute it and/or
////    modify it under the terms of the GNU General Public
////    License as published by the Free Software Foundation; either
////    version 2 of the License, or (at your option) any later version.
////
////    David de Almeida Ferreira (F-Z)
////        davidferreira@uol.com.br or davidferreira.fz@gmail.com
////        http://pjmoo.codigolivre.org.br
////////////////////////////////////////////////////////////////////////

#include "LuvaDireita.h"

LuvaDireita::LuvaDireita() 
{
	eLuva	= LUVA_DIREITA;
}
LuvaDireita::~LuvaDireita() 
{
//n�o implementado
}
void LuvaDireita::setPosicao(int x, int y) 
{
	posicao.x=x+109;
	posicao.y=y;

	if (sprite->getDirecao()==DR_CIMA){
	  	if (isSoco()){
			posicao.y-=68;
		} else {
			posicao.y-=42;
		}		
	} else {
	  	if (isSoco()){
			posicao.y+=60;
		} else {
			posicao.y+=34;
		}		
	}	
}