
#include "LuvaDireita.h"

LuvaDireita::LuvaDireita()
{
	eLuva	= LUVA_DIREITA;
}

LuvaDireita::~LuvaDireita()
{
//não implementado
}

void LuvaDireita::setPosicao(int x, int y)
{
	posicao.x=x+109;
	posicao.y=y;

	if (sprite->getDirection()==GBF::Image::Sprite::DR_CIMA){
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
