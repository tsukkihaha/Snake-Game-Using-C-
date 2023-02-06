#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
using namespace std;

bool gameOver;
const int width = 30;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum direction{ STOP, LEFT, RIGHT, UP, DOWN };
direction dir;
int tailX[100];
int tailY[100];
int nTail;

void setup(){
    gameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    fruitX = rand()%height;
    fruitY = rand()%width;
    score = 0;
}

void draw() {

    system("cls");
    for(int i=0; i<width+2; i++){
        cout << "$";
    }
    cout << endl;

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(j==0) cout << "$";

            if(i==y && j==x) cout << "X";
            else if(i==fruitY && j==fruitX) cout << "o";
            else{
                bool print = false;
                for(int k=0; k<nTail; k++){
                    if(tailX[k]==j && tailY[k]==i){
                        cout << "x";
                        print = true;
                    }
                }
                if(!print) cout << " ";
            }

            if(j==width-1) cout << "$";
        }
        cout << endl;
    }

    for(int i=0; i<width+2; i++){
        cout << "$";
    }
    cout << endl;

    cout << "Score: " << score << endl;

}

void input() {
    if(_kbhit()){
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'w':
            dir = UP;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void logic() {

    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prevX2, prevY2;
    for(int i=1; i<nTail; i++){
        prevX2 = tailX[i];
        prevY2 = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }

    switch (dir)
    {
    // case STOP:
    //     break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    if(x<0 || x>width-1 || y<0 || y>height-1) gameOver=true;

    if(x==fruitX && y==fruitY){
        score++;
        fruitX = rand()%width;
        fruitY = rand()%height;
        nTail++;
    }

    for(int i=0; i<nTail; i++){
        if(tailX[i]==x && tailY[i]==y) gameOver = true;
    }

}

int main() {

    setup();
    while(!gameOver){
        draw();
        input();
        logic();
        Sleep(200);
    }

    return 0;
}