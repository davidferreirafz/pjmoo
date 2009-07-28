/***************************************************************************
 *   Copyright (C) 2005-2006 by David Ferreira                             *
 *   davidferreira@uol.com.br - davidferreira.fz@gmail.com                 *
 *   http://pjmoo.codigolivre.org.br                                       *
 *       http://davidferreira.fz.googlepages.com                           *
 *                                                                         *
 *   Este programa é um software livre; você pode redistribui-lo e/ou      *
 *   modifica-lo dentro dos termos da Licença Pública Geral (GPL) GNU      *
 *   como publicada pela Fundação do Software Livre (FSF); na versão 2 da  *
 *   Licença.                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "NaveBorg.h"

NaveBorg::NaveBorg()
{
    GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("personagem_borg");
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,0,136,123,7,2));
    delete (spriteFactory);

    getSpritePrincipal()->setQtdDirecoes(1);

    GBF::Dimensao dimensao = getDimensao();
    setPosicao((area.right / 2)-(dimensao.w/2),area.top);
    caminho(GBF::Imagem::Sprite::DR_DIREITA);

    espera.tiroA=40;
    espera.tiroB=10;

    sistema.arma.phaser   = 1000;
    sistema.arma.plasma   = 0;
    sistema.arma.torpedo  = 1000;
    sistema.escudo.atual  = 1000;
    sistema.escudo.maximo = 1000;
    sistema.velocidade.eMaxima = VELOCIDADE_DOBRA_07;
    sistema.velocidade.eAtual  = VELOCIDADE_DOBRA_04;

    gsGFX = GBF::Kernel::Graphic::GraphicSystem::getInstance()->gfx;
    //explosao->setRaio(500);
   	//explosao->setQuantidade(1000);

    setRecarregarPhaser(10);
    setRecarregarTorpedo(8);
}
NaveBorg::~NaveBorg()
{
    //desalocação na classe base
    //UtilLog::getInstance()->status("[NaveMiniBorg]");
}
void NaveBorg::acao(GBF::Kernel::Input::InputSystem* input)
{
    if (isAtivo()){
    	checarArma();
        if (isVivo()){
            if (path->mover(sistema.velocidade.eAtual,&posicao,getDimensao())){
                GBF::Imagem::Sprite::Direcao direcaoTemporaria = direcao;
                do {
                    direcaoTemporaria = GBF::Imagem::Sprite::Direcao(rand()%8);
                } while (direcaoTemporaria==direcao);
                caminho(direcaoTemporaria);
            } else {
                prepararPhaser();
                prepararTorpedo();
            }
        } else {
            setAtivo(false);
        }
    }
}
void NaveBorg::desenhar()
{
    NaveInimigo::desenhar();
    int barra = int((474*sistema.escudo.atual)/sistema.escudo.maximo);
//setAlpha(100);
    if (barra<50){
        gsGFX->setColor(255,44,0);
    } else {
        gsGFX->setColor(67,231,67);
    }
    gsGFX->retanguloPreenchido(2,4,barra,10);
    gsGFX->setColor(255,178,0);
    gsGFX->retangulo(2,4,476,10);
//setAlpha(255);
}
void NaveBorg::choque(int forca)
{
    sistema.escudo.atual-=forca;
    soundSystem->fxManager->playPanEffect("explosao",posicao.x);

    if (sistema.escudo.atual<0){
        setVivo(false);
    }
}
void NaveBorg::dispararTorpedo()
{
    if (sistema.arma.torpedo>0){
        GBF::Dimensao dimensao=getDimensao();
        if ((posicao.y<area.bottom-dimensao.h)){
                sistema.arma.torpedo--;
                int x_r=0,y_r=0;
                switch(rand()%5){
                    case 0: x_r = 20; y_r = 20; break;
                    case 1: x_r =120; y_r = 50; break;
                    case 2: x_r = 40; y_r = 90; break;
                    case 3: x_r = 90; y_r =110; break;
                    case 4: x_r = 80; y_r = 60; break;
                }
                listTiro->adicionar(new TiroCanhaoBorg(posicao.x+x_r,posicao.y+y_r));
                listTiro->adicionar(new TiroPhaserBorg(posicao.x+x_r,posicao.y+y_r,TiroPhaserBorg::LEFT));
                listTiro->adicionar(new TiroPhaserBorg(posicao.x+x_r,posicao.y+y_r,TiroPhaserBorg::RIGHT));
                //Efeito Sonoro
                soundSystem->fxManager->playPanEffect("tiro",posicao.x);
        }
    }
}
void NaveBorg::setVivo(bool VALOR)
{
    if (VALOR==false){
        sistema.escudo.atual--;
        if (sistema.escudo.atual<0){
            //toca som de explosao
            soundSystem->fxManager->playPanEffect("explosao",posicao.x);

            //cria particulas da explosao da nave
            GBF::Dimensao dimensaoSprite = getDimensao();
            GBF::Ponto pontoExplosao;

            pontoExplosao.x = posicao.x + (dimensaoSprite.w/2);
            pontoExplosao.y = posicao.y + (dimensaoSprite.h/2);

            ParticleSystem::PSEfeitoEsferico* explosao = new EfeitoExplosao();
            explosao->setRaio(640);
            explosao->setQuantidade(int(int(dimensaoSprite.w*dimensaoSprite.h)/2));
            explosao->criar(pontoExplosao.x,pontoExplosao.y);

            particleManager->adicionar(explosao);
        } else {
            VALOR=true;
        }
    }
    Personagem::setVivo(VALOR);
}
void NaveBorg::dispararPhaser()
{
    if (sistema.arma.phaser>0){
        int x=0,y=0;

        switch(rand()%3){
            case 0: x=30;  y=80;
                break;
            case 1: x=110; y=60;
                break;
            case 2: x=80;  y=80;
                break;
        }
        //Este metodo no lugar do phaser lança uma nave miniborg
        GBF::Dimensao dimensao = getDimensao();
        if (((posicao.x>=0)&&(posicao.x<area.right-dimensao.w)) &&
            (posicao.y<area.bottom-dimensao.h)){
                NaveMiniBorg* mini = new NaveMiniBorg();
                mini->posicionar(posicao.x+x,posicao.y+y, GBF::Imagem::Sprite::DR_BAIXO);

                ListSpaceInimigo::getInstance()->adicionar(mini);
                sistema.arma.phaser--;
        }
    }
}
