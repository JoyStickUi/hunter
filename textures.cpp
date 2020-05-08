#include "textures.h"
#include "player.h"
#include "game.h"
#include <iostream>

Textures* Textures::instance = nullptr;

Textures *Textures::getInstance()
{
    if(instance == nullptr)
        instance = new Textures();
    return instance;
}

int Textures::getBattleBG()
{
    if(((Player::getInstance()->y() + (Player::getInstance()->height() / 2)) / Game::getInstance()->items_scale) >= 26){
        return Textures::CASTLE_BATTLE_BG;
    }
    return Textures::BATTLE_BG;
}

QPixmap *Textures::getTexture(int index)
{
    return &this->textures[index];
}

Textures::Textures()
{
    QPixmap spriteAtlas("://img/spmap.png");
    QPixmap dirty_road("://img/dirty-road.png");
    QPixmap flowers("://img/[A]Flower_pipo.png");

    this->textures = new QPixmap[78];

    this->textures[TEXTURES_INDEX::GRASS] = spriteAtlas.copy(0, 0, 31, 31);
    this->textures[TEXTURES_INDEX::SAND] = spriteAtlas.copy(192, 0, 31, 31);
    this->textures[TEXTURES_INDEX::DARKNESS] = spriteAtlas.copy(128, 1248, 31, 31);
    this->textures[TEXTURES_INDEX::CLIFF] = spriteAtlas.copy(0, 381, 31, 31);
    this->textures[TEXTURES_INDEX::LT_TREE] = spriteAtlas.copy(0, 32, 31, 31);
    this->textures[TEXTURES_INDEX::RT_TREE] = spriteAtlas.copy(31, 32, 31, 31);
    this->textures[TEXTURES_INDEX::LB_TREE] = spriteAtlas.copy(0, 63, 31, 31);
    this->textures[TEXTURES_INDEX::RB_TREE] = spriteAtlas.copy(31, 63, 31, 31);
    this->textures[TEXTURES_INDEX::L_THREE_TREE] = spriteAtlas.copy(0, 128, 31, 31);
    this->textures[TEXTURES_INDEX::R_THREE_TREE] = spriteAtlas.copy(31, 128, 31, 31);
    this->textures[TEXTURES_INDEX::DARK_GRASS] = spriteAtlas.copy(31, 0, 31, 31);
    this->textures[TEXTURES_INDEX::H_WOODEN_FENCE] = spriteAtlas.copy(0, 736, 31, 31);
    this->textures[TEXTURES_INDEX::V_WOODEN_FENCE] = spriteAtlas.copy(0, 704, 31, 31);
    this->textures[TEXTURES_INDEX::L_WOODEN_FENCE] = spriteAtlas.copy(128, 736, 31, 31);
    this->textures[TEXTURES_INDEX::R_WOODEN_FENCE] = spriteAtlas.copy(128, 704, 31, 31);
    this->textures[TEXTURES_INDEX::LT_WOODEN_FENCE] = spriteAtlas.copy(64, 704, 31, 31);
    this->textures[TEXTURES_INDEX::LB_WOODEN_FENCE] = spriteAtlas.copy(64, 736, 31, 31);
    this->textures[TEXTURES_INDEX::RT_WOODEN_FENCE] = spriteAtlas.copy(96, 704, 31, 31);
    this->textures[TEXTURES_INDEX::RB_WOODEN_FENCE] = spriteAtlas.copy(96, 736, 31, 31);
    this->textures[TEXTURES_INDEX::H_DIRTY_ROAD] = dirty_road.copy(64, 0, 31, 31);
    this->textures[TEXTURES_INDEX::V_DIRTY_ROAD] = dirty_road.copy(128, 32, 31, 31);
    this->textures[TEXTURES_INDEX::LB_DIRTY_ROAD] = dirty_road.copy(0, 64, 31, 31);
    this->textures[TEXTURES_INDEX::BATTLE_BG] = QPixmap("://img/forest_battle_bg.jpg");
    this->textures[TEXTURES_INDEX::SKELETON] = QPixmap("://img/skeleton.png").copy(0, 335, 64, 49);
    this->textures[TEXTURES_INDEX::CHEST] = QPixmap("://img/chest.png");
    this->textures[TEXTURES_INDEX::SLIME] = QPixmap("://img/slime.png");
    this->textures[TEXTURES_INDEX::HEAL_POTION] = QPixmap("://img/heal_potion.png");
    this->textures[TEXTURES_INDEX::MANA_POTION] = QPixmap("://img/mana_potion.png");
    this->textures[TEXTURES_INDEX::TRADE_MG] = QPixmap("://img/middleground.png");
    this->textures[TEXTURES_INDEX::TRADE_BG] = QPixmap("://img/background.png");
    this->textures[TEXTURES_INDEX::TRADER] = QPixmap("://img/trader.png");
    this->textures[TEXTURES_INDEX::PORTAL] = QPixmap("://img/portalt.png");
    this->textures[TEXTURES_INDEX::L_DOUBLE_TREE] = spriteAtlas.copy(0, 96, 31, 31);
    this->textures[TEXTURES_INDEX::R_DOUBLE_TREE] = spriteAtlas.copy(31, 96, 31, 31);
    this->textures[TEXTURES_INDEX::GRAVE] = spriteAtlas.copy(96, 256, 31, 31);
    this->textures[TEXTURES_INDEX::GRASS_2] = spriteAtlas.copy(0, 192, 31, 31);
    this->textures[TEXTURES_INDEX::BUSH] = spriteAtlas.copy(0, 160, 31, 31);
    this->textures[TEXTURES_INDEX::CROSS] = spriteAtlas.copy(127, 256, 31, 31);
    this->textures[TEXTURES_INDEX::CASTLE_ENTER_LT] = spriteAtlas.copy(96, 1312, 31, 31);
    this->textures[TEXTURES_INDEX::CASTLE_ENTER_RT] = spriteAtlas.copy(160, 1312, 31, 31);
    this->textures[TEXTURES_INDEX::CASTLE_ENTER_LM] = spriteAtlas.copy(96, 1344, 31, 31);
    this->textures[TEXTURES_INDEX::CASTLE_ENTER_RM] = spriteAtlas.copy(160, 1344, 31, 31);
    this->textures[TEXTURES_INDEX::CASTLE_ENTER_LB] = spriteAtlas.copy(96, 1376, 31, 31);
    this->textures[TEXTURES_INDEX::CASTLE_ENTER_RB] = spriteAtlas.copy(160, 1376, 31, 31);
    this->textures[TEXTURES_INDEX::CASTLE_ENTER_MT] = spriteAtlas.copy(128, 1344, 31, 31);
    this->textures[TEXTURES_INDEX::CASTLE_ENTER_MB] = spriteAtlas.copy(128, 1376, 31, 31);
    this->textures[TEXTURES_INDEX::CASTLE_WALL_T] = spriteAtlas.copy(0, 1728, 31, 31);
    this->textures[TEXTURES_INDEX::CASTLE_WALL_B] = spriteAtlas.copy(0, 1760, 31, 31);
    this->textures[TEXTURES_INDEX::CASTLE_FLOOR] = spriteAtlas.copy(64, 1280, 31, 31);
    this->textures[TEXTURES_INDEX::DEVIL_STAR] = spriteAtlas.copy(192, 256, 31, 31);
    this->textures[TEXTURES_INDEX::DIRTY_ROAD_R_END] = dirty_road.copy(96, 0, 31, 31);
    this->textures[TEXTURES_INDEX::DIRTY_ROAD_L_END] = dirty_road.copy(32, 0, 31, 31);
    this->textures[TEXTURES_INDEX::DRY_BUSH] = spriteAtlas.copy(64, 192, 31, 31);
    this->textures[TEXTURES_INDEX::DIRTY_ROAD_CROSS] = dirty_road.copy(192, 160, 31, 31);
    this->textures[TEXTURES_INDEX::DIRTY_ROAD_T_END] = dirty_road.copy(128, 0, 31, 31);
    this->textures[TEXTURES_INDEX::DIRTY_ROAD_B_END] = dirty_road.copy(128, 64, 31, 31);
    this->textures[TEXTURES_INDEX::KNIGHT_STATUE_T] = spriteAtlas.copy(128, 3616, 31, 31);
    this->textures[TEXTURES_INDEX::KNIGHT_STATUE_B] = spriteAtlas.copy(128, 3648, 31, 31);
    this->textures[TEXTURES_INDEX::GARGOYLE_STATUE_T] = spriteAtlas.copy(128, 3678, 31, 31);
    this->textures[TEXTURES_INDEX::GARGOYLE_STATUE_B] = spriteAtlas.copy(128, 3710, 31, 31);
    this->textures[TEXTURES_INDEX::SQUARE_PLATE] = spriteAtlas.copy(64, 1152, 31, 31);
    this->textures[TEXTURES_INDEX::RB_DIRTY_ROAD] = dirty_road.copy(32, 64, 31, 31);
    this->textures[TEXTURES_INDEX::LT_DIRTY_ROAD] = dirty_road.copy(0, 32, 31, 31);
    this->textures[TEXTURES_INDEX::RT_DIRTY_ROAD] = dirty_road.copy(32, 32, 31, 31);
    this->textures[TEXTURES_INDEX::STONE_WALL] = spriteAtlas.copy(0, 864, 31, 31);
    this->textures[TEXTURES_INDEX::HIGH_GRASS] = flowers.copy(0, 192, 31, 31);
    this->textures[TEXTURES_INDEX::KNIGHT] = QPixmap("://img/Knight.png").copy(0, 1295, 64, 49);
    this->textures[TEXTURES_INDEX::GARGOYLE] = QPixmap("://img/gargoyle.png").copy(0, 1295, 64, 49);
    this->textures[TEXTURES_INDEX::DIRTY_ROAD_LE] = dirty_road.copy(96, 64, 31, 31);
    this->textures[TEXTURES_INDEX::ADVENTURER] = QPixmap("://img/adventurer.png").copy(0, 648, 64, 49);
    this->textures[TEXTURES_INDEX::TOWER_FLOOR] = spriteAtlas.copy(96, 1152, 31, 31);
    this->textures[TEXTURES_INDEX::NECROMANCER] = QPixmap("://img/Necromancer.png").copy(64, 1295, 64, 49);
    this->textures[TEXTURES_INDEX::CASTLE_BATTLE_BG] = QPixmap("://img/castle_battle_bg.jpg");
    this->textures[TEXTURES_INDEX::GOLDEN_SKELETON] = QPixmap("://img/golden_skeleton.png").copy(0, 1295, 64, 49);
    this->textures[TEXTURES_INDEX::DEAD_MAN] = QPixmap("://img/dead_men.png").copy(0, 1295, 64, 49);
    this->textures[TEXTURES_INDEX::GRAVE_DEFENDER] = QPixmap("://img/grave_defender.png").copy(0, 648, 64, 49);
    this->textures[TEXTURES_INDEX::HALL_COVER] = spriteAtlas.copy(128, 1312, 31, 31);
    this->textures[TEXTURES_INDEX::GOLDEN_CHEST] = spriteAtlas.copy(192, 3424, 31, 31);
}
