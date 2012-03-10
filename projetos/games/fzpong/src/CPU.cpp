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
#include "CPU.h"

CPU::CPU()
{
    GBF::Image::SpriteFactory *spriteFactory = new GBF::Image::SpriteFactory("personagem");

    addMainSprite(spriteFactory->createSpriteCharacter(15,21,14,80,1,1));
    delete(spriteFactory);

    iniciarVisao();
}
CPU::~CPU()
{

    //dtor
}
void CPU::update(GBF::Kernel::Input::InputSystem * input)
{
    GBF::Area areaVisaoBola = Util::converterArea(getVisaoBola().getDimension(),getVisaoBola().getPoint());
    GBF::Area visao         = Util::converterArea(getDimension(),getPoint());

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
GBF::Point CPU::saque()
{
    GBF::Point saque;

    saque.x=point.x+getDimension().w;
    saque.y=point.y+rand()%(getDimension().h-getVisaoBola().getDimension().h);

    return saque;
}
bool CPU::isCollision(Character * personagem)
{
    bool retorno = Raquete::isCollision(personagem);

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
void CPU::draw()
{
    Raquete::draw();

#ifdef DEBUG
    GBF::Kernel::Graphic::GFX *gfx = GBF::Kernel::Graphic::GraphicSystem::getInstance()->gfx;

    gfx->setColor(255,255,255);
    gfx->circle(point.x+getDimension().w/2,point.y+getDimension().h/2,raioVisao);

    gfx->setColor(255,0,0);
    gfx->circle(point.x+getDimension().w/2,point.y+getDimension().h/2,int(getDimension().h*1.4));
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

    //quadrado da distância em x
    qx = std::pow(float((areaVisaoBola.left + areaVisaoBola.right/2) - (visao.left + visao.right/2)), 2);
    //quadrado da distância em y
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
