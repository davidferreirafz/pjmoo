/*****************************************************************/
/* Declaração - Includes                                         */
/*****************************************************************/
#include <GBF/GBFramework.h>
#include <GBF/SpriteFactory.h>
#include <vector>
#include <iostream>

#include "Inimigo.h"
#include "Jogador.h"

#define TOTAL_INIMIGO 3

/**********************************************************************/
/* AeroTarget - Cap01 - Código do Artigo Desenvolvimento de Jogos     */
/*                        com  Software Livre                         */
/**********************************************************************/
int main(int argc, char* argv[])
{
    GBF::GBFramework frameworkGBF;

    frameworkGBF.setPath(argv[0]);
    frameworkGBF.setTitle("AeroTarget - Cap 01","GBFramework & Revista Espitiro Livre");
    frameworkGBF.start(640,480,16,false,GBF::Kernel::FPS::FPS_30);
    frameworkGBF.inputSystemCore->setControleExclusivo(SDL_GRAB_OFF);

//carregando imagens
    frameworkGBF.graphicSystemCore->graphicSystem->imageBufferManager->loadFromFile("sprites","//data//imagem//sprites.png");

    Jogador * aviao = new Jogador();
    Inimigo * inimigo[TOTAL_INIMIGO];

    for (int i=0; i<TOTAL_INIMIGO; i++){
        inimigo[i] = new Inimigo();
    }


	while (true) {
		if (frameworkGBF.inputSystemCore->inputSystem->keyboard->isKey(SDLK_ESCAPE)){
			break;
		}

        for (int i=0; i<TOTAL_INIMIGO; i++){
            inimigo[i]->update(NULL);
        }

        aviao->update(frameworkGBF.inputSystemCore->inputSystem);

        for (int i=0; i<TOTAL_INIMIGO; i++){
            inimigo[i]->draw();
        }

        aviao->draw();

        frameworkGBF.writeSystem->write(GBF::Kernel::Write::WriteManager::defaultFont,10,460,"AeroTarget - Cap01 : GBFramework & Revista Espírito Livre");

		//realiza refresh, fps, flip
		frameworkGBF.update();
		frameworkGBF.graphicSystemCore->clear();
	}

    delete(aviao);
    for (int i=0; i<TOTAL_INIMIGO; i++){
        delete(inimigo[i]);
    }

	return 0;
}

