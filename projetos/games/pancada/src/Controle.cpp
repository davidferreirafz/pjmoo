//***************************************************************************
//  Pancada <Game - Boxing Style>
//  Copyright (C) 2007 by David Ferreira - FZ
//  davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net
//***************************************************************************
//    Este programa é software livre; você pode redistribuí-lo e/ou
//    modificá-lo sob os termos da Licença Pública Geral GNU, conforme
//    publicada pela Free Software Foundation; tanto a versão 2 da
//    Licença como (a seu critério) qualquer versão mais nova.
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
    tempoEspera.setInitialTime(4);
    tempoEspera.setUnit(GBF::Kernel::Timer::TIME_SECOND_ONE);
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
    tempoEspera.setReset();
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
void Controle::executar(GBF::Kernel::Input::InputSystem * input)
{
    if (!tempoEspera.isFinish()){

        tempoEspera.update();
        fase->desenhar();

        GBF::Kernel::Write::WriteManager::getInstance()->write("menu",220,170,"ROUND %02d",fase->getRound());

        if (tempoEspera.getTime()<=2){
            fight->draw(94,200);
        }
    } else if (fase->isFimRound()){
        if (fase->isProximoRound()){
            fase->iniciar();
            fase->proximoRound();
            tempoEspera.setReset();
        }
    } else if (fase->isNocaute()){
        fase->desenhar();
        for (int i=100;i<430;i+=30){
            GBF::Kernel::Write::WriteManager::getInstance()->write("menu",200,i,"NOCAUTE");
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
    GBF::Image::SpriteFactory *spriteFactory = new GBF::Image::SpriteFactory("personagem");
    fight = spriteFactory->createSpriteItem(0,316,453,82,1,1);
}
