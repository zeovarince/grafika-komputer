#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<iostream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
float postY=0.0;
float postX=0.0;
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10);
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-3.0 + postX,-3.0 + postY);
	glVertex2f(-2.0 + postX,0.0 + postY);
	glVertex2f(-4.0 + postX,2.0 + postY);
	glVertex2f(-1.0 + postX,2.0 + postY);
	glVertex2f(0.0 + postX,4.0 + postY);
	glVertex2f(1.0 + postX,2.0 + postY);
	glVertex2f(4.0 + postX,2.0 + postY);
	glVertex2f(2.0 + postX,-0.0 + postY);
	glVertex2f(3.0 + postX,-3.0 + postY);
	glVertex2f(0.0 + postX,-1.0 + postY);



	glEnd();

	glFlush();
}

void myinit(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.0,5.0,-5.0,5.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0,0.0,0.0,1.0);
	glColor3f(1.0,1.0,1.0);

    srand (time(NULL));
    int randAngka = rand() % 10;
    cout << "Angka hasil random: " << randAngka << endl;
}

void input(unsigned char key, int x, int y){
    if(key == 'q') {
       exit(0);
    }
    if(key == 'w'){
        postY +=1.5;

    }
    if(key=='s'){
        postY -=1.5;
        cout <<postY<<endl;
    }
    if (key=='a'){
        postX -=0.1;
        cout << "Nilai pos" << postY;
    }
    if (key=='d'){
        postX +=0.1;
        cout <<'ke kanan ';
    }
    if (key=='r'){
        srand (time(NULL));
        int randAngka = rand() % 10;
        cout << randAngka;
    }
    display();
}

int main(int argc, char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(750,750);
	glutInitWindowPosition(500,50);
	glutCreateWindow("RUMAH WOWOKK");
	glutDisplayFunc(display);
	glutKeyboardFunc(input);
	myinit();
	glutMainLoop();

	return 0;
}
