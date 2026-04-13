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

void drawRect(float left, float top, float right, float bottom)
{
    glBegin(GL_POLYGON);
    glVertex2f(left, top);
    glVertex2f(right, top);
    glVertex2f(right, bottom);
    glVertex2f(left, bottom);
    glEnd();
}

void drawNRP(float x, float y)
{
    glColor3f(0.0, 0.0, 1.0); // Warna Biru
    float s = 0.2;            // Ukuran diperkecil dari 1.5 ke 0.45

    // Angka 0
    drawRect(x, y, x + s, y + 5 * s);
    drawRect(x + 2 * s, y, x + 3 * s, y + 5 * s);
    drawRect(x, y, x + 3 * s, y + s);
    drawRect(x, y + 4 * s, x + 3 * s, y + 5 * s);

    // Angka 3
    float ox = x + 4 * s;
    drawRect(ox, y, ox + 3 * s, y + s);
    drawRect(ox, y + 2 * s, ox + 3 * s, y + 3 * s);
    drawRect(ox, y + 4 * s, ox + 3 * s, y + 5 * s);
    drawRect(ox + 2 * s, y, ox + 3 * s, y + 5 * s);

    // Angka 4
    ox = x + 8 * s;
    drawRect(ox, y + 2 * s, ox + s, y + 5 * s);
    drawRect(ox, y + 2 * s, ox + 3 * s, y + 3 * s);
    drawRect(ox + 2 * s, y, ox + 3 * s, y + 5 * s);
}

void maze1()
{
    glColor3f(1.0, 0.0, 0.0);

    // --- DINDING TERLUAR (BORDER) ---
    // Atas
    drawRect(-18.0, 18.0, -1.5, 17.0);
    drawRect(1.5, 18.0, 18.0, 17.0);

    // Bawah
    drawRect(-18.0, -17.0, -1.5, -18.0);
    drawRect(1.5, -17.0, 18.0, -18.0);

    // Samping
    drawRect(-18.0, 18.0, -17.0, -18.0); // Kiri
    drawRect(17.0, 18.0, 18.0, -18.0);   // Kanan

    // --- DINDING DALAM ---
    // Baris Y = 14
    drawRect(-14.5, 14.5, -5.5, 13.5);
    drawRect(-2.5, 14.5, 2.5, 13.5);
    drawRect(5.5, 14.5, 10.5, 13.5);
    drawRect(13.5, 14.5, 17.0, 13.5);

    // Baris Y = 10
    drawRect(-17.0, 10.5, -13.5, 9.5);
    drawRect(-10.5, 10.5, -5.5, 9.5);
    drawRect(1.5, 10.5, 6.5, 9.5);
    drawRect(9.5, 10.5, 17.0, 9.5);

    // Baris Y = 6
    drawRect(-17.0, 6.5, -9.5, 5.5);
    drawRect(-6.5, 6.5, 2.5, 5.5);
    drawRect(5.5, 6.5, 14.5, 5.5);

    // Baris Y = 2
    drawRect(-14.5, 2.5, -5.5, 1.5);
    drawRect(-2.5, 2.5, 2.5, 1.5);

    // Baris Y = -2
    drawRect(-17.0, -1.5, -5.5, -2.5);
    drawRect(1.5, -1.5, 10.5, -2.5);
    drawRect(9.5, -1.5, 14.5, -2.5);

    // Baris Y = -6
    drawRect(-14.5, -5.5, -9.5, -6.5);
    drawRect(-10.5, -5.5, -1.5, -6.5);
    drawRect(1.5, -5.5, 10.5, -6.5);
    drawRect(13.5, -5.5, 17.0, -6.5);

    // --- GARIS BARU (SESUAI GAMBAR USER) ---
    // Menghubungkan celah di area bawah
    drawRect(-6.5, -9.5, 1.5, -10.5);

    // Baris Y = -10 (Sisa)
    drawRect(-17.0, -9.5, -9.5, -10.5);
    drawRect(1.5, -9.5, 6.5, -10.5);
    drawRect(9.5, -9.5, 14.5, -10.5);

    // Baris Y = -14
    drawRect(-17.0, -13.5, -13.5, -14.5);
    drawRect(-10.5, -13.5, -1.5, -14.5);
    drawRect(5.5, -13.5, 10.5, -14.5);

    // Kolom Vertikal
    drawRect(-14.5, 14.5, -13.5, 9.5);
    drawRect(-14.5, 2.5, -13.5, -6.5);
    drawRect(-14.5, -9.5, -13.5, -14.5);
    drawRect(-10.5, 17.0, -9.5, 13.5);
    drawRect(-10.5, 10.5, -9.5, 5.5);
    drawRect(-10.5, -1.5, -9.5, -6.5);
    drawRect(-10.5, -9.5, -9.5, -14.5);
    drawRect(-6.5, 10.5, -5.5, 5.5);
    drawRect(-6.5, 6.5, -5.5, 1.5);
    drawRect(-6.5, -5.5, -5.5, -10.5);
    drawRect(-2.5, 14.5, -1.5, 9.5);
    drawRect(-2.5, 6.5, -1.5, -2.5);
    drawRect(5.5, 10.5, 6.5, 5.5);
    drawRect(5.5, 6.5, 6.5, -10.5);
    drawRect(9.5, 14.5, 10.5, 9.5);
    drawRect(9.5, 6.5, 10.5, 1.5);
    drawRect(9.5, -1.5, 10.5, -6.5);
    drawRect(9.5, -9.5, 10.5, -14.5);
    drawRect(13.5, 6.5, 14.5, 1.5);
    drawRect(13.5, 2.5, 14.5, -2.5);
    drawRect(13.5, -5.5, 14.5, -10.5);
    drawRect(13.5, -9.5, 14.5, -17.0);
}
void maze2()
{
    // Tempat untuk menggambar maze 2
}

void randomizeNRP()
{
    // Daftar koordinat (x, y) yang merupakan jalan kosong di maze kamu
    // Kamu bisa menambah atau menyesuaikan angka-angka ini
    float safePointsX[] = {-12.0, -8.0, 0.0, 8.0, 12.0, -15.0, 15.0, 4.0, -4.0};
    float safePointsY[] = {12.0, 8.0, 4.0, 0.0, -4.0, -8.0, -12.0, 15.0, -15.0};

    int jumlahTitik = sizeof(safePointsX) / sizeof(safePointsX[0]);
    int index = rand() % jumlahTitik;

    nrpPosX = safePointsX[index];
    nrpPosY = safePointsY[index];
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
    drawNRP(nrpPosX, nrpPosY);

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