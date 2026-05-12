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

// Variabel rotasi NRP
float nrpRotX = 0.0;
float nrpRotY = 0.0;
float nrpRotZ = 0.0;
float nrpRotSpeed = 2.0;
int nrpRotAxis = 0;

// Variable deteksi tabrakan
bool checkMode = false;
bool isColliding = false;
float checkX = 0.0;
float checkY = 0.0;

// Variable status view
bool isIsometric = false;

// Variabel Rotasi maze
float mazeRotX = 0.0;
float mazeRotY = 0.0;

// Deklarasi fungsi cekTabrakan agar bisa dipanggil di randomizeNRP
bool cekTabrakan(float nextX, float nextY);

void Dinding(float left, float top, float right, float bottom, float zFront, float zBack)
{
    // Jika tidak dalam mode cek tabrakan, gambar dinding seperti biasa
    if (!checkMode)
    {
        // Sisi DEPAN (z = zFront)
        glBegin(GL_POLYGON);
        glVertex3f(left, top, zFront);
        glVertex3f(right, top, zFront);
        glVertex3f(right, bottom, zFront);
        glVertex3f(left, bottom, zFront);
        glEnd();

        // Sisi BELAKANG (z = zBack)
        glBegin(GL_POLYGON);
        glVertex3f(right, top, zBack);
        glVertex3f(left, top, zBack);
        glVertex3f(left, bottom, zBack);
        glVertex3f(right, bottom, zBack);
        glEnd();

        // Sisi ATAS (y = top)
        glBegin(GL_POLYGON);
        glVertex3f(left, top, zFront);
        glVertex3f(right, top, zFront);
        glVertex3f(right, top, zBack);
        glVertex3f(left, top, zBack);
        glEnd();

        // Sisi BAWAH (y = bottom)
        glBegin(GL_POLYGON);
        glVertex3f(left, bottom, zBack);
        glVertex3f(right, bottom, zBack);
        glVertex3f(right, bottom, zFront);
        glVertex3f(left, bottom, zFront);
        glEnd();

        // Sisi KIRI (x = left)
        glBegin(GL_POLYGON);
        glVertex3f(left, top, zBack);
        glVertex3f(left, top, zFront);
        glVertex3f(left, bottom, zFront);
        glVertex3f(left, bottom, zBack);
        glEnd();

        // Sisi KANAN (x = right)
        glBegin(GL_POLYGON);
        glVertex3f(right, top, zFront);
        glVertex3f(right, top, zBack);
        glVertex3f(right, bottom, zBack);
        glVertex3f(right, bottom, zFront);
        glEnd();
    }
    // Jika dalam mode cek tabrakan, lakukan pengecekan
    else
    {
        float p_left = checkX - 0.9;
        float p_right = checkX + 0.9;
        float p_top = checkY + 0.9;
        float p_bottom = checkY - 0.9;

        if (p_left < right && p_right > left && p_bottom < top && p_top > bottom)
        {
            isColliding = true;
        }
    }
}

// Timer animasi rotasi otomatis
void timerNRP(int value)
{
    if (isIsometric)
    {
        if (nrpRotAxis == 0)
        {
            nrpRotY += nrpRotSpeed;
            if (nrpRotY >= 360.0f)
                nrpRotY -= 360.0f;
        }
        else if (nrpRotAxis == 1)
        {
            nrpRotX += nrpRotSpeed;
            if (nrpRotX >= 360.0f)
                nrpRotX -= 360.0f;
        }
        else
        {
            nrpRotZ += nrpRotSpeed;
            if (nrpRotZ >= 360.0f)
                nrpRotZ -= 360.0f;
        }
        glutPostRedisplay();
    }

    glutTimerFunc(16, timerNRP, 0);
}

// Kontrol axis rotasi via mouse
void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
            nrpRotAxis = 0; // rotasi sumbu Y
        else if (button == GLUT_MIDDLE_BUTTON)
            nrpRotAxis = 1; // rotasi sumbu X
        else if (button == GLUT_RIGHT_BUTTON)
            nrpRotAxis = 2; // rotasi sumbu Z
    }
}

void NRP(float x, float y)
{
    bool tempMode = checkMode;
    checkMode = false;

    glColor3f(0.0, 0.0, 0.0);
    float s = 0.15;
    float zf = 0.5;
    float zb = -0.5;

    // Titik tengah NRP untuk rotasi
    float cx = 0.825;
    float cy = 0.375;

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glTranslatef(cx, cy, 0.0f);
    glRotatef(nrpRotX, 1.0, 0.0, 0.0);
    glRotatef(nrpRotY, 0.0, 1.0, 0.0);
    glRotatef(nrpRotZ, 0.0, 0.0, 1.0);
    glTranslatef(-cx, -cy, 0.0f);

    // ── ANGKA 0 ──
    Dinding(0.00, 0.75, 0.15, 0.00, 0.5, -0.5);
    Dinding(0.30, 0.75, 0.45, 0.00, 0.5, -0.5);
    Dinding(0.00, 0.15, 0.45, 0.00, 0.5, -0.5);
    Dinding(0.00, 0.75, 0.45, 0.60, 0.5, -0.5);

    // ── ANGKA 3 ──
    Dinding(0.60, 0.15, 1.05, 0.00, 0.5, -0.5);
    Dinding(0.60, 0.45, 1.05, 0.30, 0.5, -0.5);
    Dinding(0.60, 0.75, 1.05, 0.60, 0.5, -0.5);
    Dinding(0.90, 0.75, 1.05, 0.00, 0.5, -0.5);

    // ── ANGKA 4 ──
    Dinding(1.20, 0.75, 1.35, 0.30, 0.5, -0.5);
    Dinding(1.20, 0.45, 1.65, 0.30, 0.5, -0.5);
    Dinding(1.50, 0.75, 1.65, 0.00, 0.5, -0.5);

    glPopMatrix();

    checkMode = tempMode;
}

void maze1()
{
    glColor3f(0.0, 0.0, 1.0);
    // Border
    Dinding(-18.0, 18.0, -1.5, 17.0, -1.0, 1.0);
    Dinding(1.5, 18.0, 18.0, 17.0, -1.0, 1.0);
    Dinding(-18.0, -17.0, -1.5, -18.0, -1.0, 1.0);
    Dinding(1.5, -17.0, 18.0, -18.0, -1.0, 1.0);
    Dinding(-18.0, 18.0, -17.0, -18.0, -1.0, 1.0);
    Dinding(17.0, 18.0, 18.0, -18.0, -1.0, 1.0);

    // Maze dalam
    Dinding(-14.5, 14.5, -5.5, 13.5, -1.0, 1.0);
    Dinding(-2.5, 14.5, 2.5, 13.5, -1.0, 1.0);
    Dinding(5.5, 14.5, 10.5, 13.5, -1.0, 1.0);
    Dinding(13.5, 14.5, 17.0, 13.5, -1.0, 1.0);
    Dinding(-17.0, 10.5, -13.5, 9.5, -1.0, 1.0);
    Dinding(-10.5, 10.5, -5.5, 9.5, -1.0, 1.0);
    Dinding(1.5, 10.5, 6.5, 9.5, -1.0, 1.0);
    Dinding(9.5, 10.5, 17.0, 9.5, -1.0, 1.0);
    Dinding(-17.0, 6.5, -9.5, 5.5, -1.0, 1.0);
    Dinding(-6.5, 6.5, 2.5, 5.5, -1.0, 1.0);
    Dinding(5.5, 6.5, 14.5, 5.5, -1.0, 1.0);
    Dinding(-14.5, 2.5, -5.5, 1.5, -1.0, 1.0);
    Dinding(-2.5, 2.5, 2.5, 1.5, -1.0, 1.0);
    Dinding(-17.0, -1.5, -5.5, -2.5, -1.0, 1.0);
    Dinding(1.5, -1.5, 10.5, -2.5, -1.0, 1.0);
    Dinding(9.5, -1.5, 14.5, -2.5, -1.0, 1.0);
    Dinding(-14.5, -5.5, -9.5, -6.5, -1.0, 1.0);
    Dinding(-10.5, -5.5, -1.5, -6.5, -1.0, 1.0);
    Dinding(1.5, -5.5, 10.5, -6.5, -1.0, 1.0);
    Dinding(13.5, -5.5, 17.0, -6.5, -1.0, 1.0);
    Dinding(-6.5, -9.5, 1.5, -10.5, -1.0, 1.0);
    Dinding(-17.0, -9.5, -9.5, -10.5, -1.0, 1.0);
    Dinding(1.5, -9.5, 6.5, -10.5, -1.0, 1.0);
    Dinding(9.5, -9.5, 14.5, -10.5, -1.0, 1.0);
    Dinding(-17.0, -13.5, -13.5, -14.5, -1.0, 1.0);
    Dinding(-10.5, -13.5, -1.5, -14.5, -1.0, 1.0);
    Dinding(5.5, -13.5, 10.5, -14.5, -1.0, 1.0);
    Dinding(-14.5, 14.5, -13.5, 9.5, -1.0, 1.0);
    Dinding(-14.5, 2.5, -13.5, -6.5, -1.0, 1.0);
    Dinding(-14.5, -9.5, -13.5, -14.5, -1.0, 1.0);
    Dinding(-10.5, 17.0, -9.5, 13.5, -1.0, 1.0);
    Dinding(-10.5, 10.5, -9.5, 5.5, -1.0, 1.0);
    Dinding(-10.5, -1.5, -9.5, -6.5, -1.0, 1.0);
    Dinding(-10.5, -9.5, -9.5, -14.5, -1.0, 1.0);
    Dinding(-6.5, 10.5, -5.5, 5.5, -1.0, 1.0);
    Dinding(-6.5, 6.5, -5.5, 1.5, -1.0, 1.0);
    Dinding(-6.5, -5.5, -5.5, -10.5, -1.0, 1.0);
    Dinding(-2.5, 14.5, -1.5, 9.5, -1.0, 1.0);
    Dinding(-2.5, 6.5, -1.5, -2.5, -1.0, 1.0);
    Dinding(5.5, 10.5, 6.5, 5.5, -1.0, 1.0);
    Dinding(5.5, 6.5, 6.5, -10.5, -1.0, 1.0);
    Dinding(9.5, 14.5, 10.5, 9.5, -1.0, 1.0);
    Dinding(9.5, 6.5, 10.5, 1.5, -1.0, 1.0);
    Dinding(9.5, -1.5, 10.5, -6.5, -1.0, 1.0);
    Dinding(9.5, -9.5, 10.5, -14.5, -1.0, 1.0);
    Dinding(13.5, 6.5, 14.5, 1.5, -1.0, 1.0);
    Dinding(13.5, 2.5, 14.5, -2.5, -1.0, 1.0);
}

void maze2()
{
    glColor3f(0.0, 0.0, 1.0);
    // Border
    Dinding(-18.0, 18.0, -1.5, 17.0, -1.0, 1.0);
    Dinding(1.5, 18.0, 18.0, 17.0, -1.0, 1.0);
    Dinding(-18.0, -17.0, -1.5, -18.0, -1.0, 1.0);
    Dinding(1.5, -17.0, 18.0, -18.0, -1.0, 1.0);
    Dinding(-18.0, 18.0, -17.0, -18.0, -1.0, 1.0);
    Dinding(17.0, 18.0, 18.0, -18.0, -1.0, 1.0);

    // Maze horizontal dalam
    Dinding(-18.0, 14.5, -13.5, 13.5, -1.0, 1.0);
    Dinding(-6.5, 14.5, -1.5, 13.5, -1.0, 1.0);
    Dinding(1.5, 14.5, 6.5, 13.5, -1.0, 1.0);
    Dinding(13.5, 14.5, 18.0, 13.5, -1.0, 1.0);
    Dinding(-14.5, 10.5, -5.5, 9.5, -1.0, 1.0);
    Dinding(5.5, 10.5, 14.5, 9.5, -1.0, 1.0);
    Dinding(-18.0, 6.5, -13.5, 5.5, -1.0, 1.0);
    Dinding(-2.5, 6.5, 2.5, 5.5, -1.0, 1.0);
    Dinding(13.5, 6.5, 18.0, 5.5, -1.0, 1.0);
    Dinding(-10.5, 2.5, -1.5, 1.5, -1.0, 1.0);
    Dinding(1.5, 2.5, 10.5, 1.5, -1.0, 1.0);
    Dinding(-18.0, -1.5, -9.5, -2.5, -1.0, 1.0);
    Dinding(9.5, -1.5, 18.0, -2.5, -1.0, 1.0);
    Dinding(-10.5, -5.5, -5.5, -6.5, -1.0, 1.0);
    Dinding(-2.5, -5.5, 2.5, -6.5, -1.0, 1.0);
    Dinding(5.5, -5.5, 10.5, -6.5, -1.0, 1.0);
    Dinding(-18.0, -9.5, -13.5, -10.5, -1.0, 1.0);
    Dinding(-6.5, -9.5, -1.5, -10.5, -1.0, 1.0);
    Dinding(1.5, -9.5, 6.5, -10.5, -1.0, 1.0);
    Dinding(13.5, -9.5, 18.0, -10.5, -1.0, 1.0);
    Dinding(-14.5, -13.5, -9.5, -14.5, -1.0, 1.0);
    Dinding(-2.5, -13.5, 2.5, -14.5, -1.0, 1.0);
    Dinding(9.5, -13.5, 14.5, -14.5, -1.0, 1.0);

    // Maze vertikal dalam
    Dinding(-14.5, 14.5, -13.5, 9.5, -1.0, 1.0);
    Dinding(-14.5, 6.5, -13.5, 1.5, -1.0, 1.0);
    Dinding(-14.5, -1.5, -13.5, -6.5, -1.0, 1.0);
    Dinding(-14.5, -9.5, -13.5, -14.5, -1.0, 1.0);
    Dinding(-10.5, 18.0, -9.5, 13.5, -1.0, 1.0);
    Dinding(-10.5, -13.5, -9.5, -18.0, -1.0, 1.0);
    Dinding(-6.5, 10.5, -5.5, 5.5, -1.0, 1.0);
    Dinding(-6.5, 2.5, -5.5, -2.5, -1.0, 1.0);
    Dinding(-6.5, -5.5, -5.5, -10.5, -1.0, 1.0);
    Dinding(-2.5, 14.5, -1.5, 9.5, -1.0, 1.0);
    Dinding(-2.5, 2.5, -1.5, -2.5, -1.0, 1.0);
    Dinding(-2.5, -9.5, -1.5, -14.5, -1.0, 1.0);
    Dinding(1.5, 14.5, 2.5, 9.5, -1.0, 1.0);
    Dinding(1.5, 2.5, 2.5, -2.5, -1.0, 1.0);
    Dinding(1.5, -9.5, 2.5, -14.5, -1.0, 1.0);
    Dinding(5.5, 10.5, 6.5, 5.5, -1.0, 1.0);
    Dinding(5.5, 2.5, 6.5, -2.5, -1.0, 1.0);
    Dinding(5.5, -5.5, 6.5, -10.5, -1.0, 1.0);
    Dinding(9.5, 18.0, 10.5, 13.5, -1.0, 1.0);
    Dinding(9.5, -13.5, 10.5, -18.0, -1.0, 1.0);
    Dinding(13.5, 14.5, 14.5, 9.5, -1.0, 1.0);
    Dinding(13.5, 6.5, 14.5, 1.5, -1.0, 1.0);
    Dinding(13.5, -1.5, 14.5, -6.5, -1.0, 1.0);
    Dinding(13.5, -9.5, 14.5, -14.5, -1.0, 1.0);
}

// Random NRP
void randomizeNRP()
{
    float safePositionsMaze1[][2] = {
        {-16.0, 16.0},
        {14.0, 16.0},
        {-16.0, -16.0},
        {14.0, -16.0},
        {-1.0, 0.0},
        {-9.0, 8.0},
        {8.0, -8.0},
        {-4.0, -4.0},
        {3.0, 4.0},
        {-17.0, 0.0},
    };

    float safePositionsMaze2[][2] = {
        {-16.0, 16.0},
        {14.0, 16.0},
        {-16.0, -16.0},
        {14.0, -16.0},
        {-1.0, 0.0},
        {-9.0, 8.0},
        {8.0, -8.0},
        {-4.0, -4.0},
        {3.0, 4.0},
        {-17.0, 0.0},
    };

    int jumlah = 10;
    bool ditemukan = false;

    while (!ditemukan)
    {
        int idx = rand() % jumlah;

        float cx, cy;
        if (currentMaze == 1)
        {
            cx = safePositionsMaze1[idx][0];
            cy = safePositionsMaze1[idx][1];
        }
        else
        {
            cx = safePositionsMaze2[idx][0];
            cy = safePositionsMaze2[idx][1];
        }

        if (!cekTabrakan(cx, cy))
        {
            nrpPosX = cx;
            nrpPosY = cy;
            ditemukan = true;
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
    if (currentMaze == 1)
        maze1();
    else
        maze2();

    // matikan fungsi
    checkMode = false;

    return isColliding;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (isIsometric)
    {
        glTranslatef(0.0, 0.0, -8.0);

        glRotatef(mazeRotX, 1.0, 0.0, 0.0);
        glRotatef(mazeRotY, 0.0, 1.0, 0.0);
    }

    if (currentMaze == 1)
    {
        maze1();
    }
    else
    {
        maze2();
    }
    NRP(nrpPosX, nrpPosY);
    

    // Player - balok 3D langsung
    float L = -0.9f + postX;
    float R = 0.9f + postX;
    float T = 0.9f + postY;
    float B = -0.9f + postY;
    float zF = 0.9f + 1.0f; 
    float zBk = -0.9f + 1.0f;

    glColor4f(1.0, 1.0, 1.0, 1.0);

    // Sisi Depan
    glBegin(GL_POLYGON);
    glVertex3f(L, T, zF);
    glVertex3f(R, T, zF);
    glVertex3f(R, B, zF);
    glVertex3f(L, B, zF);
    glEnd();

    // Sisi Belakang
    glBegin(GL_POLYGON);
    glVertex3f(R, T, zBk);
    glVertex3f(L, T, zBk);
    glVertex3f(L, B, zBk);
    glVertex3f(R, B, zBk);
    glEnd();

    // Sisi Atas
    glBegin(GL_POLYGON);
    glVertex3f(L, T, zF);
    glVertex3f(R, T, zF);
    glVertex3f(R, T, zBk);
    glVertex3f(L, T, zBk);
    glEnd();

    // Sisi Bawah
    glBegin(GL_POLYGON);
    glVertex3f(L, B, zBk);
    glVertex3f(R, B, zBk);
    glVertex3f(R, B, zF);
    glVertex3f(L, B, zF);
    glEnd();

    // Sisi Kiri
    glBegin(GL_POLYGON);
    glVertex3f(L, T, zBk);
    glVertex3f(L, T, zF);
    glVertex3f(L, B, zF);
    glVertex3f(L, B, zBk);
    glEnd();

    // Sisi Kanan
    glBegin(GL_POLYGON);
    glVertex3f(R, T, zF);
    glVertex3f(R, T, zBk);
    glVertex3f(R, B, zBk);
    glVertex3f(R, B, zF);
    glEnd();    

    glColor4f(0.5, 0.5, 0.5, 0.3);
    Dinding(-18.0, 18.0, 18.0, -18.0, 0.2, 0.0);

    glutSwapBuffers();
}

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void input(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(0);

    float nextX = postX;
    float nextY = postY;

    if (key == 'w' || key == 'W')
        nextY += 0.5;
    if (key == 's' || key == 'S')
        nextY -= 0.5;
    if (key == 'a' || key == 'A')
        nextX -= 0.5;
    if (key == 'd' || key == 'D')
        nextX += 0.5;

    if (isIsometric)
    {
        if (key == 'j' || key == 'J')
            mazeRotY -= 2.0;
        if (key == 'l' || key == 'L')
            mazeRotY += 2.0;
        if (key == 'i' || key == 'I')
            mazeRotX -= 2.0;
        if (key == 'k' || key == 'K')
            mazeRotX += 2.0;
    }
    if (nextY > 17.0f)
        nextY = 17.0f;
    if (nextY < -17.0f)
        nextY = -17.0f;

    if (nextX != postX || nextY != postY)
    {
        if (!cekTabrakan(nextX, nextY))
        {
            postX = nextX;
            postY = nextY;
        }
    }

    if (key == 'c' || key == 'C')
    {
        randomizeNRP();
        currentMaze = (currentMaze == 1) ? 2 : 1;
        postX = 0.0;
        postY = 17.0;
    }

    if (key == 'v' || key == 'V')
    {
        isIsometric = !isIsometric;
        if (!isIsometric)
        {
            nrpRotX = 0.0f;
            nrpRotY = 0.0f;
            nrpRotZ = 0.0f;
        }
    }

    glutPostRedisplay();
}

void tampilkanInstruksi()
{
    cout << "=== PANDUAN MAZE GAME 3D ===" << endl;
    cout << "- Tombol W, A, S, D untuk bergerak" << endl;
    cout << "- Tombol C untuk ganti maze" << endl;
    cout << "- Tombol V untuk ganti mode view (Ortho/Isometrik)" << endl;
    cout << "- Tombol J, K, L, I untuk memutar maze di mode Isometrik" << endl;
    cout << "- Klik Mouse (Kiri, Tengah, Kanan) untuk mengganti sumbu putar NRP" << endl;
    cout << "============================" << endl;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    tampilkanInstruksi();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Maze Game 3D");
    glutMouseFunc(mouse);
    glutTimerFunc(16, timerNRP, 0);
    myinit();

    randomizeNRP();
    glutDisplayFunc(display);
    glutKeyboardFunc(input);

    glutMainLoop();
    return 0;
}