#pragma once
#include<bits/stdc++.h>
#include<raylib.h>
#include "entities.hpp"

extern int player1Score, player2Score, CPUScore;
extern Sound paddle_hit, bounds_hit, point_scored; 
extern Image menuasset, endasset, modeasset;
extern Texture2D menuscr, endscr, modescr;

extern bool menuexit;
extern bool gameover;
extern bool pickMade;
extern bool gmode;

extern Ball ball;
extern Player1Paddle player1;
extern Player2Paddle player2;
extern CPU cpu_paddle;


void initVar(const int& width, const int& height);
void menuScreen();
void modeChoose();
void gameoverScreen();
void singleplayer();
void multiplayer();
