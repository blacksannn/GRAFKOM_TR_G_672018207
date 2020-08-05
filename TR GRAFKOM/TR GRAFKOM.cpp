#include <GL/freeglut.h>\
#include <window.s>
#include "header.h"


GLuint _textureID;
float angle = 0.0f;

void drawCube() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, -0.5, -0.5);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glRotatef(angle, 0.0, 1.0, 0.0);
	drawCube();
	glPopMatrix();

	glutSwapBuffers();
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	_textureID = loadBMP_custom("C:/Users/Andrew Nussy/source/repos/TR GRAFKOM/TR GRAFKOM/Woman12.bmp");
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 30, timer, 0);
	angle += 1.0f;

}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {

	case 'j':
		glRotatef(2.0, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;

	case 'u':
		glRotatef(-2.0, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;

	case 'i':
		glRotatef(2.0, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;

	case 'y':
		glRotatef(-2.0, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;

	case 'n':
		glRotatef(2.0, 0.0, 0.0, 1.0);
		glutPostRedisplay();
		break;

	case 'm':
		glRotatef(-2.0, 0.0, 0.0, 1.0);
		glutPostRedisplay();
		break;

	case 'r':
		glTranslatef(3.0, 0.0, 0.0);
		glutPostRedisplay();
		break;

	case 'w':
		glTranslatef(-3.0, 0.0, 0.0);
		glutPostRedisplay();
		break;

	case 'e':
		glTranslatef(0.0, 3.0, 0.0);
		glutPostRedisplay();
		break;

	case 'd':
		glTranslatef(0.0, -3.0, 0.0);
		glutPostRedisplay();
		break;

	case 'x':
		if (_textureID) {
			_textureID = 0;
			glDisable(GL_DEPTH_TEST);
		}
		else {
			_textureID = 1;
			glEnable(GL_DEPTH_TEST);
		}
	}
}

void key(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_PAGE_UP:
		glTranslatef(0.0, 0.0, 0.1);
		glutPostRedisplay();
		
		break;

	case GLUT_KEY_PAGE_DOWN:
		glTranslatef(0.0, 0.0, -0.1);
		glutPostRedisplay();
		break;
	}

}

void ukuran(int lebar, int tinggi) {
	if (tinggi == 0) tinggi = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0, lebar / tinggi, 5.0, 500.0);
	glTranslatef(0.0, -5.0, -150.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Texturing");
	glutDisplayFunc(display);
	myinit();
	//glutKeyboardFunc(keyboard);
	//glutSpecialFunc(key);
	//glutReshapeFunc(ukuran);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();

	return 0;
}