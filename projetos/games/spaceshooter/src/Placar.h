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
	/** Incrementar valor da pontuação atual*/
	void incrementar();
    /** Retorna o valor da pontuação atual*/
    unsigned int getPontos();
    RankingSystem::RSRecorde getRecorde();
	/** Adiciona bonus em pontos*/
    void adicionarBonus(int pontos);


private:
//Atributos
	Tempo tempoJogo;
	/** Informações sobre bonus*/
	Bonus bonus;
	/** Instancia da classe (SINGLETON)*/
	static Placar* instance;
//Metodos
    /** Construtor */
	Placar();
	/** Informações do jogo atual*/
	//PlacarRegistro registroAtual;
	RankingSystem::RSRecorde registroAtual;
	/** Verifica se deve lançar um novo item de bonus*/
    void contagemBonus();
    /** Lança bonus no jogo */
    void lancarBonus();
};

#endif


