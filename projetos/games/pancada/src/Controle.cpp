
#include "Controle.h"


Controle::Controle()
{
    fase = NULL;
    tempoEspera.setTempoOriginal(4);
    tempoEspera.setUnidade(TEMPO_SEGUNDO);
    iniciar();
}
// Destrutor
Controle::~Controle()
{
    if (fase){
        delete(fase);
        fase=NULL;
    }
    delete(fight);
}

void Controle::carregar()
{
    SpriteFactory *spriteFactory = new SpriteFactory(GraphicSystemImageBufferManager::getInstance()->getImageBuffer("personagem"));
    fight = spriteFactory->criarSpriteItem(0,316,453,82,1,1);
}

bool Controle::isGameOver()
{
    if ((fase!=NULL)&&(fase->isGameOver())){
        return true;
    } else {
        return false;
    }
}

bool Controle::isFaseFinalizada()
{
  //   if ((!FaseFactory::isProximaFase(faseNumero))&&(fase->isFaseFinalizada())){
    if ((fase!=NULL)&&(fase->isFaseFinalizada())){
        return true;
    } else {
        return false;
    }
}
//inicia novo jogo
void Controle::iniciar()
{
    faseNumero=0;
}
void Controle::mudarFase()
{
    FaseAbstract* novaFase = FaseFactory::criarFase(faseNumero);
    if (novaFase!=NULL){
        if (fase){
            delete (fase);
            fase = NULL;
        }
        fase = novaFase;
        novaFase = NULL;
        fase->iniciar();
    }
}
bool Controle::carregarFase()
{
    bool maisFase = FaseFactory::isProximaFase(faseNumero);

    if (maisFase){
        faseNumero++;
        mudarFase();
    } else {
        faseNumero=8;
    }

    return maisFase;
}



void Controle::executar(InputSystem * input)
{
    if (!tempoEspera.isTerminou()){
        tempoEspera.processar();
        fase->desenhar();
        WriteSystemManager::getInstance()->escrever("menu",180,170,"ROUND %02d",fase->getRound());
        if (tempoEspera.getTempo()<=2){
            fight->desenhar(50,200);
        }
    } else if (fase->isFimRound()){
        if (fase->isProximoRound()){
            fase->iniciar();
            fase->proximoRound();
            tempoEspera.setResetar();
        }
    } else if (fase->isNocaute()){
        fase->desenhar();
        for (int i=100;i<460;i+=30){
            WriteSystemManager::getInstance()->escrever("menu",180,i,"NOCAUTE");
        }

    } else {
        fase->executar(input);
        fase->desenhar();
    }


}

void Controle::desenhar()
{
    fase->desenhar();
}


