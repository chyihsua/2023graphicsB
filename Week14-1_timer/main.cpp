#include <GL/glut.h>

float angle=0;
void timer(int t)
{
    glutTimerFunc(500,timer,t+1); ///���ݦh�[500=0.5s
    angle+=90;
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glRotatef(angle,0,0,1);
        glutSolidTeapot(0.3);
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc,char**argv)
    {
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
        glutCreateWindow("week14");

        glutTimerFunc(3000,timer,0);///3000=3s
        glutDisplayFunc(display);

        glutMainLoop();
    }
