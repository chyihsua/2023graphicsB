#include <GL/glut.h>
#include <math.h>

void mycircle(float r,float x,float y) ///r=�b�|�Ax�By�N�����y��
{
    glBegin(GL_POLYGON);
        for(float a=0;a<=2*3.141592;a+=0.01) ///a=����
        {
            glVertex2f(r*cos(a)+x,r*sin(a)+y);
        }
    glEnd();
}
void display()
{
	glColor3f(235/255.0,141/255.0,148/255.0);
	mycircle(0.5,0,0);

	glColor3f(135/255.0,14/255.0,148/255.0);
	mycircle(0.3,-0.5,-0.5);

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
