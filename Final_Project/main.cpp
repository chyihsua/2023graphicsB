#include <opencv/highgui.h>
#include <opencv/cv.h>
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

int ID=9;
float angle[20]={},angle2[20]={};

float teapotX=0,teapotY=0,oldX=0,oldY=0;
FILE * fout=NULL;
FILE * fin=NULL;

void keyboard(unsigned char key,int x, int y)
{
    if (key=='0') ID=0;
    if (key=='1') ID=1;
    if (key=='2') ID=2;
    if (key=='3') ID=3;
    if (key=='4') ID=4;
    if (key=='5') ID=5;
    if (key=='6') ID=6;
    if (key=='7') ID=7;
    if (key=='8') ID=8;
    if(key=='s'){ ///save存檔 也會動到檔案
        if(fout == NULL) fout = fopen("motion.txt", "w");
        for(int i=0; i<20; i++){
            fprintf(fout, "%.2f ", angle[i] );
            fprintf(fout, "%.2f ", angle2[i] );
        }
        fprintf(fout, "\n");
        printf("寫了一行\n");
    }
    if(key=='r'){ ///read讀檔 也會動到檔案
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            fscanf(fin, "%f", &angle[i] );
            fscanf(fin, "%f", &angle2[i] );
        }
        glutPostRedisplay();
    }
    if(key=='p'){ ///play播放 也會動到檔案
        //glutTimerFunc(0, timer, 0);
    }
    glutPostRedisplay(); ///重畫畫面
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();     ///all window
        glScalef(0.3,0.3,0.3);
        glPushMatrix(); ///all model
            glColor3f(1,1,0);  //yellow
            glmDraw(body,GLM_MATERIAL); ///body

            glPushMatrix(); ///Reye v ?
                //glTranslatef(teapotX,teapotY,0);
                glColor3f(1,1,1);
                //if(ID==1)glColor3f(1,0,0);
                //else glColor3f(1,1,1);
                glmDraw(Reye,GLM_MATERIAL);
            glPopMatrix();

            glPushMatrix(); ///Leye v ?
                //glTranslatef(teapotX,teapotY,0);///為了得知Translate要移動多少
                //glTranslatef(-1.086666 ,0.593333 ,0);
                //glRotatef(angle[2],0,0,1);
                //glTranslatef(1.160000 ,-0.633334 ,0);
                glColor3f(1,1,1);
                //if(ID==2)glColor3f(1,0,0);
                //else glColor3f(1,1,1);
                glmDraw(Leye,GLM_MATERIAL);
            glPopMatrix();

            glPushMatrix(); ///Left Arm hand ?
                 ///LArm
                    //glTranslatef(teapotX,teapotY,0);///為了得知Translate要移動多少
                    glTranslatef(1.47, -0.60, 0 );
                    glRotatef(angle[3],0,1,0);
                    glRotatef(angle2[3],1,0,0);///?
                    glTranslatef(-1.47, 0.60, 0 );

                    if(ID==3)glColor3f(1,0,0);
                    else glColor3f(1,1,0);
                    glmDraw(Larm,GLM_MATERIAL);

                glPushMatrix(); ///Lhand
                    //glTranslatef(teapotX,teapotY,0);//為了得知Translate要移動多少
                    //glTranslatef(2.07, -0.67 ,0);
                    //glRotatef(angle[4],0,1,0);
                    //glRotatef(angle2[4],1,0,0);///?
                    //glTranslatef( -2.07, 0.67, 0 );

                    if(ID==4) glColor3f(1,0,0);
                    else glColor3f(0.4,0.4,0.4); //grey
                    glmDraw(Lhand,GLM_MATERIAL);
                glPopMatrix();
            glPopMatrix();

            glPushMatrix(); ///Lleg
                //glTranslatef(teapotX,teapotY,0);///為了得知Translate要移動多少
                glTranslatef(0.293334 ,-1.939999 ,0);
                glRotatef(angle[5],0,1,0);
                glRotatef(angle2[5],1,0,0);///?
                glTranslatef(-0.233332 ,1.946666 ,0);
                glTranslatef(0.006667 ,-0.066668 ,0);

                if(ID==5)glColor3f(1,0,0);
                else glColor3f(1,1,0);
                glmDraw(Lleg,GLM_MATERIAL);
            glPopMatrix();

            glPushMatrix(); ///Right Arm hand ?
                 ///RArm
                    //glTranslatef(teapotX,teapotY,0);///為了得知Translate要移動多少
                    glTranslatef(-1.233332 ,-0.620001 ,0);
                    glRotatef(angle[6],0,1,0);
                    glRotatef(angle2[6],1,0,0);///?
                    glTranslatef(1.299999 ,0.633333 ,0);

                    if(ID==6)glColor3f(1,0,0);
                    else glColor3f(1,1,0);
                    glmDraw(Rarm,GLM_MATERIAL);

                glPushMatrix(); ///Rhand
                    //glTranslatef(teapotX,teapotY,0);//為了得知Translate要移動多少
                    glTranslatef(-2.093333 ,-0.606667 ,0);
                    glRotatef(angle[7],0,1,0);
                    glRotatef(angle2[7],1,0,0);///?
                    glTranslatef(2.166666 ,0.613333 ,0);

                    if(ID==7) glColor3f(1,0,0);
                    else glColor3f(0.4,0.4,0.4); //grey
                    glmDraw(Rhand,GLM_MATERIAL);
                glPopMatrix();
            glPopMatrix();

            glPushMatrix(); ///Rleg
                //glTranslatef(teapotX,teapotY,0);///為了得知Translate要移動多少
                glTranslatef(-0.226666 ,-1.959999 ,0);
                glRotatef(angle[8],0,1,0);
                glRotatef(angle2[8],1,0,0);///?
                glTranslatef(0.180000 ,1.939999 ,0);
                glTranslatef(0.060000 ,-0.073334 ,0);

                if(ID==8)glColor3f(1,0,0);
                else glColor3f(1,1,0);
                glmDraw(Rleg,GLM_MATERIAL);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glColor3f(0,1,0);
    glutSolidTeapot(0.02);///用來表示中心點
    glutSwapBuffers();
}


void mouse(int button,int state,int x,int y)
{
        oldX=x;
        oldY=y;
}

void motion(int x, int y) {
    teapotX += (x - oldX) / 150.0 * 10; ///teapotX = (x-150)/150.0;
    teapotY += (oldY - y) / 150.0 * 10; ///teapotY = (150-y)/150.0;
    angle[ID] += x - oldX;
    angle2[ID] += oldY - y;
    oldX = x;
    oldY = y;
    glutPostRedisplay();
    printf("  glTranslatef( %.2f, %.2f, 0 ); \n", teapotX, teapotY );
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("week16");

    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    body=glmReadOBJ("CGmodel/body.obj");
    Leye=glmReadOBJ("CGmodel/L_eyeball.obj");
    Reye=glmReadOBJ("CGmodel/R_eyeball.obj");
    Larm=glmReadOBJ("CGmodel/L_arm.obj");
    Lhand=glmReadOBJ("CGmodel/L_hand.obj");
    Lleg=glmReadOBJ("CGmodel/L_leg.obj");
    Rarm=glmReadOBJ("CGmodel/R_arm.obj");
    Rhand=glmReadOBJ("CGmodel/R_hand.obj");
    Rleg=glmReadOBJ("CGmodel/R_leg.obj");

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
