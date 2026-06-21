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

// ukuran grid maze 19x19
const int GRID_SIZE = 19;

// posisi pintu masuk (atas tengah) dan pintu keluar (bawah tengah)
const int ENTRANCE_X = 9, ENTRANCE_Y = 18;
const int EXIT_X = 9, EXIT_Y = 0;

int maze1[GRID_SIZE][GRID_SIZE] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// data maze 2, layout beda buat ganti level
// dibangkitkan pakai algoritma "perfect maze" (recursive backtracker)
// dengan kerangka 9 ruangan x 9 ruangan yang sama seperti maze1,
// supaya gaya & densitas dindingnya konsisten. Sudah divalidasi BFS juga.
int maze2[GRID_SIZE][GRID_SIZE] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// pointer ke maze yang lagi aktif (awalnya nunjuk ke maze1)
int (*currentMaze)[GRID_SIZE] = maze1;

// penanda level berapa yang aktif (1 atau 2)
int levelFlag = 1;

// posisi player, mulai dari pintu masuk
int playerX = ENTRANCE_X;
int playerY = ENTRANCE_Y;

// posisi NRP
int nrpX, nrpY;
// rotasi animasi NRP (derajat), tiap axis disimpan terpisah
float nrpRotX = 0.0f;
float nrpRotY = 0.0f;
float nrpRotZ = 0.0f;
float nrpRotSpeed = 1.5f; // kecepatan rotasi per frame
int nrpRotAxis = 2;       // 0 = X, 1 = Y, 2 = Z -> diubah lewat klik mouse

// flag mode tampilan: false = orthogonal (atas), true = isometric
bool isIsometricMode = false;
// sudut rotasi maze (derajat), disimpan permanen -> tidak reset saat ganti mode
float mazeTiltX = 50.0f;  // tilt/pitch (tombol i/k)
float mazeYawZ = 45.0f;   // yaw/putar mendatar (tombol j/l)
float mazeRotStep = 5.0f; // besar perubahan tiap penekanan tombol

// deklarasi fungsi
void drawMaze();
void drawPlayer();
void drawNRP(int gridX, int gridY);
void randomizeNRP();
void resetLevel();
bool isInsideGrid(int x, int y);
bool isWall(int x, int y);
void gambarBalok(float x1, float y1, float z1, float x2, float y2, float z2);

void drawCell(int gridX, int gridY, float r, float g, float b, bool isWallCell)
{
    float wallHeight = 1.0f; // tinggi tembok di sumbu Z

    if (isWallCell)
    {
        // --- SISI ATAS TEMBOK (top face) ---
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex3f((float)gridX, (float)gridY, wallHeight);
        glVertex3f((float)gridX + 1.0f, (float)gridY, wallHeight);
        glVertex3f((float)gridX + 1.0f, (float)gridY + 1.0f, wallHeight);
        glVertex3f((float)gridX, (float)gridY + 1.0f, wallHeight);
        glEnd();

        // --- SISI DEPAN TEMBOK (menghadap kamera di Y rendah) ---
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        glVertex3f((float)gridX, (float)gridY, 0.0f);
        glVertex3f((float)gridX + 1.0f, (float)gridY, 0.0f);
        glVertex3f((float)gridX + 1.0f, (float)gridY, wallHeight);
        glVertex3f((float)gridX, (float)gridY, wallHeight);
        glEnd();

        // --- SISI KANAN TEMBOK ---
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        glVertex3f((float)gridX + 1.0f, (float)gridY, 0.0f);
        glVertex3f((float)gridX + 1.0f, (float)gridY + 1.0f, 0.0f);
        glVertex3f((float)gridX + 1.0f, (float)gridY + 1.0f, wallHeight);
        glVertex3f((float)gridX + 1.0f, (float)gridY, wallHeight);
        glEnd();
    }
    else
    {
        // Jalan tetap datar di Z=0, sama seperti sebelumnya
        glColor3f(0.05f, 0.05f, 0.2f);
        glBegin(GL_QUADS);
        glVertex3f((float)gridX, (float)gridY, 0.0f);
        glVertex3f((float)gridX + 1.0f, (float)gridY, 0.0f);
        glVertex3f((float)gridX + 1.0f, (float)gridY + 1.0f, 0.0f);
        glVertex3f((float)gridX, (float)gridY + 1.0f, 0.0f);
        glEnd();
    }
}
void drawMaze()
{
    for (int y = 0; y < GRID_SIZE; y++)
    {
        for (int x = 0; x < GRID_SIZE; x++)
        {
            if (currentMaze[y][x] == 1)
            {
                // UBAH: tambah parameter true untuk isWallCell
                drawCell(x, y, 0.2f, 0.2f, 0.2f, true);
            }
            else
            {
                // UBAH: tambah parameter false
                drawCell(x, y, 0.85f, 0.85f, 0.85f, false);
            }
        }
    }
}

void drawPlayer_2D()
{
    float margin = 0.15f;
    float z = 0.01f;

    glColor3f(0.1f, 0.3f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(playerX + margin, playerY + margin, z);
    glVertex3f(playerX + 1.0f - margin, playerY + margin, z);
    glVertex3f(playerX + 1.0f - margin, playerY + 1.0f - margin, z);
    glVertex3f(playerX + margin, playerY + 1.0f - margin, z);
    glEnd();
}

// versi 3D, dipakai di mode isometric - player jadi balok beneran
void drawPlayer_3D()
{
    float margin = 0.15f;
    float bottomZ = 0.02f; // sedikit di atas lantai
    float topZ = 0.6f;     // tinggi player, lebih rendah dari tembok (1.0)

    glColor3f(0.1f, 0.3f, 0.9f);
    gambarBalok(playerX + margin, playerY + margin, bottomZ,
                playerX + 1.0f - margin, playerY + 1.0f - margin, topZ);
}

// switcher
void drawPlayer()
{
    if (isIsometricMode)
        drawPlayer_3D();
    else
        drawPlayer_2D();
}

// ===================================================
// GAMBAR ANGKA NRP "034" PAKAI GAYA SEVEN SEGMENT
// tiap angka dibentuk dari beberapa kotak kecil
// (GL_QUADS), bukan ditimpa/dilubangi warna background
// ===================================================

// gambar 1 batang segmen (kotak kecil) dari titik (x1,y1) ke (x2,y2)
void gambarSegmen(float x1, float y1, float x2, float y2, float z = 0.02f)
{
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, z);
    glVertex3f(x2, y1, z);
    glVertex3f(x2, y2, z);
    glVertex3f(x1, y2, z);
    glEnd();
}

// angka 0, butuh 4 kotak: atas, bawah, kiri penuh, kanan penuh
void gambarAngka0(float baseX, float baseY, float lebar, float tinggi)
{
    float tebal = 0.04f;
    float kiri = baseX;
    float kanan = baseX + lebar;
    float bawah = baseY;
    float atas = baseY + tinggi;

    glColor3f(1.0f, 0.8f, 0.0f); // warna kuning oranye

    gambarSegmen(kiri, atas - tebal, kanan, atas);   // batang atas
    gambarSegmen(kiri, bawah, kanan, bawah + tebal); // batang bawah
    gambarSegmen(kiri, bawah, kiri + tebal, atas);   // batang kiri (penuh)
    gambarSegmen(kanan - tebal, bawah, kanan, atas); // batang kanan (penuh)
}

// angka 3, butuh 5 kotak: atas, tengah, bawah, kanan atas, kanan bawah
void gambarAngka3(float baseX, float baseY, float lebar, float tinggi)
{
    float tebal = 0.04f;
    float kiri = baseX;
    float kanan = baseX + lebar;
    float bawah = baseY;
    float atas = baseY + tinggi;
    float tengah = baseY + tinggi / 2.0f;

    glColor3f(1.0f, 0.8f, 0.0f);

    gambarSegmen(kiri, atas - tebal, kanan, atas);                           // batang atas
    gambarSegmen(kiri, tengah - tebal / 2.0f, kanan, tengah + tebal / 2.0f); // batang tengah
    gambarSegmen(kiri, bawah, kanan, bawah + tebal);                         // batang bawah
    gambarSegmen(kanan - tebal, tengah, kanan, atas);                        // batang kanan atas
    gambarSegmen(kanan - tebal, bawah, kanan, tengah);                       // batang kanan bawah
}

// angka 4, butuh 3 kotak: kiri atas, tengah, kanan penuh
void gambarAngka4(float baseX, float baseY, float lebar, float tinggi)
{
    float tebal = 0.04f;
    float kiri = baseX;
    float kanan = baseX + lebar;
    float bawah = baseY;
    float atas = baseY + tinggi;
    float tengah = baseY + tinggi / 2.0f;

    glColor3f(1.0f, 0.8f, 0.0f);

    gambarSegmen(kiri, tengah, kiri + tebal, atas);                          // batang kiri atas
    gambarSegmen(kiri, tengah - tebal / 2.0f, kanan, tengah + tebal / 2.0f); // batang tengah
    gambarSegmen(kanan - tebal, bawah, kanan, atas);                         // batang kanan (penuh)
}

// gambar 1 balok dari pojok (x1,y1,z1) ke (x2,y2,z2)
// 6 sisi independen x 4 vertex = 24 vertex total
void gambarBalok(float x1, float y1, float z1,
                 float x2, float y2, float z2)
{
    // depan (z2)
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);
    glEnd();
    // belakang (z1)
    glBegin(GL_QUADS);
    glVertex3f(x2, y1, z1);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y2, z1);
    glVertex3f(x2, y2, z1);
    glEnd();
    // kiri (x1)
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y2, z1);
    glEnd();
    // kanan (x2)
    glBegin(GL_QUADS);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z2);
    glEnd();
    // atas (y2)
    glBegin(GL_QUADS);
    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);
    glEnd();
    // bawah (y1)
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x1, y1, z2);
    glEnd();
}

// versi 3D dari gambarSegmen: jadikan tiap batang segmen jadi balok tipis
void gambarSegmen3D(float x1, float y1, float x2, float y2,
                    float zBelakang, float zDepan)
{
    gambarBalok(x1, y1, zBelakang, x2, y2, zDepan);
}

void gambarAngka0_3D(float baseX, float baseY, float lebar, float tinggi,
                     float zBelakang, float zDepan)
{
    float tebal = 0.04f;
    float kiri = baseX, kanan = baseX + lebar;
    float bawah = baseY, atas = baseY + tinggi;

    glColor3f(1.0f, 0.8f, 0.0f);
    gambarSegmen3D(kiri, atas - tebal, kanan, atas, zBelakang, zDepan);
    gambarSegmen3D(kiri, bawah, kanan, bawah + tebal, zBelakang, zDepan);
    gambarSegmen3D(kiri, bawah, kiri + tebal, atas, zBelakang, zDepan);
    gambarSegmen3D(kanan - tebal, bawah, kanan, atas, zBelakang, zDepan);
}

void gambarAngka3_3D(float baseX, float baseY, float lebar, float tinggi,
                     float zBelakang, float zDepan)
{
    float tebal = 0.04f;
    float kiri = baseX, kanan = baseX + lebar;
    float bawah = baseY, atas = baseY + tinggi;
    float tengah = baseY + tinggi / 2.0f;

    glColor3f(1.0f, 0.8f, 0.0f);
    gambarSegmen3D(kiri, atas - tebal, kanan, atas, zBelakang, zDepan);
    gambarSegmen3D(kiri, tengah - tebal / 2.0f, kanan, tengah + tebal / 2.0f, zBelakang, zDepan);
    gambarSegmen3D(kiri, bawah, kanan, bawah + tebal, zBelakang, zDepan);
    gambarSegmen3D(kanan - tebal, tengah, kanan, atas, zBelakang, zDepan);
    gambarSegmen3D(kanan - tebal, bawah, kanan, tengah, zBelakang, zDepan);
}

void gambarAngka4_3D(float baseX, float baseY, float lebar, float tinggi,
                     float zBelakang, float zDepan)
{
    float tebal = 0.04f;
    float kiri = baseX, kanan = baseX + lebar;
    float bawah = baseY, atas = baseY + tinggi;
    float tengah = baseY + tinggi / 2.0f;

    glColor3f(1.0f, 0.8f, 0.0f);
    gambarSegmen3D(kiri, tengah, kiri + tebal, atas, zBelakang, zDepan);
    gambarSegmen3D(kiri, tengah - tebal / 2.0f, kanan, tengah + tebal / 2.0f, zBelakang, zDepan);
    gambarSegmen3D(kanan - tebal, bawah, kanan, atas, zBelakang, zDepan);
}

// gambar tulisan NRP "034" di dalam satu kotak grid (gridX, gridY)
// versi 2D (kode lama kamu, tidak diubah) - dipakai di mode orthogonal
void drawNRP_2D(int gridX, int gridY)
{
    float lebarAngka = 0.22f;
    float tinggiAngka = 0.55f;
    float jarak = 0.05f;

    float totalLebar = (lebarAngka * 3) + (jarak * 2);
    float marginKiri = (1.0f - totalLebar) / 2.0f;
    float baseY = gridY + (1.0f - tinggiAngka) / 2.0f;

    float x0 = gridX + marginKiri;
    float x1 = x0 + lebarAngka + jarak;
    float x2 = x1 + lebarAngka + jarak;

    gambarAngka0(x0, baseY, lebarAngka, tinggiAngka);
    gambarAngka3(x1, baseY, lebarAngka, tinggiAngka);
    gambarAngka4(x2, baseY, lebarAngka, tinggiAngka);
}

// versi 3D + animasi rotasi - dipakai di mode isometric
void drawNRP_3D(int gridX, int gridY)
{
    float lebarAngka = 0.22f;
    float tinggiAngka = 0.55f;
    float jarak = 0.05f;
    float tebalZ = 0.15f;

    float totalLebar = (lebarAngka * 3) + (jarak * 2);
    float marginKiri = (1.0f - totalLebar) / 2.0f;
    float baseY = (1.0f - tinggiAngka) / 2.0f;

    float x0 = marginKiri - 0.5f;
    float x1 = x0 + lebarAngka + jarak;
    float x2 = x1 + lebarAngka + jarak;

    glPushMatrix();
    // pindah ke tengah sel grid, sedikit di atas lantai (lantai z=0, tembok z=1)
    glTranslatef(gridX + 0.5f, gridY + 0.5f, 0.5f);

    glRotatef(nrpRotX, 1.0f, 0.0f, 0.0f);
    glRotatef(nrpRotY, 0.0f, 1.0f, 0.0f);
    glRotatef(nrpRotZ, 0.0f, 0.0f, 1.0f);

    gambarAngka0_3D(x0, baseY - 0.275f, lebarAngka, tinggiAngka, -tebalZ / 2.0f, tebalZ / 2.0f);
    gambarAngka3_3D(x1, baseY - 0.275f, lebarAngka, tinggiAngka, -tebalZ / 2.0f, tebalZ / 2.0f);
    gambarAngka4_3D(x2, baseY - 0.275f, lebarAngka, tinggiAngka, -tebalZ / 2.0f, tebalZ / 2.0f);
    glPopMatrix();
}

// switcher, dipanggil dari display() - tidak perlu ubah display()
void drawNRP(int gridX, int gridY)
{
    if (isIsometricMode)
        drawNRP_3D(gridX, gridY);
    else
        drawNRP_2D(gridX, gridY);
}

// cek apakah koordinat (x,y) masih di dalam grid 0..GRID_SIZE-1
bool isInsideGrid(int x, int y)
{
    return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE);
}

// cek apakah sel (x,y) di maze aktif adalah tembok
bool isWall(int x, int y)
{
    return (currentMaze[y][x] == 1);
}

// acak posisi NRP baru, harus jalan, bukan pintu masuk/keluar, bukan posisi player
void randomizeNRP()
{
    do
    {
        nrpX = rand() % GRID_SIZE;
        nrpY = rand() % GRID_SIZE;
    } while (
        currentMaze[nrpY][nrpX] != 0 ||
        (nrpX == ENTRANCE_X && nrpY == ENTRANCE_Y) ||
        (nrpX == EXIT_X && nrpY == EXIT_Y) ||
        (nrpX == playerX && nrpY == playerY));
}

// reset player ke pintu masuk, lalu acak ulang NRP
void resetLevel()
{
    playerX = ENTRANCE_X;
    playerY = ENTRANCE_Y;
    randomizeNRP();
}

// baca input keyboard buat gerak player dan ganti level
void keyboard(unsigned char key, int x, int y)
{
    int dx = 0, dy = 0;

    switch (key)
    {
    case 'w':
    case 'W':
        dy = 1;
        break; // gerak ke atas
    case 's':
    case 'S':
        dy = -1;
        break; // gerak ke bawah
    case 'a':
    case 'A':
        dx = -1;
        break; // gerak ke kiri
    case 'd':
    case 'D':
        dx = 1;
        break; // gerak ke kanan

    case 'c':
    case 'C':
    {
        // ganti maze aktif
        if (levelFlag == 1)
        {
            currentMaze = maze2;
            levelFlag = 2;
        }
        else
        {
            currentMaze = maze1;
            levelFlag = 1;
        }

        resetLevel();
        glutPostRedisplay();
        return;
    }

    case 'v':
    case 'V':
    {
        isIsometricMode = !isIsometricMode;
        glutPostRedisplay();
        return;
    }
    case 'j':
    case 'J':
    {
        if (isIsometricMode)
            mazeYawZ -= mazeRotStep;
        glutPostRedisplay();
        return;
    }
    case 'l':
    case 'L':
    {
        if (isIsometricMode)
            mazeYawZ += mazeRotStep;
        glutPostRedisplay();
        return;
    }
    case 'i':
    case 'I':
    {
        if (isIsometricMode)
            mazeTiltX -= mazeRotStep;
        glutPostRedisplay();
        return;
    }
    case 'k':
    case 'K':
    {
        if (isIsometricMode)
            mazeTiltX += mazeRotStep;
        glutPostRedisplay();
        return;
    }

    default:
        return;
    }

    int newX = playerX + dx;
    int newY = playerY + dy;

    // cek keluar batas grid
    if (!isInsideGrid(newX, newY))
    {
        return;
    }

    // cek nabrak tembok
    if (isWall(newX, newY))
    {
        return;
    }

    // gerakan valid, update posisi player
    playerX = newX;
    playerY = newY;

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (state != GLUT_DOWN)
        return;

    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        nrpRotAxis = 0;
        break; // rotasi sumbu X
    case GLUT_MIDDLE_BUTTON:
        nrpRotAxis = 1;
        break; // rotasi sumbu Y
    case GLUT_RIGHT_BUTTON:
        nrpRotAxis = 2;
        break; // rotasi sumbu Z
    }
}

void timer(int value)
{
    if (isIsometricMode) // animasi cuma jalan di mode isometric
    {
        switch (nrpRotAxis)
        {
        case 0:
            nrpRotX += nrpRotSpeed;
            if (nrpRotX >= 360.0f)
                nrpRotX -= 360.0f;
            break;
        case 1:
            nrpRotY += nrpRotSpeed;
            if (nrpRotY >= 360.0f)
                nrpRotY -= 360.0f;
            break;
        case 2:
            nrpRotZ += nrpRotSpeed;
            if (nrpRotZ >= 360.0f)
                nrpRotZ -= 360.0f;
            break;
        }
        glutPostRedisplay();
    }
    glutTimerFunc(16, timer, 0); // tetap dijadwalkan ulang walau mode orthogonal
}

// atur projection & modelview sesuai mode tampilan aktif
void setupView()
{
    float centerX = GRID_SIZE / 2.0f;
    float centerY = GRID_SIZE / 2.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (isIsometricMode)
    {
        double half = (double)GRID_SIZE * 0.75; // bisa diatur buat zoom
        glOrtho(centerX - half, centerX + half,
                centerY - half, centerY + half,
                -50.0, 50.0);
    }
    else
    {
        glOrtho(0.0, (double)GRID_SIZE, 0.0, (double)GRID_SIZE, -10.0, 10.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (isIsometricMode)
    {
        glTranslatef(centerX, centerY, 0.0f);
        glRotatef(mazeTiltX, 1.0f, 0.0f, 0.0f);
        glRotatef(mazeYawZ, 0.0f, 0.0f, 1.0f);
        glTranslatef(-centerX, -centerY, 0.0f);
    }
}

// dipanggil GLUT tiap kali layar perlu digambar ulang
void display()
{
    setupView(); // <-- baris baru, taruh paling atas

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMaze();
    drawNRP(nrpX, nrpY);
    drawPlayer();

    glutSwapBuffers();
}

// inisialisasi awal sebelum game jalan
void myinit()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (double)GRID_SIZE, 0.0, (double)GRID_SIZE, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST); // aktifkan depth test untuk 3D
    glEnable(GL_BLEND);      // aktifkan blending untuk transparansi
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    srand(time(NULL)); // seed random sekali di awal program

    randomizeNRP();
}

int main(int argc, char **argv)
{
    cout << "Maze 3D" << endl;
    cout << "W A S D untuk gerak, C untuk ganti level" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Maze 3D");

    myinit();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(16, timer, 0);

    glutMainLoop();
    return 0;
}