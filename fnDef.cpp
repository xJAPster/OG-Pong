#include "fnHeader.h"
#include<raylib.h>

int player1Score=0, player2Score=0, CPUScore=0;
bool menuexit=false;
bool gameover=false;
bool pickMade=false;
bool gmode=false;

Image menuasset, endasset, modeasset;
Texture2D menuscr, endscr, modescr;
Sound paddle_hit, bounds_hit, point_scored; 

Ball ball;
Player1Paddle player1;
Player2Paddle player2;
CPU cpu_paddle;


void Ball::Update(){
    x+=speedx;
    y+=speedy;

    //window edge collision
    if(y+radius >= GetScreenHeight() || y-radius <=0){
        speedy*=-1;
        PlaySound(bounds_hit);
    }

    //scoring
    if(x+radius >= GetScreenWidth()){
        player1Score++;
        PlaySound(point_scored);
        ResetBall();
    }
    if(x-radius <=0){
        player2Score++;
        PlaySound(point_scored);
        CPUScore++;
        ResetBall();
    }
}

void initVar(const int& width, const int& height){
    ball.radius=15;
    ball.x=width/2;
    ball.y=height/2;
    ball.speedx=8;
    ball.speedy=8;

    player1.x=10;
    player1.y=height/2-60;
    player1.width=25;
    player1.height=120;
    player1.speed=7;

    player2.x=width-35;
    player2.y=height/2-60;
    player2.width=25;
    player2.height=120;
    player2.speed=7;

    cpu_paddle.x=width-35;
    cpu_paddle.y=height/2-60;
    cpu_paddle.width=25;
    cpu_paddle.height=120;
    cpu_paddle.speed=7;
}

void menuScreen(){
    while(!WindowShouldClose() && menuexit==false){
        if(IsKeyPressed(KEY_ENTER)){
            menuexit=true;
            return;
        }

        BeginDrawing();

        ClearBackground(BLACK);
        DrawTexture(menuscr,0,0,WHITE);

        EndDrawing();

        if(WindowShouldClose())gameover=true;
    }
}

void modeChoose(){
    while(!WindowShouldClose() && menuexit && !pickMade){
        BeginDrawing();

        ClearBackground(BLACK);
        DrawTexture(modescr,0,0,WHITE);

        EndDrawing();

        if(IsKeyPressed(KEY_ONE)){
            pickMade=1;
            gmode=0;
        }

        else if(IsKeyPressed(KEY_TWO)){
            pickMade=1;
            gmode=1;
        }

        if(WindowShouldClose())gameover=true;
    }
}

void gameoverScreen(){
    while(!WindowShouldClose() && !IsKeyPressed(KEY_ENTER) && gameover==true){
        BeginDrawing();

        DrawTexture(endscr,0,0,WHITE);

        EndDrawing();

        if(IsKeyPressed(KEY_R)){
            gameover=false;
            pickMade=false;
            player1Score=0;
            player2Score=0;
            CPUScore=0;
            return;
        }
    }
}

void singleplayer(){
    BeginDrawing();
    
    //drawing the ball
    ball.Update();
    ball.Draw();
    
    //drawing the paddles
    player1.Draw();
    player1.Update();

    cpu_paddle.Draw();
    cpu_paddle.Update(ball.y);

    //collision detection
    if(CheckCollisionCircleRec(Vector2{ball.x,ball.y}, 15, Rectangle{player1.x, player1.y,player1.width,player1.height})){
        ball.speedx*=-1;
        PlaySound(paddle_hit);
    }
    if(CheckCollisionCircleRec(Vector2{ball.x,ball.y}, 15, Rectangle{cpu_paddle.x, cpu_paddle.y,cpu_paddle.width,cpu_paddle.height})){
        ball.speedx*=-1;
        PlaySound(paddle_hit);
    }
    
    //scoreboard
    DrawText(TextFormat("YOU: %i", player1Score), (GetScreenWidth())/4-20, 20, 30, WHITE);
    DrawText(TextFormat("CPU: %i", CPUScore), 3*(GetScreenWidth())/4-20, 20, 30, WHITE);

    DrawLine((GetScreenWidth())/2, GetScreenHeight(), (GetScreenWidth())/2, 0, WHITE);
    ClearBackground(BLACK);
    HideCursor();
}

void multiplayer(){ 
    BeginDrawing();
    
    //drawing the ball
    ball.Update();
    ball.Draw();
    
    //drawing the paddles
    player1.Draw();
    player1.Update();

    player2.Draw();
    player2.Update();

    //collision detection
    if(CheckCollisionCircleRec(Vector2{ball.x,ball.y}, 15, Rectangle{player1.x, player1.y,player1.width,player1.height})){
        ball.speedx*=-1;
        PlaySound(paddle_hit);
    }
    if(CheckCollisionCircleRec(Vector2{ball.x,ball.y}, 15, Rectangle{player2.x, player2.y, player2.width, player2.height})){
        ball.speedx*=-1;
        PlaySound(paddle_hit);
    }
    
    //scoreboard
    DrawText(TextFormat("P1: %i", player1Score), (GetScreenWidth())/4-20, 20, 30, WHITE);
    DrawText(TextFormat("P2: %i", player2Score), 3*(GetScreenWidth())/4-20, 20, 30, WHITE);

    DrawLine((GetScreenWidth())/2, GetScreenHeight(), (GetScreenWidth())/2, 0, WHITE);
    ClearBackground(BLACK);
    HideCursor();
}