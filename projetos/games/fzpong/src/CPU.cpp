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

CPU::CPU(){

    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();
    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(15,21,14,80,1,1));
    delete(spriteFactory);

    iniciarVisao();
}

CPU::~CPU(){

    //dtor
}

void CPU::acao(InputSystem * input)
{
//    fazerJogada(raioVisao,efeito);
    Area areaVisaoBola = Util::converterArea(getVisaoBola().getDimensao(),getVisaoBola().getPosicao());
    Area visao         = Util::converterArea(getDimensao(),getPosicao());

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
Ponto CPU::saque()
{
    Ponto saque;

    saque.x=posicao.x+getDimensao().w;
    saque.y=posicao.y+rand()%(getDimensao().h-getVisaoBola().getDimensao().h);

    return saque;
}
bool CPU::isColisao(PersonagemAbstract * personagem)
{
    bool retorno = Raquete::isColisao(personagem);

    if (retorno){
        efeito = Efeito(rand()%3);
    }

    return retorno;
}
void CPU::iniciarVisao()
{
    raioVisao=380;
}
void CPU::aumentarVisao()
{
    raioVisao+=20;

    if (raioVisao>=getAreaTela().bottom){
        raioVisao=getAreaTela().bottom;
    }
}
Decisao CPU::pensar(Area visao, Area areaVisaoBola)
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
	qe = std::pow(float(visao.bottom), 2);


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
