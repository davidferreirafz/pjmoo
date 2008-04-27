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

/*****************************************************************/
/* Declaração - Includes                                         */
/*****************************************************************/
#include <GBF/GBF.h>
#include <GBF/GAT.h>

#include "Jogo.h"
#include <exception>



/*****************************************************************/
/* Execução do Programa                                          */
/*****************************************************************/
int main(int argc, char* argv[])
{
    GAT* jogo = NULL;
    jogo = new Jogo(argc,argv);

    try {
        jogo->executar();
    } catch (std::exception& e) {
        UtilLog::sistema("!!!!!!!!!!");
        UtilLog::sistema("Exceção: %s",e.what());        
        UtilLog::sistema("!!!!!!!!!!");
    } catch (...) {
        UtilLog::sistema("!!!!!!!!!!");
        UtilLog::sistema("Exceção Desconhecida");
        UtilLog::sistema("!!!!!!!!!!");        
    }

    delete(jogo);

    return 0;
}

