#include <GL/glut.h>

float X=0,Y=0,Z=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT); ///清除
    glPushMatrix();///備份矩陣
        glTranslatef(X,Y,Z); ///移動(x,y,z)
        glutSolidTeapot(0.3);
    glPopMatrix();///還原矩陣
    glutSwapBuffers();
}

void mouse(int buttom,int state,int x,int y)
{   ///       左右鍵  按下/放開  x,y介於0~300
    X=(x-150)/150.0; ///減一半除一半
    Y=-(y-150)/150.0;///記得加負號
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
