#include "fnHeader.hpp"
using namespace std;

int main (){
    //setup
    const int width=1280;
    const int height=800;

    InitAudioDevice(); // loading audio sound fx
    SetTargetFPS(60);
    InitWindow(width, height,"OG Pong!");

    paddle_hit = LoadSound("assets/sfx/paddle_hit.mp3");
    bounds_hit = LoadSound("assets/sfx/boundary_hit.mp3");
    point_scored = LoadSound("assets/sfx/point_score.mp3");

    menuasset=LoadImage("assets/vfx/MENUASSET2.png");
    menuscr=LoadTextureFromImage(menuasset);
    modeasset=LoadImage("assets/vfx/GAMEMODEASSET1.png");
    modescr=LoadTextureFromImage(modeasset);
    endasset = LoadImage("assets/vfx/ENDSCREEN_ASSET1.png");
    endscr=LoadTextureFromImage(endasset);

    //initializing object attributes
    initVar(width, height);

    //game loop start
    while(!WindowShouldClose()){
        if(!menuexit)menuScreen();
        if(menuexit && !pickMade)modeChoose();

        gameoverScreen();
        if(gameover) break;

        if(!gmode)singleplayer();
        else multiplayer();

        //game over condition 
        if(player1Score==5||player2Score==5||CPUScore==5) gameover=true;
        EndDrawing();
    }
    
    //handling opened resources
    UnloadSound(paddle_hit);
    UnloadSound(bounds_hit);
    UnloadSound(point_scored);
    
    UnloadImage(menuasset);
    UnloadTexture(menuscr);
    UnloadImage(modeasset);
    UnloadTexture(modescr);
    UnloadImage(endasset);
    UnloadTexture(endscr);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}