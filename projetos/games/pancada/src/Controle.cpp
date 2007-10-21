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
#include "Controle.h"

//Construtor
Controle::Controle()
{
    fase = NULL;
    tempoEspera.setTempoOriginal(4);
    tempoEspera.setUnidade(TEMPO_SEGUNDO);
    iniciar();
}
//Destrutor
Controle::~Controle()
{
    if (fase){
        delete(fase);
        fase=NULL;
    }
    if (fight){
        delete(fight);
    }
}
void Controle::iniciar()
{
    faseNumero=0;
    tempoEspera.setResetar();
}
bool Controle::carregarFase()
{
    bool maisFase = FaseFactory::isProximaFase(faseNumero);

    if (maisFase){
        faseNumero++;
        mudarFase();
    } else {
        faseNumero++;
    }

    return maisFase;
}
void Controle::mudarFase()
{
    FaseAbstract* novaFase = FaseFactory::criarFase(faseNumero);
    if (novaFase!=NULL){
        if (fase){
            delete(fase);
            fase = NULL;
        }
        fase = novaFase;
        novaFase = NULL;
        fase->iniciar();
    }
}
bool Controle::isGameOver()
{
    if ((fase!=NULL)&&(fase->isGameOver())){
        return true;
    } else {
        return false;
    }
}
bool Controle::isFaseFinalizada()
{
    if ((fase!=NULL)&&(fase->isFaseFinalizada())){
        return true;
    } else {
        return false;
    }
}
void Controle::executar(InputSystem * input)
{
    if (!tempoEspera.isTerminou()){
        tempoEspera.processar();
        fase->desenhar();
        WriteSystemManager::getInstance()->escrever("menu",220,170,"ROUND %02d",fase->getRound());
        if (tempoEspera.getTempo()<=2){
            fight->desenhar(94,200);
        }
//    } else if (fase->isFimRound()){
//        if (fase->isProximoRound()){
    } else if ((fase->isFimRound()) && (fase->isProximoRound())){
            fase->iniciar();
            fase->proximoRound();
            tempoEspera.setResetar();
    } else if (fase->isNocaute()){
        fase->desenhar();
        for (int i=100;i<430;i+=30){
            WriteSystemManager::getInstance()->escrever("menu",200,i,"NOCAUTE");
        }
    } else {
        fase->executar(input);
        fase->desenhar();
    }
}
void Controle::desenhar()
{
    fase->desenhar();
}
void Controle::carregar()
{
    SpriteFactory *spriteFactory = new SpriteFactory(GraphicSystem::getInstance()->imageBufferManager->getImageBuffer("personagem"));
    fight = spriteFactory->criarSpriteItem(0,316,453,82,1,1);
}
