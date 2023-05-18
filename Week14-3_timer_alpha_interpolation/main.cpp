#include <GL/glut.h>

float angle=0,newangle=0,oldangle=0;
float oldX=0;
void timer(int t)
{
    if(t<100) glutTimerFunc(33,timer,t+1);
    float alpha=t/100.0;
    angle=alpha*newangle+(1-alpha)*oldangle;
    angle+=3;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x,int y)
{
    glutTimerFunc(0,timer,0);
}

void mouse(int button,int state,int x,int y)
{
    if(state==GLUT_DOWN) oldangle=angle;
    if(state==GLUT_UP) newangle=angle;
    oldX=x;
    glutPostRedisplay();
}

void motion(int x,int y)
{
    angle+=x-oldX;
    oldX=x;///更新角度
    glutPostRedisplay();///更新畫面
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

        glutMouseFunc(mouse);
        glutMotionFunc(motion);
        glutKeyboardFunc(keyboard);
        glutDisplayFunc(display);

        glutMainLoop();
    }
