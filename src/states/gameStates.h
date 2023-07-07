#ifndef GAME_STATES_H
#define GAME_STATES_H

enum {
    STATE_MENU,
    STATE_PAUSED,
    STATE_GAMEOVER,
    STATE_WIN,
    STATE_RUNNING,
    STATE_QUITTING,
};

void DrawMenu();
void UpdateMenu();

void UpdateRunning();
void DrawRunning();

void UpdateGameover();
void DrawGameover();

void UpdateWin();
void DrawWin();

void UpdatePaused();
void DrawPaused();

#endif // GAME_STATES_H