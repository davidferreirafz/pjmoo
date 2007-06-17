#include "ParserRecorde.h" // class's header file


ParserRecorde::ParserRecorde(char* httpMessage)
{
	std::string buffer = httpMessage;
	int tamanho=buffer.length();
	int posicaoInicial = 0;
		
	//procura pela posição do retorno de linha, caracterizando a separação entre 
	//o cabecalho http e os dados em formato "pure text/plain"
	for (int l=tamanho; l>0; --l){
		if (httpMessage[l]=='\r'){
			posicaoInicial=l;
			break;
		}
	}

	split(buffer.substr(posicaoInicial,tamanho));
}
ParserRecorde::~ParserRecorde()
{
}
void ParserRecorde::split(std::string httpDados)
{
	printf("\n*Verificando dados baixados.");
	totalLinha=0;
	for (int c=0; c<httpDados.length();c++){
		if (httpDados[c]=='\n'){
			totalLinha++;
		}
	}

	if (totalLinha>1){
		totalLinha--;
	}

	printf("\n *Encontrados %d registros",totalLinha);
	
	
	int* corte= new int[totalLinha];
	
	int n=0;	
	for (int c=0; c<httpDados.length();c++){
		if (httpDados[c]=='\n'){
			corte[n]=c;
			n++;
		}
	}
	printf("\n *Avaliando os registros:\n  >> ");
	
	dado = new std::string[totalLinha];

	for (int i=0; i<totalLinha; i++){
		int tamanho = corte[i+1] - corte[i];
		dado[i] = httpDados.substr((corte[i])+1,tamanho-1);
		printf("%d ",i);	
	}
	
	printf(" [Ok]");
}

Recorde ParserRecorde::getRecorde(int i)
{
	int corte[7];
	int n=0;
	int tamanho = dado[i].length();

	//procura pela posição do pipe "|"
	for (int c=0; c<tamanho; c++){
		if (dado[i][c]=='|'){
			corte[n]=c;
			n++;
		}
	}
	
	Recorde recorde;
	recorde.id=atoi(dado[i].substr(0,corte[0]).c_str());
	sprintf(recorde.nome,"%s",dado[i].substr(corte[0]+1,corte[1]-corte[0]-1).c_str());
	recorde.pontos=atoi(dado[i].substr(corte[1]+1,corte[2]-corte[1]-1).c_str());
	sprintf(recorde.dataPublicacao,"%s",dado[i].substr(corte[2]+1,corte[3]-corte[2]-1).c_str());
	sprintf(recorde.tipo,"Global");
	recorde.fase=atoi(dado[i].substr(corte[4]+1,corte[5]-corte[4]-1).c_str());
	recorde.tempo=atoi(dado[i].substr(corte[5]+1,corte[6]-corte[5]-1).c_str());
		
	return recorde;
}
RecordeManager ParserRecorde::getRecorde()
{
	RecordeManager recordeManager;

	for (int i=0; i<totalLinha; i++){
		recordeManager.adicionar(getRecorde(i));
	}

	return recordeManager;
}
int ParserRecorde::getID()
{
	int corte[2];
	int n=0;
	int tamanho = dado[0].length();

	//procura pela posição do pipe "|"
	for (int c=0; c<tamanho; c++){
		if (dado[0][c]=='|'){
			corte[n]=c;
			n++;
		}
	}
	
	return atoi(dado[0].substr(0,corte[0]).c_str());
}
std::string ParserRecorde::getDataPublicacao()
{
	int corte[2];
	int n=0;
	int tamanho = dado[0].length();

	//procura pela posição do pipe "|"
	for (int c=0; c<tamanho; c++){
		if (dado[0][c]=='|'){
			corte[n]=c;
			n++;
		}
	}
	
	return dado[0].substr(corte[0]+1,corte[1]-corte[0]-1);
}







