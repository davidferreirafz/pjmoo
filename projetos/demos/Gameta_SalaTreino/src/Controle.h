#ifndef CONTROLE_H
#define CONTROLE_H

#include <GBF/InputSystem.h>
#include <GBF/TimerProgressive.h>
#include <GBF/WriteManager.h>
#include <GBF/GraphicSystem.h>
#include "Jogador.h"
#include "Canhao.h"

#define TOTAL_CANHAO 4

class Controle
{
    public:
        Controle();
        virtual ~Controle();
        void iniciar();
        void executar(GBF::Kernel::Input::InputSystem * input);
        bool isGameOver();

    protected:

    private:
        void dificuldade(int tempo);
        void ativarCanhao(bool um, bool dois, bool tres, bool quatro);
        Jogador * jogador;
        GBF::Image::Layer::FrameLayer * background;
        GBF::Image::Layer::FrameLayer * foreground;
        Canhao * canhao[TOTAL_CANHAO];
        GBF::Kernel::Timer::TimerProgressive cronometro;
        GBF::Kernel::Write::WriteManager * writeManager;
        GBF::Kernel::Graphic::GraphicSystem * graphicSystem;
        int level;
};

#endif // CONTROLE_H
