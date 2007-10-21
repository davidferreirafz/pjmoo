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
#include "FaseFactory.h"

//criar fabrica de fase baseada no conceito de prototype

FaseAbstract * FaseFactory::criarFase(int numero)
{
    FaseAbstract * fase = NULL;

    switch(numero){
        case 1:
            fase = new Fase(Mascarado);
            fase->setTotalRound(3);
        break;
        case 2:
            fase = new Fase(Punk);
            fase->setTotalRound(3);
        break;
        case 3:
            fase = new Fase(Cobra);
            fase->setTotalRound(3);
        break;
        case 4:
            fase = new Fase(Skar);
            fase->setTotalRound(3);
        break;
        default:
            return NULL;
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
const int FaseFactory::MAX_FASE;

