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
#ifndef _FASEABSTRACT_H
#define _FASEABSTRACT_H

#include <string>

#include <GBF/FrameLayer.h>
#include <GBF/LayerManager.h>
#include <GBF/SpriteFactory.h>
#include <GBF/ImageBufferManager.h>
#include <GBF/InputSystem.h>
#include <GBF/SoundSystem.h>
#include <GBF/WriteManager.h>
#include <GBF/PSManager.h>
#include <GBF/SoundSystemUtility.h>

#include "ListSpaceInimigo.h"
#include "ListSpaceObstaculo.h"
#include "ListSpaceObstaculoNeutro.h"
#include "ListTiroJogador.h"
#include "ListTiroInimigo.h"
#include "ListItem.h"
#include "NaveFactory.h"
#include "Placar.h"
#include "ItemFactory.h"
#include "InterfaceStatus.h"

struct ArsenalStatus
{
	int escudo;
	int arma;
	int velocidade;
};

class FaseAbstract : public GBF::Kernel::Sound::SoundSystemUtility
{
public:
    FaseAbstract();
    virtual ~FaseAbstract();
    /** Carrega(Load) da fase*/
    void carregar();
    /** Inicia a fase */
    virtual void iniciar()=0;
    /** Informa se passou de fase*/
    virtual bool isTerminou();
    bool isPerdeu();

    void executar(GBF::Kernel::Input::InputSystem * input);

    std::string getZona();
    std::string getMissao();
    std::string getInimigo();
    GBF::Area  getAreaZona();
    ArsenalStatus getArsenalStatus();
    void restaurarNave();
    void checkRestaurar();


protected:
	NaveAliado *nave;
   	GBF::Imagem::Layer::FrameLayer *tileSpace;
    static GBF::Imagem::Layer::FrameLayer *tileStatus;
  	static GBF::Imagem::Layer::FrameLayer *tileMensagem;
    static GBF::Kernel::Write::WriteManager *writeManager;
    static ParticleSystem::PSManager *particleManager;
    std::string zona;
    std::string missao;
    std::string inimigo;
    bool ultimoQuadro;
    GBF::Area areaZona;
    /** Referencia ao objeto singleton Placar */
    Placar * placar;
    /** Referencia ao objeto singleton InterfaceStatus */
    InterfaceStatus * status;


    /** Configura a fase */
    virtual void configurar()=0;
    /** Condi��o executada durante toda a fase */
    virtual void condicaoNavegandoFase()=0;
    /** Condi��o executada apenas na ultima tela*/
    virtual void condicaoUnicaUltimoQuadro()=0;
    virtual void ganchoUltimoQuadro();
    virtual std::string getMissaoCompleta()=0;
    virtual void hookMensagens();
    virtual void hookMensagemFinal();


private:
    bool restaurar;
    static Sistema sistemaNaveBackup;
	void definir();
	void armazenar();
	/** Desenha o Cenario*/
    void desenharCenario();
    /** Desenha o Painel com indicadores de Status*/
    void desenharPainel();
    /** Desenha as mensagens no painel*/
    void exibirMensagem();

    //A��o Principal - movimenta��o
    ListSpaceInimigo   *listSpaceInimigo;
    ListSpaceObstaculo *listSpaceObstaculo;
    ListTiroJogador    *listTiroJogador;
    ListTiroInimigo    *listTiroInimigo;
    ListItem           *listItem;
};

#endif

