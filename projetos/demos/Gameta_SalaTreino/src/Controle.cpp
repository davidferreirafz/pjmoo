#include "Controle.h"

Controle::Controle()
{
    nivel = 4;

    jogador = new Jogador();
    for (int i=0; i<TOTAL_CANHAO; i++){
        canhao[i]=new Canhao(276,36+((2+i)*30));


        canhao[i]->setNivel(nivel);
    }
    background     = GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("background");
    foreground = GBF::Imagem::Layer::LayerManager::getInstance()->getFrameLayer("foreground");
    cronometro.setUnidade(GBF::Kernel::Timer::TEMPO_SEGUNDO);

    writeManager = GBF::Kernel::Write::WriteManager::getInstance();
    graphicSystem = GBF::Kernel::Graphic::GraphicSystem::getInstance();


}

Controle::~Controle()
{
    delete(jogador);
    for (int i=0; i<TOTAL_CANHAO; i++){
        delete(canhao[i]);
    }
}

void Controle::iniciar()
{
    cronometro.setResetar();
    jogador->inicializar();

}

void Controle::executar(GBF::Kernel::Input::InputSystem * input)
{
        cronometro.processar();

        int tempo = cronometro.getTempo();
        int segundos = (tempo % 60);
        int minutos = (tempo / 60);

        dificuldade(minutos,segundos);

        for (int i=0; i<TOTAL_CANHAO; i++){
            if(canhao[i]->isAtivo()){
                canhao[i]->acao();
            }
        }
        jogador->acao(input);


        for (int i=0; i<TOTAL_CANHAO; i++){
            if ((canhao[i]->isBala())&&(jogador->colidiu(canhao[i]->getAreaColisao()))){
                jogador->setBateu();
                canhao[i]->desativarBala();
                break;
            }
        }

        background->desenhar();

        for (int i=0; i<TOTAL_CANHAO; i++){
            canhao[i]->desenhar();
        }

        jogador->desenhar();

        foreground->desenhar();





        writeManager->escrever("default",200,0,"TEMPO: %02d:%02d",minutos,segundos);
        int barra =  10 * jogador->getVida();
        graphicSystem->gfx->setColor(255,255,0);
        graphicSystem->gfx->retanguloPreenchido(16,5,barra,7);
        writeManager->escrever("default",20,0,"LIFE: %02d",jogador->getVida());
}

void Controle::dificuldade(int minutos, int segundos)
{
    if (segundos==0){

        switch(minutos){
            case  0: ativarCanhao( true, false, false, false); break;
            case  1: ativarCanhao(false,  true, false, false); break;
            case  2: ativarCanhao(false, false,  true, false); break;
            case  3: ativarCanhao( true, false, false,  true); break;
            case  4: ativarCanhao(false, false,  true,  true); break;
            case  5: ativarCanhao( true,  true, false, false); break;
            case  8: ativarCanhao(false,  true,  true, false); break;
            case  9: ativarCanhao( true,  true,  true, false); break;
            case 10: ativarCanhao( true, false,  true, false); break;
            case 12: ativarCanhao( true, false,  true,  true); break;
        }

    }
}

void Controle::ativarCanhao(bool um, bool dois, bool tres, bool quatro)
{
    canhao[3]->setAtivar(um);
    canhao[2]->setAtivar(dois);
    canhao[1]->setAtivar(tres);
    canhao[0]->setAtivar(quatro);
}

bool Controle::isGameOver()
{
    if (!jogador->isAtivo()){
        return true;
    } else {
        return false;
    }
}
