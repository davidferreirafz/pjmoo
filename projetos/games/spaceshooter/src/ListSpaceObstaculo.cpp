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
#include "ListSpaceObstaculo.h"

ListSpaceObstaculo* ListSpaceObstaculo::instance=NULL;

bool ListSpaceObstaculo::OBSTACULO_ESFERA   = false;
bool ListSpaceObstaculo::OBSTACULO_ASTEROID = false;
bool ListSpaceObstaculo::OBSTACULO_MINA     = false;
bool ListSpaceObstaculo::OBSTACULO_FURACAO  = false;

ListSpaceObstaculo::ListSpaceObstaculo()
{
	limite=0;
}
ListSpaceObstaculo::~ListSpaceObstaculo()
{
	//UtilLog::getInstance()->inicializando("Removendo ListSpaceObstaculo (Singleton)");
}
ListSpaceObstaculo* ListSpaceObstaculo::getInstance()
{
	if (instance == NULL){
		instance = new ListSpaceObstaculo();
	}
	return instance;
}
void ListSpaceObstaculo::criar()
{
    ObstaculoAbstract *obstaculo=NULL;
    int selecao =0;
    bool gerandoObstaculo = OBSTACULO_ESFERA||OBSTACULO_ASTEROID
                            ||OBSTACULO_MINA||OBSTACULO_FURACAO;

    if (gerandoObstaculo){
        while(!obstaculo){
            selecao=rand()%4;
            if ((selecao==0)&&(OBSTACULO_ESFERA)){
                obstaculo = new ObstaculoEsfera();
            }else if ((selecao==1)&&(OBSTACULO_ASTEROID)){
                obstaculo = new ObstaculoAsteroid();
            }else if ((selecao==2)&&(OBSTACULO_MINA)){
                obstaculo = new ObstaculoMina();
            }else if ((selecao==3)&&(OBSTACULO_FURACAO)){
                obstaculo = new ObstaculoFuracao();
            }
        }
        lista.push_back(obstaculo);
    }
}
void ListSpaceObstaculo::adicionar(int quantidade)
{
	for (int i=0; i<quantidade;i++){
		criar();
	}
}
void ListSpaceObstaculo::setLimite(int maximo)
{
	limite=maximo;
}
void ListSpaceObstaculo::acao(GBF::Kernel::Input::InputSystem * input)
{
	Personagem::ListPersonagem::acao(NULL);

	adicionar(limite-lista.size());
}
void ListSpaceObstaculo::colisao(NaveAbstract* nave)
{
	ObstaculoAbstract *obstaculo=NULL;

    for (int iObstaculo=0; iObstaculo<size(); iObstaculo++){
        obstaculo=(ObstaculoAbstract*)getPersonagem(iObstaculo);
        if ((obstaculo!=NULL)&&(obstaculo->isVivo())){
            if ((nave!=NULL)&&(nave->isVivo())){
				if (obstaculo->isColisao(nave)){
                    obstaculo->setVivo(false);
					nave->choque(obstaculo->getDanos());
 					break;
				}
            }
        }
    }
}



