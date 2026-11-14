#include <GL/freeglut.h>

void display();
void teclado(unsigned char tecla, int x, int y);

int main(int argc, char **argv){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Jogo da Nave");

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);

    glutMainLoop();

    return 0;
}

void display(void){
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
