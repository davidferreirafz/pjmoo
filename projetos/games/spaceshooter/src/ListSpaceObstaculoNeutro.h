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
#ifndef _LISTSPACEOBSTACULONEUTRO_H
#define _LISTSPACEOBSTACULONEUTRO_H

/** 
 Rever metodos e logica para criacao, objetos devem ser criado
 de acordo com as necessidades (pontos no mapa) e nao de forma
 aleatoria ou continua
*/
#include "ListSpaceAbstract.h"
#include "ObstaculoAbstract.h"
#include "ObstaculoMina.h"
#include "ObstaculoFuracao.h"
#include "ObstaculoAsteroid.h"
#include "ObstaculoEsfera.h"
/** 
 TODO: observar para remover, aparentemente nao tem mais utilidade
*/
class ListSpaceObstaculoNeutro : public ListSpaceAbstract
{
public:
   virtual ~ListSpaceObstaculoNeutro();
   static ListSpaceObstaculoNeutro* getInstance(void);

   //rever essa aqui colocar como virtual a primeira listcontainer
   void adicionar(ObstaculoAbstract* obstaculo);	   
//   void acao(void);


protected:
   static ListSpaceObstaculoNeutro* instance;
   int limite;

private:
   ListSpaceObstaculoNeutro();


};

#endif
