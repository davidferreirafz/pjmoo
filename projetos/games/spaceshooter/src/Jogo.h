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

#include <GBF/LayerManager.h>
#include <GBF/GAT.h>
#include <GBF/CronometroCrescente.h>
#include <GBF/UIMenuAbstract.h>
#include <GBF/UIMenu.h>
#include <GBF/UIItemTexto.h>
#include <GBF/UIWindowTitulo.h>
#include <GBF/UIVisualSolido.h>
#include <GBF/UIVisualImagem.h>
#include <GBF/UIMenuTransparente.h>
#include <GBF/UIWindowRecorde.h>
#include <GBF/UIWindowDialog.h>
#include "Controle.h"
#include "Apresentacao.h"

//Assinatura do cabecalho do arquivo de recordes
#define ASSINATURA_JOGO_NOME 'S'+'p'+'a'+'c'+'e'+'S'+'h'+'o'+'o'+'t'+'e'+'r'
#define ASSINATURA_JOGO_SIGLA 'S'+'S'
#define ASSINATURA_JOGO_VERSAO 'v'+'1'+'0'



class Jogo : public GAT::GAT
{
public:
    int main(int argc, char * argv[]);
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
    GBF::Imagem::Sprite::SpriteItem* iconeGlobal;
    GBF::Imagem::Sprite::SpriteItem* iconeLocal;
    GBF::Imagem::Sprite::SpriteItem* banner;

    UserInterface::Menu::UIMenu *uiMenuIdioma;

	GBF::Kernel::Timer::CronometroCrescente tempoBlink;

    bool desenharBotaoEnter();

    void showInfo();
    void showTitulo();

    UserInterface::Window::UIWindowTitulo * janelaSobre;

    UserInterface::Window::UIWindowTitulo * janelaCredito;

    UserInterface::Window::UIWindowTitulo * janelaAjuda;

    UserInterface::Window::UIWindowTitulo * janelaRecorde;

    UserInterface::Window::UIWindowTitulo * janela;
};

#endif
