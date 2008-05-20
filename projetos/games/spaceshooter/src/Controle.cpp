/***************************************************************************
*   Copyright (C) 2005-2007 by David Ferreira                             *
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
#include "Controle.h"

Controle::Controle()
{
    fase = NULL;
    placar = Placar::getInstance();

    NaveAliado::setListTiro(ListTiroJogador::getInstance());
    NaveInimigo::setListTiro(ListTiroInimigo::getInstance());
}
Controle::~Controle()
{
    if (fase){
        delete(fase);
        fase=NULL;
    }
    if (placar){
        delete(placar);
    }
    // Deletando Singletons
    delete (ListTiroJogador::getInstance());
    delete (ListTiroInimigo::getInstance());
    delete (ListSpaceObstaculo::getInstance());
    delete (ListSpaceInimigo::getInstance());
    delete (InterfaceStatus::getInstance());
}
void Controle::mudarFase()
{
    FaseAbstract* novaFase = FaseFactory::criarFase(numeroFase);
    if (novaFase!=NULL){
        if (fase){
            delete (fase);
            fase = NULL;
        }
        fase = novaFase;
        novaFase = NULL;
        limparList();
        fase->carregar();
    }
}
void Controle::limparList()
{
    ListTiroJogador::getInstance()->limpar();
    ListTiroInimigo::getInstance()->limpar();
    ListSpaceObstaculo::getInstance()->limpar();
    ListSpaceInimigo::getInstance()->limpar();
    ListItem::getInstance()->limpar();
}
void Controle::novoJogo()
{
    numeroFase = 0;
    placar->zerarRegistroAtual();
}
bool Controle::carregarFase()
{
    bool maisFase = FaseFactory::isProximaFase(numeroFase);

    if (maisFase){
        numeroFase++;
        mudarFase();
    } else {
        numeroFase=8;
    }

    return maisFase;
}
void Controle::faseFinalizada()
{
    int pontuacaoBonus = 0;
    ArsenalStatus arsenal = fase->getArsenalStatus();

    pontuacaoBonus+= 50 * arsenal.arma;
    pontuacaoBonus+= 20 * arsenal.escudo;
    pontuacaoBonus+= 10 * arsenal.velocidade;

    placar->adicionarBonus(pontuacaoBonus);
}
bool Controle::isGameOver()
{
    return fase->isPerdeu();
}
bool Controle::isFaseFinalizada()
{
    return fase->isTerminou();
}
void Controle::jogoExecutando(GBF::Kernel::Input::InputSystem * input)
{
    fase->executar(input);
}
RankingSystem::RSRecorde Controle::novoRecorde()
{
    RankingSystem::RSRecorde novoRecorde = placar->getRecorde();
    novoRecorde.fase=numeroFase;

    return novoRecorde;
}
GBF::Area Controle::getFaseAreaZona()
{
    return fase->getAreaZona();
}
void Controle::inicializarFase()
{
    fase->iniciar();
    fase->restaurarNave();
}
const char* Controle::getZona()
{
    return fase->getZona().c_str();
}
const char* Controle::getMissao()
{
    return fase->getMissao().c_str();
}
const char* Controle::getInimigo()
{
    return fase->getInimigo().c_str();
}

