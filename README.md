# Maze Game 3D OpenGL

Proyek ini adalah implementasi tugas Grafika Komputer untuk membangun aplikasi labirin (maze) 3 dimensi interaktif menggunakan OpenGL dan GLUT dalam bahasa C++.

## Fitur Utama
* **Lingkungan 3D Penuh:** Dinding labirin, lantai transparan, dan objek pemain dirender sebagai balok 3D yang dibangun menggunakan definisi vertex manual (tanpa `glutSolidCube`).
* **Multi-Level:** Tersedia 2 layout peta labirin yang dapat ditukar secara langsung.
* **Kamera Dinamis:**
    * **Orthogonal:** Sudut pandang atas (top-down) untuk melihat rute labirin.
    * **Isometrik:** Sudut pandang miring 3D untuk menonjolkan kedalaman dan volume bangunan.
* **Interaksi Rotasi Lingkungan:** Saat berada di mode isometrik, labirin dan lantai dapat diputar 360 derajat pada sumbunya. Posisi perputaran ini akan otomatis tersimpan ketika pengguna berganti kamera.
* **Objek 3D Beranimasi:** Menampilkan inisial 3D yang berputar otomatis di porosnya saat mode isometrik aktif. Sumbu rotasi (X, Y, atau Z) dapat diubah secara dinamis.
* **Collision Detection:** Sistem deteksi tabrakan yang secara akurat mencegah balok pemain menembus dinding labirin.

## Panduan Kontrol
| Input | Aksi | Deskripsi |
| :--- | :--- | :--- |
| **W, A, S, D** | Gerak Player | Memindahkan balok pemain ke atas, kiri, bawah, dan kanan. |
| **C / c** | Ganti Maze | Menukar layout antara Maze 1 dan Maze 2, lalu mereset posisi awal. |
| **V / v** | Ganti Pandangan | Mengganti mode kamera antara Orthogonal dan Isometrik. |
| **J, L** | Rotasi Z (Maze) | (Mode Isometrik) Memutar labirin sejajar lantai (seperti komidi putar). |
| **I, K** | Rotasi X (Maze) | (Mode Isometrik) Mendongakkan atau merebahkan kemiringan labirin. |
| **Klik Kiri** | Rotasi Y (Inisial) | Mengubah sumbu rotasi animasi inisial ke sumbu Y. |
| **Klik Tengah** | Rotasi X (Inisial) | Mengubah sumbu rotasi animasi inisial ke sumbu X. |
| **Klik Kanan** | Rotasi Z (Inisial) | Mengubah sumbu rotasi animasi inisial ke sumbu Z. |
| **Q / q** | Keluar | Menghentikan program. |

## Cara Menjalankan
1.  Pastikan IDE (seperti Code::Blocks) sudah terkonfigurasi dengan library FreeGLUT/GLUT.
2.  Lakukan *compile and build* pada *source code*.
3.  Jalankan aplikasi. Panduan singkat akan tampil di terminal bawaan sebelum jendela grafis terbuka.
