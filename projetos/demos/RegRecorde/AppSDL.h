#ifndef APPSDL_H
#define APPSDL_H

#include <SDL/SDL.h>
#include <SDL/SDL_net.h>

#include <string>

#include "ParserRecorde.h"

class AppSDL
{
public:
	AppSDL();
	~AppSDL();
	bool conectar(std::string host, int porta);
	bool enviarMensagem(std::string msg);
	bool receberMensagem(char *msg);

protected:
	TCPsocket sock;
	std::string hostname;
	
};

#endif // APPSDL_H

 
