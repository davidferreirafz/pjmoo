#ifndef STATUSPLAYER_H
#define STATUSPLAYER_H

#include "Status.h"


class StatusPlayer : public Status
{
    public:
        StatusPlayer();
        virtual ~StatusPlayer();
        void desenhar(int pontos, int round, int energia);
    protected:
    private:
};



#endif // STATUSPLAYER_H
