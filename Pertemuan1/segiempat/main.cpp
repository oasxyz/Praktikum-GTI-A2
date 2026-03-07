#include <GL/glut.h>
#include <stdlib.h>

void SegiEmpat(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,0.0f);
	glRectf(-0.18,0.18,0.18,-0.18);
	glFlush();
}

int main(int argc, char* argv[]){
	glutInitWindowSize(800,600);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Romualdus Yoas Wicaksono");
	glutDisplayFunc(SegiEmpat);
	glClearColor(0.0f,0.0f,1.0f,1.0f);
	glutMainLoop();
	return 0;
}
