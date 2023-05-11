#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"

GLMmodel * head = NULL;
GLMmodel * body =NULL;
GLMmodel * Ruparm=NULL;
GLMmodel * Luparm=NULL;

float teapotX=0,teapotY=0;
FILE * fout=NULL;
FILE * fin=NULL;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if (head==NULL)
    {
        head=glmReadOBJ("model/head.obj");
        body=glmReadOBJ("model/body.obj");
        Ruparm=glmReadOBJ("model/r_up_arm.obj");
        Luparm=glmReadOBJ("model/l_up_arm.obj");
        ///glmUnitize(head);
    }
    glPushMatrix();
        glScalef(0.3,0.3,0.3);
        glmDraw(Luparm,GLM_MATERIAL);
        glmDraw(Ruparm,GLM_MATERIAL);
        glmDraw(body,GLM_MATERIAL);
        glmDraw(head,GLM_MATERIAL);
    glPopMatrix();
    glutSwapBuffers();
}

void mouse(int button,int state,int x,int y)
{
    teapotX=(x-150)/150.0;
    teapotY=(150-y)/150.0;
    if (state==GLUT_DOWN)
    {
        if (fout==NULL) fout =fopen("file4.txt","w");
        fprintf(fout,"%f %f\n",teapotX,teapotY);
    }
    display();
}

void keyboard(unsigned char key,int x ,int y)
{
    if (fin==NULL)
    {
        fclose(fout);
        fin =fopen("file4.txt","r");
    }
    fscanf(fin,"%f%f",&teapotX,&teapotY);
    display();
}

int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE||GLUT_DEPTH);
    glutCreateWindow("week12");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();
}
