#include <GL/glut.h>

void display()
{
	///glColor3f(0,1,0);///���X���T����
	glBegin(GL_POLYGON);
        glColor3f(1,0,0); glVertex2d(0,1);
        glColor3f(0,1,0); glVertex2d(-1,-1);
        glColor3f(0,0,1); glVertex2d(1,-1);
    glEnd();

    glColor3b(1,1,0);
	glutSolidTeapot( 0.3 ); /// �e�X��ߤp����

	glutSwapBuffers(); ///�洫��ܥX��
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv); ///�}�lglut���\��
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); ///�]�w��ܼҦ�

    glutCreateWindow("GLUT Shapes"); ///�إߤ@�ӵ��l�A�s"..."

    glutDisplayFunc(display);///�n��ܪ��禡

    glutMainLoop(); ///�D�n�j��d�᭱
}
