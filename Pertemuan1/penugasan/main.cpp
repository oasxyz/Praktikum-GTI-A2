#include <GL/glut.h>
#include <stdlib.h>

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	//POINT
	glPointSize(6);
	glColor3f(0,0,0);
	glBegin(GL_POINTS);
		glVertex2f(-0.8, 0.8);
		glVertex2f(-0.8,0.5);
	glEnd();
	
	//LINES
	glColor3f(0,0,0);
	glBegin(GL_LINES);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
	glEnd();
	
	//LINE STRIP
	glBegin(GL_LINE_STRIP);
        glVertex2f(-0.5, 0.7);
        glVertex2f(-0.3, 0.9);
        glVertex2f(0, 0.7);
        glVertex2f(0.3, 0.9);
    glEnd();
    
    //LINE LOOP
    glBegin(GL_LINE_LOOP);
    	glVertex2f(0.2,0.4);
    	glVertex2f(0.4,0.4);
    	glVertex2f(0.4, 0.2);
        glVertex2f(0.2, 0.2);
    glEnd();
    
    //TRIANGLE FAN
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(-0.4, 0.4); // pusat
        glVertex2f(-0.3, 0.2);
        glVertex2f(-0.5, 0.2);
    glEnd();

    //TRIANGLE STRIP
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(0.2, 0.1);
        glVertex2f(0.2, -0.3);
        glVertex2f(0.4, 0.1);
//        glVertex2f(0.4, -0.6);
//        glVertex2f(0.6, -0.2);
//        glVertex2f(0.6, -0.6);
    glEnd();

    //QUADS
    glBegin(GL_QUADS);
        glVertex2f(-0.1, -0.2);
        glVertex2f(0.1, -0.2);
        glVertex2f(0.1, -0.4);
        glVertex2f(-0.1, -0.4);
    glEnd();

    //QUAD STRIP
    glBegin(GL_QUAD_STRIP);
        glVertex2f(0.5, 0.1);
        glVertex2f(0.5, -0.1);
        glVertex2f(0.7, 0.1);
        glVertex2f(0.7, -0.1);
//        glVertex2f(0.9, 0.1);
//        glVertex2f(0.9, -0.1);
    glEnd();
    
    
    //TUGAS 5 KUBUS
	// Persegi bawah 3
	glColor3f(0,0,1);
	// Persegi 1
	glBegin(GL_QUADS);
	    glVertex2f(-0.9, -0.8);
	    glVertex2f(-0.9, -0.7);
	    glVertex2f(-0.81, -0.7);
	    glVertex2f(-0.81, -0.8);
	glEnd();
	
	
	// Persegi 2
	glBegin(GL_QUADS);
	    glVertex2f(-0.79, -0.8);
	    glVertex2f(-0.79, -0.7);
	    glVertex2f(-0.7, -0.7);
	    glVertex2f(-0.7, -0.8);
	glEnd();
	
	// Persegi 3
	glBegin(GL_QUADS);
	    glVertex2f(-0.68, -0.8);
	    glVertex2f(-0.68, -0.7);
	    glVertex2f(-0.59, -0.7);
	    glVertex2f(-0.59, -0.8);
	glEnd();
	
	// Persegi atas 2 (ditengah ketiga persegi bawah)
	glColor3f(0,0,1);
	// Persegi 4
	glBegin(GL_QUADS);
	    glVertex2f(-0.85, -0.65);
	    glVertex2f(-0.85, -0.55);
	    glVertex2f(-0.76, -0.55);
	    glVertex2f(-0.76, -0.65);
	glEnd();
	
	// Persegi 5
	glBegin(GL_QUADS);
	    glVertex2f(-0.74, -0.65);
	    glVertex2f(-0.74, -0.55);
	    glVertex2f(-0.65, -0.55);
	    glVertex2f(-0.65, -0.65);
	glEnd();
    
	
	glFlush();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutCreateWindow("Romualdus Yoas Wicaksono");
	glClearColor(1,1,1,0);
	glutDisplayFunc(display);
	glutMainLoop();
	
	return 0;
}
