
#include "Cabeca.h"

//* Construtor 

//* Construtor 
Cabeca::Cabeca(){
    sprite=NULL;
}

//Destrutor 

//Destrutor 
Cabeca::~Cabeca(){
}

bool Cabeca::isColisao(Area aSoco) 
{
	float qx, qy, qr; //para guardar o quadrado de x, y e raio

	Area aCabeca   = getArea();

	//quadrado da distância em x
	qx = std::pow(float((aSoco.left + aSoco.right/2) - (aCabeca.left + aCabeca.right/2)), 2);
	//quadrado da distância em y	
	qy = std::pow(float((aSoco.top + aSoco.bottom/2) - (aCabeca.top  + aCabeca.bottom/2)), 2);
	//quadrado da soma dos raios	
	qr = std::pow(float(70), 2);

	if (qx + qy <= qr){
		return true;	
	} else {
		return false;
	}
}
void Cabeca::setPosicao(int x, int y) 
{
	posicao.x=x+47;
	posicao.y=y;
}
