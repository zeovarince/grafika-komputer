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

void Dinding(float left, float top, float right, float bottom)
{
    glBegin(GL_POLYGON);
    glVertex2f(left, top);
    glVertex2f(right, top);
    glVertex2f(right, bottom);
    glVertex2f(left, bottom);
    glEnd();
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
    // Atas
    Dinding(-18.0, 18.0, -1.5, 17.0);
    Dinding(1.5, 18.0, 18.0, 17.0);

    // Bawah
    Dinding(-18.0, -17.0, -1.5, -18.0);
    Dinding(1.5, -17.0, 18.0, -18.0);

    // Samping
    Dinding(-18.0, 18.0, -17.0, -18.0); // Kiri
    Dinding(17.0, 18.0, 18.0, -18.0);   // Kanan

    // --- DINDING DALAM ---
    // Baris Y = 14
    Dinding(-14.5, 14.5, -5.5, 13.5);
    Dinding(-2.5, 14.5, 2.5, 13.5);
    Dinding(5.5, 14.5, 10.5, 13.5);
    Dinding(13.5, 14.5, 17.0, 13.5);

    // Baris Y = 10
    Dinding(-17.0, 10.5, -13.5, 9.5);
    Dinding(-10.5, 10.5, -5.5, 9.5);
    Dinding(1.5, 10.5, 6.5, 9.5);
    Dinding(9.5, 10.5, 17.0, 9.5);

    // Baris Y = 6
    Dinding(-17.0, 6.5, -9.5, 5.5);
    Dinding(-6.5, 6.5, 2.5, 5.5);
    Dinding(5.5, 6.5, 14.5, 5.5);

    // Baris Y = 2
    Dinding(-14.5, 2.5, -5.5, 1.5);
    Dinding(-2.5, 2.5, 2.5, 1.5);

    // Baris Y = -2
    Dinding(-17.0, -1.5, -5.5, -2.5);
    Dinding(1.5, -1.5, 10.5, -2.5);
    Dinding(9.5, -1.5, 14.5, -2.5);

    // Baris Y = -6
    Dinding(-14.5, -5.5, -9.5, -6.5);
    Dinding(-10.5, -5.5, -1.5, -6.5);
    Dinding(1.5, -5.5, 10.5, -6.5);
    Dinding(13.5, -5.5, 17.0, -6.5);

    // Menghubungkan celah di area bawah
    Dinding(-6.5, -9.5, 1.5, -10.5);

    // Baris Y = -10 (Sisa)
    Dinding(-17.0, -9.5, -9.5, -10.5);
    Dinding(1.5, -9.5, 6.5, -10.5);
    Dinding(9.5, -9.5, 14.5, -10.5);

    // Baris Y = -14
    Dinding(-17.0, -13.5, -13.5, -14.5);
    Dinding(-10.5, -13.5, -1.5, -14.5);
    Dinding(5.5, -13.5, 10.5, -14.5);

    // Kolom Vertikal
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
    // Atas (pintu di tengah x=-1.5..1.5)
    Dinding(-18.0,  18.0, -1.5,  17.0);
    Dinding(  1.5,  18.0, 18.0,  17.0);

    // Bawah (pintu di tengah x=-1.5..1.5)
    Dinding(-18.0, -17.0, -1.5, -18.0);
    Dinding(  1.5, -17.0, 18.0, -18.0);

    // Samping
    Dinding(-18.0,  18.0, -17.0, -18.0); // Kiri
    Dinding( 17.0,  18.0,  18.0, -18.0); // Kanan

    // --- DINDING HORIZONTAL DALAM ---
    // Setiap ujung X ditambahkan/dikurangi 0.5 agar masuk ke dalam grid persimpangan

    // Baris 0 bawah (y=14.5..13.5)
    Dinding(-18.0,  14.5, -13.5,  13.5);
    Dinding( -6.5,  14.5,  -1.5,  13.5);
    Dinding(  1.5,  14.5,   6.5,  13.5);
    Dinding( 13.5,  14.5,  18.0,  13.5);

    // Baris 1 bawah (y=10.5..9.5)
    Dinding(-14.5,  10.5,  -5.5,   9.5);
    Dinding(  5.5,  10.5,  14.5,   9.5);

    // Baris 2 bawah (y=6.5..5.5)
    Dinding(-18.0,   6.5, -13.5,   5.5);
    Dinding( -2.5,   6.5,   2.5,   5.5);
    Dinding( 13.5,   6.5,  18.0,   5.5);

    // Baris 3 bawah (y=2.5..1.5)
    Dinding(-10.5,   2.5,  -1.5,   1.5);
    Dinding(  1.5,   2.5,  10.5,   1.5);

    // Baris 4 bawah (y=-1.5..-2.5)
    Dinding(-18.0,  -1.5,  -9.5,  -2.5);
    Dinding(  9.5,  -1.5,  18.0,  -2.5);

    // Baris 5 bawah (y=-5.5..-6.5)
    Dinding(-10.5,  -5.5,  -5.5,  -6.5);
    Dinding( -2.5,  -5.5,   2.5,  -6.5);
    Dinding(  5.5,  -5.5,  10.5,  -6.5);

    // Baris 6 bawah (y=-9.5..-10.5)
    Dinding(-18.0,  -9.5, -13.5, -10.5);
    Dinding( -6.5,  -9.5,  -1.5, -10.5);
    Dinding(  1.5,  -9.5,   6.5, -10.5);
    Dinding( 13.5,  -9.5,  18.0, -10.5);

    // Baris 7 bawah (y=-13.5..-14.5)
    Dinding(-14.5, -13.5,  -9.5, -14.5);
    Dinding( -2.5, -13.5,   2.5, -14.5);
    Dinding(  9.5, -13.5,  14.5, -14.5);

    // --- DINDING VERTIKAL DALAM ---
    // Setiap ujung Y ditambahkan/dikurangi 0.5 agar masuk ke dalam grid persimpangan

    // Kolom 0 kanan (x=-14.5..-13.5)
    Dinding(-14.5,  14.5, -13.5,   9.5);
    Dinding(-14.5,   6.5, -13.5,   1.5);
    Dinding(-14.5,  -1.5, -13.5,  -6.5);
    Dinding(-14.5,  -9.5, -13.5, -14.5);

    // Kolom 1 kanan (x=-10.5..-9.5)
    Dinding(-10.5,  18.0,  -9.5,  13.5);
    Dinding(-10.5, -13.5,  -9.5, -18.0);

    // Kolom 2 kanan (x=-6.5..-5.5)
    Dinding( -6.5,  10.5,  -5.5,   5.5);
    Dinding( -6.5,   2.5,  -5.5,  -2.5);
    Dinding( -6.5,  -5.5,  -5.5, -10.5);

    // Kolom 3 kanan (x=-2.5..-1.5)
    Dinding( -2.5,  14.5,  -1.5,   9.5);
    Dinding( -2.5,   2.5,  -1.5,  -2.5);
    Dinding( -2.5,  -9.5,  -1.5, -14.5);

    // Kolom 4 kanan (x=1.5..2.5)
    Dinding(  1.5,  14.5,   2.5,   9.5);
    Dinding(  1.5,   2.5,   2.5,  -2.5);
    Dinding(  1.5,  -9.5,   2.5, -14.5);

    // Kolom 5 kanan (x=5.5..6.5)
    Dinding(  5.5,  10.5,   6.5,   5.5);
    Dinding(  5.5,   2.5,   6.5,  -2.5);
    Dinding(  5.5,  -5.5,   6.5, -10.5);

    // Kolom 6 kanan (x=9.5..10.5)
    Dinding(  9.5,  18.0,  10.5,  13.5);
    Dinding(  9.5, -13.5,  10.5, -18.0);

    // Kolom 7 kanan (x=13.5..14.5)
    Dinding( 13.5,  14.5,  14.5,   9.5);
    Dinding( 13.5,   6.5,  14.5,   1.5);
    Dinding( 13.5,  -1.5,  14.5,  -6.5);
    Dinding( 13.5,  -9.5,  14.5, -14.5);
}

void randomizeNRP()
{ 
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Menggambar Player (Kotak Hitam)
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.9 + postX, 0.9 + postY);
    glVertex2f(0.9 + postX, 0.9 + postY);
    glVertex2f(0.9 + postX, -0.9 + postY);
    glVertex2f(-0.9 + postX, -0.9 + postY);
    glEnd();

    // Gambar NRP
    NRP(nrpPosX, nrpPosY);

    // Gambar Maze
    if (currentMaze == 1)
    {
        maze1();
    }
    else
    {
        maze2();
    }

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
    if (key == 'q')
    {
        exit(0);
    }
    if (key == 'w' || key == 'W')
    {
        postY += 0.5;
    }
    if (key == 's' || key == 'S')
    {
        postY -= 0.5;
    }
    if (key == 'a' || key == 'A')
    {
        postX -= 0.5;
    }
    if (key == 'd' || key == 'D')
    {
        postX += 0.5;
    }

    // MODIFIKASI DI SINI
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
    randomizeNRP(); // Set posisi awal secara amana

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(750, 750);
    glutCreateWindow("demo 2 maze statis");

    glutDisplayFunc(display);
    glutKeyboardFunc(input);

    myinit();
    glutMainLoop();
    return 0;
}