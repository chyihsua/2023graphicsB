#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"

GLMmodel * Lleg = NULL;
GLMmodel * Lhand = NULL;
GLMmodel * Larm = NULL;
GLMmodel * Rleg = NULL;
GLMmodel * Rhand = NULL;
GLMmodel * Rarm = NULL;
GLMmodel * eyeball = NULL;
GLMmodel * eyeout = NULL;
GLMmodel * body = NULL;
GLMmodel * head = NULL;
GLMmodel * pants = NULL;
GLMmodel * mouth = NULL;
GLMmodel * Reyeball = NULL;
GLMmodel * Leyeball = NULL;

float teapotX = 0, teapotY = 0, oldX = 0, oldY = 0;
float angle[20] = {}, angle2[20] = {};
float NewAngle[20] = {}, NewAngle2[20] = {};
float OldAngle[20] = {}, OldAngle2[20] = {};
int ID=0;
FILE * fout = NULL;
FILE * fin = NULL;

void timer(int t) {
    printf("現在timer(%d)\n", t);
    glutTimerFunc(20, timer, t+1);

    float alpha = (t%50) / 50.0;

    if(t%50==0){
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            OldAngle[i] = NewAngle[i];
            OldAngle2[i] = NewAngle2[i];
            fscanf(fin, "%f", &NewAngle[i] );
            fscanf(fin, "%f", &NewAngle2[i] );
        }
    }
    for(int i=0; i<20; i++){
        angle[i] = NewAngle[i] * alpha + OldAngle[i] * (1-alpha);
        angle2[i] = NewAngle2[i] * alpha + OldAngle2[i] * (1-alpha);
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if(key=='0') ID = 0;
    if(key=='1') ID = 1;
    if(key=='2') ID = 2;
    if(key=='3') ID = 3;
    if(key=='4') ID = 4;
    if(key=='5') ID = 5;
    if(key=='6') ID = 6;
    if(key=='7') ID = 7;
    if(key=='8') ID = 8;
    if(key=='9') ID = 9;
    if(key=='s'){
        if(fout == NULL) fout = fopen("motion.txt", "w");
        for(int i=0; i<20; i++){
            fprintf(fout, "%.2f ", angle[i] );
            fprintf(fout, "%.2f ", angle2[i] );
        }
        fprintf(fout, "\n");
        printf("寫了一行\n");
    }
    if(key=='r'){
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            fscanf(fin, "%f", &angle[i] );
            fscanf(fin, "%f", &angle2[i] );
        }
        glutPostRedisplay();
    }
    if(key=='p'){
        glutTimerFunc(0, timer, 0);
    }
}

void mouse(int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glRotatef(180, 0, 1, 0);   ///調整正面朝前
        glPushMatrix(); ///整個模型
            glRotatef(angle[0], 0, 1, 0);
            glPushMatrix(); ///靜態配件
                glColor3f(0,0,0);   ///黑眼球
                glmDraw(Leyeball,GLM_MATERIAL);

                glColor3f(0,0,0);   ///黑眼球
                glmDraw(Reyeball,GLM_MATERIAL);

                glColor3f(1,1,1);   ///眼白
                glmDraw(eyeball,GLM_MATERIAL);

                glColor3f(0.2,0.2,0.2); ///眼眶
                glmDraw(eyeout,GLM_MATERIAL);

                glColor3f(0,0,0);   /// 頭帶
                glmDraw(head,GLM_MATERIAL);

                glColor3f(1,1,1);   /// 嘴巴
                glmDraw(mouth,GLM_MATERIAL);

                glColor3f(0,0,1);   ///褲子
                glmDraw(pants,GLM_MATERIAL);

                glColor3f(1,1,0);   ///身體
                glmDraw(body, GLM_MATERIAL);
            glPopMatrix();

            glPushMatrix(); ///小小兵方向的右手
                //glTranslatef(teapotX, teapotY, 0);
                glTranslatef( -1.13, -0.60, 0 );
                glRotatef(angle[1], 0, 1, 0);
                glRotatef(angle2[1], 1, 0, 0);
                glTranslatef(  1.13, 0.60, 0 );///glTranslatef(teapotX, teapotY, 0);
                glmDraw(Rarm, GLM_MATERIAL);

                glPushMatrix();
                    //glTranslatef(teapotX, teapotY, 0);
                    glTranslatef(  -1.9, -0.60, 0 );
                    glRotatef(angle[2], 0, 1, 0);
                    glRotatef(angle2[2], 1, 0, 0);
                    glTranslatef(   1.9, 0.60, 0 );///glTranslatef(teapotX, teapotY, 0);
                    glColor3f(0,0,1);
                    glmDraw(Rhand, GLM_MATERIAL);
                glPopMatrix();
            glPopMatrix();

            glPushMatrix(); ///小小兵方向的左手
                //glTranslatef(teapotX, teapotY, 0);
                glTranslatef( 1.13, -0.60, 0 );
                glRotatef(angle[3], 0, 1, 0);
                glRotatef(angle2[3], 1, 0, 0);
                glTranslatef(  -1.13, 0.60, 0 );///glTranslatef(teapotX, teapotY, 0);
                glColor3f(1,1,0);
                glmDraw(Larm, GLM_MATERIAL);

                glPushMatrix();
                    //glTranslatef(teapotX, teapotY, 0);
                    glTranslatef(  2.13, -0.60, 0 );
                    glRotatef(angle[4], 0, 1, 0);
                    glRotatef(angle2[4], 1, 0, 0);
                    glTranslatef(   -2.13, 0.60, 0 );///glTranslatef(teapotX, teapotY, 0);
                    glColor3f(0,0,1);
                    glmDraw(Lhand, GLM_MATERIAL);
                glPopMatrix();
            glPopMatrix();

            glPushMatrix(); ///小小兵方向的右腳
                //glTranslatef(teapotX, teapotY, 0);
                glTranslatef( -0.40, -1.80, 0 );
                glRotatef(angle[5], 0, 1, 0);
                glRotatef(angle2[5], 1, 0, 0);
                glTranslatef(  0.40, 1.80, 0 );///glTranslatef(teapotX, teapotY, 0);
                glColor3f(0.3,0.3,0.3);
                glmDraw(Rleg, GLM_MATERIAL);
            glPopMatrix();

            glPushMatrix(); ///小小兵方向的左腳
                //glTranslatef(teapotX, teapotY, 0);
                glTranslatef( 0.40, -1.80, 0 );
                glRotatef(angle[6], 0, 1, 0);
                glRotatef(angle2[6], 1, 0, 0);
                glTranslatef(  -0.40, 1.80, 0 );///glTranslatef(teapotX, teapotY, 0);
                glmDraw(Lleg, GLM_MATERIAL);
            glPopMatrix();
        glPopMatrix();

        //glColor3f(0,1,0);
        //glutSolidTeapot( 0.02 );
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(400,400);
    glutCreateWindow("final Project");

    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    Lleg = glmReadOBJ("CGmodel/L_leg.obj");
    Lhand = glmReadOBJ("CGmodel/L_hand.obj");
    Larm = glmReadOBJ("CGmodel/L_arm.obj");
    Rleg = glmReadOBJ("CGmodel/R_leg.obj");
    Rhand = glmReadOBJ("CGmodel/R_hand.obj");
    Rarm = glmReadOBJ("CGmodel/R_arm.obj");
    eyeball = glmReadOBJ("CGmodel/eyeball.obj");
    eyeout = glmReadOBJ("CGmodel/eye_out.obj");
    body = glmReadOBJ("CGmodel/body.obj");
    head = glmReadOBJ("CGmodel/head_bl.obj");
    pants = glmReadOBJ("CGmodel/pants.obj");
    mouth = glmReadOBJ("CGmodel/mouth.obj");
    Reyeball = glmReadOBJ("CGmodel/R_eyeball.obj");
    Leyeball = glmReadOBJ("CGmodel/L_eyeball.obj");

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
