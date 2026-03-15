#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>

#define PI 3.1415926535898

void drawCircle(float radius){
	int circle_points = 100;
	float angle;
	
	glBegin(GL_POLYGON);
	for(int i = 0; i < circle_points;i++){
		angle = 2 * PI * i / circle_points;
		glVertex2f(cos(angle) * radius, sin(angle) * radius);
	}
	glEnd();
}

//void drawCircle(float radius){
//	int circle_points = 100;
//	float angle;
//	
//	glBegin(GL_LINE_LOOP);
//	for(int i = 0; i < circle_points;i++){
//		angle = 2 * PI * i / circle_points;
//		glVertex2f(cos(angle) * radius, sin(angle) * radius);
//	}
//	glEnd();
//}

void RenderScene(void){
	glClear(GL_COLOR_BUFFER_BIT);
	
	//LAMPU DEPAN
	glPushMatrix();
	glColor3f(1.0f,1.0f,0.0f);
		glBegin(GL_QUADS);
        glVertex2f(0.24, 0.04);
        glVertex2f(0.26, 0.04);
        glVertex2f(0.26, 0.08);
        glVertex2f(0.24, 0.08);
    	glEnd();
    glPopMatrix();
    
    //LAMPU BELAKANG
	glPushMatrix();
	glColor3f(1.0f,0.0f,0.0f);
		glBegin(GL_QUADS);
        glVertex2f(-0.24, 0.04);
        glVertex2f(-0.26, 0.04);
        glVertex2f(-0.26, 0.08);
        glVertex2f(-0.24, 0.08);
    	glEnd();
    glPopMatrix();
	
	//ATEP MOBIL
    glPushMatrix();
	glColor3f(0.0f,1.0f,1.0f);
		glBegin(GL_QUADS);
        glVertex2f(-0.2, 0.0);
        glVertex2f(0.2, 0.0);
        glVertex2f(0.1, 0.18);
        glVertex2f(-0.1, 0.18);
    	glEnd();
    glPopMatrix();
    
    //STRIP KACA
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex2f(0.0f,0.0f);
		glVertex2f(0.0f,2.0f);
		glEnd();
	glPopMatrix();
	
	//BODY MOBIL
	glPushMatrix();
	glColor3f(0.0f,0.40f,0.0f);
		glBegin(GL_QUADS);
        glVertex2f(-0.24, 0.0);
        glVertex2f(0.24, 0.0);
        glVertex2f(0.24, 0.1);
        glVertex2f(-0.24, 0.1);
    	glEnd();
    glPopMatrix();
	
	// BAN BELAKANG
	glPushMatrix();
		glTranslatef(-0.15f, 0.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f); 
		drawCircle(0.05f);
	glPopMatrix();
	
	
	// BAN DEPAN
	glPushMatrix();
		glTranslatef(0.15f, 0.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		drawCircle(0.05f);
	glPopMatrix();
	
	glFlush();
}



int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitWindowSize(800,600);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Romualdus Yoas Wicaksono");
	glutDisplayFunc(RenderScene);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glutMainLoop();
	
	return 0;
}

