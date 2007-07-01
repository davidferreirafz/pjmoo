#include "RecordeManager.h" // class's header file

void RecordeManager::ordenar()
{
	int passo,Pi,j,indice,aux;
	Recorde recordeAuxiliar;
	int Ppasso[4]={5,3,2,1};
	
	for(Pi=0; Pi<4; Pi++ ){
		passo=Ppasso[Pi];
		for(indice=passo; indice < tamanho; indice++){
		recordeAuxiliar=recorde[indice];      
			for(j=indice-passo; recordeAuxiliar.pontos > recorde[j].pontos && j >=0; j-=passo){
				recorde[j+passo] = recorde[j];
			}  
			recorde[j+passo] = recordeAuxiliar;
		}
	}
}
Recorde RecordeManager::getPrimeiro()
{
	return recorde[0];
}
Recorde RecordeManager::getUltimo()
{
	return recorde[(tamanho-1)];
}
bool RecordeManager::adicionar(Recorde novo)
{
	bool ok = false;
	if (novo.pontos > recorde[9].pontos){
		recorde[9]=novo;
		ordenar();
		ok=true;
	}
	return ok;
}
bool RecordeManager::pesquisar(Recorde pesquisa)
{
	bool encontrou = false;
	
	for (int i=0; i<tamanho; i++){
		
		if ((recorde[i].id==pesquisa.id)
			&&(recorde[i].pontos==pesquisa.pontos)
			&&(recorde[i].pontos==pesquisa.pontos)
			&&(recorde[i].fase==pesquisa.fase)){
				encontrou=true;
		}
	}
	
	return encontrou;
}

