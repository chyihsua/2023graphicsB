#include <GL/glut.h>

void display()
{
	///glColor3f(0,1,0);///劃出綠色三角形
	glBegin(GL_POLYGON);
        glColor3f(1,0,0); glVertex2d(0,1);
        glColor3f(0,1,0); glVertex2d(-1,-1);
        glColor3f(0,0,1); glVertex2d(1,-1);
    glEnd();

    glColor3b(1,1,0);
	glutSolidTeapot( 0.3 ); /// 畫出實心小茶壼

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
