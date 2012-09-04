#include "Controle.h"

Controle::Controle()
{
    level = 1;
    cronometro.setUnit(GBF::Kernel::Timer::TIME_SECOND_ONE);

    jogador = new Jogador();

    for (int i = 0; i < TOTAL_CANHAO; i++){
        canhao[i] = new Canhao(276, 36 + ((2 + i)*30));
        canhao[i]->setNivel(level);
    }

    background = GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("background");
    foreground = GBF::Image::Layer::LayerManager::getInstance()->getFrameLayer("foreground");

    writeManager  = GBF::Kernel::Write::WriteManager::getInstance();
    graphicSystem = GBF::Kernel::Graphic::GraphicSystem::getInstance();
}

Controle::~Controle()
{
    delete(jogador);

    for (int i = 0; i < TOTAL_CANHAO; i++){
        delete(canhao[i]);
    }
}

void Controle::iniciar()
{
    cronometro.setReset();
    jogador->inicializar();
}

void Controle::executar(GBF::Kernel::Input::InputSystem * input)
{
    cronometro.update();

    int tempo = cronometro.getTime();
    int segundos = (tempo % 60);
    int minutos = (tempo / 60);

    dificuldade(tempo);

    for (int i = 0; i < TOTAL_CANHAO; i++){
        if (canhao[i]->isAtivo()){
            canhao[i]->update();
        }
    }
    jogador->update(input);


    for (int i = 0; i < TOTAL_CANHAO; i++){
        if ((canhao[i]->isBala()) && (jogador->colidiu(canhao[i]->getAreaColisao()))){
            jogador->setBateu();
            canhao[i]->desativarBala();
            break;
        }
    }

    background->draw();

    for (int i = 0; i < TOTAL_CANHAO; i++){
        canhao[i]->draw();
    }

    jogador->draw();
    foreground->draw();


    writeManager->write("default", 130, 0, "TEMPO %02d:%02d  LEVEL %02d", minutos, segundos, level);
    int barra =  10 * jogador->getVida();
    graphicSystem->gfx->setColor(255, 255, 0);
    graphicSystem->gfx->rectangleFill(16, 5, barra, 7);

#ifdef DEBUG
    writeManager->write("default", 0, 12, "LIFE: %02d", jogador->getVida());
#endif
}

void Controle::dificuldade(int tempo)
{
    if (tempo < 20){
        ativarCanhao(true, false, false, false);
        level = 1;
    } else if (tempo < 30){
        ativarCanhao(false, true, false, false);
        level = 2;
    } else if (tempo < 50){
        ativarCanhao(false, false, true, false);
        level = 3;
    } else if (tempo < 70){
        ativarCanhao(false, false, false, true);
        level = 4;
    } else if (tempo < 90){
        ativarCanhao(false, false, true, true);
        level = 5;
    } else if (tempo < 120){
        ativarCanhao(true, true, false, false);
        level = 6;
    } else if (tempo < 150){
        ativarCanhao(false, true, true, false);
        level = 7;
    } else if (tempo < 180){
        ativarCanhao(true, true, true, false);
        level = 8;
    } else if (tempo < 200){
        ativarCanhao(true, false, true, false);
        level = 9;
    } else if (tempo < 240){
        ativarCanhao(true, false, true, true);
        level = 10;
    } else {
        ativarCanhao(true, true , true , true);
        level = 100;
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
    if (!jogador->isActive()){
        return true;
    } else {
        return false;
    }
}
