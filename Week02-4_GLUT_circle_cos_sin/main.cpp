#include <GL/glut.h>
#include <math.h>

void mycircle(float r,float x,float y) ///r=半徑，x、y代表平面座標
{
    glBegin(GL_POLYGON);
        for(float a=0;a<=2*3.141592;a+=0.01) ///a=角度
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

	glutSwapBuffers(); ///交換顯示出來
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv); ///開始glut的功能
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); ///設定顯示模式

    glutCreateWindow("GLUT Shapes"); ///建立一個窗子，叫"..."

    glutDisplayFunc(display);///要顯示的函式

    glutMainLoop(); ///主要迴圈卡後面
}
