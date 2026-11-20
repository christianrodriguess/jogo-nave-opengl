#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include "programa_nome.h"

#define PI 3.14159

void display(void);
void keyboard(unsigned char tecla, int x, int y);
void desenha_chao();
void desenha_nave();
void desenha_canhao();
void desenha_mira();
void desenha_tiro();
void dispara_tiro();
void desenha_placar();
int verifica_colisao();
void atualizar(int valor);
void desenha_texto(char *texto);

float nave_x = -15;
float nave_y = 0;
float nave_z = 0;
float nave_raio = 1;
float nave_velocidade = 0.08;

float canhao_x = 0;
float canhao_y = 0;
float canhao_z = 0;
float canhao_rotacao = 0;

// vetor de direcao da mira
float mira_x, mira_y;

int tiro_ativo = 0;
float tiro_x = 0;
float tiro_y = 5;
float tiro_z = 0;
float tiro_raio = 0.5;
float tiro_velocidade = 0.5;

int placar_pontos = 0;
int janela_principal;

int main(int argc, char **argv){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);
    janela_principal = glutCreateWindow("Jogo da Nave");

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1280.0 / 720.0, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, atualizar, 0);

    glClearColor(0.5, 0.8, 0.9, 1);

    glutMainLoop();

    return 0;
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0, 15, 20,
        0, 0, 0,
        0, 1, 0
    );

    desenha_chao();
    desenha_nave();
    desenha_canhao();
    desenha_mira();
    desenha_tiro();
    desenha_placar();

    glutSwapBuffers();
}

void keyboard(unsigned char tecla, int x, int y){
    switch(tecla){
        case 27: // tecla ESC
            exit(0);
            break;
        case 'a':
            if(canhao_rotacao > -45)
                canhao_rotacao -= 2;
            break;
        case 'd':
            if(canhao_rotacao < 45)
                canhao_rotacao += 2;
            break;
        case ' ':
            dispara_tiro();
            break;
        case 'r':
            placar_pontos = 0;
            break;
        case 'c':
            programa_nome();
            break;
        default:
            break;
    }
}

void desenha_chao(){
    glColor3f(0.2, 0.4, 0.2);

    glBegin(GL_QUADS);
        glVertex3f(-100, 0, -15);
        glVertex3f(100, 0, -15);
        glVertex3f(100, 0, 15);
        glVertex3f(-100, 0, 15);
    glEnd();
}

void desenha_nave(){
    nave_y = 8 + 1.5 * sin(0.5 * nave_x);

    glPushMatrix();
    glTranslatef(nave_x, nave_y, nave_z);

    // corpo
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
        glScalef(2, 0.5, 1.2);
        glutSolidSphere(nave_raio, 24, 24);
    glPopMatrix();

    // cabine
    glColor3f(0.3, 0.9, 0.3);
    glPushMatrix();
        glTranslatef(0, 0.35, 0);
        glutSolidSphere(0.6, 20, 20);
    glPopMatrix();

    glPopMatrix();
}

void desenha_canhao(){
    glPushMatrix();
    glTranslatef(canhao_x, canhao_y, canhao_z);

    // base
    glColor3f(0.3, 0.3, 0.3);
    glPushMatrix();
        glScalef(1.4, 0.5, 1.4);
        glutSolidSphere(1, 24, 24);
    glPopMatrix();

    // cano
    glColor3f(0.1, 0.1, 0.2);
    glPushMatrix();
        glTranslatef(0, 0.3, 0);
        glRotatef(-canhao_rotacao, 0, 0, 1);
        glRotatef(-90, 1, 0, 0); // gira -90 graus em X para que ele aponte para cima
        glutSolidCylinder(0.5, 2.5, 24, 4);
    glPopMatrix();

    glPopMatrix();
}

void desenha_mira(){
    if(tiro_ativo) return;

    mira_x = sin(canhao_rotacao * PI / 180);
    mira_y = cos(canhao_rotacao * PI / 180);

    float comprimento = 8;

    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
        glVertex3f(canhao_x + mira_x * 2.5, canhao_y + mira_y * 2.5, canhao_z);
        glVertex3f(canhao_x + mira_x * comprimento, canhao_y + mira_y * comprimento, canhao_z);
    glEnd();
}

void desenha_tiro(){
    if(!tiro_ativo) return;
    
    glColor3f(1, 0.4, 0);
    glPushMatrix();
        glTranslatef(tiro_x, tiro_y, tiro_z);
        glutSolidSphere(tiro_raio, 16, 16);
    glPopMatrix();
}

void dispara_tiro(){
    if(tiro_ativo) return;

    tiro_x = canhao_x + mira_x * 2.5;
    tiro_y = canhao_y + mira_y * 2.5;
    
    tiro_ativo = 1;
}

void desenha_placar(){
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1280, 0, 720);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);

    // fundo
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
        glVertex2f(10, 30);
        glVertex2f(220, 30);
        glVertex2f(220, 70);
        glVertex2f(10, 70);
    glEnd();

    char placar[9] = "Placar: ";
    char pontos[3];
    itoa(placar_pontos, pontos, 10); // converte de int para string

    glColor3f(1, 1, 1);
    glTranslatef(30, 40, 0);
    glScalef(0.2, 0.2, 0.2);
    desenha_texto(placar);

    glTranslatef(180, 0, 0);
    desenha_texto(pontos);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

int verifica_colisao(){
    // dois circulos colidem se a distancia entre os centros for menor que a soma dos raios

    float distancia_x = nave_x - tiro_x;
    float distancia_y = nave_y - tiro_y;

    // Teorema de Pitagoras 
    // as distancias de X e Y formam os catetos de um triangulo retangulo, e a hipotenusa eh a reta entre os dois centros
    float distancia = sqrt(distancia_x * distancia_x + distancia_y * distancia_y);

    if(distancia < nave_raio + tiro_raio) return 1;

    return 0;
}

void atualizar(int valor){
    nave_x += nave_velocidade;

    if(nave_x > 17)
        nave_x = -17;

    if(tiro_ativo){
        tiro_x += mira_x * tiro_velocidade;
        tiro_y += mira_y * tiro_velocidade;

        if(tiro_x > 17 || tiro_x < -17 || tiro_y > 15)
            tiro_ativo = 0;

        if(verifica_colisao()){
           tiro_ativo = 0;
           placar_pontos++;
           
            if(placar_pontos >= 99)
                placar_pontos = 0;
        }
    }

    glutSetWindow(janela_principal);
    glutPostRedisplay();
    glutTimerFunc(16, atualizar, 0);
}

void desenha_texto(char *texto){
    char *p = texto;

    while(*p)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p++);
}