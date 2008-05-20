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
#ifndef _APRESENTACAO_H_
#define _APRESENTACAO_H_

#include <GBF/WriteManager.h>
#include <GBF/LayerManager.h>
#include <GBF/CronometroDecrescente.h>
#include <GBF/GraphicSystem.h>
#include <GBF/GFX.h>
#include <GBF/ImageBufferManager.h>
#include <GBF/SpriteFactory.h>
#include <GBF/UIWindowDialog.h>
#include <GBF/UIVisualSolido.h>

// Classe para criação da apresentação inicial do jogo
class Apresentacao
{
public:
	virtual ~Apresentacao();
	Apresentacao();
    bool executar();

    void preTela();

	void tela01();
	void tela02();
	void tela03();
	void tela04();
	void tela05();
	void tela06();
	void tela07();
	void tela08();
	void tela09();
	void reset();



protected:


    GBF::Kernel::Write::WriteManager * wsManager;
    GBF::Imagem::Layer::LayerManager * flManager;
    GBF::Kernel::Graphic::GFX *   gsGFX;

    GBF::Kernel::Timer::CronometroDecrescente tempo;

    UserInterface::Window::UIWindowDialog* janela;
    UserInterface::Window::UIWindowDialog* janelaCopyright;

private:
    int numeroTela;

    GBF::Imagem::Sprite::SpriteItem* zangoesBorg;
    GBF::Imagem::Sprite::SpriteItem* terra;
    GBF::Imagem::Sprite::SpriteItem* babyBorg;
    GBF::Imagem::Sprite::SpriteItem* logoInimigos;
    GBF::Imagem::Sprite::SpriteItem* naveDefiant;
    GBF::Imagem::Sprite::SpriteItem* naveEsquemas;
    GBF::Imagem::Sprite::SpriteItem* batalha;
    GBF::Imagem::Sprite::SpriteItem* naveBorg;
    GBF::Imagem::Sprite::SpriteItem* david;


};

#endif


