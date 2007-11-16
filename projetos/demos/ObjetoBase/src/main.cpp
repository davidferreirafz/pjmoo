////***************************************************************************
////  ObjetoBase <Demo de Recursos>
////  Copyright (C) 2007 by David Ferreira - FZ
////  davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net
////***************************************************************************
////    Este programa é software livre; você pode redistribuí-lo e/ou
////    modificá-lo sob os termos da Licença Pública Geral GNU, conforme
////    publicada pela Free Software Foundation; tanto a versão 2 da
////    Licença como (a seu critério) qualquer versão mais nova.
////***************************************************************************
////    This program is free software; you can redistribute it and/or modify
////    it under the terms of the GNU General Public License as published by
////    the Free Software Foundation; either version 2 of the License, or
////    (at your option) any later version.
////
////    You should have received a copy of the GNU General Public License
////    along with this program; if not, write to the
////    Free Software Foundation, Inc.,
////    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
////***************************************************************************
#include "main.h"

int main(int argc, char * argv[])
{
      Sprite sprite;
      SpriteManager * spriteManager = new SpriteManager();
      SpritePersonagem * spritePersonagem = new SpritePersonagem();
      Sprite * spritePersonagem2 = new SpritePersonagem();

      if (sprite.isInstance<Sprite>()){
          std::cout << "sprite eh Sprite" << std::endl;
      }

      if (spritePersonagem->isInstance(SpritePersonagem())){
          std::cout << "spritePersonagem eh SpritePersonagem" << std::endl;
      }

      if (spritePersonagem2->isInstance(Sprite())){
          std::cout << "spritePersonagem2 eh Sprite" << std::endl;
      }

      if (spritePersonagem2->isInstance(new SpritePersonagem())){
          std::cout << "spritePersonagem2 eh SpritePersonagem" << std::endl;
      }

      if (spriteManager->isInstance(ObjetoManager())){
          std::cout << "spriteManager eh ObjetoManager" << std::endl;
      }

      if (!sprite.isInstance<SpritePersonagem>()){
          std::cout << "sprite NAO eh SpritePersonagem" << std::endl;
      }

      if (!spriteManager->isInstance(Sprite())){
          std::cout << "spriteManager NAO eh Sprite" << std::endl;
      }

      if (spriteManager->isInstance(ObjetoBase())){
          std::cout << "spriteManager eh ObjetoBase" << std::endl;
      }

    return 0;

}

