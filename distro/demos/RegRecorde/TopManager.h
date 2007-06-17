#ifndef _TOPMANAGER_H_
#define _TOPMANAGER_H_

#include "AppSDL.h"
#include "TopRecorde.h"
#include "ParserRecorde.h"

class TopManager
{
public:
	TopManager();
	~TopManager();
	
	void executar();
	TopRecorde getTop();

protected:
	void procurar();
	void novaVersao();
	void downloadTop3();
	
private:
	AppSDL sdl;
	
	TopRecorde top;
};

#endif
