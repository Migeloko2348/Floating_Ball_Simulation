#include <windows.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

char title[] = "3D Shapes";
int slices = 50;
int stacks = 50;
GLfloat x_pos = 0;
GLfloat z_pos = 0;
GLfloat gravity = 0.000001f;
GLfloat speed = 0;
bool falling = false;
double a = 0;
GLfloat max_z = -5.0f;
GLfloat test = 1.0f;
GLfloat pin_y = -0.5f;
GLfloat pin_z = -9.0f;
GLfloat y_pos = 1.5f;
GLfloat waterLevel = -0.4f;
GLfloat boundary = -0.4+0.3;
GLfloat potential = 0.0005f;
GLfloat radius = 0.3f;


void renderH1(std::string str, GLfloat px, GLfloat py, int r, int g, int b){
    int l = str.size(), i;

    glPushMatrix();
        glRasterPos3f(px, py, 0);
        for(i = 0; i < l; i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
        }
    glPopMatrix();
}

void renderP(std::string str, GLfloat px, GLfloat py, int r, int g, int b){
    int l = str.size(), i;
    float x = 0.0f;
    glPushMatrix();
        glRasterPos3f(px, py, 0);
        for(i = 0; i < l; i++){
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
            x += 0.048f;
        }
}

void initGL() {
    glClearColor(189/255.0f, 225/255.0f, 247/255.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    cout << test << endl;
    gluLookAt(0.0, 0.8f, 0.5f,
              0.0, 0.5f, -1.0,
              0.0, 1.0f, 0.0);
}

void display() {
    if (falling) {
        speed = speed - gravity;
        y_pos = y_pos + speed;
    }

    if (y_pos < waterLevel-0.02) {
        speed = 0;
        speed = speed + potential;
        if (potential > 0)
            potential -= 0.0002;
        else
            potential = 0;
    }

    if (y_pos < boundary) {
        waterLevel -= speed;
    }


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glColor3d(1,0,0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(1, 1, 1, 0.5f);
    glPushMatrix();
        glTranslated(0,y_pos,-6.0f);
        glutSolidSphere(radius,slices,stacks);
    glPopMatrix();


    glBegin(GL_QUADS);
        glColor4f(90/255.0, 101/255.0, 104/255.0, 1);
        glVertex3f( 2.0f, 0.0f, -7.0f);
        glVertex3f(-2.0f, 0.0f, -7.0f);
        glVertex3f(-2.0f,  -2.0f, -7.0f);
        glVertex3f( 2.0f,  -2.0f, -7.0f);

        glColor4f(34/255.0, 34/255.0, 34/255.0, 1);
        glVertex3f(-2.0f, 0.0f, -7.0f);
        glVertex3f(-2.0f,  -2.0f, -7.0f);
        glVertex3f(-2.0f,  -2.0f, -5.0f);
        glVertex3f(-2.0f,  0.0f, -5.0f);

        glColor4f(34/255.0, 34/255.0, 34/255.0, 1);
        glVertex3f(2.0f, 0.0f, -7.0f);
        glVertex3f(2.0f,  -2.0f, -7.0f);
        glVertex3f(2.0f,  -2.0f, -5.0f);
        glVertex3f(2.0f,  0.0f, -5.0f);

        glColor4f(82/255.0, 116/255.0, 145/255.0, 1);
        glVertex3f(-2.0f,  -2.0f, -7.0f);
        glVertex3f( 2.0f,  -2.0f, -7.0f);
        glVertex3f( 2.0f,  -2.0f, -5.0f);
        glVertex3f(-2.0f,  -2.0f, -5.0f);

        glColor4f(63/255.0, 97/255.0, 126/255.0, 0.5f);
        glVertex3f( 2.0f, waterLevel, -5.0f);
        glVertex3f(-2.0f, waterLevel, -5.0f);
        glVertex3f(-2.0f,  -2.0f, -5.0f);
        glVertex3f( 2.0f,  -2.0f, -5.0f);

        // top
        // water level -0.3f
        glColor4f(82/255.0, 116/255.0, 145/255.0, 0.5f);
        glVertex3f(-2.0f,  waterLevel, -7.0f);
        glVertex3f( 2.0f,  waterLevel, -7.0f);
        glVertex3f( 2.0f,  waterLevel, -5.0f);
        glVertex3f(-2.0f,  waterLevel, -5.0f);

        glColor4f(90/255.0, 101/255.0, 104/255.0, 0.3f);
        glVertex3f( 2.0f, 0.0f, -5.0f);
        glVertex3f(-2.0f, 0.0f, -5.0f);
        glVertex3f(-2.0f,  -2.0f, -5.0f);
        glVertex3f( 2.0f,  -2.0f, -5.0f);

    glEnd();

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void idle(void){
    glutPostRedisplay();
}

void resetDefaults(){
    z_pos = 0;
    x_pos = 0;
    falling = false;
    pin_y = -0.5f;
    pin_z = -9.0f;
    char title[] = "3D Shapes";
    gravity = 0.000001f;
    speed = 0;
    a = 0;
    y_pos = 1.5f;
    waterLevel = -0.4f;
    boundary = -0.4+0.3;
    potential = 0.0005f;
    radius = 0.3f;
}

static void key(unsigned char key, int x, int y){
    if (key == 32) {
        falling = true;
    }
    if (key == 's') {
        resetDefaults();
    }
    if (key == '-') {
        if (radius > 0.2){
            radius -= 0.001;
            y_pos -=0.001;
        }
    }
    if (key == '+') {
        if (radius < 0.6){
            radius += 0.001;
        }
    }

    glutPostRedisplay();
}

void specialKey(int key, int x, int y){
    glutSetKeyRepeat(1);

    switch(key) {
    case GLUT_KEY_RIGHT:
        x_pos += 0.001;
        break;
    case GLUT_KEY_LEFT:
        x_pos -= 0.001;
        break;
    case GLUT_KEY_UP:
        test += 0.001;
        break;
    case GLUT_KEY_DOWN:
        test -= 0.001;
        break;
    }
}


const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow(title);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    initGL();
    glutMainLoop();
    return 0;
}
