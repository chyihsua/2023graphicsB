#include <GL/glut.h>
#include "glm.h" ///include " "�|�h�P�@�ӥؿ�����
GLMmodel * pmodel =NULL;///�ҫ������йw�]���ū���

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    if (pmodel==NULL)
    {
        pmodel=glmReadOBJ("f-16.obj");
        glmUnitize(pmodel);///�N�j�p�s�����j�p(-1~1)
    }
    glmDraw(pmodel,GLM_SMOOTH|GLM_MATERIAL);///�e��(�ҫ�,�Ҧ�)

    ///glutSolidTeapot(0.3);
    glutSwapBuffers();
}

int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week08");

    glutDisplayFunc(display);
    glutMainLoop();
}
