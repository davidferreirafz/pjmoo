#include <cstdlib>
#include <iostream>
#include <stdio.h>

#include "TopManager.h"

int main(int argc, char **argv)
{
	char message[1024];

	TopManager *topManager = new TopManager();
	
	topManager->executar();
	
	TopRecorde top = topManager->getTop();
	/*
	Recorde *recorde = new Recorde();
	strcpy(recorde->nome,"the one");
	recorde->pontos=1500;
	strcpy(recorde->tipo,"Local");
	recorde->fase=3;
	recorde->tempo=001000;
	top.adicionar(*recorde);
	delete (recorde);
	*/
	top.imprimir();
	

	delete (topManager);

	return(0);
}
