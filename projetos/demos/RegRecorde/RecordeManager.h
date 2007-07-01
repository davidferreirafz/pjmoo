#ifndef RECORDEMANAGER_H
#define RECORDEMANAGER_H

#include <vector>

#include "Recorde.h"

class RecordeManager
{
public:
	const static int tamanho = 10;
	Recorde recorde[tamanho];
	
	
	void ordenar();
	
	
	Recorde getPrimeiro();
	Recorde getUltimo();
	bool adicionar(Recorde novo);
	bool pesquisar(Recorde pesquisa);

};


#endif // RECORDEMANAGER_H


