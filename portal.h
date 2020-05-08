#ifndef PORTAL_H
#define PORTAL_H

#include "gameobject.h"

class Portal : public GameObject
{
public:
    Portal(int x_tp_to, int y_tp_to, std::function<void()> onTp);
    void activation_func() override;
private:
    std::function<void()> onTp;
    int x_tp_to = 5;
    int y_tp_to = 4;
};

#endif // PORTAL_H
