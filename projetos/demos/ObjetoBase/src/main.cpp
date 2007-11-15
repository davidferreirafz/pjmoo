////***************************************************************************
////  ObjetoBase <Demo de Recursos>
////  Copyright (C) 2007 by David Ferreira - FZ
////  davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net
////***************************************************************************
////    Este programa é software livre; você pode redistribuí-lo e/ou
////    modificá-lo sob os termos da Licença Pública Geral GNU, conforme
////    publicada pela Free Software Foundation; tanto a versão 2 da
////    Licença como (a seu critério) qualquer versão mais nova.
////***************************************************************************
////    This program is free software; you can redistribute it and/or modify
////    it under the terms of the GNU General Public License as published by
////    the Free Software Foundation; either version 2 of the License, or
////    (at your option) any later version.
////
////    You should have received a copy of the GNU General Public License
////    along with this program; if not, write to the
////    Free Software Foundation, Inc.,
////    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
////***************************************************************************
#include "main.h"

    class Teste {
        public:
        virtual ~Teste(){}
    };


template <class T>
class instanceOf
{
public:
    template <class Tipo>
    static bool is (Tipo *tipo)
    {
        if (dynamic_cast<T*>(tipo)){
            return true;
        } else {
            return false;
        }
    }
    template <class Tipo>
    static bool is (Tipo tipo)
    {
        if (dynamic_cast<T*>(&tipo)){
            return true;
        } else {
            return false;
        }
    }
};
//////-------------------------
template <class T, class Tipo>
bool instance (Tipo tipo)
{
    if (dynamic_cast<T*>(&tipo)){
        return true;
    } else {
        return false;
    }
};
template <class T, class Tipo>
bool instance (Tipo *tipo)
{
    if (dynamic_cast<T*>(tipo)){
        return true;
    } else {
        return false;
    }
};



int main(int argc, char * argv[])
{
    ObjetoBase obj;
    ObjetoManager m;
    Teste t;

    if (instance<ObjetoBase>(t)){
//    if (instanceOf<Teste>::is(m)){
        std::cout << "Ok é do tipo" << std::endl;
    } else {
        std::cout << "Não é do tipo" << std::endl;
    }

}

