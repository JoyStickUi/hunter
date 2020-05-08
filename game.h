#ifndef GAME_H
#define GAME_H

#include "enemy.h"

class Game
{
public:    
    enum GameStates{
        Paused,
        Battle,
        Adventure,
        DEAD,
        END,
        START,
        Trade
    };
    enum  MEMBERS{
        PLAYER,
        ENEMY
    };
    unsigned gameState = GameStates::START;
    static Game *getInstance();
    int items_scale = 0;
    void start();
    void restart();
    void startBattle(Enemy* enemy);
    void endBattle();
    void start_enemy_turn();
    void start_player_turn();
    int getCurrentTurn();
    void playerDeath();
    void startTrade();
private:
    Game();

    static Game* instance;

    int current_turn = PLAYER;
};

#endif // GAME_H
