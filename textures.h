#ifndef TEXTURES_H
#define TEXTURES_H

#include <QFile>
#include <QIODevice>
#include <QPixmap>

class Textures
{
public:
    enum TEXTURES_INDEX{
        GRASS = 0,
        SAND,
        DARKNESS,
        CLIFF,
        LT_TREE,
        RT_TREE,
        LB_TREE,
        RB_TREE,
        L_THREE_TREE,
        R_THREE_TREE,
        DARK_GRASS,
        H_WOODEN_FENCE,
        V_WOODEN_FENCE,
        L_WOODEN_FENCE,
        R_WOODEN_FENCE,
        LT_WOODEN_FENCE,
        LB_WOODEN_FENCE,
        RT_WOODEN_FENCE,
        RB_WOODEN_FENCE,
        H_DIRTY_ROAD,
        V_DIRTY_ROAD,
        LB_DIRTY_ROAD,
        BATTLE_BG,
        SKELETON,
        CHEST,
        SLIME,
        HEAL_POTION,
        MANA_POTION,
        TRADE_BG,
        TRADE_MG,
        TRADER,
        PORTAL,
        L_DOUBLE_TREE,
        R_DOUBLE_TREE,
        GRAVE,
        GRASS_2,
        BUSH,
        CROSS,
        CASTLE_ENTER_LT,
        CASTLE_ENTER_RT,
        CASTLE_ENTER_LM,
        CASTLE_ENTER_RM,
        CASTLE_ENTER_LB,
        CASTLE_ENTER_RB,
        CASTLE_ENTER_MT,
        CASTLE_ENTER_MB,
        CASTLE_WALL_T,
        CASTLE_WALL_B,
        CASTLE_FLOOR,
        DEVIL_STAR,
        DIRTY_ROAD_R_END,
        DIRTY_ROAD_L_END,
        DRY_BUSH,
        DIRTY_ROAD_CROSS,
        DIRTY_ROAD_T_END,
        DIRTY_ROAD_B_END,
        KNIGHT_STATUE_T,
        KNIGHT_STATUE_B,
        GARGOYLE_STATUE_T,
        GARGOYLE_STATUE_B,
        SQUARE_PLATE,
        RB_DIRTY_ROAD,
        LT_DIRTY_ROAD,
        RT_DIRTY_ROAD,
        STONE_WALL,
        HIGH_GRASS,
        KNIGHT,
        GARGOYLE,
        DIRTY_ROAD_LE,
        ADVENTURER,
        TOWER_FLOOR,
        NECROMANCER,
        CASTLE_BATTLE_BG,
        GOLDEN_SKELETON,
        DEAD_MAN,
        GRAVE_DEFENDER,
        HALL_COVER,
        GOLDEN_CHEST
    };
    static Textures *getInstance();
    static int getBattleBG();
    QPixmap *getTexture(int index);
private:
    Textures();
    static Textures* instance;
    QPixmap* textures;
};

#endif // TEXTURES_H
