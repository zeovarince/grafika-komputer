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

// Tambahkan deklarasi posisi NRP di sini
float nrpPosX = -5.0; // Contoh posisi awal X untuk NRP
float nrpPosY = 0.0;  // Contoh posisi awal Y untuk NRP

// --- VARIABEL UNTUK DETEKSI TABRAKAN ---
bool checkMode = false;
bool isColliding = false;
float checkX = 0.0f;
float checkY = 0.0f;

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
    // Jika sedang dalam mode cek twadsabrakan
    else {
        // Mendapatkan batas kotak player (ukuran asli 0.9, kita pakai 0.85 
        // agar pergerakan sedikit lebih mulus dan tidak terlalu nyangkut di siku dinding)
        float p_left = checkX - 0.85f;
        float p_right = checkX + 0.85f;
        float p_top = checkY + 0.85f;
        float p_bottom = checkY - 0.85f;

        // Cek overlap kotak player dengan kotak dinding
        if (p_left < right && p_right > left && p_bottom < top && p_top > bottom) {
            isColliding = true; // Tabrakan terdeteksi!
        }
    }
}

void NRP(float x, float y)
{
    glColor3f(0.0, 0.0, 1.0); // Warna Biru
    float s = 0.15;            // Ukuran diperkecil dari 1.5 ke 0.45

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

    // --- DINDING TERLUAR (BORDER) ---
    Dinding(-18.0, 18.0, -1.5, 17.0);
    Dinding(1.5, 18.0, 18.0, 17.0);
    Dinding(-18.0, -17.0, -1.5, -18.0);
    Dinding(1.5, -17.0, 18.0, -18.0);
    Dinding(-18.0, 18.0, -17.0, -18.0);
    Dinding(17.0, 18.0, 18.0, -18.0);  

    // --- DINDING DALAM ---
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

    // --- DINDING TERLUAR (BORDER) ---
    Dinding(-18.0,  18.0, -1.5,  17.0);
    Dinding(  1.5,  18.0, 18.0,  17.0);
    Dinding(-18.0, -17.0, -1.5, -18.0);
    Dinding(  1.5, -17.0, 18.0, -18.0);
    Dinding(-18.0,  18.0, -17.0, -18.0); 
    Dinding( 17.0,  18.0,  18.0, -18.0); 

    // --- DINDING HORIZONTAL DALAM ---
    Dinding(-18.0,  14.5, -13.5,  13.5);
    Dinding( -6.5,  14.5,  -1.5,  13.5);
    Dinding(  1.5,  14.5,   6.5,  13.5);
    Dinding( 13.5,  14.5,  18.0,  13.5);
    Dinding(-14.5,  10.5,  -5.5,   9.5);
    Dinding(  5.5,  10.5,  14.5,   9.5);
    Dinding(-18.0,   6.5, -13.5,   5.5);
    Dinding( -2.5,   6.5,   2.5,   5.5);
    Dinding( 13.5,   6.5,  18.0,   5.5);
    Dinding(-10.5,   2.5,  -1.5,   1.5);
    Dinding(  1.5,   2.5,  10.5,   1.5);
    Dinding(-18.0,  -1.5,  -9.5,  -2.5);
    Dinding(  9.5,  -1.5,  18.0,  -2.5);
    Dinding(-10.5,  -5.5,  -5.5,  -6.5);
    Dinding( -2.5,  -5.5,   2.5,  -6.5);
    Dinding(  5.5,  -5.5,  10.5,  -6.5);
    Dinding(-18.0,  -9.5, -13.5, -10.5);
    Dinding( -6.5,  -9.5,  -1.5, -10.5);
    Dinding(  1.5,  -9.5,   6.5, -10.5);
    Dinding( 13.5,  -9.5,  18.0, -10.5);
    Dinding(-14.5, -13.5,  -9.5, -14.5);
    Dinding( -2.5, -13.5,   2.5, -14.5);
    Dinding(  9.5, -13.5,  14.5, -14.5);

    // --- DINDING VERTIKAL DALAM ---
    Dinding(-14.5,  14.5, -13.5,   9.5);
    Dinding(-14.5,   6.5, -13.5,   1.5);
    Dinding(-14.5,  -1.5, -13.5,  -6.5);
    Dinding(-14.5,  -9.5, -13.5, -14.5);
    Dinding(-10.5,  18.0,  -9.5,  13.5);
    Dinding(-10.5, -13.5,  -9.5, -18.0);
    Dinding( -6.5,  10.5,  -5.5,   5.5);
    Dinding( -6.5,   2.5,  -5.5,  -2.5);
    Dinding( -6.5,  -5.5,  -5.5, -10.5);
    Dinding( -2.5,  14.5,  -1.5,   9.5);
    Dinding( -2.5,   2.5,  -1.5,  -2.5);
    Dinding( -2.5,  -9.5,  -1.5, -14.5);
    Dinding(  1.5,  14.5,   2.5,   9.5);
    Dinding(  1.5,   2.5,   2.5,  -2.5);
    Dinding(  1.5,  -9.5,   2.5, -14.5);
    Dinding(  5.5,  10.5,   6.5,   5.5);
    Dinding(  5.5,   2.5,   6.5,  -2.5);
    Dinding(  5.5,  -5.5,   6.5, -10.5);
    Dinding(  9.5,  18.0,  10.5,  13.5);
    Dinding(  9.5, -13.5,  10.5, -18.0);
    Dinding( 13.5,  14.5,  14.5,   9.5);
    Dinding( 13.5,   6.5,  14.5,   1.5);
    Dinding( 13.5,  -1.5,  14.5,  -6.5);
    Dinding( 13.5,  -9.5,  14.5, -14.5);
}

void randomizeNRP()
{ 
}

// --- FUNGSI DETEKSI TABRAKAN ---
bool cekTabrakan(float nextX, float nextY)
{
    // Aktifkan mode cek (Dinding() tidak akan menggambar ke layar)
    checkMode = true;
    isColliding = false;
    checkX = nextX;
    checkY = nextY;

    // Panggil labirin saat ini (ini akan memanggil Dinding() secara virtual)
    if (currentMaze == 1) maze1();
    else maze2();

    // Matikan mode cek agar display() bisa menggambar lagi
    checkMode = false;

    return isColliding;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Gambar Maze
    if (currentMaze == 1) {
        maze1();
    } else {
        maze2();
    }

    // Gambar NRP
    NRP(nrpPosX, nrpPosY);

    // Menggambar Player (Kotak Hitam)
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
    glColor3f(1.0, 1.0, 1.0);
}

void input(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q') exit(0);

    // Prediksi posisi baru berdasarkan tombol yang ditekan
    float nextX = postX;
    float nextY = postY;

    if (key == 'w' || key == 'W') nextY += 0.5;
    if (key == 's' || key == 'S') nextY -= 0.5;
    if (key == 'a' || key == 'A') nextX -= 0.5;
    if (key == 'd' || key == 'D') nextX += 0.5;

    // Cek apakah posisi prediksi ini berpotensi menabrak dinding
    if (nextX != postX || nextY != postY) {
        if (!cekTabrakan(nextX, nextY)) {
            // Jika tidak menabrak (False), pindahkan player
            postX = nextX;
            postY = nextY;
        }
    }

    if (key == 'c' || key == 'C')
    {
        currentMaze = (currentMaze == 1) ? 2 : 1;
        randomizeNRP(); // Panggil fungsi titik aman
        postX = 0.0;
        postY = 17.0;
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    randomizeNRP(); // Set posisi awal secara aman

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(750, 750);
    glutCreateWindow("demo 2 maze statis - Dengan Deteksi Dinding");

    glutDisplayFunc(display);
    glutKeyboardFunc(input);

    myinit();
    glutMainLoop();
    return 0;
}