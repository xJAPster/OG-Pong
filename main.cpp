#include <iostream>
#include <raylib.h>

using namespace std;

//declaration space
int player1Score=0, player2Score=0, CPUScore=0;
Sound paddle_hit, bounds_hit, point_scored; 
Image menuasset, endasset;
Texture2D menuscr, endscr;
bool menuexit=false;
bool gameover=false;

class Ball{
public:
    float x, y;
    int speedx, speedy;
    int radius;

    void Draw(){
        DrawCircle(x , y, radius, WHITE);
    }

    void Update(); //forward declaration

    void ResetBall(){
        x=GetScreenWidth()/2;
        y=GetScreenHeight()/2;

        int speedreset[2]={-1,1};
        speedx*=speedreset[GetRandomValue(0,1)];
        speedy*=speedreset[GetRandomValue(0,1)];
    }
};

class Player1Paddle{
public:
    float x, y;
    int speed;
    float width, height;

    void Draw(){
        DrawRectangle(x,y,width,height,WHITE);
    }

    void Update(){
        if(IsKeyDown(KEY_W))y-=speed;
        if(IsKeyDown(KEY_S))y+=speed;
        Limit();
    }

protected:
    void Limit(){
        //out of bounds
        if(y<0) y=0;
        if(y+height>=GetScreenHeight()) y=GetScreenHeight()-height;
    }
};

class Player2Paddle : public Player1Paddle{
public:
    void Update(){
        if(IsKeyDown(KEY_UP))y-=speed;
        if(IsKeyDown(KEY_DOWN))y+=speed;
        Limit();
    }
};

class CPU : public Player1Paddle{
public:
    //overriding Update() method
    void Update(int ball_y){
        if(ball_y > y)y+=speed;
        if(ball_y < y)y-=speed;
        Limit();
    }
};

//declaration of objects
Ball ball;
Player1Paddle player1;
Player2Paddle player2;
CPU cpu_paddle;

void menuScreen();
void gameoverScreen();
void singleplayer();
void multiplayer();

int main (){
    //setup
    const int width=1280;
    const int height=800;
    
    InitAudioDevice(); // loading audio sound fx
    paddle_hit = LoadSound("assets/paddle_hit.mp3");
    bounds_hit = LoadSound("assets/boundary_hit.mp3");
    point_scored = LoadSound("assets/point_score.mp3");

    SetTargetFPS(60);
    InitWindow(width, height,"OG Pong!");

    //initializing object attributes
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
    
    //game loop start
    while(!WindowShouldClose()){
        //MAIN MENU SCREEN ----------------------------------------------
        menuScreen();

        //GAME OVER SCREEN ----------------------------------------------
        gameoverScreen();
        if(gameover) break;

        //GAMEPLAY ------------------------------------------------------
        singleplayer();

        //game over condition 
        if(player1Score==5||player2Score==5||CPUScore==5) gameover=true;
        EndDrawing();
    }
    
    //handling opened resources
    CloseWindow();
    UnloadSound(paddle_hit);
    UnloadSound(bounds_hit);
    UnloadSound(point_scored);
    UnloadImage(menuasset);
    UnloadImage(endasset);
    UnloadTexture(menuscr);
    UnloadTexture(endscr);

    return 0;
}

//forward declaration definitions
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

void menuScreen(){
    while(!WindowShouldClose() && menuexit==false){
        if(IsKeyPressed(KEY_ENTER)){
            menuexit=true;
            return;
        }

        BeginDrawing();

        ClearBackground(BLACK);
        menuasset=LoadImage("assets/MENUASSET2.png");
        menuscr=LoadTextureFromImage(menuasset);

        DrawTexture(menuscr,0,0,WHITE);

        EndDrawing();

        if(WindowShouldClose())gameover=true;
    }
}

void gameoverScreen(){
    while(!WindowShouldClose() && !IsKeyPressed(KEY_ENTER) && gameover==true){
        BeginDrawing();

        endasset = LoadImage("assets/ENDSCREEN_ASSET1.png");
        endscr=LoadTextureFromImage(endasset);
        DrawTexture(endscr,0,0,WHITE);

        EndDrawing();

        if(IsKeyPressed(KEY_R)){
            gameover=false;
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

void multiplayer(){ //to be implemented
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
    DrawText(TextFormat("YOU: %i", player1Score), (GetScreenWidth())/4-20, 20, 30, WHITE);
    DrawText(TextFormat("CPU: %i", player2Score), 3*(GetScreenWidth())/4-20, 20, 30, WHITE);

    DrawLine((GetScreenWidth())/2, GetScreenHeight(), (GetScreenWidth())/2, 0, WHITE);
    ClearBackground(BLACK);
    HideCursor();
}