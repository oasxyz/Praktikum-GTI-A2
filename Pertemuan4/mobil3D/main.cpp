#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// ======================
// Kamera
// ======================
float angle = 0.0f, deltaAngle = 0.0f, ratio;

float x = 0.0f;
float y = 2.0f;
float z = 15.0f;

float lx = 0.0f;
float ly = 0.0f;
float lz = -1.0f;

int deltaMove = 0;
int h, w;

// ======================
// Lighting
// ======================
const GLfloat light_ambient[]  = {0.3f, 0.3f, 0.3f, 1.0f};
const GLfloat light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {5.0f, 10.0f, 10.0f, 1.0f};

const GLfloat mat_ambient[]    = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[]    = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[]   = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {80.0f};

// ======================
// Sisi Kotak
// ======================
void SisiKotak(float w, float h) {

    glBegin(GL_QUADS);

        glNormal3f(0.0f, 0.0f, 1.0f);

        glVertex3f(-w, -h, 0.0f);
        glVertex3f( w, -h, 0.0f);
        glVertex3f( w,  h, 0.0f);
        glVertex3f(-w,  h, 0.0f);

    glEnd();
}

// ======================
// Kotak 3D
// ======================
void Kotak3D(float lx, float ly, float lz) {

    // Depan
    glPushMatrix();
        glTranslatef(0, 0, lz);
        SisiKotak(lx, ly);
    glPopMatrix();

    // Belakang
    glPushMatrix();
        glRotatef(180, 0, 1, 0);
        glTranslatef(0, 0, lz);
        SisiKotak(lx, ly);
    glPopMatrix();

    // Atas
    glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        glTranslatef(0, 0, ly);
        SisiKotak(lx, lz);
    glPopMatrix();

    // Bawah
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0, 0, ly);
        SisiKotak(lx, lz);
    glPopMatrix();

    // Kanan
    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 0, lx);
        SisiKotak(lz, ly);
    glPopMatrix();

    // Kiri
    glPushMatrix();
        glRotatef(-90, 0, 1, 0);
        glTranslatef(0, 0, lx);
        SisiKotak(lz, ly);
    glPopMatrix();
}

// ======================
// Roda
// ======================
void Roda() {

    glPushMatrix();

        glColor3f(0.12f, 0.12f, 0.12f);

        // Rotasi dihapus agar sumbu Z otomatis menjadi ketebalan ban.
        // Radius X dan Y dibuat 0.35, ketebalan Z dibuat 0.15 agar bentuknya pipih seperti ban asli.
        Kotak3D(0.35f, 0.35f, 0.15f);

    glPopMatrix();
}

// ======================
// Mobil
// ======================
void Mobil3D() {

    // ======================
    // Body utama
    // ======================
    glPushMatrix();

        glColor3f(0.25f, 0.5f, 1.0f);

        // Posisi Y disesuaikan (0.7f) agar bawah body pas berada di poros roda
        glTranslatef(0.0f, 0.7f, 0.0f);

        // Proporsi diubah: panjang 2.2, tinggi 0.35, lebar 1.0
        Kotak3D(2.2f, 0.35f, 1.0f);

    glPopMatrix();

    // ======================
    // Atas / kabin
    // ======================
    glPushMatrix();

        glColor3f(0.2f, 0.4f, 0.9f);

        // [UBAH] Posisi Y (1.4f) dihitung agar kabin duduk presisi di atas body utama (0.7 + 0.35 + 0.35 = 1.4)
        glTranslatef(0.0f, 1.4f, 0.0f);

        // [UBAH] Proporsi diseimbangkan dengan body bawah
        Kotak3D(1.1f, 0.35f, 0.8f);

    glPopMatrix();

    // ======================
    // Roda
    // ======================
    // [UBAH] Translasi disesuaikan dengan proporsi body yang baru:
    // X (maju/mundur) = 1.5f, Y (tinggi poros) = 0.35f, Z (lebar ban) = 1.0f

    // Depan kiri
    glPushMatrix();
        glTranslatef(-1.5f, 0.35f, 1.0f);
        Roda();
    glPopMatrix();

    // Depan kanan
    glPushMatrix();
        glTranslatef(1.5f, 0.35f, 1.0f);
        Roda();
    glPopMatrix();

    // Belakang kiri
    glPushMatrix();
        glTranslatef(-1.5f, 0.35f, -1.0f);
        Roda();
    glPopMatrix();

    // Belakang kanan
    glPushMatrix();
        glTranslatef(1.5f, 0.35f, -1.0f);
        Roda();
    glPopMatrix();
}

// ======================
// Grid
// ======================
void Grid() {

    double i;

    const float Z_MIN = -30;
    const float Z_MAX = 30;

    const float X_MIN = -30;
    const float X_MAX = 30;

    const float gap = 2.0f;

    glDisable(GL_LIGHTING);

    glColor3f(0.4f, 0.4f, 0.4f);

    glBegin(GL_LINES);

        for (i = Z_MIN; i <= Z_MAX; i += gap) {

            glVertex3f(i, 0, Z_MIN);
            glVertex3f(i, 0, Z_MAX);
        }

        for (i = X_MIN; i <= X_MAX; i += gap) {

            glVertex3f(X_MIN, 0, i);
            glVertex3f(X_MAX, 0, i);
        }

    glEnd();

    glEnable(GL_LIGHTING);
}

// ======================
// Rotasi kamera
// ======================
void orientMe(float ang) {

    lx = sin(ang);
    lz = -cos(ang);

    glLoadIdentity();

    gluLookAt(
        x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f
    );
}

// ======================
// Gerak kamera
// ======================
void moveMeFlat(int i) {

    // SUPER pelan
    x = x + i * (lx) * 0.0025f;
    z = z + i * (lz) * 0.0025f;

    glLoadIdentity();

    gluLookAt(
        x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f
    );
}

// ======================
// Display
// ======================
void display() {

    if (deltaMove)
        moveMeFlat(deltaMove);

    if (deltaAngle) {

        angle += deltaAngle;
        orientMe(angle);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Grid();
    Mobil3D();

    glutSwapBuffers();
    glFlush();
}

// ======================
// Resize
// ======================
void Reshape(int w1, int h1) {

    if (h1 == 0)
        h1 = 1;

    w = w1;
    h = h1;

    ratio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(45, ratio, 0.1, 1000);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(
        x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f
    );
}

// ======================
// Arrow Key
// ======================
void pressKey(int key, int x2, int y2) {

    switch (key) {

        // SUPER halus
        case GLUT_KEY_LEFT:
            deltaAngle = -0.0008f;
            break;

        case GLUT_KEY_RIGHT:
            deltaAngle = 0.0008f;
            break;

        case GLUT_KEY_UP:
            deltaMove = 1;
            break;

        case GLUT_KEY_DOWN:
            deltaMove = -1;
            break;
    }
}

void releaseKey(int key, int x2, int y2) {

    switch (key) {

        case GLUT_KEY_LEFT:
            if (deltaAngle < 0.0f)
                deltaAngle = 0.0f;
            break;

        case GLUT_KEY_RIGHT:
            if (deltaAngle > 0.0f)
                deltaAngle = 0.0f;
            break;

        case GLUT_KEY_UP:
            if (deltaMove > 0)
                deltaMove = 0;
            break;

        case GLUT_KEY_DOWN:
            if (deltaMove < 0)
                deltaMove = 0;
            break;
    }
}

// ======================
// Keyboard
// ======================
void keyboard(unsigned char k, int x2, int y2) {

    switch (k) {

        case 'q':
        case 'Q':
        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

// ======================
// Lighting
// ======================
void lighting() {

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

// ======================
// Init
// ======================
void init() {

    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// ======================
// Main
// ======================
int main(int argc, char **argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);

    glutCreateWindow("Mobil 3D - Romualdus Yoas Wicaksono");

    glutIgnoreKeyRepeat(1);

    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    glutKeyboardFunc(keyboard);

    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutReshapeFunc(Reshape);

    lighting();
    init();

    printf("=== Mobil 3D ===\n");
    printf("Arrow Keys : Kamera\n");
    printf("Q / ESC    : Keluar\n");

    glutMainLoop();

    return 0;
}
