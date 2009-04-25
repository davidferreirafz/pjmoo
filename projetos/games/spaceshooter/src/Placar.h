/***************************************************************************
 *   Copyright (C) 2005-2006 by David Ferreira                             *
 *   davidferreira@uol.com.br - davidferreira.fz@gmail.com                 *
 *   http://pjmoo.codigolivre.org.br                                       *
 *       http://davidferreira.fz.googlepages.com                           *
 *                                                                         *
 *   Este programa � um software livre; voc� pode redistribui-lo e/ou      *
 *   modifica-lo dentro dos termos da Licen�a P�blica Geral (GPL) GNU      *
 *   como publicada pela Funda��o do Software Livre (FSF); na vers�o 2 da  *
 *   Licen�a.                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef _PLACAR_H_
#define _PLACAR_H_

#include <string>

#include <GBF/RSRecorde.h>


#include "ListItem.h"
#include "ItemFactory.h"

struct TipoBonus
{
    int quantidade;
    bool ativo;
};

struct Bonus
{
    TipoBonus escudo;
    TipoBonus velocidade;
    TipoBonus arma;
};

struct Tempo
{
	Uint32 inicio;
	Uint32 termino;
};

class Placar
{
public:
    /** Destrutor */
	virtual ~Placar();
    /** Retorna a instancia da classe*/
	static Placar* getInstance();
	/** Reinicia o marcado do registro atual*/
	void zerarRegistroAtual();
	/** Incrementar valor da pontua��o atual*/
	void incrementar();
    /** Retorna o valor da pontua��o atual*/
    unsigned int getPontos();
    RankingSystem::RSRecorde getRecorde();
	/** Adiciona bonus em pontos*/
    void adicionarBonus(int pontos);


private:
//Atributos
	Tempo tempoJogo;
	/** Informa��es sobre bonus*/
	Bonus bonus;
	/** Instancia da classe (SINGLETON)*/
	static Placar* instance;
//Metodos
    /** Construtor */
	Placar();
	/** Informa��es do jogo atual*/
	//PlacarRegistro registroAtual;
	RankingSystem::RSRecorde registroAtual;
	/** Verifica se deve lan�ar um novo item de bonus*/
    void contagemBonus();
    /** Lan�a bonus no jogo */
    void lancarBonus();
};

#endif


