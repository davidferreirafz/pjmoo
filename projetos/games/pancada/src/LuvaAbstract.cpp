
#include "LuvaAbstract.h"

//Construtor

//Construtor
LuvaAbstract::LuvaAbstract(){
    GraphicSystem  *graphicSystem = GraphicSystem::getInstance();
    SpriteFactory  *spriteFactory = new SpriteFactory(graphicSystem->imageBufferManager->getImageBuffer("personagem"));

    sprite=spriteFactory->criarSpritePersonagem(0,231,76,84,1,1);
    sprite->setQtdDirecoes(2);

	delete(spriteFactory);


	setSoco(false);
}

//Destrutor

//Destrutor
LuvaAbstract::~LuvaAbstract(){
}

void LuvaAbstract::setSoco(bool soco) 
{
	this->soco=soco;
}
bool LuvaAbstract::isSoco() 
{
	return soco;
}
bool LuvaAbstract::isLuvaDireita() 
{
	if (eLuva==LUVA_DIREITA){
		return true;
	} else {
		return false;
	}
}
bool LuvaAbstract::isLuvaEsquerda() 
{
	if (eLuva==LUVA_ESQUERDA){
		return true;
	} else {
		return false;
	}
}
