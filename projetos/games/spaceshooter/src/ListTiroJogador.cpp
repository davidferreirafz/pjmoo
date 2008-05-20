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
#include "ListTiroJogador.h"

ListTiroJogador* ListTiroJogador::instance=NULL;
ParticleSystem::PSManager * ListTiroJogador::particleManager = NULL;
ListTiroJogador::ListTiroJogador()
{
    placar = Placar::getInstance();
    particleManager = ParticleSystem::PSManager::getInstance();
}
ListTiroJogador::~ListTiroJogador()
{
    placar = NULL;
	//UtilLog::getInstance()->inicializando("Removendo ListTiroJogador (Singleton)");
}
ListTiroJogador* ListTiroJogador::getInstance()
{
		if (instance == NULL){
			instance = new ListTiroJogador();
		}
		return instance;
}
/** Verifica colisão de uma lista com outra lista de objetos (SOBREESCRITO)*/
void ListTiroJogador::colisao(Personagem::ListPersonagem * lista)
{
	TiroAbstract *tiro=NULL;
    SpaceObject  *alvo=NULL;

    for (int iTiro=0; iTiro<size(); iTiro++){
        tiro=(TiroAbstract*)getPersonagem(iTiro);
        if (tiro!=NULL){
            for (int iLista=0; iLista<lista->size(); iLista++){
                alvo=(SpaceObject*)lista->getPersonagem(iLista);
                if ((alvo!=NULL)&&(alvo->isVivo())){
					if (tiro->isColisao(alvo)){
						tiro->setAtivo(false);
						alvo->choque(tiro->getPotencia());
                        placar->incrementar();
                        //remover depois, ver uma forma para identificar o objeto que foi
                        //atingido e passar os pontos de colisao
                        //forma provisoria
                        if (alvo->tipoClasse(11)){
                            ParticleSystem::PSEfeitoEsferico* efeito  = new EfeitoExplosao();
                            efeito->setQuantidade(150);
                            efeito->setRaio(50);
                            GBF::Ponto ponto = tiro->getPosicao();
                            efeito->criar(ponto.x,ponto.y);
                            particleManager->adicionar(efeito);
                        }

						break;
					}
                }
            }
        }
    }
}
/** Verifica colisão de uma lista com apenas um objeto (SOBREESCRITO)*/
void ListTiroJogador::colisao(Personagem::Personagem * objeto)
{
	TiroAbstract    *tiro=NULL;
    SpaceObject     *alvo=NULL;

    alvo=(SpaceObject*)objeto;

    for (int iTiro=0; iTiro<size(); iTiro++){
        tiro=(TiroAbstract*)getPersonagem(iTiro);
        if (tiro!=NULL){
            if ((alvo!=NULL)&&(alvo->isVivo())){
				if (tiro->isColisao(alvo)){
					tiro->setAtivo(false);
					alvo->choque(tiro->getPotencia());
                    placar->incrementar();
					break;
				}
            }
        }
    }
}


