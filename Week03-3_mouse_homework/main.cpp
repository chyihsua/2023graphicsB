#include <GL/glut.h>
#include <stdio.h>  ///���F��printf

float X=0,Y=0,Z=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT); ///�M��
    glBegin(GL_LINE_LOOP);
       glVertex2f(-0.35,-0.19);
       glVertex2f(-0.45,-0.10);
       glVertex2f(-0.40,0.09);
       glVertex2f(-0.26,0.11);
       glVertex2f(-0.06,-0.13);
       glVertex2f(-0.06,-0.20);
       glVertex2f(-0.15,-0.38);
       glVertex2f(-0.23,-0.41);
    glEnd();


    glutSwapBuffers();
}

void mouse(int buttom,int state,int x,int y)
{   ///       ���k��  ���U/��}  x,y����0~300
    X=(x-150)/150.0; ///��@�b���@�b
    Y=-(y-150)/150.0;///�O�o�[�t��
    if(state==GLUT_DOWN) printf("   glVertex2f(%.2f,%.2f);\n",X,Y); ///�L�X�I�y��
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
