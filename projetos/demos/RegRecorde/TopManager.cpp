#include "TopManager.h"


TopManager::TopManager()
{
	std::string host="pjmoo.codigolivre.org.br";
//	std::string host="tomcat-nuadd";
	
	sdl.conectar(host,80);
}
TopManager::~TopManager()
{
	
}
TopRecorde TopManager::getTop()
{
	return top;
}
void TopManager::executar()
{	
	if (top.carregar()){
		procurar();
		//downloadTop3();
	} else {
		novaVersao();
	}
}
void TopManager::procurar()
{
	char mensagem[1024];
	
	for (int i=0; i<RecordeManager::tamanho; i++){
		if (top.manager.recorde[i].id==0){
			sprintf(mensagem,"teste/php/regpublicar.php?nome=%s&pontos=%d&fase=%d&tempo=%d",top.manager.recorde[i].nome,top.manager.recorde[i].pontos,top.manager.recorde[i].fase,top.manager.recorde[i].tempo);

			if (sdl.enviarMensagem(mensagem)){
				sdl.receberMensagem(mensagem);
				ParserRecorde *parser = new ParserRecorde(mensagem);
				int idRetorno = parser->getID();
				
				switch(idRetorno){
					case RECORDE_INVALIDO:
						break;
						
					default:
						top.manager.recorde[i].id = idRetorno;
						strcpy(top.manager.recorde[i].dataPublicacao,parser->getDataPublicacao().c_str());
						strcpy(top.manager.recorde[i].tipo,"Local");
						break;		
				}
				delete (parser);
			}
		}
	}
}
void TopManager::novaVersao()
{
	char mensagem[1024];
	
	if (sdl.enviarMensagem("teste/php/regrecorde.php?quantidade=10")){
		if(sdl.receberMensagem(mensagem)){
			ParserRecorde *parser = new ParserRecorde(mensagem);
			top.setRecordeManager(parser->getRecorde());
			top.salvar();
			delete (parser);
		}
	}
}
void TopManager::downloadTop3()
{
	char mensagem[1024];
	printf("Baixando Top 3");
	if (sdl.enviarMensagem("teste/php/regrecorde.php?quantidade=3")){
		if(sdl.receberMensagem(mensagem)){
			ParserRecorde *parser = new ParserRecorde(mensagem);
			for (int r=0; r<3; r++){
                if (top.adicionar(parser->getRecorde(r))){
                	printf("...adicionando recorde global...");
                }
            }
            top.salvar();
        	printf("... salvando ");
			delete (parser);
		}
	}
}



