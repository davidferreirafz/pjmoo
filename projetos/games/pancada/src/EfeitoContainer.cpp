
#include "EfeitoContainer.h"

EfeitoContainer * EfeitoContainer::instance;

EfeitoContainer * EfeitoContainer::getInstance()
{
    if(instance==NULL){
        instance = new EfeitoContainer();
    }
    
    return instance;
}
//Destrutor 
EfeitoContainer::~EfeitoContainer() 
{

	limpar();
}
void EfeitoContainer::adicionar(int x, int y, EnumEfeito eEfeito) 
{

	EfeitoAbstract* efeito = NULL;	
	
	switch(eEfeito){	
		case EFEITO_SANGUE:
		default:
				efeito = new EfeitoSangue();
			break;
	}
	
	efeito->setPosicao(x,y);
	lista.push_back(efeito);	
}
void EfeitoContainer::desenhar() 
{

	if (!lista.empty()){
		for (unsigned int t=0; t<lista.size(); t++){
			if (lista[t]!=NULL){
	            lista[t]->desenhar();
			}
		}
	}
	removerDesativado();	
}
void EfeitoContainer::removerDesativado() 
{

	for (int i=lista.size()-1; i>=0; i--){
		if (lista[i]!=NULL){
			if (lista[i]->isAtivo()==false){
				delete lista[i];
				lista[i]=NULL;                 
				lista.erase(lista.begin()+i);
			}
		}
	}
}
void EfeitoContainer::limpar() 
{

	for (unsigned int i=0; i<lista.size(); i++){
		try {    
			if (lista[i]!=NULL){
	            delete lista[i];
    	        lista[i]=NULL;
			}
        } catch (...){
        }            
    }
    lista.clear(); 	
}
//Construtor 
EfeitoContainer::EfeitoContainer(){

}

