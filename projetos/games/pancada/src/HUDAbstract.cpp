#include "HUDAbstract.h"


WriteSystemManager * HUDAbstract::wsManager = NULL;

HUDAbstract::HUDAbstract()
{

    if (wsManager==NULL){
        wsManager = WriteSystemManager::getInstance();
    }
}

HUDAbstract::~HUDAbstract()
{
    wsManager = NULL;

    if (painel){
        delete(painel);
    }
}


