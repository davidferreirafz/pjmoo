/*****************************************************************/
/* Declaração - Includes                                         */
/*****************************************************************/
#include <math.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GBF/GBF.h>
#include "SystemColor.h"

#define NUMERO 1000

float ambienteVento     = 0;
float ambienteGravidade = 0;

struct Particula
{
    PontoVirtual posicao;
    PontoVirtual velocidade;
    PontoVirtual posicaoAntiga;
    int energia;
    bool ativa;
	HSV cor;
};

Particula sistema[NUMERO];

HSV corAmbiente;

void criarExplosao(int origemX, int origemY)
{
    float angulo, velocidade;
    int cor = rand()%3;
    
    for (int i=0; i<NUMERO; i++){
        velocidade = ((float)(rand()%9000)/1000);
        angulo     = ((float)(rand()%6280)/1000);        
        sistema[i].posicao.x    = origemX;
        sistema[i].posicao.y    = origemY;
        sistema[i].velocidade.x = velocidade * cos(angulo);
        sistema[i].velocidade.y = velocidade * sin(angulo);
        sistema[i].energia      = 10 + rand()%10;  
        sistema[i].ativa        = true;

        sistema[i].cor.h=120; //cor
        sistema[i].cor.s=1.0; //brilho
	    sistema[i].cor.v=1.0; //escuro

    }   
}
void atualizarExplosao()
{
    for (int i=0; i<NUMERO; i++){
        if (sistema[i].ativa){
            sistema[i].posicao.x  += sistema[i].velocidade.x;
            sistema[i].posicao.y  += sistema[i].velocidade.y;
            sistema[i].velocidade.x  += ambienteVento;
            sistema[i].velocidade.y  += ambienteGravidade;
            sistema[i].energia--;
            
            if (sistema[i].energia<0){
                sistema[i].ativa = false;
                sistema[i].energia = 0;
            } else {
				sistema[i].cor.h=corAmbiente.h;
				sistema[i].cor.s=corAmbiente.s;
				sistema[i].cor.v=corAmbiente.v;							
			}         
        }          
        
        if ((sistema[i].posicao.x<0)||(sistema[i].posicao.x>640)||
            (sistema[i].posicao.y<0)||(sistema[i].posicao.y>480)){
                sistema[i].ativa = false;
        }
    }
}

void desenharExplosao()
{
    static GraphicSystem* graphicSystem = GraphicSystem::getInstance();    

    graphicSystem->gsScreen->travar();
    for (int i=0; i<NUMERO; i++){
        if (sistema[i].ativa){
			RGB tcor = SystemColor::forRGB(sistema[i].cor);
            graphicSystem->gsGFX->setColor(tcor.r,tcor.g,tcor.b);			
            graphicSystem->gsGFX->putPixel(int(sistema[i].posicao.x),int(sistema[i].posicao.y));
        }
    }
    graphicSystem->gsScreen->destravar();    
}

bool isTerminouEfeito()
{
    for (int i=0; i<NUMERO; i++){
        if (sistema[i].ativa){
            return false;
        }
    }
    return true;
}


//////////////////////////////////////////////
// Entry point
int main(int argc, char *argv[])
{
	GBF *frameworkGBF = new GBF();   
	
    frameworkGBF->setPath(argv[0]);
    frameworkGBF->setTitulo("GBF :: Particula - Fogos de Artificio","David de Almeida Ferreira");
    frameworkGBF->iniciar(640,480,16,false);
    frameworkGBF->inputSystem->setControleExclusivo(SDL_GRAB_OFF);
    
	corAmbiente.h=0;
	corAmbiente.s=1.0;
	corAmbiente.v=1.0;
	
	while(true) {

		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_ESCAPE)){
			break;
		}
		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_LEFT)){
			ambienteVento-=0.1;
        }
		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_RIGHT)){
			ambienteVento+=0.1;
		}		        
		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_UP)){
			ambienteGravidade-=0.1;
        }
		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_DOWN)){
			ambienteGravidade+=0.1;
		}		        		

		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_h)){
			corAmbiente.h++;
			if (corAmbiente.h>360){
				corAmbiente.h=0;
			}
		}
		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_s)){
			corAmbiente.s+=0.1;
			if (corAmbiente.s>1.0){
				corAmbiente.s=0.0;
			}
		}
		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_v)){
			corAmbiente.v+=0.1;
			if (corAmbiente.v>1.0){
				corAmbiente.v=0.0;
			}
		}				

		//if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_p))&&(isTerminouEfeito())){
        if (isTerminouEfeito()){            
			criarExplosao(300,300);
		}		

        desenharExplosao();
        atualizarExplosao();        
		frameworkGBF->atualizar();
		frameworkGBF->graphicSystem->clear();
		
		
	}
	
    if (frameworkGBF){
        delete(frameworkGBF);
    }   
    	
	return 0;  
}
