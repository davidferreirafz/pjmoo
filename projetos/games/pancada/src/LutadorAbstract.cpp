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

#include "LutadorAbstract.h"

Area LutadorAbstract::ringue;

//Construtor
LutadorAbstract::LutadorAbstract()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();

    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,0,153,76,2,8));
    delete(spriteFactory);

    getSpritePrincipal()->setQtdDirecoes(2);

	luvaesquerda = new LuvaEsquerda();
	luvadireita  = new LuvaDireita();

	delay.acao  = 0;
	delay.tiroA = 0;
	delay.tiroB = 0;

	posicao.x = 0;
	posicao.y = 0;

    luvaesquerda->setSoco(false);
    luvadireita->setSoco(false);
}
//Destrutor
LutadorAbstract::~LutadorAbstract()
{
    if (cabeca){
	    delete(cabeca);
	}
    if (luvaesquerda){
	    delete(luvaesquerda);
    }
    if (luvadireita){
	    delete(luvadireita);
	}
}
//Desenha na tela
void LutadorAbstract::desenhar()
{
//    corrigirPosicao();
    PersonagemControlado::desenhar();
	cabeca->desenhar();
	luvaesquerda->desenhar();
	luvadireita->desenhar();
}
//O lutador está na olhando pra cima
void LutadorAbstract::olharCima()
{
	cabeca->setCima();
	luvaesquerda->setCima();
	luvadireita->setCima();
    getSpritePrincipal()->setDirecao(DR_CIMA);
}
//O lutador está na olhando pra baixo
void LutadorAbstract::olharBaixo()
{
	cabeca->setBaixo();
	luvaesquerda->setBaixo();
	luvadireita->setBaixo();
    getSpritePrincipal()->setDirecao(DR_BAIXO);
}
Ponto LutadorAbstract::getPosicao()
{
	return posicao;
}
void LutadorAbstract::setPosicao(int x, int y)
{
    PersonagemAbstract::setPosicao(x,y);
	luvaesquerda->setPosicao(x,y);
	luvadireita->setPosicao(x,y);
	cabeca->setPosicao(x,y);
}
void LutadorAbstract::setRingue(Area ringue)
{
    ringue.left   +=32;
	ringue.top    +=32;
	ringue.right  -=32;
	ringue.bottom -=32;

    LutadorAbstract::ringue=ringue;
}
Area LutadorAbstract::getArea()
{
    Area area;

    area.top=posicao.y;
    area.left=posicao.x;

    Dimensao d = getDimensao();

    area.bottom=d.h;
    area.right=d.w;

    return area;
}
//checka com limites do ringue
void LutadorAbstract::checklimites()
{
	Ponto posicao     = getPosicao();
	Dimensao dimensao = getDimensao();

    if (posicao.x-22<=ringue.left){
        posicao.x=ringue.left+22;
    } else if (posicao.x+dimensao.w+22>=(ringue.right)){
        posicao.x=(ringue.right) - dimensao.w-22;
    }
	if (getSpritePrincipal()->getDirecao()==DR_CIMA){
	    if (posicao.y-32<=ringue.top){
	        posicao.y=ringue.top+32;
	    } else if (posicao.y+dimensao.h-32>=(ringue.bottom)){
	        posicao.y=(ringue.bottom) - dimensao.h+32;
	    }
	} else {
	    if (posicao.y+32<=ringue.top){
	        posicao.y=ringue.top-32;
	    } else if (posicao.y+dimensao.h+32>=(ringue.bottom)){
	        posicao.y=(ringue.bottom) - dimensao.h-32;
	    }
	}

	setPosicao(posicao.x,posicao.y);
}
bool LutadorAbstract::choqueAdversario(Area aCorpoAdversario)
{
	Area aCorpoLcl  = getArea();

	if ((aCorpoLcl.left + aCorpoLcl.right  >= aCorpoAdversario.left)&&
		(aCorpoLcl.left                    <= aCorpoAdversario.left + aCorpoAdversario.right)&&
		(aCorpoLcl.top  + aCorpoLcl.bottom >= aCorpoAdversario.top) &&
		(aCorpoLcl.top                     <= aCorpoAdversario.top + aCorpoAdversario.bottom)){
		return true;
	} else {
		return false;
	}
}
bool LutadorAbstract::socouAdversario(LutadorAbstract * adversario)
{
	bool retorno =  false;

	if ((luvaesquerda->isSoco())&&
		(adversario->levouSoco(luvaesquerda))){
			retorno = true;
	}else if ((luvadireita->isSoco())&&
				(adversario->levouSoco(luvadireita))){
			retorno = true;
	}

	if (retorno){
        Ponto posicao = getPosicao();

		if (getSpritePrincipal()->getDirecao()==DR_CIMA){
			posicao.y+=8;
		}else {
			posicao.y-=8;
		}

		setPosicao(posicao.x,posicao.y);
	}
	checklimites();
	return retorno;
}
bool LutadorAbstract::levouSoco(LuvaAbstract * luva)
{
	bool levou = false;
	if (delay.acao<=0){
		delay.acao=2;
		if ((levou=cabeca->isColisao(luva->getArea()))){
			Ponto pntCabeca = cabeca->getPosicao();
			Ponto posicao = getPosicao();
			pntCabeca.x+=22;
			if (getSpritePrincipal()->getDirecao()!=DR_CIMA){
				pntCabeca.y+=53;
				posicao.y-=20;
				if (luva->isLuvaEsquerda()){
					posicao.x+=20;
				} else {
					posicao.x-=20;
				}
			}else {
				posicao.y+=20;
				if (luva->isLuvaEsquerda()){
					posicao.x+=20;
				} else {
					posicao.x-=20;
				}
			}
			setPosicao(posicao.x,posicao.y);
			EfeitoContainer::getInstance()->adicionar(pntCabeca.x,pntCabeca.y,EFEITO_SANGUE);
		}
	} else {
        delay.acao--;
        return false;
	}
	return levou;
}
void LutadorAbstract::mover(InputSystem * input, LutadorAbstract * adversario)
{
	Ponto pAnterior = getPosicao();

	acao(input);
	checklimites();
	if (choqueAdversario(adversario->getArea())){
		setPosicao(pAnterior.x,pAnterior.y);
	}
}
