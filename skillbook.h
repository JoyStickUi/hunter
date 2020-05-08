#ifndef SKILLBOOK_H
#define SKILLBOOK_H

#include "item.h"

class SkillBook : public Item
{
public:
    SkillBook(int x, int y, int sprite_index, QString name, int skill, float skill_points, bool isResist);
    void activation_func() override;
    void use() override;
private:
    int skill;
    bool isResist;    
};

#endif // SKILLBOOK_H
