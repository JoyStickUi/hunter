#include "game.h"

#include "player.h"
#include "gamescene.h"
#include "gamemap.h"

#include "battle_ui.h"

Game* Game::instance = nullptr;

Game::Game()
{

}

Game* Game::getInstance(){
    if(instance == nullptr)
        instance = new Game();
    return instance;
}

void Game::start()
{
    this->gameState = START;
}

void Game::restart()
{
    Player::getInstance()->restart();
    GameMap::getInstance()->restart();
    this->current_turn = PLAYER;
    Battle_UI::getInstance()->setActiveSkill(NONE);
    this->gameState = Adventure;
}

void Game::startBattle(Enemy *enemy)
{
    Player::getInstance()->current_enemy = enemy;
    Player::getInstance()->change_health_by(0.1f);
    Player::getInstance()->change_mana_by(0.2f);
    this->gameState = this->Battle;
    GameScene::getInstance()->addItem(enemy);
}

void Game::endBattle()
{
    this->gameState = this->Adventure;
    Player::getInstance()->current_enemy = nullptr;
    this->current_turn = PLAYER;
    Battle_UI::getInstance()->setActiveSkill(NONE);
}

void Game::start_enemy_turn()
{
    this->current_turn = ENEMY;
    Player::getInstance()->current_enemy->make_choose();    
}

void Game::start_player_turn()
{
    this->current_turn = PLAYER;
    Player::getInstance()->restore_hp();
    Player::getInstance()->restore_mana();
    Battle_UI::getInstance()->setActiveSkill(NONE);
}

int Game::getCurrentTurn()
{
    return this->current_turn;
}

void Game::playerDeath()
{
    this->gameState = DEAD;
}

void Game::startTrade()
{
    this->gameState = Trade;
}
