#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
float postY=17.0;
float postX=0.0;
int currentMaze = 1;

void drawRect(float left, float top, float right, float bottom){
    glBegin(GL_POLYGON);
    glVertex2f(left, top);
    glVertex2f(right, top);
    glVertex2f(right, bottom);
    glVertex2f(left, bottom);
    glEnd();
}
void maze1(){
    glColor3f(1.0, 0.0, 0.0); 
    // Kotak Atas Kiri 
    drawRect(-18.0, 18.0, -1.5, 16.0);

    // Kotak Atas Kanan 
    drawRect(1.5, 18.0, 18.0, 16.0);

    // Kotak Bawah Kiri
    drawRect(-18.0, -16.0, -1.5, -18.0);

    // Kotak Bawah Kanan
    drawRect(1.5, -16.0, 18.0, -18.0);

    // Kotak Kiri Penuh 
    drawRect(-18.0, 16.0, -16.0, -16.0);

    // Kotak Kanan Penuh
    drawRect(16.0, 16.0, 18.0, -16.0);
    
    // Baris Y = 14
    drawRect(-14.5, 14.5, -5.5, 13.5);
    drawRect(-2.5, 14.5, 2.5, 13.5);
    drawRect(5.5, 14.5, 10.5, 13.5);
    drawRect(13.5, 14.5, 18.0, 13.5);

    // Baris Y = 10
    drawRect(-18.0, 10.5, -13.5, 9.5);
    drawRect(-10.5, 10.5, -5.5, 9.5);
    drawRect(1.5, 10.5, 6.5, 9.5);
    drawRect(9.5, 10.5, 18.0, 9.5);

    // Baris Y = 6
    drawRect(-18.0, 6.5, -9.5, 5.5);
    drawRect(-6.5, 6.5, 2.5, 5.5);
    drawRect(5.5, 6.5, 14.5, 5.5);

    // Baris Y = 2
    drawRect(-14.5, 2.5, -5.5, 1.5);
    drawRect(-2.5, 2.5, 2.5, 1.5);

    // Baris Y = -2
    drawRect(-18.0, -1.5, -5.5, -2.5);
    drawRect(1.5, -1.5, 10.5, -2.5);
    drawRect(9.5, -1.5, 14.5, -2.5);

    // Baris Y = -6
    drawRect(-14.5, -5.5, -9.5, -6.5);
    drawRect(-10.5, -5.5, -1.5, -6.5);
    drawRect(1.5, -5.5, 10.5, -6.5);
    drawRect(13.5, -5.5, 18.0, -6.5);

    // Baris Y = -10
    drawRect(-18.0, -9.5, -9.5, -10.5);
    drawRect(-6.5, -9.5, -1.5, -10.5);
    drawRect(1.5, -9.5, 6.5, -10.5);
    drawRect(9.5, -9.5, 14.5, -10.5);

    // Baris Y = -14
    drawRect(-18.0, -13.5, -13.5, -14.5);
    drawRect(-10.5, -13.5, -1.5, -14.5);
    drawRect(5.5, -13.5, 10.5, -14.5);

    // Kolom X = -14
    drawRect(-14.5, 14.5, -13.5, 9.5);
    drawRect(-14.5, 2.5, -13.5, -6.5);
    drawRect(-14.5, -9.5, -13.5, -14.5);

    // Kolom X = -10
    drawRect(-10.5, 18.0, -9.5, 13.5);
    drawRect(-10.5, 10.5, -9.5, 5.5);
    drawRect(-10.5, -1.5, -9.5, -6.5);
    drawRect(-10.5, -9.5, -9.5, -14.5);

    // Kolom X = -6
    drawRect(-6.5, 10.5, -5.5, 5.5);
    drawRect(-6.5, 6.5, -5.5, 1.5);
    drawRect(-6.5, -5.5, -5.5, -10.5);

    // Kolom X = -2
    drawRect(-2.5, 14.5, -1.5, 9.5);
    drawRect(-2.5, 6.5, -1.5, -2.5);

    // Kolom X = 2
    drawRect(1.5, 18.0, 2.5, 13.5);
    drawRect(1.5, 14.5, 2.5, 9.5);
    drawRect(1.5, -5.5, 2.5, -18.0);

    // Kolom X = 6
    drawRect(5.5, 10.5, 6.5, 5.5);
    drawRect(5.5, 6.5, 6.5, -10.5);

    // Kolom X = 10
    drawRect(9.5, 14.5, 10.5, 9.5);
    drawRect(9.5, 6.5, 10.5, 1.5);
    drawRect(9.5, -1.5, 10.5, -6.5);
    drawRect(9.5, -9.5, 10.5, -14.5);

    // Kolom X = 14
    drawRect(13.5, 6.5, 14.5, 1.5);
    drawRect(13.5, 2.5, 14.5, -2.5);
    drawRect(13.5, -5.5, 14.5, -10.5);
    drawRect(13.5, -9.5, 14.5, -18.0);
}

void maze2(){

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.0);
    glVertex2f(-1.0 + postX ,1.0 + postY);
    glVertex2f(1.0 + postX ,1.0 + postY);
    glVertex2f(1.0 + postX ,-1.0 + postY);
    glVertex2f(-1.0 + postX ,-1.0 + postY);
    glEnd();

    if(currentMaze == 1){
        maze1();
    } else {
        maze2();
    }
    glFlush();
}

void myinit(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-18.0,18.0,-18.0,18.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,1.0,1.0);
}

void input(unsigned char key, int x, int y){
    if(key == 'q') {
       exit(0);
    }
    if(key == 'w' || key == 'W'){
        postY +=0.1;

    }
    if(key=='s' || key == 'S'){
        postY -=0.1;
    }
    if (key=='a' || key=='A'){
        postX -=0.1;
    }
    if (key=='d' || key=='D'){
        postX +=0.1;
    }
    if(key == 'c' || key == 'C'){
        currentMaze = (currentMaze == 1) ? 2 : 1;
        glutPostRedisplay(); 
    }
    display();
}

int main(int argc, char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(750,750);
	glutCreateWindow("demo 2 maze statis");
	
	glutDisplayFunc(display);
	glutKeyboardFunc(input);

	myinit();
	glutMainLoop();
	return 0;
}
