#ifndef PROGRAMA_NOME_H
#define PROGRAMA_NOME_H

#include <GL/freeglut.h>

void programa_nome();
void desenha(void);
void teclado(unsigned char tecla, GLint x, GLint y);
void mouse(int button, int state, int mousex, int mousey);
void verificaClique(int x, int y);
void desenhaBotoes();
void desenhaLetraC(float x, float y);
void desenhaLetraH(float x, float y);
void desenhaLetraR(float x, float y);
void desenhaLetraI(float x, float y);
void desenhaLetraS(float x, float y);
void desenhaLetraT(float x, float y);
void desenhaLetraA(float x, float y);
void desenhaLetraN(float x, float y);

GLfloat escala = 10;
GLfloat translacao_horizontal = 0;
GLfloat translacao_vertical = 0;
GLfloat rotacao = 0;

int botao_x = 1, botao_y = 0, botao_z = 0;

int programa_janela = 0;

void programa_nome() {
    if(programa_janela != 0) return;

    int atual = glutGetWindow();

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    programa_janela = glutCreateWindow("Programa Nome");

    glutKeyboardFunc(teclado);
    glutMouseFunc(mouse);
    glutDisplayFunc(desenha);

    glClearColor(0, 0, 1, 0);

    glutSetWindow(atual);
}

void desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(0, 640, 0, 480);

    desenhaBotoes();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glScalef(escala, escala, 0);
    glTranslatef(translacao_horizontal, translacao_vertical, 0);
    glRotatef(rotacao, botao_x, botao_y, botao_z);

    glColor3f(1, 1, 1);

    desenhaLetraC(1, 1);
    desenhaLetraH(5, 1);
    desenhaLetraR(9, 1);
    desenhaLetraI(13, 1);
    desenhaLetraS(15, 1);
    desenhaLetraT(19, 1);
    desenhaLetraI(23, 1);
    desenhaLetraA(25, 1);
    desenhaLetraN(29, 1);
    glPopMatrix();

    glFlush();  
}

void teclado(unsigned char tecla, GLint x, GLint y){
    switch (tecla){
        case 27:
            exit(0);
            break;
        case '+':
            escala += 0.5;
            break;
        case '-':
            if(escala > 2){
                escala -= 0.5;
            }
            break;
        case 'a':
            translacao_horizontal--;
            break;
        case 'd':
            translacao_horizontal++;
            break;
        case 'w':
            translacao_vertical++;
            break;
        case 's':
            translacao_vertical--;
            break;
        case 'q':
            rotacao++;
            break;
        case 'e':
            rotacao--;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int mousex, int mousey){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        int x = mousex;
        int y = 480 - mousey;

        verificaClique(x, y);
    }
    glutPostRedisplay();
}

void verificaClique(int x, int y){
    // Botao X
    if((x >= 50 && x <= 150) && (y >= 400 && y <= 450) && !botao_x){
        botao_x = 1;
        botao_y = 0;
        botao_z = 0;
        rotacao = 0;
    }

    // Botao Y
    if((x >= 270 && x <= 370) && (y >= 400 && y <= 450) && !botao_y){
        botao_y = 1;
        botao_x = 0;
        botao_z = 0;
        rotacao = 0;
    }

    // Botao Z
    if((x >= 490 && x <= 590) && (y >= 400 && y <= 450) && !botao_z){
        botao_z = 1;
        botao_x = 0;
        botao_y = 0;
        rotacao = 0;
    }
}

void desenhaBotoes(){
    if(botao_x){
        glColor3f(1, 0, 0);
    }
    else {
        glColor3f(1, 1, 1);
    }
    
    // Botao X
    glBegin(GL_QUADS);
        glVertex2f(50, 400);
        glVertex2f(50, 450);
        glVertex2f(150, 450);
        glVertex2f(150, 400);
    glEnd();

    if(botao_y){
        glColor3f(0, 1, 0);
    }
    else {
        glColor3f(1, 1, 1);
    }

    // Botao Y
    glBegin(GL_QUADS);
        glVertex2f(270, 400);
        glVertex2f(270, 450);
        glVertex2f(370, 450);
        glVertex2f(370, 400);
    glEnd();

    if(botao_z){
        glColor3f(1, 0, 1);
    }
    else {
        glColor3f(1, 1, 1);
    }

    // Botao Z
    glBegin(GL_QUADS);
        glVertex2f(490, 400);
        glVertex2f(490, 450);
        glVertex2f(590, 450);
        glVertex2f(590, 400);
    glEnd();

    glColor3f(0, 0, 0);

    // Rotulo X
    glBegin(GL_LINES);
        glVertex2f(90, 415);
        glVertex2f(110, 435);
        glVertex2f(110, 415);
        glVertex2f(90, 435);
    glEnd();

    // Rotulo Y
    glBegin(GL_LINE_STRIP);
        glVertex2f(320, 415);
        glVertex2f(320, 425);
        glVertex2f(330, 435);
        glVertex2f(320, 425);
        glVertex2f(310, 435);
    glEnd();

    // Rotulo Z
    glBegin(GL_LINE_STRIP);
        glVertex2f(530, 435);
        glVertex2f(550, 435);
        glVertex2f(530, 415);
        glVertex2f(550, 415);
    glEnd();
}

void desenhaLetraC(float x, float y){
    glBegin(GL_LINE_STRIP);
        glVertex2f(x+2, y);
        glVertex2f(x+1, y);
        glVertex2f(x, y+1);
        glVertex2f(x, y+3);
        glVertex2f(x+1, y+4);
        glVertex2f(x+2, y+4);
    glEnd();
}

void desenhaLetraH(float x, float y){
    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y+4);
        glVertex2f(x, y+2);
        glVertex2f(x+2, y+2);
        glVertex2f(x+2, y);
        glVertex2f(x+2, y+4);
    glEnd();
}

void desenhaLetraR(float x, float y){
    glBegin(GL_LINE_STRIP);
        glVertex2f(x, y);
        glVertex2f(x, y+4);
        glVertex2f(x+2, y+4);
        glVertex2f(x+2, y+2);
        glVertex2f(x, y+2);
        glVertex2f(x+2, y);
    glEnd();
}

void desenhaLetraI(float x, float y){
    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y+4);
    glEnd();
}

void desenhaLetraS(float x, float y){
    glBegin(GL_LINE_STRIP);
        glVertex2f(x, y);
        glVertex2f(x+2, y);
        glVertex2f(x+2, y+2);
        glVertex2f(x, y+2);
        glVertex2f(x, y+4);
        glVertex2f(x+2, y+4);
    glEnd();
}

void desenhaLetraT(float x, float y){
    glBegin(GL_LINES);
        glVertex2f(x+1, y);
        glVertex2f(x+1, y+4);
        glVertex2f(x, y+4);
        glVertex2f(x+2, y+4);
    glEnd();
}

void desenhaLetraA(float x, float y){
    glBegin(GL_LINE_STRIP);
        glVertex2f(x, y);
        glVertex2f(x, y+4);
        glVertex2f(x+2, y+4);
        glVertex2f(x+2, y+2);
        glVertex2f(x, y+2);
        glVertex2f(x+2, y+2);
        glVertex2f(x+2, y);
    glEnd();
}

void desenhaLetraN(float x, float y){
    glBegin(GL_LINE_STRIP);
        glVertex2f(x, y);
        glVertex2f(x, y+4);
        glVertex2f(x+2, y);
        glVertex2f(x+2, y+4);
    glEnd();
}

#endif