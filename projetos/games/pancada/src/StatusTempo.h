#ifndef STATUSTEMPO_H
#define STATUSTEMPO_H

#include <GBF/GraphicSystemImageBufferManager.h>
#include <GBF/SpriteFactory.h>

#include "HUDAbstract.h"


class StatusTempo : public HUDAbstract
{
    public:
        StatusTempo();
        virtual ~StatusTempo();
        void desenhar(int tempo);

    protected:

    private:
};



#endif // STATUSTEMPO_H
