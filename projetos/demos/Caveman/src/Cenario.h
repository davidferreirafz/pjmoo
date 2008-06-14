#ifndef CENARIO_H
#define CENARIO_H

#include <GBF/FrameLayer.h>
#include <GBF/SpriteFactory.h>

#include "PersonagemAdventure.h"
#include "Colisao.h"

class Cenario
{
 public:
    Cenario();
    virtual ~Cenario();
    void executar(PersonagemAdventure * personagem);
    void desenhar();

 protected:
    GBF::Imagem::Layer::FrameLayer * layer;
    int * mapaColisao;

 private:
    void carregarColisaoMemoria(int * vetor);
};

#endif // CENARIO_H
