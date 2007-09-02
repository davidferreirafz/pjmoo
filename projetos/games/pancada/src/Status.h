#ifndef STATUS_H
#define STATUS_H

#include <GBF/SpriteItem.h>
#include <GBF/GraphicSystemImageBufferManager.h>
#include <GBF/SpriteFactory.h>

#include "HUDAbstract.h"

class Status : public HUDAbstract
{
    public:
        Status();
        virtual ~Status();
        void virtual desenhar(int pontos, int round, int energia)=0;

    protected:
        SpriteItem * pontuacao;
        SpriteItem * statusEnergia;

    private:
};



#endif // STATUS_H
