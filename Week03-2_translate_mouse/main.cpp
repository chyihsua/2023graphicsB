#include <GL/glut.h>

float X=0,Y=0,Z=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT); ///�M��
    glPushMatrix();///�ƥ��x�}
        glTranslatef(X,Y,Z); ///����(x,y,z)
        glutSolidTeapot(0.3);
    glPopMatrix();///�٭�x�}
    glutSwapBuffers();
}

void mouse(int buttom,int state,int x,int y)
{   ///       ���k��  ���U/��}  x,y����0~300
    X=(x-150)/150.0; ///��@�b���@�b
    Y=-(y-150)/150.0;///�O�o�[�t��
}

int main(int argc,char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week03");

    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutMainLoop();
}
