#include <GL/glut.h>

void display()
{
    glColor3f(235/255.0,141/255.0,128/255.0); ///��RGB�ƭȰ��H255
	glBegin(GL_POLYGON);
        glVertex2d((65-100)/100.0,-(54-100)/100.0);
        glVertex2d((34-100)/100.0,-(138-100)/100.0);
        glVertex2d((59-100)/100.0,-(138-100)/100.0);
        glVertex2d((87-100)/100.0,-(54-100)/100.0);
    glEnd();

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
