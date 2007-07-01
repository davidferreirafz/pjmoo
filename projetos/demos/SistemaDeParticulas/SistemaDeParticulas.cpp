/*****************************************************************/
/* Declaração - Includes                                         */
/*****************************************************************/
#include <math.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GBF/GBF.h>


#include "Efeito.h"
#include "Explosao.h"
#include "FogosDeArtificio.h"

/*
  Tecle E -> Para Acionar o efeito de Explosão
  Tecle F -> Para Acionar o efeito de Fogos de Artificio
*/


//////////////////////////////////////////////
// Entry point
int main(int argc, char *argv[])
{
	GBF *frameworkGBF = new GBF();   
    frameworkGBF->setPath(argv[0]);
    frameworkGBF->setTitulo("GBF :: Sistema de Particulas","David de Almeida Ferreira");
    frameworkGBF->iniciar(640,480,16,false);
    frameworkGBF->inputSystem->setControleExclusivo(SDL_GRAB_OFF);
    
	Efeito *efeito = new Explosao();
	Efeito *efeito2 = new FogosDeArtificio();
        
    efeito->setQuantidade(200);
    efeito2->setQuantidade(150);
            
	while(true) {

		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_ESCAPE)){
			break;
		}
		if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_e))&&(efeito->isTerminou())){
            efeito->criar(300,300);
        }
		if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_f))&&(efeito2->isTerminou())){
            efeito2->criar(rand()%640,rand()%480);
        }
        efeito->desenhar();
        efeito2->desenhar();
        efeito->atualizar();        
        efeito2->atualizar();
		frameworkGBF->atualizar();
		frameworkGBF->graphicSystem->clear();
	}
	

    if (efeito){
        delete(efeito);
    }
    if (efeito2){
        delete(efeito2);
    }
    
    if (frameworkGBF){
        delete(frameworkGBF);
    }   
    	
	return 0;  
}
