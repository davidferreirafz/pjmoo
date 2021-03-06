//***************************************************************************
//  UML <Demo - GoF - Designer Patterns>
//  Copyright (C) 2007 by David Ferreira - FZ
//  davidferreira.fz@gmail.com - http://pjmoo.wiki.sourceforge.net/GoF
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
#ifndef _MAPSITE_H
#define _MAPSITE_H

#include <GBF/SpriteItem.h>

#include <GBF/GraphicSystemUtility.h>

#include <GBF/ObjetoBase.h>

#include <GBF/SpriteFactory.h>


enum Direction {
  North,
  South,
  East,
  West,
  INVALID
};
class MapSite : public GraphicSystemUtility, public ObjetoBase
{
  public:
    MapSite();

    virtual ~MapSite();

    virtual void enter() = 0;

    virtual void draw(int x, int y);


  protected:
    SpriteItem * sprite;

};
#endif
