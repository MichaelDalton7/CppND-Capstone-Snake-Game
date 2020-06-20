#ifndef CONSTANTS_H
#define CONSTANTS_H

enum class Difficulty { kEasyDiff, kNormalDiff, kHardDiff };
enum class GameMode { kStandardMode, kWallMode };
enum class GameState { kMainMenuState, kDifficultyMenuState, kGameModeMenuState, kGameState };
enum class MainMenuOptions { kStartGame, kSetGameMode, kSetDifficulty, kExitGame };

#endif