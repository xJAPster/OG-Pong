#pragma once
#include<raylib.h>

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
