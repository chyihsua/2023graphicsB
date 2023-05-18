#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"

GLMmodel * head = NULL;
GLMmodel * body =NULL;
GLMmodel * Ruparm=NULL;
GLMmodel * Luparm=NULL;

int show[4]={1,1,1,1};
int ID=2;
float angle=0;

float teapotX=0,teapotY=0;
FILE * fout=NULL;
FILE * fin=NULL;

void keyboard(unsigned char key,int x, int y)
{
    if (key=='0') ID=0; show[0]=!show[0];
    if (key=='1') ID=1; show[1]=!show[1];
    if (key=='2') ID=2; show[2]=!show[2];
    if (key=='3') ID=3; show[3]=!show[3];
    glutPostRedisplay(); ///重畫畫面
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if (head==NULL)
    {
        head=glmReadOBJ("model/head.obj");
        body=glmReadOBJ("model/body.obj");
        Ruparm=glmReadOBJ("model/uparmR.obj");
        Luparm=glmReadOBJ("model/uparmL.obj");
        ///glmUnitize(head);
    }
    glPushMatrix();
        glScalef(0.3,0.3,0.3);

        glPushMatrix();
            glTranslatef(teapotX,teapotY,0);
            if(ID==0)glColor3f(1,0,0);
            else glColor3f(1,1,1);
            if (show[0]) glmDraw(head,GLM_MATERIAL);
        glPopMatrix();

        if(ID==1)glColor3f(1,0,0);
        else glColor3f(1,1,1);
        if (show[1]) glmDraw(body,GLM_MATERIAL);

        glPushMatrix();
            ///glTranslatef(teapotX,teapotY,0);為了得知Translate要移動多少
            glTranslatef(-1.360000,0.360000,0);
            glRotatef(angle,0,0,1);
            glTranslatef(1.360000,-0.360000,0);

            if(ID==2)glColor3f(1,0,0);
            else glColor3f(1,1,1);
            if (show[2]) glmDraw(Ruparm,GLM_MATERIAL);

            glPushMatrix();
                ///glTranslatef(teapotX,teapotY,0);為了得知Translate要移動多少
                glTranslatef(-1.360000,0.360000,0);
                glRotatef(angle,0,0,1);
                glTranslatef(1.360000,-0.360000,0);
                if(ID==3)glColor3f(1,0,0);
                else glColor3f(1,1,1);
                if (show[3]) glmDraw(Luparm,GLM_MATERIAL);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    glColor3f(0,1,0);
    glutSolidTeapot(0.02);///用來表示中心點
    glutSwapBuffers();
}

int oldX=0,oldY=0;
void mouse(int button,int state,int x,int y)
{
    if (state=GLUT_DOWN)///當滑鼠按下時
    {
        oldX=x;
        oldY=y;
    }
}

void motion(int x,int y)
{
    teapotX+=(x-oldX)/150.0;
    teapotY-=(y-oldY)/150.0;
    printf("Translatef(%f ,%f ,0)",teapotX,teapotY);
    angle+=x-oldX;
    oldX=x;
    oldY=y;
    glutPostRedisplay();///重畫畫面
}

int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE||GLUT_DEPTH);
    glutCreateWindow("week12");

    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();
}
