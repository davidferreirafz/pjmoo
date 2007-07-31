
#include "Controle.h"


Controle::Controle()
{
    fase = NULL;
    tempoEspera.setTempoOriginal(3);
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
        WriteSystemManager::getInstance()->escrever(WriteSystemFontDefault::pumpdemi,100,100,"%02d",tempoEspera.getTempo());
    } else if (fase->isFimRound()){
        if (fase->isProximoRound()){
            fase->iniciar();
            fase->proximoRound();
            tempoEspera.setResetar();
        }
    } else {
        fase->executar(input);
        fase->desenhar();
    }

        WriteSystemManager::getInstance()->escrever(WriteSystemFontDefault::pumpdemi,100,150,"round %02d",fase->getRound());
}

void Controle::desenhar()
{
    fase->desenhar();
}


