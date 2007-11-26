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
#ifndef _ENCHANTEDMAZEFACTORY_H
#define _ENCHANTEDMAZEFACTORY_H

#include "MazeFactory.h"
#include "EnchantedRoom.h"
#include "EnchantedDoor.h"
#include "Room.h"
#include "Door.h"

class EnchantedMazeFactory : public MazeFactory
{
  public:
    EnchantedMazeFactory();

    virtual ~EnchantedMazeFactory();

    Room * makeRoom(int number);

    Door * makeDoor(Room * room1, Room * room2);

};
#endif
