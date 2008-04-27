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
#include "NaveInimigo.h"
#include "PathStrategy.h"


ListTiroInimigo* NaveInimigo::listTiro=NULL;
ParticleSystemManager* NaveInimigo::particleManager=NULL;
void NaveInimigo::setListTiro(ListTiroInimigo* list)
{
    listTiro=list;
}
NaveInimigo::NaveInimigo()
{
    path = NULL;

    if (particleManager==NULL){
        particleManager = ParticleSystemManager::getInstance();
    }
}
NaveInimigo::~NaveInimigo()
{
//	sprite=NULL;
//	sprite_atingido=NULL;

    if (path!=NULL){
        delete(path);
    }
}
void NaveInimigo::acao(InputSystem* INPUT)
{
    if (isAtivo()){
    	checarArma();
        if (isVivo()){
            if (path->mover(sistema.velocidade.eAtual,&posicao,getDimensao())){
                setAtivo(false);
            } else {
                prepararPhaser();
                prepararTorpedo();
            }
        } else {
            setAtivo(false);
        }
    }
}
void NaveInimigo::desenhar()
{
    if (isVivo()){
        PersonagemAbstract::desenhar();
    }
}
void NaveInimigo::checarArma()
{
    delay.tiroA--;
    delay.tiroB--;
}
void NaveInimigo::setVivo(bool VALOR)
{
    if (VALOR==false){
        sistema.escudo.atual--;
        if (sistema.escudo.atual<0){
            //toca som de explosao
            soundSystem->fxManager->playPanEffect("explosao",posicao.x);

            //cria particulas da explosao da nave
//            Dimensao dimensaoSprite = sprite->getTamanho();
            Dimensao dimensaoSprite = getDimensao();
            Ponto pontoExplosao;

            pontoExplosao.x = posicao.x + (dimensaoSprite.w/2);
            pontoExplosao.y = posicao.y + (dimensaoSprite.h/2);

            ParticleSystemEfeitoEsferico* explosao = new EfeitoExplosao();
            explosao->setRaio(dimensaoSprite.w*2);
            explosao->setQuantidade(int(int(dimensaoSprite.w*dimensaoSprite.h)/10));
            explosao->criar(pontoExplosao.x,pontoExplosao.y);

            particleManager->adicionar(explosao);
        } else {
            VALOR=true;
        }
    }
    PersonagemAbstract::setVivo(VALOR);
}
void NaveInimigo::choque(int forca)
{
    sistema.escudo.atual-=forca;

    if (sistema.escudo.atual<0){
		soundSystem->fxManager->playPanEffect("explosao",posicao.x);
        setVivo(false);
    }
}
void NaveInimigo::prepararTorpedo()
{
    if (delay.tiroB<=0){
        dispararTorpedo();
        delay.tiroB=espera.tiroB;
    }
}
void NaveInimigo::prepararPhaser()
{
    if (delay.tiroA<=0){
        dispararPhaser();
        delay.tiroA=espera.tiroA;
    }
}
void NaveInimigo::selecionarPosicao()
{
//    DIRECAO dir = DIRECAO(rand()%sprite->getQtdDirecoes());
    DIRECAO dir = DIRECAO(rand()%getSpritePrincipal()->getQtdDirecoes());
//    sprite->setDirecao(dir);
    getSpritePrincipal()->setDirecao(dir);
    Dimensao dimensao = getDimensao();
    int x=0,y=0;

    switch(dir){
        case DR_CIMA:
            x=area.left+(rand()%(area.right-area.left))-dimensao.w;
            y=area.bottom;
            break;

        case DR_DIREITA:
            x=area.left-dimensao.w;
            y=(rand()%(area.top-area.bottom))-dimensao.h;
            break;

        case DR_BAIXO:
            x=(rand()%(area.right-area.left))-dimensao.w;
            y=area.top-dimensao.h;
            break;

        case DR_ESQUERDA:
            x=area.right;
            y=area.top+(rand()%(area.top-area.bottom))+dimensao.h;
            break;

        case DR_CIMADIREITA:
            x=area.left-dimensao.w;
            y=area.bottom;
            break;

        case DR_BAIXODIREITA:
            x=area.left-dimensao.w;
            y=area.top-dimensao.h;
            break;

    	case DR_CIMAESQUERDA:
            x=area.right;
            y=area.bottom;
            break;

    	case DR_BAIXOESQUERDA:
            x=area.right;
            y=area.top-dimensao.h;
            break;
	}

	setPosicao(x,y);
}
void NaveInimigo::caminho()
{
//    DIRECAO dir = DIRECAO(rand()%sprite->getQtdDirecoes());
    DIRECAO dir = DIRECAO(rand()%getSpritePrincipal()->getQtdDirecoes());
//    sprite->setDirecao(dir);
    getSpritePrincipal()->setDirecao(dir);
    caminho(dir);
}
void NaveInimigo::caminho(DIRECAO dir)
{
	PathStrategy *newPath = NULL;
    switch(dir){
        case DR_CIMA:
                newPath = PathFactory::criar(PATH_UP);
            break;
        case DR_DIREITA:
                newPath = PathFactory::criar(PATH_RIGHT);
            break;
        case DR_BAIXO:
                newPath = PathFactory::criar(PATH_DOWN);
            break;
        case DR_ESQUERDA:
                newPath = PathFactory::criar(PATH_LEFT);
            break;
        case DR_CIMADIREITA:
                newPath = PathFactory::criar(PATH_UP_RIGHT);
            break;
        case DR_BAIXODIREITA:
                newPath = PathFactory::criar(PATH_DOWN_RIGHT);
            break;
        case DR_BAIXOESQUERDA:
                newPath = PathFactory::criar(PATH_DOWN_LEFT);
            break;
        case DR_CIMAESQUERDA:
                newPath = PathFactory::criar(PATH_UP_LEFT);
            break;
    }
    //remove path se ja existir
    //obs.: o path só não existe quando a nave é criada
    if (path){
        delete (path);
        path = NULL;
    }
    path = newPath;
    newPath = NULL;
    this->direcao = dir;
}
int NaveInimigo::tipoClasse()
{
    return 11;//(int)"NaveInimigo";
}
