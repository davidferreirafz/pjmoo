///***************************************************************************
// *   FZPong <Game - Pong Clone>                                            *
// *   Copyright (C) 2007 by David Ferreira - FZ                             *
// *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
// ***************************************************************************
// *   Este programa é software livre; você pode redistribuí-lo e/ou         *
// *   modificá-lo sob os termos da Licença Pública Geral GNU, conforme      *
// *   publicada pela Free Software Foundation; tanto a versão 2 da          *
// *   Licença como (a seu critério) qualquer versão mais nova.              *
// ***************************************************************************
// *   This program is free software; you can redistribute it and/or modify  *
// *   it under the terms of the GNU General Public License as published by  *
// *   the Free Software Foundation; either version 2 of the License, or     *
// *   (at your option) any later version.                                   *
// *                                                                         *
// *   You should have received a copy of the GNU General Public License     *
// *   along with this program; if not, write to the                         *
// *   Free Software Foundation, Inc.,                                       *
// *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
// ***************************************************************************/
#include "Controle.h"
#include "Jogador.h"

Controle::Controle(){

    cenario    = FrameLayerManager::getInstance()->getFrameLayer("background");
    wsManager  = WriteSystemManager::getInstance();

    raqueteJogador = new Jogador();
    raqueteCPU     = new CPU();

    raqueteJogador->setLado(LADO_DIREITO);
    raqueteCPU->setLado(LADO_ESQUERDO);
}

Controle::~Controle(){
    delete(raqueteJogador);
    delete(raqueteCPU);

}

void Controle::iniciar() 
{
    Objeto::setArea(cenario->getArea());

    bola.iniciar();
    Raquete::setBola(&bola);

    raqueteJogador->iniciar();
    raqueteCPU->iniciar();
    raqueteCPU->iniciarVisao();

    placar.iniciar();
}
void Controle::iniciarSet() 
{
    placar.novaPartida();
}
void Controle::prepararSet() 
{
    bola.continuar();
    raqueteJogador->iniciar();
    raqueteCPU->iniciar();
}
void Controle::executar(InputSystem * input) 
{
    bola.acao(NULL);
    raqueteJogador->acao(input);
    raqueteCPU->acao(NULL);

    bola.isColisao(raqueteJogador);
    bola.isColisao(raqueteCPU);

    juiz();

    display();
}
bool Controle::isGameOver() 
{
    bool terminou = false;

    if (placar.getVitoriaCPU()>=placar.getVitoriaJogador()+DIFERENCA_VITORIA_TERMINAR){
        terminou = true;
    }

    return terminou;
}
bool Controle::isFinalizado() 
{
    bool terminou = false;

    if (placar.getVitoriaJogador()>=placar.getVitoriaCPU()+DIFERENCA_VITORIA_TERMINAR){
        terminou = true;
    }

    return terminou;
}
bool Controle::isSetFinalizado() 
{
    bool finalizado = false;

    int diferenca=placar.getCPU()-placar.getJogador();

    if ((diferenca>=DIFERENCA_PARTIDA_TERMINAR)||(diferenca<=-DIFERENCA_PARTIDA_TERMINAR)){
        finalizado = true;
        placar.novaPartida();
        if (placar.getVitoriaJogador()>=placar.getVitoriaCPU()){
            raqueteCPU->aumentarVisao();
        }
    }

    return finalizado;
}
int Controle::getNumeroSet() 
{
    return placar.getVitoriaCPU()+placar.getVitoriaJogador();
}
void Controle::display() 
{
    cenario->desenhar();
    wsManager->escrever("texto",260,10,"%02d X %02d",placar.getCPU(),placar.getJogador());

    wsManager->escrever("texto" ,20,10,"%02d",placar.getVitoriaCPU());
    wsManager->escrever("texto",590,10,"%02d",placar.getVitoriaJogador());

    bola.desenhar();
    raqueteJogador->desenhar();
    raqueteCPU->desenhar();
}
//Ativar demonstração do jogo
void Controle::ativarDemo(bool ativo) 
{
    if (ativo){
        if (raqueteJogador!=NULL){
            delete(raqueteJogador);
        }
        raqueteJogador = new CPU();
        raqueteJogador->setLado(LADO_DIREITO);
    } else {
        if (raqueteJogador!=NULL){
            delete(raqueteJogador);
        }
        raqueteJogador = new Jogador();
        raqueteJogador->setLado(LADO_DIREITO);
    }
}
void Controle::juiz() 
{
    if (bola.getPosicao().x>=cenario->getArea().right){
        placar.pontuarCPU();
        raqueteCPU->iniciar();
        raqueteJogador->iniciar();

        bola.iniciar(raqueteCPU->saque());
    } else  if (bola.getPosicao().x+bola.getDimensao().w<=cenario->getArea().left){
        placar.pontuarJogador();
        raqueteJogador->iniciar();
        raqueteCPU->iniciar();

        bola.iniciar(raqueteJogador->saque());
    }
}
void Controle::setFinalizado() 
{
}
int Controle::DIFERENCA_PARTIDA_TERMINAR =5;

int Controle::DIFERENCA_VITORIA_TERMINAR =2;

