#include "gamescene.h"

#include "background.h"
#include "game.h"
#include "objectsdrawer.h"
#include "gamemap.h"
#include "gameobject.h"
#include "enemy.h"
#include "battle_ui.h"
#include "notifications.h"
#include "stat_ui.h"
#include "trader_ui.h"
#include "trader.h"
#include "inventory_ui.h"
#include "textures.h"
#include "skillbook.h"
#include "potion.h"
#include "questlogger.h"

GameScene* GameScene::instance = nullptr;

GameScene *GameScene::getInstance()
{
    if(instance == nullptr)
        instance = new GameScene();
    return instance;
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

}

void GameScene::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (Game::getInstance()->gameState) {
        case Game::Adventure:
        {
            switch(keyEvent->key()){
                case Qt::Key_W:
                {
                    GameObject* collided = this->player->hitTest(0, -1);
                    if(this->player->y() > Game::getInstance()->items_scale * 3 && !collided->isCollidable())
                        this->player->forceBy(0, -5);
                    if(collided->isActivatable())
                        collided->activate();
                    this->player->anim_state = this->player->BACK;
                }
                break;
                case Qt::Key_S:
                {
                    GameObject* collided =  this->player->hitTest(0, 1);
                    if(this->player->y() < (GameMap::getInstance()->height() * Game::getInstance()->items_scale) - (Game::getInstance()->items_scale * 4) && !collided->isCollidable())
                        this->player->forceBy(0, 5);
                    if(collided->isActivatable())
                        collided->activate();
                    this->player->anim_state = this->player->FORWARD;
                }
                break;
                case Qt::Key_A:
                {
                    GameObject* collided = this->player->hitTest(-1, 0);
                    if(this->player->x() > Game::getInstance()->items_scale * 5 && !collided->isCollidable())
                        this->player->forceBy(-5, 0);
                    if(collided->isActivatable())
                        collided->activate();
                    this->player->anim_state = this->player->LEFT;
                }
                break;
                case Qt::Key_D:
                {
                    GameObject* collided = this->player->hitTest(1, 0);
                    if(this->player->x() < (GameMap::getInstance()->width() * Game::getInstance()->items_scale) - (Game::getInstance()->items_scale * 6) && !collided->isCollidable())
                        this->player->forceBy(5, 0);
                    if(collided->isActivatable())
                        collided->activate();
                    this->player->anim_state = this->player->RIGHT;
                }
                break;
                case Qt::Key_T:
                    Inventory_UI::getInstance()->visiability = false;
                    Stat_UI::getInstance()->visiability = !Stat_UI::getInstance()->visiability;
                break;
                case Qt::Key_I:
                    Stat_UI::getInstance()->visiability = false;
                    Inventory_UI::getInstance()->visiability = !Inventory_UI::getInstance()->visiability;
                break;
                case Qt::Key_1:
                {
                    if(Inventory_UI::getInstance()->visiability)
                        this->player->use(0);
                }
                break;
                case Qt::Key_2:
                {
                    if(Inventory_UI::getInstance()->visiability)
                        this->player->use(1);
                }
                break;
                case Qt::Key_3:
                {
                    if(Inventory_UI::getInstance()->visiability)
                        this->player->use(2);
                }
                break;
                case Qt::Key_4:
                {
                    if(Inventory_UI::getInstance()->visiability)
                        this->player->use(3);
                }
                break;
                case Qt::Key_5:
                {
                    if(Inventory_UI::getInstance()->visiability)
                        this->player->use(4);
                }
                break;
                case Qt::Key_6:
                {
                    if(Inventory_UI::getInstance()->visiability)
                        this->player->use(5);
                }
                break;
            }
        }
        break;
        case Game::Battle:
        {
            if(Game::getInstance()->getCurrentTurn() == Game::PLAYER){                 
                switch(keyEvent->key()){
                    case Qt::Key_Z: //Fire attack
                    {
                        if(this->player->getManaValue() >= 0.1f)
                        {
                            this->player->change_mana_by(-0.1f);
                            this->player->current_enemy->receiveDamage(DAMAGE_TYPES::FIRE, this->player->getSkillValue(DAMAGE_TYPES::FIRE));
                            Battle_UI::getInstance()->setActiveSkill(FIRE);
                        }
                    }
                    break;
                    case Qt::Key_X: //Ice attack
                    {
                        if(this->player->getManaValue() >= 0.15f)
                        {
                            this->player->change_mana_by(-0.15f);
                            this->player->current_enemy->receiveDamage(DAMAGE_TYPES::ICE, this->player->getSkillValue(DAMAGE_TYPES::ICE));
                            Battle_UI::getInstance()->setActiveSkill(ICE);
                        }
                    }
                    break;
                    case Qt::Key_C: //Lightning attack
                    {
                        if(this->player->getManaValue() >= 0.25f)
                        {
                            this->player->change_mana_by(-0.25f);
                            this->player->current_enemy->receiveDamage(DAMAGE_TYPES::LIGHTNING, this->player->getSkillValue(DAMAGE_TYPES::LIGHTNING));
                            Battle_UI::getInstance()->setActiveSkill(LIGHTNING);
                        }
                    }
                    break;                    
                    case Qt::Key_F: //Intimidation magic
                    {
                        if(this->player->getManaValue() >= 0.5f)
                        {
                            this->player->change_mana_by(-0.5f);
                            this->player->current_enemy->receiveDamage(DAMAGE_TYPES::INTIMIDATION, this->player->getSkillValue(DAMAGE_TYPES::INTIMIDATION));
                            Battle_UI::getInstance()->setActiveSkill(INTIMIDATION);
                        }
                    }
                    break;
                    case Qt::Key_Space:
                        this->player->current_enemy->receiveDamage(DAMAGE_TYPES::NONE, 0.0f);
                    break;
                    case Qt::Key_Q:
                        Game::getInstance()->endBattle();
                        Game::getInstance()->gameState = Game::Adventure;
                    break;
                    case Qt::Key_1:
                    {
                        this->player->use(0);
                    }
                    break;
                    case Qt::Key_2:
                    {
                        this->player->use(1);
                    }
                    break;
                    case Qt::Key_3:
                    {
                        this->player->use(2);
                    }
                    break;
                    case Qt::Key_4:
                    {
                        this->player->use(3);
                    }
                    break;
                    case Qt::Key_5:
                    {
                        this->player->use(4);
                    }
                    break;
                    case Qt::Key_6:
                    {
                        this->player->use(5);
                    }
                    break;
                }
            }
        }
        break;
        case Game::Paused:
        {

        }
        break;
        case Game::DEAD:
        {
            if(keyEvent->key() == Qt::Key_R){
                Game::getInstance()->restart();
            }
        }
        break;
        case Game::END:
        {

        }
        break;
        case Game::START:
        {
            if(keyEvent->key() == Qt::Key_Space)
                Game::getInstance()->gameState = Game::Adventure;
        }
        break;
        case Game::Trade:
        {
            switch (keyEvent->key()) {
                case Qt::Key_T:
                {
                    Trader_UI::getInstance()->state = Trader_UI::TRADER;
                }
                break;
                case Qt::Key_I:
                {
                    Trader_UI::getInstance()->state = Trader_UI::PLAYER;
                }
                break;
                case Qt::Key_1:
                {
                    if(Trader_UI::getInstance()->state == Trader_UI::TRADER){
                        Trader::getInstance()->buyItem(0);
                    }else if(Trader_UI::getInstance()->state == Trader_UI::PLAYER){
                        Player::getInstance()->cellItem(0);
                    }
                }
                break;
                case Qt::Key_2:
                {
                    if(Trader_UI::getInstance()->state == Trader_UI::TRADER){
                        Trader::getInstance()->buyItem(1);
                    }else if(Trader_UI::getInstance()->state == Trader_UI::PLAYER){
                        Player::getInstance()->cellItem(1);
                    }
                }
                break;
                case Qt::Key_3:
                {
                    if(Trader_UI::getInstance()->state == Trader_UI::TRADER){
                        Trader::getInstance()->buyItem(2);
                    }else if(Trader_UI::getInstance()->state == Trader_UI::PLAYER){
                        Player::getInstance()->cellItem(2);
                    }
                }
                break;
                case Qt::Key_4:
                {
                    if(Trader_UI::getInstance()->state == Trader_UI::TRADER){
                        Trader::getInstance()->buyItem(3);
                    }else if(Trader_UI::getInstance()->state == Trader_UI::PLAYER){
                        Player::getInstance()->cellItem(3);
                    }
                }
                break;
                case Qt::Key_5:
                {
                    if(Trader_UI::getInstance()->state == Trader_UI::TRADER){
                        Trader::getInstance()->buyItem(4);
                    }else if(Trader_UI::getInstance()->state == Trader_UI::PLAYER){
                        Player::getInstance()->cellItem(4);
                    }
                }
                break;
                case Qt::Key_6:
                {
                    if(Trader_UI::getInstance()->state == Trader_UI::TRADER){
                        Trader::getInstance()->buyItem(5);
                    }else if(Trader_UI::getInstance()->state == Trader_UI::PLAYER){
                        Player::getInstance()->cellItem(5);
                    }
                }
                break;
                case Qt::Key_Space:
                {
                    Game::getInstance()->gameState = Game::Adventure;
                }
                break;
            }
        }
        break;
    }   
}

GameScene::GameScene() : QGraphicsScene()
{
    Game::getInstance()->items_scale = QApplication::desktop()->width() / 10;
    GameMap* gameMap = GameMap::getInstance();

    this->player = Player::getInstance();    

    this->player->moveItTo(Game::getInstance()->items_scale * 4.5, Game::getInstance()->items_scale * 2.5);

    this->addItem(Background::getInstance());
    this->addItem(new ObjectsDrawer());
    this->addItem(this->player);
    this->addItem(QuestLogger::getInstance());
    this->addItem(Battle_UI::getInstance());
    this->addItem(Notifications::getInstance());
    this->addItem(Stat_UI::getInstance());
    this->addItem(Inventory_UI::getInstance());
    this->addItem(Trader_UI::getInstance());


    QuestLogger::getInstance()->addQuest("Путь в глушь", "Найдите путь в глубь леса.");

    //OBJECTS SPAWN
    //start location
    gameMap->spawn_enemy(11, 3, Textures::SLIME, "Слизь", [](){
        Player::getInstance()->putMoney(10);
    }, 0.01f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.02f);
    gameMap->spawn_enemy(16, 5, Textures::SKELETON, "Скелет", [](){
        Player::getInstance()->putMoney(10);
    }, 0.05f, 0.0001f, 0.0f, 0.0f, 0.0f, 0.0f, 0.02f);
    gameMap->spawn_enemy(16, 3, Textures::SKELETON, "Скелет", [](){
        Player::getInstance()->putMoney(15);
    }, 0.05f, 0.0001f, 0.0f, 0.0f, 0.0f, 0.0f, 0.02f);

    //trader location
    gameMap->spawn_enemy(15, 15, Textures::SKELETON, "Скелет", [](){
        Player::getInstance()->putMoney(10);
    }, 0.1f, 0.001f, 0.0f, 0.05f, 0.1f, 0.1f, 0.5f);
    gameMap->spawn_enemy(17, 17, Textures::SKELETON, "Скелет", [](){
        Player::getInstance()->putMoney(15);
    }, 0.1f, 0.1f, 0.0f, 0.1f, 0.1f, 0.01f, 0.8f);
    gameMap->spawn_enemy(11, 15, Textures::SKELETON, "Скелет", [](){
        Player::getInstance()->putMoney(15);
    }, 0.0f, 0.0f, 0.1f, 0.1f, 0.1f, 0.1f, 1.0f);
    gameMap->spawn_enemy(15, 18, Textures::SKELETON, "Скелет", [](){
        Player::getInstance()->putMoney(20);
    }, 0.1f, 0.1f, 0.0f, 0.15f, 0.02f, 0.01f, 1.0f);
    gameMap->spawn_enemy(12, 19, Textures::SKELETON, "Скелет", [](){
        Player::getInstance()->putMoney(25);
    }, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 1.0f);
    //adventurer location
    gameMap->spawn_enemy(22, 15, Textures::SKELETON, "Скелет", [](){
        Player::getInstance()->putMoney(25);
    }, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 1.0f);
    //gargoyle location
    gameMap->spawn_enemy(15, 21, Textures::DEAD_MAN, "Мертвец", [](){
        Player::getInstance()->putMoney(25);
    }, 0.1f, 0.25f, 0.1f, 0.0f, 0.2f, 0.0f, 0.8f);
    //knight location
    gameMap->spawn_enemy(7, 11, Textures::GOLDEN_SKELETON, "Светящийся скелет", [](){
        Player::getInstance()->putMoney(35);
    }, 0.0f, 0.01f, 0.25f, 0.2f, 0.2f, 0.3f, 1.0f);
    gameMap->spawn_enemy(7, 11, Textures::GOLDEN_SKELETON, "Светящийся скелет", [](){
        Player::getInstance()->putMoney(35);
    }, 0.0f, 0.01f, 0.25f, 0.2f, 0.2f, 0.3f, 1.0f);
    //near castle location
    gameMap->spawn_enemy(8, 20, Textures::SKELETON, "Скелет", [](){
        Player::getInstance()->putMoney(35);
    }, 0.1f, 0.4f, 0.2f, 0.3f, 0.15f, 0.10f, 1.0f);
    gameMap->spawn_enemy(9, 22, Textures::SKELETON, "Скелет", [](){
        Player::getInstance()->putMoney(35);
    }, 0.2f, 0.3f, 0.4f, 0.25f, 0.3f, 0.2f, 1.0f);
    gameMap->spawn_enemy(4, 21, Textures::SKELETON, "Скелет", [](){
        Player::getInstance()->putMoney(35);
    }, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 1.0f);
    gameMap->spawn_enemy(5, 20, Textures::GRAVE_DEFENDER, "Страж гробницы", [](){
        Player::getInstance()->putMoney(45);
    }, 0.3f, 0.25f, 0.1f, 0.3f, 0.3f, 0.3f, 0.8f);
    //treasury
    gameMap->spawn_enemy(5, 32, Textures::GRAVE_DEFENDER, "Страж сокровищницы", [](){
        Player::getInstance()->putMoney(50);
    }, 0.4f, 0.25f, 0.1f, 0.2f, 0.2f, 0.2f, 1.5f);
    //main hall
    gameMap->spawn_enemy(10, 31, Textures::GRAVE_DEFENDER, "Страж зала", [](){
        Player::getInstance()->putMoney(50);
    }, 0.4f, 0.3f, 0.15f, 0.25f, 0.25f, 0.25f, 1.5f);
    //portal
    gameMap->spawn_enemy(15, 32, Textures::GRAVE_DEFENDER, "Страж портала", [](){
        Player::getInstance()->putMoney(50);
    }, 0.4f, 0.35f, 0.2f, 0.3f, 0.3f, 0.3f, 1.5f);


    //BOSSES
    gameMap->spawn_enemy(4, 12, Textures::KNIGHT, "Неизвестный рыцарь", [](){                                      //
        Player::getInstance()->putMoney(200);                                                                      //
        SkillBook* book = new SkillBook(0, 0, Textures::DARK_GRASS, "", DAMAGE_TYPES::INTIMIDATION, 0.25f, false); // Knight BOSS
        book->use();                                                                                               //
    }, 0.1f, 0.05f, 0.5f, 1.0f, 1.0f, 0.1f, 1.0f);                                                                 //

    gameMap->spawn_enemy(22, 22, Textures::GARGOYLE, "Неизвестное создание", [](){                                 //
        Player::getInstance()->putMoney(100);                                                                      //
        SkillBook* book = new SkillBook(0, 0, Textures::DARK_GRASS, "", DAMAGE_TYPES::INTIMIDATION, 0.25f, false); // Gargoyle BOSS
        book->use();                                                                                               //
    }, 0.25f, 0.01f, 0.01f, 0.1f, 1.0f, 1.0f, 1.0f);                                                               //

    gameMap->spawn_enemy(22, 15, Textures::ADVENTURER, "Скелет авантюриста", [](){                                 //
        Player::getInstance()->putMoney(50);                                                                       //
        SkillBook* book = new SkillBook(0, 0, Textures::DARK_GRASS, "", DAMAGE_TYPES::INTIMIDATION, 0.25f, false); // Adventurer boss
        book->use();                                                                                               //
    }, 0.25f, 0.1f, 0.05f, 0.1f, 0.3f, 0.4f, 1.0f);                                                                //

    gameMap->spawn_enemy(7, 29, Textures::GRAVE_DEFENDER, "Страж", [](){                                           //
        Player::getInstance()->putMoney(200);                                                                      //
        SkillBook* book = new SkillBook(0, 0, Textures::DARK_GRASS, "", DAMAGE_TYPES::INTIMIDATION, 0.25f, false); // Guardian boss
        book->use();                                                                                               //
    }, 0.4f, 0.3f, 0.3f, 0.5f, 0.5f, 0.5f, 1.5f);                                                                  //

    gameMap->spawn_enemy(24, 29, Textures::NECROMANCER, "Некромант", [](){                                         //
        Game::getInstance()->gameState = Game::END;                                                                // Necromancer boss
    }, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f);                                                                  //

    //SKILLBOOKS
    gameMap->spawn_skillbook(9, 3, Textures::DARK_GRASS, "Заклинание отпугивания", DAMAGE_TYPES::INTIMIDATION, 0.1f, false);
    gameMap->spawn_skillbook(6, 12, Textures::DIRTY_ROAD_B_END, "Заклинание молнии", DAMAGE_TYPES::LIGHTNING, 0.25f, false);
    gameMap->spawn_skillbook(12, 17, Textures::DIRTY_ROAD_B_END, "Заклинание искр", DAMAGE_TYPES::LIGHTNING, 0.1f, false);
    gameMap->spawn_skillbook(12, 14, Textures::DIRTY_ROAD_B_END, "Заклинание защиты от искр", DAMAGE_TYPES::LIGHTNING, 0.1f, true);
    gameMap->spawn_skillbook(23, 14, Textures::DIRTY_ROAD_B_END, "Заклинание огненного вихря", DAMAGE_TYPES::FIRE, 0.25f, false);
    gameMap->spawn_skillbook(14, 20, Textures::DIRTY_ROAD_B_END, "Заклинание льда", DAMAGE_TYPES::ICE, 0.1f, false);
    gameMap->spawn_skillbook(16, 17, Textures::DIRTY_ROAD_B_END, "Заклинание огненной защиты", DAMAGE_TYPES::FIRE, 0.1f, true);
    gameMap->spawn_skillbook(23, 21, Textures::DIRTY_ROAD_B_END, "Заклинание льда", DAMAGE_TYPES::ICE, 0.25f, false);
    gameMap->spawn_skillbook(16, 15, Textures::DIRTY_ROAD_B_END, "Заклинание ледянной защиты", DAMAGE_TYPES::ICE, 0.1f, true);
    gameMap->spawn_skillbook(19, 20, Textures::DIRTY_ROAD_B_END, "Заклинание ледянной защиты", DAMAGE_TYPES::ICE, 0.25f, true);
    gameMap->spawn_skillbook(7, 20, Textures::DIRTY_ROAD_B_END, "Заклинание огненной защиты", DAMAGE_TYPES::FIRE, 0.3f, true);
    gameMap->spawn_skillbook(15, 5, Textures::DIRTY_ROAD_B_END, "Заклинание искры", DAMAGE_TYPES::FIRE, 0.1f, false);
    gameMap->spawn_skillbook(4, 33, Textures::DIRTY_ROAD_B_END, "Заклинание защиты от искр", DAMAGE_TYPES::LIGHTNING, 0.25f, true);
    gameMap->spawn_skillbook(4, 34, Textures::DIRTY_ROAD_B_END, "Заклинание искр", DAMAGE_TYPES::LIGHTNING, 0.25f, false);
    gameMap->spawn_skillbook(6, 33, Textures::DIRTY_ROAD_B_END, "Заклинание защиты от льда", DAMAGE_TYPES::ICE, 0.25f, true);
    gameMap->spawn_skillbook(6, 34, Textures::DIRTY_ROAD_B_END, "Заклинание льда", DAMAGE_TYPES::ICE, 0.25f, false);

    //POTIONS
    gameMap->spawn_potion(11, 5, Textures::MANA_POTION, "слабое зелье маны", Potion::MANA_REGEN, 0.1f);
    gameMap->spawn_potion(15, 13, Textures::HEAL_POTION, "среднее зелье лечения", Potion::HEAL, 0.5f);
    gameMap->spawn_potion(6, 10, Textures::HEAL_POTION, "среднее зелье маны", Potion::HEAL, 0.5f);
    gameMap->spawn_potion(4, 20, Textures::HEAL_POTION, "среднее зелье маны", Potion::HEAL, 0.5f);
    gameMap->spawn_potion(23, 20, Textures::HEAL_POTION, "среднее зелье лечения", Potion::HEAL, 0.5f);
    gameMap->spawn_potion(7, 33, Textures::HEAL_POTION, "сильное зелье лечения", Potion::HEAL, 1.0f);
    gameMap->spawn_potion(7, 34, Textures::HEAL_POTION, "среднее зелье лечения", Potion::HEAL, 0.5f);
    gameMap->spawn_potion(8, 33, Textures::MANA_POTION, "сильное зелье маны", Potion::MANA_REGEN, 1.0f);
    gameMap->spawn_potion(8, 34, Textures::MANA_POTION, "среднее зелье маны", Potion::MANA_REGEN, 0.5f);

    //PORTALS    
    gameMap->spawn_portal(18, 3, 14, 10, [](){
        QuestLogger::getInstance()->removeQuest(0);
        QuestLogger::getInstance()->addQuest("Лидер", "Найди некроманта, поднявшего мертвых из могил.");
    }); // tp from player start location to main location
    gameMap->spawn_portal(20, 32, 24, 35, [](){
        QuestLogger::getInstance()->removeQuest(0);
        QuestLogger::getInstance()->addQuest("Финал", "Победи некроманта.");
    }); // tp to final location

    //START
    Game::getInstance()->start();
}
