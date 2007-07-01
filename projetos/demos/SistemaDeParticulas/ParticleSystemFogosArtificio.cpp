#include "ParticleSystemFogosArtificio.h" // class's header file


ParticleSystemFogosArtificio::ParticleSystemFogosArtificio()
{
}
ParticleSystemFogosArtificio::~ParticleSystemFogosArtificio()
{
}
void ParticleSystemFogosArtificio::criar()
{
    float angulo, velocidade;
    int cor = rand()%3;
    
    for (int i=0; i<quantidade; i++){
        velocidade = ((float)(rand()%9000)/1000);
        angulo     = ((float)(rand()%6280)/1000);        
        particulas[i].posicao.x    = posicao.x;
        particulas[i].posicao.y    = posicao.y;
        particulas[i].velocidade.x = velocidade * cos(angulo);
        particulas[i].velocidade.y = velocidade * sin(angulo);
        particulas[i].energia      = 10 + rand()%10;  
        particulas[i].ativa        = true;
        
        switch(cor){
            case 0:
                particulas[i].r = rand()%255;
                particulas[i].g = 0;
                particulas[i].b = 0;
                break;
            case 1:
                particulas[i].r = 0;
                particulas[i].g = rand()%255;
                particulas[i].b = 0;               
                break;
            case 2:
                particulas[i].r = 0;
                particulas[i].g = 0;
                particulas[i].b = rand()%255;             
                break;                                
        }
    }   
}
void ParticleSystemFogosArtificio::atualizar()
{
    for (int i=0; i<quantidade; i++){
        if (particulas[i].ativa){
            particulas[i].posicao.x     += particulas[i].velocidade.x;
            particulas[i].posicao.y     += particulas[i].velocidade.y;
            particulas[i].velocidade.x  += ambienteVento;
            particulas[i].velocidade.y  += ambienteGravidade;
            particulas[i].energia--;

            particulas[i].r-=10;
            particulas[i].g-=10;
            particulas[i].b-=10;                        

            
            if (particulas[i].energia<0){
                particulas[i].ativa = false;
                particulas[i].energia = 0;
            }          
            
            if (particulas[i].r<=0){ particulas[i].r=0; }
            if (particulas[i].g<=0){ particulas[i].g=0; }
            if (particulas[i].b<=0){ particulas[i].b=0; }
        }          
        
        if ((particulas[i].posicao.x<0)||(particulas[i].posicao.x>640)||
            (particulas[i].posicao.y<0)||(particulas[i].posicao.y>480)){
                particulas[i].ativa = false;
        }
    }
}

