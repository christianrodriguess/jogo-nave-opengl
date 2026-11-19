#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159

void display();
void teclado(unsigned char tecla, int x, int y);
void desenha_chao();
void desenha_nave();
void desenha_canhao();
void desenha_mira();
void desenha_tiro();
void dispara_tiro();
void atualizar(int valor);

float nave_x = -15.0f;
float nave_velocidade = 0.08f;

float canhao_x = 0.0f;
float canhao_y = 0.0f;
float canhao_z = 0.0f;
float rotacao_canhao = 0.0f;

// vetor de direcao da mira
float mira_x, mira_y;

int tiro_ativo = 0;
float tiro_x = 0.0f;
float tiro_y = 5.0f;
float tiro_z = 0.0f;
float tiro_velocidade = 0.5f;


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

    desenha_chao();
    desenha_nave();
    desenha_canhao();
    desenha_mira();
    desenha_tiro();

    glutSwapBuffers();
}

void teclado(unsigned char tecla, int x, int y){
    switch(tecla){
        case 27: // tecla ESC
            exit(0);
            break;
        case 'a':
            if(rotacao_canhao > -45)
                rotacao_canhao -= 2;

            break;
        case 'd':
            if(rotacao_canhao < 45)
                rotacao_canhao += 2;

            break;
        case ' ':
            dispara_tiro();
            break;
        
        default:
            break;
    }
}

void desenha_chao(){
    glColor3f(0.25f, 0.45f, 0.25f);

    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -15.0f);
        glVertex3f(100.0f, 0.0f, -15.0f);
        glVertex3f(100.0f, 0.0f, 15.0f);
        glVertex3f(-100.0f, 0.0f, 15.0f);
    glEnd();
}

void desenha_nave(){
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

void desenha_canhao(){
    glPushMatrix();
    glTranslatef(canhao_x, canhao_y, canhao_z);

    // base (meia esfera achatada apoiada no chao)
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
        glScalef(1.4f, 0.5f, 1.4f);
        glutSolidSphere(1.0, 24, 24);
    glPopMatrix();

    // corpo do cano (cilindro apontando para o ceu)
    // glutSolidCylinder desenha ao longo do eixo Z, então giramos -90 graus em X
    // para que ele aponte para +Y (para cima)
    glColor3f(0.15f, 0.15f, 0.2f);
    glPushMatrix();
        glTranslatef(0.0f, 0.3f, 0.0f);
        glRotatef(-rotacao_canhao, 0.0f, 0.0f, 1.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCylinder(0.5, 2.5, 24, 4);
    glPopMatrix();

    glPopMatrix();
}

void desenha_mira(){
    if(tiro_ativo) return;

    mira_x = sinf(rotacao_canhao * PI / 180.0f);
    mira_y = cosf(rotacao_canhao * PI / 180.0f);

    float comprimento = 8.0f;

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3f(canhao_x + mira_x * 2.5f, canhao_y + mira_y * 2.5f, canhao_z);
        glVertex3f(canhao_x + mira_x * comprimento, canhao_y + mira_y * comprimento, canhao_z);
    glEnd();
}


void desenha_tiro(){
    if(!tiro_ativo) return;
    
    glColor3f(1.0f, 0.4f, 0.0f);
    glPushMatrix();
        glTranslatef(tiro_x, tiro_y, tiro_z);
        glutSolidSphere(0.5f, 16, 16);
    glPopMatrix();
}

void dispara_tiro(){
    if(tiro_ativo) return;

    tiro_x = canhao_x + mira_x * 2.5f;
    tiro_y = canhao_y + mira_y * 2.5f;
    
    tiro_ativo = 1;
}


void atualizar(int valor){
    nave_x += nave_velocidade;

    if(nave_x > 17.0f){
        nave_x = -17.0f;
    }

    if(tiro_ativo){
        tiro_x += mira_x * tiro_velocidade;
        tiro_y += mira_y * tiro_velocidade;

        if(tiro_x > 17.0f || tiro_x < -17.0f || tiro_y > 20.0f){
            tiro_ativo = 0;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, atualizar, 0);
}
