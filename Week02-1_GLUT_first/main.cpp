#include <GL/glut.h>

void display()
{
    glColor3f(1,1,0);///���X�������
	glutSolidTeapot( 0.5 ); /// �e�X��ߤj����

	glColor3f(0,1,0);///���X������
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
