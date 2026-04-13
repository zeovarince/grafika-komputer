#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

#define SIZE 9
#define CELL 0.2f

typedef struct {
    int top, bottom, left, right;
} Cell;

Cell maze[SIZE][SIZE];

int playerX, playerY;
int nrpX, nrpY;

void drawRect(float x1, float y1, float x2, float y2){
    glBegin(GL_POLYGON);
        glVertex2f(x1,y1);
        glVertex2f(x2,y1);
        glVertex2f(x2,y2);
        glVertex2f(x1,y2);
    glEnd();
}

void initMaze() {
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            maze[i][j].top = 1;
            maze[i][j].bottom = 1;
            maze[i][j].left = 1;
            maze[i][j].right = 1;
        }
    }
}

void generateMaze() {
    initMaze();

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){

            if(i==0 && j==SIZE-1) continue;

            if(i==0){
                maze[i][j].right = 0;
                maze[i][j+1].left = 0;
            }
            else if(j==SIZE-1){
                maze[i][j].top = 0;
                maze[i-1][j].bottom = 0;
            }
            else{
                if(rand()%2==0){
                    maze[i][j].top = 0;
                    maze[i-1][j].bottom = 0;
                } else {
                    maze[i][j].right = 0;
                    maze[i][j+1].left = 0;
                }
            }
        }
    }

    maze[0][SIZE/2].top = 0;
    maze[SIZE-1][SIZE/2].bottom = 0;
}

void randomNRP(){
    nrpX = rand()%SIZE;
    nrpY = rand()%SIZE;
}

void drawDigit(int d, float x, float y){
    glColor3f(1,0,1); // ungu

    if(d==0){
        glBegin(GL_LINE_LOOP);
            glVertex2f(x, y);
            glVertex2f(x+0.04f, y);
            glVertex2f(x+0.04f, y-0.06f);
            glVertex2f(x, y-0.06f);
        glEnd();
    }
    else if(d==3){
        glBegin(GL_LINE_STRIP);
            glVertex2f(x, y);
            glVertex2f(x+0.04f, y);
            glVertex2f(x+0.04f, y-0.03f);
            glVertex2f(x, y-0.03f);
            glVertex2f(x+0.04f, y-0.03f);
            glVertex2f(x+0.04f, y-0.06f);
            glVertex2f(x, y-0.06f);
        glEnd();
    }
    else if(d==4){
        glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x, y-0.03f);

            glVertex2f(x, y-0.03f);
            glVertex2f(x+0.04f, y-0.03f);

            glVertex2f(x+0.04f, y);
            glVertex2f(x+0.04f, y-0.06f);
        glEnd();
    }
}

void drawNRP(){
    float cellStartX = -0.9f + nrpX * CELL;
    float cellStartY = 0.9f - nrpY * CELL;

    float digitWidth = 0.14f;
    float digitHeight = 0.06f;

    float x = cellStartX + (CELL - digitWidth) / 2;
    float y = cellStartY - (CELL - digitHeight) / 2;

    drawDigit(0, x, y);
    drawDigit(3, x + 0.05f, y);
    drawDigit(4, x + 0.10f, y);
}

void drawCell(int x, int y){
    float startX = -0.9f + x * CELL;
    float startY = 0.9f - y * CELL;

    glColor3f(0,0,1); // biru

    if(maze[y][x].top)
        drawRect(startX, startY, startX+CELL, startY-0.01f);

    if(maze[y][x].bottom)
        drawRect(startX, startY-CELL, startX+CELL, startY-CELL+0.01f);

    if(maze[y][x].left)
        drawRect(startX, startY, startX+0.01f, startY-CELL);

    if(maze[y][x].right)
        drawRect(startX+CELL, startY, startX+CELL-0.01f, startY-CELL);
}

void drawPlayer(){
    float x = -0.9f + playerX * CELL;
    float y = 0.9f - playerY * CELL;

    glColor3f(0,0,0);
    drawRect(x+0.03f, y-0.03f, x+CELL-0.03f, y-CELL+0.03f);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            drawCell(j,i);
        }
    }

    drawPlayer();
    drawNRP();

    glFlush();
}

void keyboard(unsigned char key, int x, int y){

    if(key=='w'||key=='W'){
        if(maze[playerY][playerX].top==0 && playerY>0)
            playerY--;
    }
    if(key=='s'||key=='S'){
        if(maze[playerY][playerX].bottom==0 && playerY<SIZE-1)
            playerY++;
    }
    if(key=='a'||key=='A'){
        if(maze[playerY][playerX].left==0 && playerX>0)
            playerX--;
    }
    if(key=='d'||key=='D'){
        if(maze[playerY][playerX].right==0 && playerX<SIZE-1)
            playerX++;
    }

    if(key=='c'||key=='C'){
        generateMaze();
        randomNRP();
        playerX = SIZE/2;
        playerY = 0;
    }

    glutPostRedisplay();
}

void init(){
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1,1,-1,1);

    glLineWidth(3);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Maze 9x9 Binary Tree");

    init();

    generateMaze();
    randomNRP();

    playerX = SIZE/2;
    playerY = 0;

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}