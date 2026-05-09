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

// posisi NRP  ← tambahkan ini
float nrpPosX = -5.0f;
float nrpPosY = 0.0f;

// Variabel rotasi NRP (tambahkan di bagian variabel global)
float nrpRotX = 0.0f;
float nrpRotY = 0.0f;
float nrpRotZ = 0.0f;
float nrpRotSpeed = 2.0f;
int nrpRotAxis = 0; // 0=Y, 1=X, 2=Z

// Variable deteksi tabrakan
bool checkMode = false;
bool isColliding = false;
float checkX = 0.0f;
float checkY = 0.0f;

// Deklarasi fungsi cekTabrakan agar bisa dipanggil di randomizeNRP
bool cekTabrakan(float nextX, float nextY);

void Dinding(float left, float top, float right, float bottom, float zFront, float zBack)
{
    // Jika tidak sedang mode cek (sedang menggambar)
    if (!checkMode) {
        // Sisi DEPAN (z = zFront)
        glBegin(GL_POLYGON);
        glVertex3f(left,  top,    zFront);
        glVertex3f(right, top,    zFront);
        glVertex3f(right, bottom, zFront);
        glVertex3f(left,  bottom, zFront);
        glEnd();

        // Sisi BELAKANG (z = zBack)
        glBegin(GL_POLYGON);
        glVertex3f(right, top,    zBack);
        glVertex3f(left,  top,    zBack);
        glVertex3f(left,  bottom, zBack);
        glVertex3f(right, bottom, zBack);
        glEnd();

        // Sisi ATAS (y = top)
        glBegin(GL_POLYGON);
        glVertex3f(left,  top, zFront);
        glVertex3f(right, top, zFront);
        glVertex3f(right, top, zBack);
        glVertex3f(left,  top, zBack);
        glEnd();

        // Sisi BAWAH (y = bottom)
        glBegin(GL_POLYGON);
        glVertex3f(left,  bottom, zBack);
        glVertex3f(right, bottom, zBack);
        glVertex3f(right, bottom, zFront);
        glVertex3f(left,  bottom, zFront);
        glEnd();

        // Sisi KIRI (x = left)
        glBegin(GL_POLYGON);
        glVertex3f(left, top,    zBack);
        glVertex3f(left, top,    zFront);
        glVertex3f(left, bottom, zFront);
        glVertex3f(left, bottom, zBack);
        glEnd();

        // Sisi KANAN (x = right)
        glBegin(GL_POLYGON);
        glVertex3f(right, top,    zFront);
        glVertex3f(right, top,    zBack);
        glVertex3f(right, bottom, zBack);
        glVertex3f(right, bottom, zFront);
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

// Timer animasi rotasi otomatis
void timerNRP(int value)
{
    if (nrpRotAxis == 0)      { nrpRotY += nrpRotSpeed; if (nrpRotY >= 360.0f) nrpRotY -= 360.0f; }
    else if (nrpRotAxis == 1) { nrpRotX += nrpRotSpeed; if (nrpRotX >= 360.0f) nrpRotX -= 360.0f; }
    else                      { nrpRotZ += nrpRotSpeed; if (nrpRotZ >= 360.0f) nrpRotZ -= 360.0f; }

    glutPostRedisplay();
    glutTimerFunc(16, timerNRP, 0);
}

// Kontrol axis rotasi via mouse
void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON)        nrpRotAxis = 0; // rotasi sumbu Y
        else if (button == GLUT_MIDDLE_BUTTON) nrpRotAxis = 1; // rotasi sumbu X
        else if (button == GLUT_RIGHT_BUTTON)  nrpRotAxis = 2; // rotasi sumbu Z
    }
}

void NRP(float x, float y)
{
    bool tempMode = checkMode;
    checkMode = false;

    glColor3f(0.0, 0.0, 1.0);
    float s  = 0.15f;
    float zf =  0.5f;
    float zb = -0.5f;

    // Titik tengah NRP untuk rotasi
    float cx = x + 5.5f * s;
    float cy = y + 2.5f * s;

    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    glRotatef(nrpRotX, 1.0f, 0.0f, 0.0f);
    glRotatef(nrpRotY, 0.0f, 1.0f, 0.0f);
    glRotatef(nrpRotZ, 0.0f, 0.0f, 1.0f);
    glTranslatef(-cx, -cy, 0.0f);

    // ── ANGKA 0 ──
    Dinding(x,       y+5*s,  x+s,     y,     zf, zb); // batang kiri
    Dinding(x+2*s,   y+5*s,  x+3*s,   y,     zf, zb); // batang kanan
    Dinding(x,       y+s,    x+3*s,   y,     zf, zb); // batang bawah
    Dinding(x,       y+5*s,  x+3*s,   y+4*s, zf, zb); // batang atas

    // ── ANGKA 3 ──
    float ox = x + 4*s;
    Dinding(ox,      y+s,    ox+3*s,  y,     zf, zb); // batang bawah
    Dinding(ox,      y+3*s,  ox+3*s,  y+2*s, zf, zb); // batang tengah
    Dinding(ox,      y+5*s,  ox+3*s,  y+4*s, zf, zb); // batang atas
    Dinding(ox+2*s,  y+5*s,  ox+3*s,  y,     zf, zb); // batang kanan vertikal

    // ── ANGKA 4 ──
    ox = x + 8*s;
    Dinding(ox,      y+5*s,  ox+s,    y+2*s, zf, zb); // batang kiri atas
    Dinding(ox,      y+3*s,  ox+3*s,  y+2*s, zf, zb); // batang tengah horizontal
    Dinding(ox+2*s,  y+5*s,  ox+3*s,  y,     zf, zb); // batang kanan vertikal

    glPopMatrix();

    checkMode = tempMode;
}

void maze1()
{
    glColor3f(1.0, 0.0, 0.0);
    // Border
    Dinding(-18.0, 18.0, -1.5, 17.0, -1.0, 1.0);
    Dinding(1.5, 18.0, 18.0, 17.0, -1.0, 1.0);
    Dinding(-18.0, -17.0, -1.5, -18.0 , -1.0, 1.0);
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
    // Posisi aman yang sudah ditetapkan di tengah koridor maze
    // Maze 1 dan Maze 2 punya posisi aman berbeda
    
    float safePositionsMaze1[][2] = {
        {-16.0f,  16.0f},  // pojok kiri atas
        { 14.0f,  16.0f},  // pojok kanan atas //
        {-16.0f, -16.0f},  // pojok kiri bawah
        { 14.0f, -16.0f},  // pojok kanan bawah //
        {  0.0f,   0.0f},  // tengah
        { -9.0f,   8.0f},  // koridor tengah kiri atas //
        {  8.0f,  -8.0f},  // koridor tengah kanan bawah
        { -4.0f,  -4.0f},  // koridor bawah kiri
        {  3.0f,   4.0f},  // koridor atas kanan //
        {-17.0f,   0.0f},  // sisi kiri tengah //
    };

    float safePositionsMaze2[][2] = {
        {-16.0f,  16.0f},  // pojok kiri atas
        { 14.0f,  16.0f},  // pojok kanan atas //
        {-16.0f, -16.0f},  // pojok kiri bawah
        { 14.0f, -16.0f},  // pojok kanan bawah //
        {  -1.0f,   0.0f},  // tengah
        { -9.0f,   8.0f},  // koridor tengah kiri atas //
        {  8.0f,  -8.0f},  // koridor tengah kanan bawah
        { -4.0f,  -4.0f},  // koridor bawah kiri
        {  3.0f,   4.0f},  // koridor atas kanan //
        {-17.0f,   0.0f},  // sisi kiri tengah //
    };

    int jumlah = 10;
    bool ditemukan = false;

    while (!ditemukan) {
        int idx = rand() % jumlah;

        float cx, cy;
        if (currentMaze == 1) {
            cx = safePositionsMaze1[idx][0];
            cy = safePositionsMaze1[idx][1];
        } else {
            cx = safePositionsMaze2[idx][0];
            cy = safePositionsMaze2[idx][1];
        }

        // Tetap verifikasi dengan cekTabrakan sebagai safety check
        if (!cekTabrakan(cx, cy)) {
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
    if (currentMaze == 1) maze1();
    else maze2();

    // matikan fungsi
    checkMode = false;

    return isColliding;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (currentMaze == 1) {
        maze1();
    } else {
        maze2();
    }
    // Player - balok 3D langsung
    float L = -0.9f + postX;
    float R =  0.9f + postX;
    float T =  0.9f + postY;
    float B = -0.9f + postY;
    float zF  = 0.9f + 1.0f;  // = 1.9
    float zBk = -0.9f + 1.0f; // = 0.1

    glColor4f(1.0, 1.0, 1.0, 1.0);

    // Sisi Depan
    glBegin(GL_POLYGON);
    glVertex3f(L, T, zF); glVertex3f(R, T, zF);
    glVertex3f(R, B, zF); glVertex3f(L, B, zF);
    glEnd();

    // Sisi Belakang
    glBegin(GL_POLYGON);
    glVertex3f(R, T, zBk); glVertex3f(L, T, zBk);
    glVertex3f(L, B, zBk); glVertex3f(R, B, zBk);
    glEnd();

    // Sisi Atas
    glBegin(GL_POLYGON);
    glVertex3f(L, T, zF);  glVertex3f(R, T, zF);
    glVertex3f(R, T, zBk); glVertex3f(L, T, zBk);
    glEnd();

    // Sisi Bawah
    glBegin(GL_POLYGON);
    glVertex3f(L, B, zBk); glVertex3f(R, B, zBk);
    glVertex3f(R, B, zF);  glVertex3f(L, B, zF);
    glEnd();

    // Sisi Kiri
    glBegin(GL_POLYGON);
    glVertex3f(L, T, zBk); glVertex3f(L, T, zF);
    glVertex3f(L, B, zF);  glVertex3f(L, B, zBk);
    glEnd();

    // Sisi Kanan
    glBegin(GL_POLYGON);
    glVertex3f(R, T, zF);  glVertex3f(R, T, zBk);
    glVertex3f(R, B, zBk); glVertex3f(R, B, zF);
    glEnd();

    // Gambar NRP
    NRP(nrpPosX, nrpPosY);

    glColor4f(0.5, 0.5, 0.5, 0.3); // abu-abu, transparan

    glBegin(GL_POLYGON);
    glVertex3f(-20.0,  -20.0,  -1.0);  // sudut kiri bawah
    glVertex3f( 20.0,  -20.0,  -1.0);  // sudut kanan bawah
    glVertex3f( 20.0,   20.0,  -1.0);  // sudut kanan atas
    glVertex3f(-20.0,   20.0,  -1.0);  // sudut kiri atas
    glEnd();

    glFlush();
    
}

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -12.0, 12.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutMouseFunc(mouse);           // tambahkan
    glutTimerFunc(16, timerNRP, 0); // tambahkan
    glutCreateWindow("Maze Game 3D");


    myinit();
    
    // Panggil random NRP setelah init agar OpenGL context siap
    randomizeNRP();

    glutDisplayFunc(display);
    glutKeyboardFunc(input);

    glutMainLoop();
    return 0;
}