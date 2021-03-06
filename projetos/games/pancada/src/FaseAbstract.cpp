//***************************************************************************
//  Pancada <Game - Boxing Style>
//  Copyright (C) 2007 by David Ferreira - FZ
//  davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net
//***************************************************************************
//    Este programa � software livre; voc� pode redistribu�-lo e/ou
//    modific�-lo sob os termos da Licen�a P�blica Geral GNU, conforme
//    publicada pela Free Software Foundation; tanto a vers�o 2 da
//    Licen�a como (a seu crit�rio) qualquer vers�o mais nova.
//***************************************************************************
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the
//    Free Software Foundation, Inc.,
//    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//***************************************************************************
#include "FaseAbstract.h"

// so para virar de costas corretamente
// so para virar de costas corretamente

// so para virar de costas corretamente
void FaseAbstract::ordenacao()
{
	GBF::Point pc     = lutadorPC->getPosicao();
	GBF::Point player = lutadorPlayer->getPosicao();

	if (player.y <= pc.y){
		lutadorPlayer->olharBaixo();
		lutadorPC->olharCima();
	} else {
		lutadorPlayer->olharCima();
		lutadorPC->olharBaixo();
	}
}
//Destrutor

//Destrutor
FaseAbstract::FaseAbstract()
{
    //informa tempo por round
    cronometroAuxiliar.setInitialTime(6);

    lutadorPlayer = NULL;
    lutadorPC     = NULL;
    ringue        = GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background");

    if (wsManager==NULL){
        wsManager = GBF::Kernel::Write::WriteManager::getInstance();
    }

    if (particleManager==NULL){
        particleManager = ParticleSystem::PSManager::getInstance();
    }

    GBF::Area areaRingue;
    areaRingue.top    =  34;
    areaRingue.bottom = 469;
    areaRingue.left   =  28;
    areaRingue.right  = 611;

    LutadorAbstract::setRingue(areaRingue);

    primeiroRound();
}

//Construtor

//Construtor
FaseAbstract::~FaseAbstract()
{
    if (lutadorPlayer){
    	delete(lutadorPlayer);
    }
    if (lutadorPC){
    	delete(lutadorPC);
    }
    if (ringue){
	    ringue=NULL;
    }
}

bool FaseAbstract::isGameOver()
{
    bool perdeu = false;

    if (((lutadorPlayer->isNocaute())&&(cronometroAuxiliar.isFinish())) ||
       ((round.isUltimo()) && (placar.isTempoTerminou()) && (placar.isPCGanhou()))){
        perdeu = true;
    }

    return perdeu;
}
bool FaseAbstract::isFaseFinalizada()
{
    bool finalizou = false;

    if (((lutadorPC->isNocaute())&&(cronometroAuxiliar.isFinish())) ||
       ((round.isUltimo()) && (placar.isTempoTerminou()) && (placar.isPlayerGanhou()))){
        finalizou = true;
    }

    return finalizou;
}
bool FaseAbstract::isFimRound()
{
    if (placar.isTempoTerminou()){
        return true;
    } else {
        return false;
    }
}
bool FaseAbstract::isNocaute()
{
    bool nocaute = false;

    if ((lutadorPlayer->isNocaute())||(lutadorPC->isNocaute())){
        nocaute = true;
        cronometroAuxiliar.update();
    }

    return nocaute;
}
bool FaseAbstract::isProximoRound()
{
    bool proximo = true;

    if (round.isUltimo()){
        proximo = false;
        if ((!placar.isPlayerGanhou())&&(!placar.isPCGanhou())){
            proximo = true;
        }
    }

    return proximo;
}
void FaseAbstract::proximoRound()
{
    round.proximo();
    placar.iniciarRound();
}
int FaseAbstract::getRound()
{
	return int(round.get());
}
void FaseAbstract::executar(GBF::Kernel::Input::InputSystem * input)
{
    //Movimenta os lutadores
	lutadorPlayer->mover(input,lutadorPC);
	lutadorPC->mover(input,lutadorPlayer);
	//coloca um de frente pro outro, escolher nome melhor
	ordenacao();

	//Verifica socos e contagem de pontos
	if (lutadorPlayer->socouAdversario(lutadorPC)){
		placar.adicionarPontoPlayer();
	}
	if (lutadorPC->socouAdversario(lutadorPlayer)){
		placar.adicionarPontoPC();
	}
    //executa o cronometro
    placar.processarTempo();
    particleManager->update();
}
void FaseAbstract::primeiroRound()
{
    round.setPrimeiro();
    placar.iniciar();
    cronometroAuxiliar.setReset();
}
void FaseAbstract::desenhar()
{
    ringue->draw();

    //desenha lutadores
    lutadorPlayer->draw();
    lutadorPC->draw();

    //desenha efeitos especiais
    particleManager->draw();

    statusPlayer.desenhar(placar.getPontosPlayer(),placar.getRoundsPlayer(),lutadorPlayer->getEnergia());
    statusPC.desenhar(placar.getPontosPC(),placar.getRoundsPC(),lutadorPC->getEnergia());
    statusTempo.desenhar(placar.getRoundTempo());
}
void FaseAbstract::setTotalRound(int total)
{
    round.setMaximo(total);
}
GBF::Kernel::Write::WriteManager * FaseAbstract::wsManager;

ParticleSystem::PSManager * FaseAbstract::particleManager;

