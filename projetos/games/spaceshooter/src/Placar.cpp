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
#include "Placar.h"


Placar* Placar::instance=NULL;
Placar* Placar::getInstance()
{
    if (instance==NULL){
        instance = new Placar();
    }
    return instance;
}
Placar::Placar()
{
}
Placar::~Placar()
{
	//UtilLog::getInstance()->inicializando("Removendo Placar (Singleton)");
}
void Placar::zerarRegistroAtual()
{
    strcpy(registroAtual.nome,"          \0");

    registroAtual.pontos  = 0;
    registroAtual.fase    = 0;
    
    bonus.arma.quantidade = 0;
    bonus.arma.ativo            = false;
    bonus.escudo.quantidade     = 0;
    bonus.escudo.ativo          = false;    
    bonus.velocidade.quantidade = 0;
    bonus.velocidade.ativo      = false;
    
	tempoJogo.inicio  = SDL_GetTicks();
	tempoJogo.termino = 0;
}
/** Incrementar valor da pontuação atual*/
void Placar::incrementar()
{
    registroAtual.pontos++;
    
    contagemBonus();
    lancarBonus();
}
/** Retorna o valor da pontuação atual*/
unsigned int Placar::getPontos()
{
    return registroAtual.pontos;
}
void Placar::contagemBonus()
{
    int qtdEscudo     = getPontos()/250;
    int qtdArma       = getPontos()/600;
    int qtdVelocidade = getPontos()/1000;
  
    if (qtdEscudo>bonus.escudo.quantidade){
        bonus.escudo.quantidade = qtdEscudo;
        bonus.escudo.ativo = true;
    }
    if (qtdArma>bonus.arma.quantidade){
        bonus.arma.quantidade = qtdArma;
        bonus.arma.ativo = true;
    }
    if (qtdVelocidade>bonus.velocidade.quantidade){
        bonus.velocidade.quantidade = qtdVelocidade;
        bonus.velocidade.ativo = true;
    }
}
/** Adiciona bonus em pontos*/
void Placar::adicionarBonus(int pontos)
{
	registroAtual.pontos+=pontos;
	contagemBonus();
}
/** Lança bonus no jogo */
void Placar::lancarBonus()
{
    if (bonus.arma.ativo){
        bonus.arma.ativo=false;
        ListItem::getInstance()->adicionar(ItemFactory::criar(ITEM_ARMA));
    } else if (bonus.escudo.ativo){
        bonus.escudo.ativo=false;
        ListItem::getInstance()->adicionar(ItemFactory::criar(ITEM_ESCUDO));
    } else if (bonus.velocidade.ativo){
        bonus.velocidade.ativo=false;
        ListItem::getInstance()->adicionar(ItemFactory::criar(ITEM_VELOCIDADE));
    }
}    
TopSystemRecorde Placar::getRecorde()
{
	tempoJogo.termino = SDL_GetTicks();	
	
	Uint32 t= int((tempoJogo.termino - tempoJogo.inicio)/1000);
	
	registroAtual.tempo=int(t);
	
    return registroAtual;
}


    
