
#include "HUDAbstract.h"

HUDAbstract::HUDAbstract(){


    if (wsManager==NULL){
        wsManager = WriteSystemManager::getInstance();
    }
}

HUDAbstract::~HUDAbstract(){

    if (painel){
        delete(painel);
    }
}

WriteSystemManager * HUDAbstract::wsManager = NULL;

