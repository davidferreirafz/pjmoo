#include "Explosao.h"

void Explosao::criar(int x, int y)
{
    float angulo, velocidade;

    origem.x=x;
    origem.y=y;

    if (!lista.empty()){
        for (int i=0; i<lista.size(); i++){
            velocidade = ((float)(rand()%9000)/1000);
            angulo     = ((float)(rand()%6280)/1000);        
            lista[i].posicao.x    = origem.x;
            lista[i].posicao.y    = origem.y;
            lista[i].velocidade.x = velocidade * cos(angulo);
            lista[i].velocidade.y = velocidade * sin(angulo);
            lista[i].energia      = rand()%(raio*2);  
            lista[i].ativa        = true;
            lista[i].cor.h = 60;
            lista[i].cor.s = 1.0;
            lista[i].cor.v = 1.0;
        }
    }
}
void Explosao::atualizar()
{
    float qx, qy, qr;

    if (!lista.empty()){
        for (int i=0; i<lista.size(); i++){
            qr = std::pow(float(rand()%raio), 2); //quadrado da soma dos raios
            if (lista[i].ativa){
                lista[i].posicao.x  += lista[i].velocidade.x;
                lista[i].posicao.y  += lista[i].velocidade.y;
                lista[i].energia--;
    
                qx = std::pow(float(origem.x-lista[i].posicao.x), 2); //quadrado da distância em x
                qy = std::pow(float(origem.y-lista[i].posicao.y), 2); //quadrado da distância em y
    
                if ((lista[i].energia<0)||(qx + qy >= qr)){
                    lista[i].ativa = false;
                } else {
                    lista[i].cor.h -=5;
    	            if (lista[i].cor.h<0){
    					lista[i].cor.h=0;
    					lista[i].cor.v-=0.01;
    					if (lista[i].cor.v<0){
    						lista[i].cor.v=0;
    					}
    				}
                }
            }
        }
    }
}


