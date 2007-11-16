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
        std::cout << "Ok é do tipo" << std::endl;
    } else {
        std::cout << "Não é do tipo" << std::endl;
    }

//    if (instanceOF<Objeto>( o )){
    if (InstanceOf<Teste>::is( n )){
        std::cout << "Ok é do tipo" << std::endl;
    } else {
        std::cout << "Não é do tipo" << std::endl;
    }

}

