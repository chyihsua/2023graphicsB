#include <GL/freeglut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glutSolidTeapot(0.3);
    glutSwapBuffers();
}

void keyboard(unsigned char key,int x,int y)
{
    if (key==27) ///ESC=27
        exit(1234); ///���UESC���������b�p�����1234
}
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week11");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);///��L

    glutMainLoop();
}
