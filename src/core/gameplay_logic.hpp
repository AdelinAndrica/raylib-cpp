#pragma once
#include <algorithm>

class Level;
class GameState;

// Această funcție se ocupă de reacția la coliziuni și modifică gameState
void HandleGameplayLogic(Level &level, GameState &gameState);