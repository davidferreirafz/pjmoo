/***************************************************************************
 *   Copyright (C) 2005-2006 by David Ferreira                             *
 *   davidferreira@uol.com.br - davidferreira.fz@gmail.com                 *
 *   http://pjmoo.codigolivre.org.br                                       *
 *       http://davidferreira.fz.googlepages.com                           *
 *                                                                         *
 *   Este programa é um software livre; você pode redistribui-lo e/ou      *
 *   modifica-lo dentro dos termos da Licença Pública Geral (GPL) GNU      *
 *   como publicada pela Fundação do Software Livre (FSF); na versão 2 da  *
 *   Licença.                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "ObstaculoAbstract.h"

int ObstaculoAbstract::velocidadeBase=0;
void ObstaculoAbstract::setVelocidadeBase(int velocidadeBase)
{
    ObstaculoAbstract::velocidadeBase=velocidadeBase;
}
ObstaculoAbstract::ObstaculoAbstract()
{
GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("personagem");
    adicionarSprite(spriteFactory->criarSpritePersonagem(0,0,48,48,6,2),"explosao");
    delete (spriteFactory);

//    sprite_atingido->setAutomatico(true);

    delay.acao  = 0;
    velocidade  = 0;
    resistencia = 0;
    danos       = 0;

	path = NULL;
}
ObstaculoAbstract::~ObstaculoAbstract()
{
    if (path){
        delete(path);
    }
}
int ObstaculoAbstract::getResistencia()
{
    return resistencia;
}
int ObstaculoAbstract::getDanos()
{
    return danos;
}
void ObstaculoAbstract::selecionarPosicao()
{
    GBF::Dimensao dimensao = getDimensao();
    setPosicao(area.left+(rand()%((area.right-dimensao.w)-area.left)),area.top-dimensao.h);
}
void ObstaculoAbstract::setVivo(bool VALOR)
{
    if (VALOR==false){
        GBF::Kernel::Sound::SoundSystem::getInstance()->fxManager->playPanEffect("explosao",posicao.x);
        Personagem::setVivo(VALOR);
    }
}
void ObstaculoAbstract::choque(int forca)
{
    resistencia-=forca;

    if (resistencia<=0){
        setVivo(false);
    }
}
void ObstaculoAbstract::desenhar()
{
    //se vivo desenha, sprite normal
    if (isVivo()){
        Personagem::desenhar();
    //se morreu desenha animacao de explosao
    } else if (getSprite("explosao")->animacao.isFim()==false){
        getSprite("explosao")->desenhar(posicao.x,posicao.y);
    }
}
void ObstaculoAbstract::acao(GBF::Kernel::Input::InputSystem * INPUT)
{
    if (isAtivo()){
        if (isVivo()){
            if (path->mover(velocidadeBase+velocidade,&posicao,getDimensao())){
                setAtivo(false);
            }
        } else {
            if (getSprite("explosao")->animacao.isFim()){
                setAtivo(false);
            }
        }
    }
}
