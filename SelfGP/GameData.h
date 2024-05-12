
#ifndef CSC340_GROUP_PROJECT_GAMEDATA_H
#define CSC340_GROUP_PROJECT_GAMEDATA_H
#include "Location.h"
#include "Player.h"

class GameData {
private:
    Player* player;
    Location location;
    void setPlayer(Player* player);
public:
    GameData();
    GameData(Player* player1, Location location1);
    Player* getPlayer() const;
    Location getLocation() const;
    GameData* movePlayerToNextLocation(GameData* gameData);
};


#endif //CSC340_GROUP_PROJECT_GAMEDATA_H
