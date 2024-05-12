#include "GameData.h"
GameData::GameData() {
    this->player = nullptr;
}
GameData::GameData(Player* player1, Location location1) {
    this->player = player1;
    this->location = location1;
}
//returns updated GameData that contains the player
GameData* GameData::movePlayerToNextLocation(GameData* gameData) {
    Player* player1 = this->player;
    if (gameData->getPlayer() == nullptr) {
        gameData->setPlayer(player1);
        this->player = nullptr;
    }
    return gameData;
}

void GameData::setPlayer(Player* player1) {
    this->player = player1;
}

Player* GameData::getPlayer() const {
    return this->player;
}

Location GameData::getLocation() const {
    return this->location;
}
