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

float teapotX = 0, teapotY = 0, oldX = 0, oldY = 0;
float angle[20] = {}, angle2[20] = {};///float angle = 0, angle2 = 0;
float NewAngle[20] = {}, NewAngle2[20] = {};
float OldAngle[20] = {}, OldAngle2[20] = {};
int ID = 0;
FILE * fout = NULL;
FILE * fin = NULL;

//int show[9]={1,1,1,1,1,1,1,1,1};
//int ID=9;
//float angle[20]={};

//float teapotX=0,teapotY=0;
//FILE * fout=NULL;
//FILE * fin=NULL;

void timer(int t) {
    printf("現在timer(%d)\n", t);
    glutTimerFunc(20, timer, t+1); ///馬上設定下一個鬧鐘

    float alpha = (t%50) / 50.0; ///0.0 ~ 1.0

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

void keyboard(unsigned char key,int x, int y)
{
    if(key=='0') ID = 0;
    if(key=='1') ID = 1;
    if(key=='2') ID = 2;
    if(key=='3') ID = 3;
    if(key=='4') ID = 4;
    if(key=='5') ID = 5;
    if(key=='6') ID = 6;
    if(key=='7') ID = 7;
    if(key=='8') ID = 8;
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
        glutTimerFunc(0, timer, 0);
    }
    glutPostRedisplay(); ///重畫畫面
}

int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glPushMatrix(); ///?
        glScalef(0.3,0.3,0.3);

        glPushMatrix();
            glColor3f(1,1,0);  //yellow
            glmDraw(body,GLM_MATERIAL);

            glPushMatrix(); ///Reye v ?
                //glTranslatef(teapotX,teapotY,0);
                glColor3f(0,0,0);
                glmDraw(Reye,GLM_MATERIAL);
            glPopMatrix();

            glPushMatrix(); ///Leye v ?
                //glTranslatef(teapotX,teapotY,0);///為了得知Translate要移動多少
                glTranslatef(-1.086666 ,0.593333 ,0);
                glRotatef(angle[2], 0, 1, 0);
                glRotatef(angle2[2], 1, 0, 0);
                glmDraw(Leye,GLM_MATERIAL);
            glPopMatrix();

            glPushMatrix(); ///Left Arm hand ?
                ///LArm
                //glTranslatef(teapotX,teapotY,0);///為了得知Translate要移動多少
                glTranslatef(1.143333 ,-0.640000 ,0);
                glRotatef(angle[3], 0, 1, 0);
                glRotatef(angle2[3], 1, 0, 0);
                glTranslatef(-1.143333 ,0.640000 ,0);
                glColor3f(1,1,0);
                glmDraw(Larm,GLM_MATERIAL);

                glPushMatrix(); ///Lhand
                    //glTranslatef(teapotX,teapotY,0);//為了得知Translate要移動多少
                    glTranslatef(2.17, -0.62 ,0);
                    glRotatef(angle[4], 0, 1, 0);
                    //glRotatef(angle2[4], 1, 0, 0);
                    glTranslatef( -2.17, 0.62 ,0);

                    glColor3f(0.4,0.4,0.4); //grey
                    glmDraw(Lhand,GLM_MATERIAL);
                    //glScalef(0.4,0.4,0.4);
                glPopMatrix();
            glPopMatrix();

            glPushMatrix(); ///Lleg
                //glTranslatef(teapotX,teapotY,0);///為了得知Translate要移動多少
                glTranslatef(0.493334 ,-1.866666 ,0);
                glRotatef(angle[5], 0, 1, 0);
                glRotatef(angle2[5], 1, 0, 0);
                glTranslatef(-0.346666 ,1.846665 ,0);
                glColor3f(1,1,0);
                glmDraw(Lleg,GLM_MATERIAL);
            glPopMatrix();

            glPushMatrix(); ///Right Arm hand ?
                ///RArm
                //glTranslatef(teapotX,teapotY,0);///為了得知Translate要移動多少
                glTranslatef(-1.0 ,-0.620001 ,0);
                glRotatef(angle[6], 0, 1, 0);
                glRotatef(angle2[6], 1, 0, 0);
                glTranslatef(1.299999 ,0.633333 ,0);
                glColor3f(1,1,0);
                glmDraw(Rarm,GLM_MATERIAL);

                glPushMatrix(); ///Rhand
                    //glTranslatef(teapotX,teapotY,0);//為了得知Translate要移動多少
                    glTranslatef(-2.1 ,-0.606667 ,0);
                    glRotatef(angle[7], 0, 1, 0);
                    glRotatef(angle2[7], 1, 0, 0);
                    glTranslatef(2.1 ,0.606667 ,0);
                    glColor3f(0.4,0.4,0.4); //grey
                    glmDraw(Rhand,GLM_MATERIAL);
                    glScalef(0.4,0.4,0.4);
                glPopMatrix();
            glPopMatrix();

            glPushMatrix(); ///Rleg
                //glTranslatef(teapotX,teapotY,0);///為了得知Translate要移動多少
                glTranslatef(-0.406668 ,-1.919999 ,0);
                glRotatef(angle[8], 0, 1, 0);
                glRotatef(angle2[8], 1, 0, 0);
                glTranslatef(0.413334 ,1.886665 ,0);
                glColor3f(1,1,0);
                glmDraw(Rleg,GLM_MATERIAL);
            glPopMatrix();
            glColor3f(0,1,0);
        glutSolidTeapot(0.02);///用來表示中心點
        glPopMatrix();
    glPopMatrix();

    glColor3f(0,1,0);
    glutSolidTeapot(0.02);///用來表示中心點
    glutSwapBuffers();
}

//int oldX=0,oldY=0;

void mouse(int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
}
void motion(int x, int y) {
    teapotX += (x - oldX) / 150.0 ; ///teapotX = (x-150)/150.0;
    teapotY += (oldY - y) / 150.0 ; ///teapotY = (150-y)/150.0;
    angle[ID] += x - oldX;
    angle2[ID] += oldY - y;
    oldX = x;
    oldY = y;
    glutPostRedisplay();
    printf("  glTranslatef( %.2f, %.2f, 0 ); \n", teapotX, teapotY );
}

int main(int argc,char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(300,300);
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
