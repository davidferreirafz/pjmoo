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
#include "FaseFactory.h"


FaseAbstract* FaseFactory::criarFase(int numero)
{
    FaseAbstract* fase = NULL;
    switch(numero){
        case 1:
            fase = new FaseUm();
        break;
        case 2:         
            fase = new FaseDois();
        break;
        case 3:
            fase = new FaseTres();
            fase->checkRestaurar();            
        break;
        case 4:
            fase = new FaseQuatro();
        break;
        case 5:
            fase = new FaseCinco();
            fase->checkRestaurar();
        break;
        case 6:
            fase = new FaseSeis();
        break;
        case 7:
            fase = new FaseSete();
        break;
    }
    return fase;
}
bool FaseFactory::isProximaFase(int faseAtual)
{
    if (faseAtual<MAX_FASE){
        return true;
    } else {
        return false;
    }
}
