#include <GL/glut.h>
#include "glm.h" ///include " "會去同一個目錄中找
GLMmodel * pmodel =NULL;///模型的指標預設為空指標

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    if (pmodel==NULL)
    {
        pmodel=glmReadOBJ("f-16.obj");
        glmUnitize(pmodel);///將大小存成單位大小(-1~1)
    }
    glmDraw(pmodel,GLM_SMOOTH|GLM_MATERIAL);///畫圖(模型,模式)

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
