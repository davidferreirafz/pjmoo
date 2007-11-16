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




template <class T>
class InstanceOf
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
bool instanceOF (Tipo tipo)
{
    if (dynamic_cast<T*>(&tipo)){
        return true;
    } else {
        return false;
    }
};
template <class T, class Tipo>
bool instanceOF (Tipo *tipo)
{
    if (dynamic_cast<T*>(tipo)){
        return true;
    } else {
        return false;
    }
};

class Objeto
{
    public:
     Objeto(){};
     virtual ~Objeto(){};

     template <class T>
     bool is(T tipo)
     {
         return instanceOF< T >( tipo );
     }

};

class Novo : public Objeto
{
    public:
     Novo(){};
     virtual ~Novo(){};

};

class Teste {
    public:
    virtual ~Teste(){}
};

int main(int argc, char * argv[])
{
    ObjetoBase obj;
    ObjetoManager m;
    Teste t;
    Objeto o;
    Novo n;



//    if (iof.is(n)){
//    if (instanceOF<Objeto>( obj )){
//    if (instanceOf<Novo>::is( o )){
//    if (itf.is( t )){
    if (o.is(t)){
        std::cout << "Ok � do tipo" << std::endl;
    } else {
        std::cout << "N�o � do tipo" << std::endl;
    }

//    if (instanceOF<Objeto>( o )){
    if (InstanceOf<Teste>::is( n )){
        std::cout << "Ok � do tipo" << std::endl;
    } else {
        std::cout << "N�o � do tipo" << std::endl;
    }

}

