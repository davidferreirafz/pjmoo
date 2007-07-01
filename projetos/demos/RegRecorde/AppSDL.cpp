#include "AppSDL.h" // class's header file


AppSDL::AppSDL()
{
	sock = NULL;
	// initialize SDL
	if(SDL_Init(0)==-1)
	{
		printf("SDL_Init: %s\n",SDL_GetError());
		exit(1);
	}
	//Desativando o log em arquivo da SDL
    freopen( "CON", "w", stdout );
    freopen( "CON", "w", stderr );
    
	printf("\n+Iniciando Programa...");
	
	// initialize SDL_net
	if(SDLNet_Init()==-1)
	{
		printf("SDLNet_Init: %s\n",SDLNet_GetError());
		exit(2);
	}
}
AppSDL::~AppSDL()
{
	if (sock){
		SDLNet_TCP_Close(sock);
	}
	// shutdown SDL_net
	SDLNet_Quit();
	// shutdown SDL
	SDL_Quit();
	printf("\n+Terminando Programa...\n");
}
bool AppSDL::conectar(std::string host, int porta)
{
	char msgResposta[255];
	IPaddress ip;
	bool retorno = false;
	hostname=host;
	
	printf("\n*Conectando... a %s",hostname.c_str());

	if(SDLNet_ResolveHost(&ip,hostname.c_str(),porta)!=0)
	{
		sprintf(msgResposta,"SDLNet_ResolveHost %s",SDLNet_GetError());
	} else {
    	sock=SDLNet_TCP_Open(&ip);
    	if(!sock){
    		sprintf(msgResposta,"SDLNet_TCP_Open %s",SDLNet_GetError());
    	} else {
            retorno = true;
        }
    }
	if (retorno){
		printf(" [conectado]");
	} else {
		printf(" [desconectado] \n\t# Erro: %s",msgResposta);
	}

	return retorno;
}
bool AppSDL::enviarMensagem(std::string msg)
{
	char buffer[1024];
	char msgResposta[255];
	bool retorno = false;
    	
	sprintf(buffer,"POST http://%s/%s HTTP/1.0 \n\rAccept: */*\n\rAccept: text/html\n\r\n\r",hostname.c_str(),msg.c_str());
	
	int bytesEnviados=strlen(buffer);
	printf("\n*Enviando solicitacao...");

	if (sock){
    	int	bytesConfirmados=SDLNet_TCP_Send(sock,buffer,bytesEnviados);
    	
        if (bytesConfirmados<bytesEnviados){
    		sprintf(msgResposta,"[Sem Sincronismo] :: SDLNet_TCP_Send %s\n",SDLNet_GetError());
    	} else {
            retorno = true;
        }
    } else {
		sprintf(msgResposta,"[Sem Socket] :: SDLNet_TCP_Send %s\n",SDLNet_GetError());        
    }

	if (retorno){
		printf(" [Ok]");
	} else {
		printf(" [Falhou] \n\t# Erro: %s",msgResposta);
	}	

	return retorno;
}
bool AppSDL::receberMensagem(char *msg)
{
	char msgResposta[255];
	bool retorno = false;
	
	printf("\n*Recebendo dados...");
	
	if (sock) {
    	int bytesRecebidos = SDLNet_TCP_Recv(sock,msg,1024);
    
    	if (bytesRecebidos>0) {
            retorno = true;
    	} else {
            sprintf(msgResposta,"[Sem recebimento de dados] :: SDLNet_TCP_Recv %s\n",SDLNet_GetError());
        }
    } else {
		sprintf(msgResposta,"[Sem Socket] :: SDLNet_TCP_Recv %s\n",SDLNet_GetError());
    }
	
	if (retorno){
		printf(" [Ok] ");
	} else {
		printf(" [Falhou] \n\t# Erro: %s",msgResposta);
	}	
}





