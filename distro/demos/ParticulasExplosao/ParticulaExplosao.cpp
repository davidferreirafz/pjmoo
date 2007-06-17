/*****************************************************************/
/* Declaração - Includes                                         */
/*****************************************************************/
#include <math.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GBF/GBF.h>
#include "SystemColor.h"

#define NUMERO 200

int raioAlcance = 50;
int raioOrigemX = 0;
int raioOrigemY = 0;

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


void criarEfeito(int origemX, int origemY)
{
    float angulo, velocidade;

    raioOrigemX=origemX;
    raioOrigemY=origemY;

    for (int i=0; i<NUMERO; i++){
        velocidade = ((float)(rand()%9000)/1000);
        angulo     = ((float)(rand()%6280)/1000);        
        sistema[i].posicao.x    = raioOrigemX;
        sistema[i].posicao.y    = raioOrigemY;
        sistema[i].velocidade.x = velocidade * cos(angulo);
        sistema[i].velocidade.y = velocidade * sin(angulo);
        sistema[i].energia      = rand()%(raioAlcance*2);  
        sistema[i].ativa        = true;
        sistema[i].cor.h = 60;
        sistema[i].cor.s = 1.0;
        sistema[i].cor.v = 1.0;
    }   
}
void atualizarEfeito()
{
    float qx, qy, qr;
    qr = std::pow(float(raioAlcance), 2); //quadrado da soma dos raios    

    for (int i=0; i<NUMERO; i++){
        if (sistema[i].ativa){
            sistema[i].posicao.x  += sistema[i].velocidade.x;
            sistema[i].posicao.y  += sistema[i].velocidade.y;
            sistema[i].energia--;

            qx = std::pow(float(raioOrigemX-sistema[i].posicao.x), 2); //quadrado da distância em x
            qy = std::pow(float(raioOrigemY-sistema[i].posicao.y), 2); //quadrado da distância em y

            if ((sistema[i].energia<0)||(qx + qy >= qr)){
                sistema[i].ativa = false;
            } else {
                sistema[i].cor.h -=5;
	            if (sistema[i].cor.h<0){
					sistema[i].cor.h=0;
					sistema[i].cor.v-=0.01;
					if (sistema[i].cor.v<0){
						sistema[i].cor.v=0;
					}
				}
            }
        }
    }
}
void desenharEfeito()
{
    static GraphicSystem* graphicSystem = GraphicSystem::getInstance();    

    graphicSystem->gsGFX->setColor(255,255,255);
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
    frameworkGBF->setTitulo("GBF :: Particula Explosao","David de Almeida Ferreira");
    frameworkGBF->iniciar(640,480,16,false);
    frameworkGBF->inputSystem->setControleExclusivo(SDL_GRAB_OFF);
    
	while(true) {
		if (frameworkGBF->inputSystem->teclado->isKey(SDLK_ESCAPE)){
			break;
		}       

		if ((frameworkGBF->inputSystem->teclado->isKey(SDLK_p))&&(isTerminouEfeito())){
			criarEfeito(320,240);
		}		

        desenharEfeito();
        atualizarEfeito();        
		frameworkGBF->atualizar();
		frameworkGBF->graphicSystem->clear();
	}
	
    if (frameworkGBF){
        delete(frameworkGBF);
    }   
    	
	return 0;  
}
