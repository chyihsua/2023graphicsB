#include <GL/glut.h>
float angle = 0;

void mycube()
{
    glPushMatrix();
        glScalef(0.5,0.1,0.1); ///�դj�p
        glutSolidCube(1); ///�e���
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1,1,1); ///�զ�
    glutSolidCube(1); ///�e����

    glPushMatrix();///�k�W��
        glTranslatef(0.5,0.5,0); ///��쥿�T��m�W
        glRotatef(angle,0,0,1); ///����
        glTranslatef(0.25,0,0); ///���쥿�T���त���I�W
        glColor3f(0,1,0); ///���
        mycube(); ///�ؤ��
    glPopMatrix();

    glPushMatrix();///���W��
        glTranslatef(-0.5,0.5,0); ///��쥿�T��m�W
        glRotatef(angle,0,0,1); ///����
        glTranslatef(0.25,0,0); ///���쥿�T���त���I�W
        glColor3f(0,1,0); ///���
        mycube(); ///�ؤ��
    glPopMatrix();

    glutSwapBuffers();
    angle++;
}
int main(int argc, char* argv[] )
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week05");

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
}
