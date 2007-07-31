
#include "EfeitoAbstract.h"

void EfeitoAbstract::verificar() 
{

    if (isAtivo()){
		if (sprite->isAnimacaoFim()){
			setAtivo(false);
		}
    }
}
//* Construtor 
EfeitoAbstract::EfeitoAbstract(){

}

//* Destrutor 
EfeitoAbstract::~EfeitoAbstract(){

	if (sprite!=NULL){
		delete (sprite);
	}	
}

void EfeitoAbstract::setPosicao(int x, int y) 
{

	posicao.x=x;
	posicao.y=y;
}
void EfeitoAbstract::desenhar() 
{

	verificar();
	sprite->desenhar(posicao.x,posicao.y);		
}
bool EfeitoAbstract::isAtivo() 
{

	return ativo;
}
void EfeitoAbstract::setAtivo(bool ativo) 
{

	this->ativo=ativo;
}
