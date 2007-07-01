/***************************************************************************
 *   Copyright (C) 2006 by David Ferreira                                  *
 *   davidferreira@uol.com.br - http://pjmoo.codigolivre.org.br            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/*****************************************************************/
/* Declaração - Includes                                         */
/*****************************************************************/
#include <GBF/GBF.h>
#include <GBF/GraphicSystemImageBufferManager.h>
#include <GBF/SpriteFactory.h>
#include <vector>
#include <iostream>


int main(int argc, char* argv[])
{

	GBF *frameworkGBF = new GBF();

    frameworkGBF->setPath(argv[0]);
    frameworkGBF->setTitulo("GBF::Teste Scrolling","David Ferreira");
    frameworkGBF->iniciar(640,480,32,false);
    frameworkGBF->inputSystem->setControleExclusivo(SDL_GRAB_OFF);


//carregando imagens
    GraphicSystemImageBufferManager *GSIBManager = GraphicSystemImageBufferManager::getInstance();
    GSIBManager->carregar("tiles","//data//imagem//tilemap_01.png");

    SpriteFactory * spriteFactory = new SpriteFactory(GSIBManager->getImageBuffer("tiles"));

    FrameLayer *tiles = spriteFactory->criarFrameLayer(0,0,32,32);

    delete (spriteFactory);

    tiles->setFrame(0,0,640,480);
    tiles->setTiles(20,30);
    tiles->setPixelTile(32,32);
    tiles->iniciarOrdenado(4);
    tiles->camera.setBottom();
    Ponto ponto;

    bool descer = tiles->camera.isTop();

	while(true) {
		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_ESCAPE)){
			break;
		}

		//desenha a tela de fundo
		tiles->desenhar();
        tiles->camera.show();

        if (descer){
			tiles->camera.runDown(1);
			if (tiles->camera.isBottom()){
			    descer=false;
            }
        } else {
			tiles->camera.runUp(1);
			if (tiles->camera.isTop()){
			    descer=true;
            }
        }
        ponto=tiles->camera.getPosicao();

		frameworkGBF->writeSystem->escrever(WriteSystemFontDefault::pumpdemi,0,0,"x:%d y:%d",ponto.x,ponto.y);

		//realiza refresh, fps, flip
		frameworkGBF->atualizar();
	}
    if (frameworkGBF){
        delete(tiles);
        delete(frameworkGBF);
    }
	return 0;
}

