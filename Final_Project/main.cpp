#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"

GLMmodel * body =NULL;
GLMmodel * Leye = NULL;
GLMmodel * Reye = NULL;
GLMmodel * Rarm=NULL;
GLMmodel * Rhand=NULL;
GLMmodel * Rleg=NULL;
GLMmodel * Larm=NULL;
GLMmodel * Lhand=NULL;
GLMmodel * Lleg=NULL;

int show[9]={1,1,1,1,1,1,1,1,1};
int ID=9;
float angle[20]={};

float teapotX=0,teapotY=0;
FILE * fout=NULL;
FILE * fin=NULL;

void keyboard(unsigned char key,int x, int y)
{
    if (key=='0') ID=0; show[0]=!show[0];
    if (key=='1') ID=1; show[1]=!show[1];
    if (key=='2') ID=2; show[2]=!show[2];
    if (key=='3') ID=3; show[3]=!show[3];
    if (key=='4') ID=4; show[4]=!show[4];
    if (key=='5') ID=5; show[5]=!show[5];
    if (key=='6') ID=6; show[6]=!show[6];
    if (key=='7') ID=7; show[7]=!show[7];
    if (key=='8') ID=8; show[8]=!show[8];
    glutPostRedisplay(); ///重畫畫面
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if (body==NULL)
    {
        body=glmReadOBJ("CGmodel/body.obj");

        Leye=glmReadOBJ("CGmodel/L_eyeball.obj");
        Reye=glmReadOBJ("CGmodel/R_eyeball.obj");

        Larm=glmReadOBJ("CGmodel/L_arm.obj");
        Lhand=glmReadOBJ("CGmodel/L_hand.obj");
        Lleg=glmReadOBJ("CGmodel/L_leg.obj");

        Rarm=glmReadOBJ("CGmodel/R_arm.obj");
        Rhand=glmReadOBJ("CGmodel/R_hand.obj");
        Rleg=glmReadOBJ("CGmodel/R_leg.obj");

        ///glmUnitize(head);
    }
    glPushMatrix(); ///?
        glScalef(0.3,0.3,0.3);

        glPushMatrix(); ///body v
            //glTranslatef(teapotX,teapotY,0);

            if(ID==0)glColor3f(1,0,0);  //red
            else glColor3f(1,1,0);  //yellow
            if (show[0]) glmDraw(body,GLM_MATERIAL);
        glPopMatrix();

        glPushMatrix(); ///Reye v
            //glTranslatef(teapotX,teapotY,0);

            if(ID==1)glColor3f(1,0,0);
            else glColor3f(1,1,1);
            if (show[1]) glmDraw(Reye,GLM_MATERIAL);
        glPopMatrix();

        glPushMatrix(); ///Leye v
            //glTranslatef(teapotX,teapotY,0);///為了得知Translate要移動多少
            //glTranslatef(-1.086666 ,0.593333 ,0);
            //glRotatef(angle[2],0,0,1);
            //glTranslatef(1.160000 ,-0.633334 ,0);

            if(ID==2)glColor3f(1,0,0);
            else glColor3f(1,1,1);
            if (show[2]) glmDraw(Leye,GLM_MATERIAL);
        glPopMatrix();

        glPushMatrix(); ///Left Arm hand
            glPushMatrix(); ///LArm
            //glTranslatef(teapotX,teapotY,0);///為了得知Translate要移動多少
            glTranslatef(-0.979998 ,0.959998 ,0);
            glRotatef(angle[2],0,0,1);///?
            glTranslatef(0.979998 ,-0.959998 ,0);

            if(ID==3)glColor3f(1,0,0);
            else glColor3f(1,1,0);
            if (show[3]) glmDraw(Larm,GLM_MATERIAL);
            glPopMatrix();

            glPushMatrix(); ///Lhand
                //glTranslatef(teapotX,teapotY,0);//為了得知Translate要移動多少
                glTranslatef(2.159998 ,-0.620000 ,0);
                glRotatef(angle[3],0,0,1);///?
                glTranslatef(-2.159998 ,0.620000 ,0);

                if(ID==4) glColor3f(1,0,0);
                else glColor3f(0.4,0.4,0.4); //grey
                if (show[4]) glmDraw(Lhand,GLM_MATERIAL);
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
    angle[ID]+=x-oldX;
    oldX=x;
    oldY=y;
    glutPostRedisplay();///重畫畫面
}

int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week15");

    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();
}
