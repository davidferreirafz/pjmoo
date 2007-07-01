#include "Efeito.h"


GraphicSystem* Efeito::graphicSystem = NULL;
Efeito::Efeito()
{
    if (graphicSystem==NULL){
        graphicSystem = GraphicSystem::getInstance();         
    }   
}

void Efeito::setQuantidade(int quantidade)
{
    for (int i=0; i<quantidade; i++){
        Particula particula;
       
        particula.posicao.x    = 0;
        particula.posicao.y    = 0;
        particula.velocidade.x = 0;
        particula.velocidade.y = 0;
        particula.energia      = 0;  
        particula.ativa        = false;
        particula.cor.h = 0;
        particula.cor.s = 0.0;
        particula.cor.v = 0.0;

        lista.push_back(particula);
    }
}
void Efeito::desenhar()
{
    if (!lista.empty()){
        graphicSystem->gsGFX->setColor(255,255,255);
        graphicSystem->gsScreen->travar();
        for (int i=0; i<lista.size(); i++){
            if (lista[i].ativa){
    			RGB tcor = SystemColor::forRGB(lista[i].cor);
                graphicSystem->gsGFX->setColor(tcor.r,tcor.g,tcor.b);
                graphicSystem->gsGFX->putPixel(int(lista[i].posicao.x),int(lista[i].posicao.y));
            }
        }
        graphicSystem->gsScreen->destravar();     
    }
}
bool Efeito::isTerminou()
{
    if (!lista.empty()){
        for (int i=0; i<lista.size();i++){
            if (lista[i].ativa){
                return false;
            }
        }
    }
    return true;
}

