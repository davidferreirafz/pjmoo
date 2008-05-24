///***************************************************************************
// *   FZPong <Game - Pong Clone>                                            *
// *   Copyright (C) 2007 by David Ferreira - FZ                             *
// *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
// ***************************************************************************
// *   Este programa � software livre; voc� pode redistribu�-lo e/ou         *
// *   modific�-lo sob os termos da Licen�a P�blica Geral GNU, conforme      *
// *   publicada pela Free Software Foundation; tanto a vers�o 2 da          *
// *   Licen�a como (a seu crit�rio) qualquer vers�o mais nova.              *
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
#include "CPU.h"

CPU::CPU()
{
    GBF::Imagem::SpriteFactory *spriteFactory = new GBF::Imagem::SpriteFactory("personagem");

    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(15,21,14,80,1,1));
    delete(spriteFactory);

    iniciarVisao();
}
CPU::~CPU()
{

    //dtor
}
void CPU::acao(GBF::Kernel::Input::InputSystem * input)
{
    GBF::Area areaVisaoBola = Util::converterArea(getVisaoBola().getDimensao(),getVisaoBola().getPosicao());
    GBF::Area visao         = Util::converterArea(getDimensao(),getPosicao());

    switch(pensar(visao,areaVisaoBola))
    {
        case DECISAO_SUBIR:
                subir();
            break;
        case DECISAO_DESCER:
                descer();
            break;
        case DECISAO_NADA:
        default:
                //nada para fazer
            break;
    }
}
GBF::Ponto CPU::saque()
{
    GBF::Ponto saque;

    saque.x=posicao.x+getDimensao().w;
    saque.y=posicao.y+rand()%(getDimensao().h-getVisaoBola().getDimensao().h);

    return saque;
}
bool CPU::isColisao(Personagem::Personagem * personagem)
{
    bool retorno = Raquete::isColisao(personagem);

    if (retorno){
        efeito = Efeito(rand()%3);
    }

    return retorno;
}
//Inicia raquete
void CPU::iniciar()
{
    Raquete::iniciar();
    aumentarVisao();
}
//Desenha o sprite principal do personagem
void CPU::desenhar()
{
    Raquete::desenhar();

#ifdef DEBUG
    GBF::Kernel::Graphic::GFX *gfx = GBF::Kernel::Graphic::GraphicSystem::getInstance()->gfx;

    gfx->setColor(255,255,255);
    gfx->circulo(posicao.x+getDimensao().w/2,posicao.y+getDimensao().h/2,raioVisao);

    gfx->setColor(255,0,0);
    gfx->circulo(posicao.x+getDimensao().w/2,posicao.y+getDimensao().h/2,int(getDimensao().h*1.4));
#endif
}
void CPU::iniciarVisao()
{
    raioVisao=340;
}
void CPU::aumentarVisao()
{
    raioVisao+=40;

    if (raioVisao>=getAreaTela().bottom){
        raioVisao=getAreaTela().bottom;
    }
}
Decisao CPU::pensar(GBF::Area visao, GBF::Area areaVisaoBola)
{
    float qx, qy, qr, qe; //para guardar o quadrado de x, y e raio
    Decisao decisao = DECISAO_NADA;

    //quadrado da dist�ncia em x
    qx = std::pow(float((areaVisaoBola.left + areaVisaoBola.right/2) - (visao.left + visao.right/2)), 2);
    //quadrado da dist�ncia em y
    qy = std::pow(float((areaVisaoBola.top + areaVisaoBola.bottom/2) - (visao.top  + visao.bottom/2)), 2);
    //quadrado da soma dos raios
    qr = std::pow(float(raioVisao), 2);
    //quadrado da soma dos raios para efeito
    qe = std::pow(float(visao.bottom*1.4), 2);


    if (qx + qy <= qr){
        if (qx + qy <= qe){
            switch (efeito){
                case EFEITO_CIMA:
                        if (visao.top >= areaVisaoBola.top+areaVisaoBola.bottom){
                            decisao = DECISAO_SUBIR;
                        } else if (visao.top+areaVisaoBola.bottom < areaVisaoBola.top+areaVisaoBola.bottom){
                            decisao = DECISAO_DESCER;
                        }
                    break;

                case EFEITO_BAIXO:
                        if (visao.top+visao.bottom <= areaVisaoBola.top){
                            decisao = DECISAO_DESCER;
                        } else
                        if (visao.top+visao.bottom >= areaVisaoBola.top+areaVisaoBola.bottom){
                            decisao = DECISAO_SUBIR;
                        }
                    break;

                case EFEITO_SEM:
                default:
                        if (visao.top > areaVisaoBola.top){
                            decisao = DECISAO_SUBIR;
                        } else  if (visao.top+visao.bottom < areaVisaoBola.top+areaVisaoBola.bottom){
                            decisao = DECISAO_DESCER;
                        }

                    break;
            }
        } else {
            if (visao.top > areaVisaoBola.top){
                decisao = DECISAO_SUBIR;
            } else  if (visao.top+visao.bottom < areaVisaoBola.top+areaVisaoBola.bottom){
                decisao = DECISAO_DESCER;
            }
        }
    }

    return decisao;
}
