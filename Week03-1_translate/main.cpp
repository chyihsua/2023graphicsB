#include <GL/glut.h>

void display()
{
    glPushMatrix();///�ƥ��x�}
        glTranslated(0.5,0.5,0); ///����(x,y,z)
        glutSolidTeapot(0.3);
    glPopMatrix();///�٭�x�}
    glutSwapBuffers();
}

int main(int argc,char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week03");

    glutDisplayFunc(display);
    glutMainLoop();
}
