#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// ================== CAMERA ==================
float angle=0.0, deltaAngle = 0.0, ratio;
float x=0.0f,y=1.75f,z=15.0f;
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w;

// ================== RESHAPE ==================
void Reshape(int w1, int h1)
{
    if(h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45,ratio,0.1,1000);

    glMatrixMode(GL_MODELVIEW);
}

// ================== CAMERA CONTROL ==================
void orientMe(float ang)
{
    lx = sin(ang);
    lz = -cos(ang);
}

void moveMeFlat(int i)
{
    x = x + i*(lx)*0.1;
    z = z + i*(lz)*0.1;
}

// ================== GRID ==================
void Grid() {
    double i;
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap = 1.5;

    glColor3f(0.5, 0.5, 0.5);

    glBegin(GL_LINES);
    for(i=Z_MIN;i<Z_MAX;i+=gap)
    {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }

    for(i=X_MIN;i<X_MAX;i+=gap)
    {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }
    glEnd();
}

// ================== OBJECT ==================
void KotakKayu()
{
    glColor3f(0.8, 0.5, 0.2);

    // depan
    glPushMatrix();
    glTranslatef(0,0,3);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glVertex3f(-3,-3,0);
    glVertex3f(3,-3,0);
    glVertex3f(3,3,0);
    glVertex3f(-3,3,0);
    glEnd();
    glPopMatrix();

    // belakang
    glPushMatrix();
    glTranslatef(0,0,-3);
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glVertex3f(-3,-3,0);
    glVertex3f(3,-3,0);
    glVertex3f(3,3,0);
    glVertex3f(-3,3,0);
    glEnd();
    glPopMatrix();

    // kiri
    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(0,0,3);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glVertex3f(-3,-3,0);
    glVertex3f(3,-3,0);
    glVertex3f(3,3,0);
    glVertex3f(-3,3,0);
    glEnd();
    glPopMatrix();

    // kanan
    glPushMatrix();
    glRotatef(-90,0,1,0);
    glTranslatef(0,0,3);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glVertex3f(-3,-3,0);
    glVertex3f(3,-3,0);
    glVertex3f(3,3,0);
    glVertex3f(-3,3,0);
    glEnd();
    glPopMatrix();

    // atas
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glTranslatef(0,0,3);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glVertex3f(-3,-3,0);
    glVertex3f(3,-3,0);
    glVertex3f(3,3,0);
    glVertex3f(-3,3,0);
    glEnd();
    glPopMatrix();

    // bawah
    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0,0,3);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glVertex3f(-3,-3,0);
    glVertex3f(3,-3,0);
    glVertex3f(3,3,0);
    glVertex3f(-3,3,0);
    glEnd();
    glPopMatrix();
}

// ================== DISPLAY ==================
void display() {

    if (deltaMove)
        moveMeFlat(deltaMove);

    if (deltaAngle) {
        angle += deltaAngle;
        orientMe(angle);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // ?? kamera selalu diset di sini
    gluLookAt(
        x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f
    );

    Grid();
    KotakKayu();

    glutSwapBuffers();
}

// ================== INPUT ==================
void pressKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
        case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
        case GLUT_KEY_UP : deltaMove = 1; break;
        case GLUT_KEY_DOWN : deltaMove = -1; break;
    }
}

void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT :
        case GLUT_KEY_RIGHT : deltaAngle = 0.0f; break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0; break;
    }
}

// ================== LIGHTING ==================
void lighting(){
    GLfloat light_pos[] = {0.0f, 20.0f, 10.0f, 1.0f};

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

// ================== INIT ==================
void init(void)
{
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
}

// ================== MAIN ==================
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,480);
    glutCreateWindow("3D Camera + Lighting");

    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);

    lighting();
    init();

    glutMainLoop();
    return 0;
}
