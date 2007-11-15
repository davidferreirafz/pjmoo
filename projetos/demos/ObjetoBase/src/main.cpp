////***************************************************************************
////  ObjetoBase <Demo de Recursos>
////  Copyright (C) 2007 by David Ferreira - FZ
////  davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net
////***************************************************************************
////    Este programa � software livre; voc� pode redistribu�-lo e/ou
////    modific�-lo sob os termos da Licen�a P�blica Geral GNU, conforme
////    publicada pela Free Software Foundation; tanto a vers�o 2 da
////    Licen�a como (a seu crit�rio) qualquer vers�o mais nova.
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
        std::cout << "Ok � do tipo" << std::endl;
    } else {
        std::cout << "N�o � do tipo" << std::endl;
    }

}

