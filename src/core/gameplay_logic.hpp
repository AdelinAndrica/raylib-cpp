#pragma once
#include <algorithm>

class GameState;
class Map;
class Player;

// Această funcție se ocupă de reacția la coliziuni și modifică gameState
void HandleGameplayLogic(GameState &gameState);
// Verifică dacă player-ul a intrat într-o zonă de tranziție
void CheckPlayerTransition(Map &map, Player &player);