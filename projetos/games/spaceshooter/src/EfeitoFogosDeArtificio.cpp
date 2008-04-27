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
#include "EfeitoFogosDeArtificio.h"
void EfeitoFogosDeArtificio::criar( int x, int y )
{
    float angulo, velocidade;
    int cor = rand()%3;
    origem.x=x;
    origem.y=y;
    if (!lista.empty()){
        for (unsigned int i=0; i<lista.size(); i++){

            velocidade = ((float)(rand()%9000)/1000);
            angulo     = ((float)(rand()%6280)/1000);
            lista[i].posicao.x    = origem.x;
            lista[i].posicao.y    = origem.y;
            lista[i].velocidade.x = velocidade * cos(angulo);
            lista[i].velocidade.y = velocidade * sin(angulo);
            lista[i].energia      = 10 + rand()%10;
            lista[i].ativa        = true;
            lista[i].cor.s = 1.0;
            lista[i].cor.v = 1.0;
            switch(cor){
                case 0:  lista[i].cor.h = 0;     break;
                case 1:  lista[i].cor.h = 120;   break;
                case 2:  lista[i].cor.h = 240;   break;
            }
        }
    }
}
void EfeitoFogosDeArtificio::executar()
{
    float qx, qy, qr;
    qr = std::pow(float(rand()), 2); //quadrado da soma dos raios
    if (!lista.empty()){
        for (unsigned int i=0; i<lista.size(); i++){
            if (lista[i].ativa){
                lista[i].posicao.x += lista[i].velocidade.x;
                lista[i].posicao.y += lista[i].velocidade.y;
                lista[i].energia--;

                qx = std::pow(float(origem.x-lista[i].posicao.x), 2); //quadrado da distância em x
                qy = std::pow(float(origem.y-lista[i].posicao.y), 2); //quadrado da distância em y
                if ((lista[i].energia<0)||(qx + qy >= qr)){
                    lista[i].ativa = false;
                } else {
                    lista[i].cor.h -= rand()%20;
    	            if (lista[i].cor.h<0){
    					lista[i].cor.h=360;
    				}
                }
            }
        }
    }
}
