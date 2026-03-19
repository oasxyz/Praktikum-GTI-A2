#include <GL/glut.h>
#include <math.h>

/* Variabel transformasi sendi */
static int shoulder = 0, elbow = 0, wrist = 0;
static int thumb[2] = {0, 0};        /* [pangkal, ujung] */
static int indexFinger[2] = {0, 0};
static int middleFinger[2] = {0, 0};
static int ringFinger[2] = {0, 0};
static int pinkyFinger[2] = {0, 0};

/* Mode seleksi */
static int selectedFinger = 0;  /* 0=jempol, 1=telunjuk, 2=tengah, 3=manis, 4=kelingking */
static int selectedJoint = 0;   /* 0=pangkal, 1=ujung */

void init(void) 
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

/* Fungsi menggambar satu ruas jari */
void drawFingerSegment(float length, float width)
{
    glPushMatrix();
        glScalef(length, width, width);
        glutWireCube(1.0);
    glPopMatrix();
}

/* Fungsi menggambar jari dengan 2 ruas */
void drawFinger(int fingerJoints[2], float startX, float startY, float startZ, 
                float segmentLength, float segmentWidth, float angleMultiplier)
{
    glPushMatrix();
        glTranslatef(startX, startY, startZ);
        
        /* Ruas pangkal */
        glRotatef((GLfloat)fingerJoints[0] * angleMultiplier, 0.0, 0.0, 1.0);
        drawFingerSegment(segmentLength, segmentWidth);
        
        /* Ruas ujung */
        glTranslatef(segmentLength, 0.0, 0.0);
        glRotatef((GLfloat)fingerJoints[1] * angleMultiplier, 0.0, 0.0, 1.0);
        drawFingerSegment(segmentLength * 0.8, segmentWidth * 0.8);
        
    glPopMatrix();
}

void display(void) 
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
        /* Lengan atas */
        glTranslatef(-1.0, 0.0, 0.0);
        glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
        glTranslatef(1.0, 0.0, 0.0);
        
        glPushMatrix();
            glScalef(2.0, 0.4, 0.4);
            glutWireCube(1.0);
        glPopMatrix();
        
        /* Lengan bawah */
        glTranslatef(1.0, 0.0, 0.0);
        glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
        glTranslatef(1.0, 0.0, 0.0);
        
        glPushMatrix();
            glScalef(2.0, 0.35, 0.35);
            glutWireCube(1.0);
        glPopMatrix();
        
        /* Pergelangan */
        glTranslatef(1.0, 0.0, 0.0);
        glRotatef((GLfloat)wrist, 0.0, 0.0, 1.0);
        glTranslatef(0.5, 0.0, 0.0);
        
        glPushMatrix();
            glScalef(0.5, 0.5, 0.5);
            glutWireCube(1.0);
        glPopMatrix();
        
        /* Telapak tangan */
        glTranslatef(0.5, 0.0, 0.0);
        glPushMatrix();
            glScalef(1.2, 0.6, 0.3);
            glutWireCube(1.0);
        glPopMatrix();
        
        /* Jari-jari */
        glPushMatrix(); /* Jempol */
            glTranslatef(0.2, -0.2, -0.15);
            glRotatef(20.0, 0.0, 0.0, 1.0);
            if (selectedFinger == 0) glColor3f(1.0, 1.0, 1.0);
            drawFinger(thumb, 0.0, 0.0, 0.0, 0.5, 0.15, 1.0);
            glColor3f(1.0, 1.0, 1.0);
        glPopMatrix();
        
        glPushMatrix(); /* Telunjuk */
            glTranslatef(0.8, 0.2, -0.05);
            if (selectedFinger == 1) glColor3f(1.0, 1.0, 1.0);
            drawFinger(indexFinger, 0.0, 0.0, 0.0, 0.6, 0.12, 1.0);
            glColor3f(1.0, 1.0, 1.0);
        glPopMatrix();
        
        glPushMatrix(); /* Tengah */
            glTranslatef(0.8, 0.0, -0.05);
            if (selectedFinger == 2) glColor3f(1.0, 1.0, 1.0);
            drawFinger(middleFinger, 0.0, 0.0, 0.0, 0.65, 0.13, 1.0);
            glColor3f(1.0, 1.0, 1.0);
        glPopMatrix();
        
        glPushMatrix(); /* Manis */
            glTranslatef(0.8, -0.2, -0.05);
            if (selectedFinger == 3) glColor3f(1.0, 1.0, 1.0);
            drawFinger(ringFinger, 0.0, 0.0, 0.0, 0.6, 0.12, 1.0);
            glColor3f(1.0, 1.0, 1.0);
        glPopMatrix();
        
        glPushMatrix(); /* Kelingking */
            glTranslatef(0.8, -0.4, -0.05);
            if (selectedFinger == 4) glColor3f(1.0, 1.0, 1.0);
            drawFinger(pinkyFinger, 0.0, 0.0, 0.0, 0.5, 0.1, 1.0);
            glColor3f(1.0, 1.0, 1.0);
        glPopMatrix();
    
    glPopMatrix();
    
    glutSwapBuffers();
}

void reshape(int w, int h) 
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -8.0);
}

void keyboard(unsigned char key, int x, int y) 
{
    /* Seleksi jari (1-5) */
    if (key == '1') selectedFinger = 0;
    if (key == '2') selectedFinger = 4;
    if (key == '3') selectedFinger = 3;
    if (key == '4') selectedFinger = 2;
    if (key == '5') selectedFinger = 1;
    
    /* Seleksi ruas (F=pangkal, V=ujung) */
    if (key == 'f' || key == 'F') selectedJoint = 0;
    if (key == 'v' || key == 'V') selectedJoint = 1;
    
    /* Gerakan jari (Q=tekuk, E=luruskan) */
    if (key == 'q' || key == 'Q') {
        switch(selectedFinger) {
            case 0: thumb[selectedJoint] = (thumb[selectedJoint] + 5) % 90; break;
            case 1: indexFinger[selectedJoint] = (indexFinger[selectedJoint] + 5) % 90; break;
            case 2: middleFinger[selectedJoint] = (middleFinger[selectedJoint] + 5) % 90; break;
            case 3: ringFinger[selectedJoint] = (ringFinger[selectedJoint] + 5) % 90; break;
            case 4: pinkyFinger[selectedJoint] = (pinkyFinger[selectedJoint] + 5) % 90; break;
        }
    }
    if (key == 'e' || key == 'E') {
        switch(selectedFinger) {
            case 0: thumb[selectedJoint] = (thumb[selectedJoint] - 5) % 90; break;
            case 1: indexFinger[selectedJoint] = (indexFinger[selectedJoint] - 5) % 90; break;
            case 2: middleFinger[selectedJoint] = (middleFinger[selectedJoint] - 5) % 90; break;
            case 3: ringFinger[selectedJoint] = (ringFinger[selectedJoint] - 5) % 90; break;
            case 4: pinkyFinger[selectedJoint] = (pinkyFinger[selectedJoint] - 5) % 90; break;
        }
    }
    
    /* Kontrol lengan */
    if (key == 'w' || key == 'W') shoulder = (shoulder + 5) % 360;
    if (key == 's' || key == 'S') shoulder = (shoulder - 5) % 360;
    if (key == 'a' || key == 'A') elbow = (elbow + 5) % 360;
    if (key == 'd' || key == 'D') elbow = (elbow - 5) % 360;
    if (key == 'z' || key == 'Z') wrist = (wrist + 5) % 360;
    if (key == 'x' || key == 'X') wrist = (wrist - 5) % 360;
    
    /* Preset pose */
    if (key == 'g' || key == 'G') { /*Pose Genggam */
        for (int i = 0; i < 2; i++) {
            thumb[i] = 30;
            indexFinger[i] = middleFinger[i] = ringFinger[i] = pinkyFinger[i] = 45;
        }
    }
    if (key == 'p' || key == 'P') { /*Pose Pointing */
        for (int i = 0; i < 2; i++) {
            middleFinger[i] = ringFinger[i] = pinkyFinger[i] = 45;
            indexFinger[i] = 0;
            thumb[i] = 30;
        }
    }
    if (key == 'k' || key == 'K') { /* Pose Peace */
        for (int i = 0; i < 2; i++) {
            thumb[i] = 30;
            ringFinger[i] = pinkyFinger[i] = 45;
        }
        indexFinger[0] = indexFinger[1] = 0;
        middleFinger[0] = middleFinger[1] = 0;
    }
    if (key == '0') { /* Reset Posisi*/
        shoulder = elbow = wrist = 0;
        for (int i = 0; i < 2; i++) {
            thumb[i] = indexFinger[i] = middleFinger[i] = 
            ringFinger[i] = pinkyFinger[i] = 0;
        }
    }
    
    glutPostRedisplay();
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Romualdus Yoas Wicaksono");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}
