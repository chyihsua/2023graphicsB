#include <GL/glut.h>

void display()
{
    glColor3f(235/255.0,141/255.0,128/255.0); ///用RGB數值除以255
	glBegin(GL_POLYGON);
        glVertex2d((65-100)/100.0,-(54-100)/100.0);
        glVertex2d((34-100)/100.0,-(138-100)/100.0);
        glVertex2d((59-100)/100.0,-(138-100)/100.0);
        glVertex2d((87-100)/100.0,-(54-100)/100.0);
    glEnd();

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
