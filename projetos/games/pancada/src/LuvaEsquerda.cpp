
#include "LuvaEsquerda.h"

LuvaEsquerda::LuvaEsquerda()
{
	eLuva	= LUVA_ESQUERDA;
}

LuvaEsquerda::~LuvaEsquerda()
{
//não implementado
}

void LuvaEsquerda::setPosicao(int x, int y)
{
	posicao.x=x-32;
	posicao.y=y;

	if (sprite->getDirecao()==GBF::Imagem::Sprite::DR_CIMA){
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
