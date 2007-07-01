#ifndef RECORDE_H
#define RECORDE_H

#include <string>


#define RECORDE_INVALIDO -80


class Recorde
{
public:
	unsigned int id;
	char nome[11];
	unsigned int pontos;
	char dataPublicacao[11];
	char tipo[6];
	unsigned int fase;
	unsigned int tempo;
	
	//Construtor com inicialização dos atributos
	Recorde()
	{
		id=0;
		strcpy(nome,"");
		pontos=0;
		strcpy(dataPublicacao,"");
		strcpy(tipo,"Local");
		fase=0;
		tempo=0;
	}
	
};


#endif 
