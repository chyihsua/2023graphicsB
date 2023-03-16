#include <GL/glut.h>
float angle = 0;

void mycube()
{
    glPushMatrix();
        glScalef(0.5,0.1,0.1); ///調大小
        glutSolidCube(1); ///畫方塊
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1,1,1); ///白色
    glutSolidCube(1); ///畫身體

    glPushMatrix();///右上角
        glTranslatef(0.5,0.5,0); ///放到正確位置上
        glRotatef(angle,0,0,1); ///旋轉
        glTranslatef(0.25,0,0); ///移到正確旋轉中心點上
        glColor3f(0,1,0); ///綠色
        mycube(); ///建方塊
    glPopMatrix();

    glPushMatrix();///左上角
        glTranslatef(-0.5,0.5,0); ///放到正確位置上
        glRotatef(angle,0,0,1); ///旋轉
        glTranslatef(0.25,0,0); ///移到正確旋轉中心點上
        glColor3f(0,1,0); ///綠色
        mycube(); ///建方塊
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
