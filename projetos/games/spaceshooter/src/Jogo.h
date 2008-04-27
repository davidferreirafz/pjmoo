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
#ifndef _JOGO_H_
#define _JOGO_H_

#include <GBF/FrameLayerManager.h>
#include <GBF/GAT.h>
#include <GBF/TimerSystemCronometroCrescente.h>
#include <GBF/UserInterfaceMenuAbstract.h>
#include <GBF/UserInterfaceMenuTexto.h>
#include <GBF/UserInterfaceMenuItemTexto.h>

#include "Controle.h"
#include "Apresentacao.h"

//Assinatura do cabecalho do arquivo de recordes
#define ASSINATURA_JOGO_NOME 'S'+'p'+'a'+'c'+'e'+'S'+'h'+'o'+'o'+'t'+'e'+'r'
#define ASSINATURA_JOGO_SIGLA 'S'+'S'
#define ASSINATURA_JOGO_VERSAO 'v'+'1'+'0'



class Jogo : public GAT
{
public:
    /** Destrutor */
	virtual ~Jogo();
	/** Construtor */
	Jogo(int argc, char* argv[]);

protected:
    /** Tela de Introducao do jogo*/
    void apresentacao();
    /** Tela de Menu */
    void gatilhoMenuPrincipal();
    void menuPrincipal();
    void menuConfiguracao();
    /** Tela de Sobre*/
    void menuSobre();
    /** Tela de Ajuda*/
    void menuAjuda();
    /** Tela de Agradecimentos a Equipe Técnica*/
	void menuCredito();
    /** Tela que exibe o Top Recorde*/
    bool gatilhoTopGaleriaExibir();
    void topGaleriaExibir();
    /** Tela para cadastro de novo Recorde*/
    bool gatilhoTopGaleriaNovo();
    void topGaleriaNovo();
    void topGaleriaSalvar();
    /** Novo Jogo */
	void jogoNovo();
	void jogoExecutando();
	bool gatilhoJogoFaseCarregar();
	void jogoFaseCarregar();
    void jogoPause();
	bool gatilhoJogoFaseFinalizada();
    void jogoFaseFinalizada();
    void jogoGameOver();
    void jogoZerado();

	/** Carregar arquivos de recursos */
	void inicializarRecursos();


private:
    Controle controle;
    Apresentacao *videoApresentacao;
    SpriteItem* iconeGlobal;
    SpriteItem* iconeLocal;
    SpriteItem* banner;

    UserInterfaceMenuAbstract *uiMenuIdioma;

	TimerSystemCronometroCrescente tempoBlink;


    void desenharGUI();
    bool desenharBotaoEnter();
    void showAvisoRecorde();
    void showInfo();
    void showTitulo();
    void showSubTitulo();
};

#endif
