#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Variabel Global
float postY = 17.0;
float postX = 0.0;
int currentMaze = 1;

// posisi NRP
float nrpPosX = -5.0; 
float nrpPosY = 0.0;

// Variable deteksi tabrakan
bool checkMode = false;
bool isColliding = false;
float checkX = 0.0f;
float checkY = 0.0f;

// Deklarasi fungsi cekTabrakan agar bisa dipanggil di randomizeNRP
bool cekTabrakan(float nextX, float nextY);

void Dinding(float left, float top, float right, float bottom)
{
    // Jika tidak sedang mode cek (sedang menggambar)
    if (!checkMode) {
        glBegin(GL_POLYGON);
        glVertex2f(left, top);
        glVertex2f(right, top);
        glVertex2f(right, bottom);
        glVertex2f(left, bottom);
        glEnd();
    } 
    // Jika sedang dalam mode cek tabrakan
    else {
    float p_left   = checkX - 0.9f; 
    float p_right  = checkX + 0.9f; 
    float p_top    = checkY + 0.9f; 
    float p_bottom = checkY - 0.9f; 

    if (p_left < right && p_right > left && p_bottom < top && p_top > bottom) {
        isColliding = true;
    }
}
}

void NRP(float x, float y)
{
    // Simpan status checkMode asli
    bool tempMode = checkMode;

    checkMode = false; 

    glColor3f(0.0, 0.0, 1.0);
    float s = 0.15;

    // Angka 0
    Dinding(x, y, x + s, y + 5 * s);
    Dinding(x + 2 * s, y, x + 3 * s, y + 5 * s);
    Dinding(x, y, x + 3 * s, y + s);
    Dinding(x, y + 4 * s, x + 3 * s, y + 5 * s);

    // Angka 3
    float ox = x + 4 * s;
    Dinding(ox, y, ox + 3 * s, y + s);
    Dinding(ox, y + 2 * s, ox + 3 * s, y + 3 * s);
    Dinding(ox, y + 4 * s, ox + 3 * s, y + 5 * s);
    Dinding(ox + 2 * s, y, ox + 3 * s, y + 5 * s);

    // Angka 4
    ox = x + 8 * s;
    Dinding(ox, y + 2 * s, ox + s, y + 5 * s);
    Dinding(ox, y + 2 * s, ox + 3 * s, y + 3 * s);
    Dinding(ox + 2 * s, y, ox + 3 * s, y + 5 * s);
}

void maze1()
{
    glColor3f(1.0, 0.0, 0.0);
    // Border
    Dinding(-18.0, 18.0, -1.5, 17.0);
    Dinding(1.5, 18.0, 18.0, 17.0);
    Dinding(-18.0, -17.0, -1.5, -18.0);
    Dinding(1.5, -17.0, 18.0, -18.0);
    Dinding(-18.0, 18.0, -17.0, -18.0);
    Dinding(17.0, 18.0, 18.0, -18.0);  

    // Maze dalam
    Dinding(-14.5, 14.5, -5.5, 13.5);
    Dinding(-2.5, 14.5, 2.5, 13.5);
    Dinding(5.5, 14.5, 10.5, 13.5);
    Dinding(13.5, 14.5, 17.0, 13.5);
    Dinding(-17.0, 10.5, -13.5, 9.5);
    Dinding(-10.5, 10.5, -5.5, 9.5);
    Dinding(1.5, 10.5, 6.5, 9.5);
    Dinding(9.5, 10.5, 17.0, 9.5);
    Dinding(-17.0, 6.5, -9.5, 5.5);
    Dinding(-6.5, 6.5, 2.5, 5.5);
    Dinding(5.5, 6.5, 14.5, 5.5);
    Dinding(-14.5, 2.5, -5.5, 1.5);
    Dinding(-2.5, 2.5, 2.5, 1.5);
    Dinding(-17.0, -1.5, -5.5, -2.5);
    Dinding(1.5, -1.5, 10.5, -2.5);
    Dinding(9.5, -1.5, 14.5, -2.5);
    Dinding(-14.5, -5.5, -9.5, -6.5);
    Dinding(-10.5, -5.5, -1.5, -6.5);
    Dinding(1.5, -5.5, 10.5, -6.5);
    Dinding(13.5, -5.5, 17.0, -6.5);
    Dinding(-6.5, -9.5, 1.5, -10.5);
    Dinding(-17.0, -9.5, -9.5, -10.5);
    Dinding(1.5, -9.5, 6.5, -10.5);
    Dinding(9.5, -9.5, 14.5, -10.5);
    Dinding(-17.0, -13.5, -13.5, -14.5);
    Dinding(-10.5, -13.5, -1.5, -14.5);
    Dinding(5.5, -13.5, 10.5, -14.5);
    Dinding(-14.5, 14.5, -13.5, 9.5);
    Dinding(-14.5, 2.5, -13.5, -6.5);
    Dinding(-14.5, -9.5, -13.5, -14.5);
    Dinding(-10.5, 17.0, -9.5, 13.5);
    Dinding(-10.5, 10.5, -9.5, 5.5);
    Dinding(-10.5, -1.5, -9.5, -6.5);
    Dinding(-10.5, -9.5, -9.5, -14.5);
    Dinding(-6.5, 10.5, -5.5, 5.5);
    Dinding(-6.5, 6.5, -5.5, 1.5);
    Dinding(-6.5, -5.5, -5.5, -10.5);
    Dinding(-2.5, 14.5, -1.5, 9.5);
    Dinding(-2.5, 6.5, -1.5, -2.5);
    Dinding(5.5, 10.5, 6.5, 5.5);
    Dinding(5.5, 6.5, 6.5, -10.5);
    Dinding(9.5, 14.5, 10.5, 9.5);
    Dinding(9.5, 6.5, 10.5, 1.5);
    Dinding(9.5, -1.5, 10.5, -6.5);
    Dinding(9.5, -9.5, 10.5, -14.5);
    Dinding(13.5, 6.5, 14.5, 1.5);
    Dinding(13.5, 2.5, 14.5, -2.5);
}

void maze2()
{
    glColor3f(0.0, 0.0, 1.0);
    // Border
    Dinding(-18.0, 18.0, -1.5, 17.0);
    Dinding(1.5, 18.0, 18.0, 17.0);
    Dinding(-18.0, -17.0, -1.5, -18.0);
    Dinding(1.5, -17.0, 18.0, -18.0);
    Dinding(-18.0, 18.0, -17.0, -18.0); 
    Dinding(17.0, 18.0, 18.0, -18.0); 

    // Maze horizontal dalam
    Dinding(-18.0, 14.5, -13.5, 13.5);
    Dinding(-6.5, 14.5, -1.5, 13.5);
    Dinding(1.5, 14.5, 6.5, 13.5);
    Dinding(13.5, 14.5, 18.0, 13.5);
    Dinding(-14.5, 10.5, -5.5, 9.5);
    Dinding(5.5, 10.5, 14.5, 9.5);
    Dinding(-18.0, 6.5, -13.5, 5.5);
    Dinding(-2.5, 6.5, 2.5, 5.5);
    Dinding(13.5, 6.5, 18.0, 5.5);
    Dinding(-10.5, 2.5, -1.5, 1.5);
    Dinding(1.5, 2.5, 10.5, 1.5);
    Dinding(-18.0, -1.5, -9.5, -2.5);
    Dinding(9.5, -1.5, 18.0, -2.5);
    Dinding(-10.5, -5.5, -5.5, -6.5);
    Dinding(-2.5, -5.5, 2.5, -6.5);
    Dinding(5.5, -5.5, 10.5, -6.5);
    Dinding(-18.0, -9.5, -13.5, -10.5);
    Dinding(-6.5, -9.5, -1.5, -10.5);
    Dinding(1.5, -9.5, 6.5, -10.5);
    Dinding(13.5, -9.5, 18.0, -10.5);
    Dinding(-14.5, -13.5, -9.5, -14.5);
    Dinding(-2.5, -13.5, 2.5, -14.5);
    Dinding(9.5, -13.5, 14.5, -14.5);

    // Maze vertikal dalam
    Dinding(-14.5, 14.5, -13.5, 9.5);
    Dinding(-14.5, 6.5, -13.5, 1.5);
    Dinding(-14.5, -1.5, -13.5, -6.5);
    Dinding(-14.5, -9.5, -13.5, -14.5);
    Dinding(-10.5, 18.0, -9.5, 13.5);
    Dinding(-10.5, -13.5, -9.5, -18.0);
    Dinding(-6.5, 10.5, -5.5, 5.5);
    Dinding(-6.5, 2.5, -5.5, -2.5);
    Dinding(-6.5, -5.5, -5.5, -10.5);
    Dinding(-2.5, 14.5, -1.5, 9.5);
    Dinding(-2.5, 2.5, -1.5, -2.5);
    Dinding(-2.5, -9.5, -1.5, -14.5);
    Dinding(1.5, 14.5, 2.5, 9.5);
    Dinding(1.5, 2.5, 2.5, -2.5);
    Dinding(1.5, -9.5, 2.5, -14.5);
    Dinding(5.5, 10.5, 6.5, 5.5);
    Dinding(5.5, 2.5, 6.5, -2.5);
    Dinding(5.5, -5.5, 6.5, -10.5);
    Dinding(9.5, 18.0, 10.5, 13.5);
    Dinding(9.5, -13.5, 10.5, -18.0);
    Dinding(13.5, 14.5, 14.5, 9.5);
    Dinding(13.5, 6.5, 14.5, 1.5);
    Dinding(13.5, -1.5, 14.5, -6.5);
    Dinding(13.5, -9.5, 14.5, -14.5);
}

// Random NRP
void randomizeNRP()
{ 
    float randX, randY;
    bool aman = false;

    // Loop sampai posisi NRP tidak menabrak dinding
    while (!aman) {
        // Acak koordinat antara -15 sampai 15
        randX = (float)(rand() % 300) / 10.0 - 15.0;
        randY = (float)(rand() % 300) / 10.0 - 15.0;

        // Gunakan fungsi cekTabrakan untuk verifikasi posisi baru
        if (!cekTabrakan(randX, randY)) {
            nrpPosX = randX;
            nrpPosY = randY;
            aman = true; 
        }
    }
}

// Fungsi cek tabrakan
bool cekTabrakan(float nextX, float nextY)
{
    // cek apakah ada dinding
    checkMode = true;
    isColliding = false;
    checkX = nextX;
    checkY = nextY;

    // Panggil maze
    if (currentMaze == 1) maze1();
    else maze2();

    // matikan fungsi
    checkMode = false;

    return isColliding;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (currentMaze == 1) {
        maze1();
    } else {
        maze2();
    }

    // Gambar NRP
    NRP(nrpPosX, nrpPosY);

    // Player
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.9 + postX, 0.9 + postY);
    glVertex2f(0.9 + postX, 0.9 + postY);
    glVertex2f(0.9 + postX, -0.9 + postY);
    glVertex2f(-0.9 + postX, -0.9 + postY);
    glEnd();

    glFlush();
}

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-18.0, 18.0, -18.0, 18.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void input(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q') exit(0);

    float nextX = postX;
    float nextY = postY;

    if (key == 'w' || key == 'W') nextY += 0.5;
    if (key == 's' || key == 'S') nextY -= 0.5;
    if (key == 'a' || key == 'A') nextX -= 0.5;
    if (key == 'd' || key == 'D') nextX += 0.5;

    // Cek apakah posisi ini berpotensi menabrak dinding, jika tidak maka update posisi
    if (nextX != postX || nextY != postY) {
        if (!cekTabrakan(nextX, nextY)) {
            postX = nextX;
            postY = nextY;
        }
    }

    if (key == 'c' || key == 'C')
    {
        currentMaze = (currentMaze == 1) ? 2 : 1;
        randomizeNRP(); // Acak ulang posisi NRP saat ganti maze
        postX = 0.0;
        postY = 17.0;
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(750, 750);
    glutCreateWindow("Maze Game - NRP Random Safe");

    myinit();
    
    // Panggil random NRP setelah init agar OpenGL context siap
    randomizeNRP();

    glutDisplayFunc(display);
    glutKeyboardFunc(input);

    glutMainLoop();
    return 0;
}