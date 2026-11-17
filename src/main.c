#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>

void display();
void teclado(unsigned char tecla, int x, int y);
void desenhaChao();
void desenhaNave();
void desenhaCanhao();
void atualizar(int valor);

float nave_x = -15.0f;
float nave_velocidade = 0.08f;

float canhao_x = 0.0f;
float canhao_y = 0.0f;
float canhao_z = 8.0f;

int main(int argc, char **argv){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Jogo da Nave");

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1280.0 / 720.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutTimerFunc(0, atualizar, 0);

    glutMainLoop();

    return 0;
}

void display(void){
    glClearColor(0.52f, 0.8f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 15.0, 20.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    desenhaChao();
    desenhaNave();
    desenhaCanhao();

    glutSwapBuffers();
}

void teclado(unsigned char tecla, int x, int y){
    switch(tecla){
        case 27: // tecla ESC
            exit(0);
            break;
        
        default:
            break;
    }
}

void desenhaChao(){
    glColor3f(0.25f, 0.45f, 0.25f);

    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -15.0f);
        glVertex3f(100.0f, 0.0f, -15.0f);
        glVertex3f(100.0f, 0.0f, 15.0f);
        glVertex3f(-100.0f, 0.0f, 15.0f);
    glEnd();
}

void desenhaNave(){
    float nave_y = 8.0f + 1.5f * sinf(0.5f * nave_x);
    float nave_z = 0.0f;

    glPushMatrix();
    glTranslatef(nave_x, nave_y, nave_z);

    // corpo
    glColor3f(0.7f, 0.7f, 0.75f);
    glPushMatrix();
        glScalef(2.0f, 0.5f, 1.2f);
        glutSolidSphere(1.0, 24, 24);
    glPopMatrix();

    // cabine
    glColor3f(0.3f, 0.9f, 0.3f);
    glPushMatrix();
        glTranslatef(0.0f, 0.35f, 0.0f);
        glutSolidSphere(0.6, 20, 20);
    glPopMatrix();

    glPopMatrix();
}

void desenhaCanhao(){
    glPushMatrix();
    glTranslatef(canhao_x, canhao_y, canhao_z);

    // base (meia esfera achatada apoiada no chão)
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
        glScalef(1.4f, 0.5f, 1.4f);
        glutSolidSphere(1.0, 24, 24);
    glPopMatrix();

    // corpo do cano (cilindro apontando para o céu)
    // glutSolidCylinder desenha ao longo do eixo Z, então giramos -90° em X
    // para que ele aponte para +Y (para cima)
    glColor3f(0.15f, 0.15f, 0.2f);
    glPushMatrix();
        glTranslatef(0.0f, 0.3f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCylinder(0.45, 2.5, 24, 4);
    glPopMatrix();

    glPopMatrix();
}

void atualizar(int valor){
    nave_x += nave_velocidade;

    if(nave_x > 17.0f){
        nave_x = -17.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, atualizar, 0);
}
