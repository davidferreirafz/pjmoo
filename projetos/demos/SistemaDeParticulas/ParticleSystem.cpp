#include "ParticleSystem.h"

GraphicSystem* ParticleSystem::graphicSystem=NULL;

ParticleSystem::ParticleSystem()
{
    if (graphicSystem==NULL){
        graphicSystem = GraphicSystem::getInstance();
    }
    ambienteVento     = 0;
    ambienteGravidade = 0;        
    quantidade        = 500;
}
ParticleSystem::~ParticleSystem()
{
}
void ParticleSystem::inicializar()
{
    for (int i=0; i<quantidade; i++){
        particulas[i].posicao.x    = 0;
        particulas[i].posicao.y    = 0;
        particulas[i].velocidade.x = 0;
        particulas[i].velocidade.y = 0;
        particulas[i].energia      = 0;  
        particulas[i].ativa        = false;
        particulas[i].r            = 0;
        particulas[i].g            = 0;
        particulas[i].b            = 0;
    }    
}
void ParticleSystem::desenhar()
{
    graphicSystem->gsScreen->travar();
    for (int i=0; i<quantidade; i++){
        if (particulas[i].ativa){
            graphicSystem->gsGFX->setColor(particulas[i].r,particulas[i].g,particulas[i].b);
            graphicSystem->gsGFX->putPixel(int(particulas[i].posicao.x),int(particulas[i].posicao.y));
        }
    }
    graphicSystem->gsScreen->destravar(); 
}
bool ParticleSystem::isTerminou()
{
    for (int i=0; i<quantidade; i++){
        if (particulas[i].ativa){
            return false;
        }
    }
    return true;
}
void ParticleSystem::setPosicao(int x, int y)
{
    posicao.x=x;
    posicao.y=y;
}

