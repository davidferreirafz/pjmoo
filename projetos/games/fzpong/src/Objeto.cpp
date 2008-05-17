///***************************************************************************
// *   FZPong <Game - Pong Clone>                                            *
// *   Copyright (C) 2007 by David Ferreira - FZ                             *
// *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
// ***************************************************************************
// *   Este programa � software livre; voc� pode redistribu�-lo e/ou         *
// *   modific�-lo sob os termos da Licen�a P�blica Geral GNU, conforme      *
// *   publicada pela Free Software Foundation; tanto a vers�o 2 da          *
// *   Licen�a como (a seu crit�rio) qualquer vers�o mais nova.              *
// ***************************************************************************
// *   This program is free software; you can redistribute it and/or modify  *
// *   it under the terms of the GNU General Public License as published by  *
// *   the Free Software Foundation; either version 2 of the License, or     *
// *   (at your option) any later version.                                   *
// *                                                                         *
// *   You should have received a copy of the GNU General Public License     *
// *   along with this program; if not, write to the                         *
// *   Free Software Foundation, Inc.,                                       *
// *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
// ***************************************************************************/
#include "Objeto.h"

Objeto::Objeto()
{

    alturaPedra=4;
	//if (!soundSystem){
	//	soundSystem = GBF::Kernel::Sound::SoundSystem::getInstance();
	//}
}
Objeto::~Objeto()
{

    //dtor
}
void Objeto::setArea(GBF::Area area)
{
    areaTela=area;

    areaTela.top=areaTela.top+4;
    areaTela.bottom=areaTela.bottom-4;
}
GBF::Area Objeto::getAreaTela()
{
    return areaTela;
}
//GBF::Kernel::Sound::SoundSystem * Objeto::soundSystem =NULL;

GBF::Area Objeto::areaTela;

