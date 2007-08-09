#ifndef STATUS_H
#define STATUS_H

#include <GBF/SpriteItem.h>
#include <GBF/GraphicSystemImageBufferManager.h>
#include <GBF/SpriteFactory.h>
#include <GBF/WriteSystemManager.h>

#include "Placar.h"

class Status
{
    public:
        Status();
        virtual ~Status();
        void virtual desenhar()=0;
        static void setPlacar(Placar *placar);

    protected:
        SpriteItem * painel;
        SpriteItem * pontuacao;
        static Placar     * placar;
        static WriteSystemManager * wsManager;

    private:
};



#endif // STATUS_H
