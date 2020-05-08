#ifndef GAMEEND_H
#define GAMEEND_H

#include "gameobject.h"

class GameEnd : public GameObject
{
public:
    GameEnd();
    void activation_func() override;
};

#endif // GAMEEND_H
