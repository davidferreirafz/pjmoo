#ifndef PARSERRECORDE_H
#define PARSERRECORDE_H


#include <string>

#include "RecordeManager.h"


class ParserRecorde
{
public:
	/** Construtor */
	ParserRecorde(char* httpMessage);
	/** Destrutor */
	~ParserRecorde();
	/** Retorna vetor de Recordes*/
	RecordeManager getRecorde();
	/** Retorna apenas um recorde*/
	Recorde ParserRecorde::getRecorde(int i);
	int getID();
	std::string getDataPublicacao();
	
private:
	//Linhas de dados em armazenamento
	std::string *dado;

	
	int totalLinha;
	
protected:
	//Meotod para separar os dados em linhas de registros
	void split(std::string httpDados);

};

#endif // PARSERRECORDE_H

 
